#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <new>
#include <random>

constexpr int BUF_SIZE   = 8;
constexpr int COUNT      = 50;
constexpr int STOP_VALUE = -1;
constexpr const char* OUT_FILE = "output.txt";

struct Channel {
    sem_t* empty;   
    sem_t* full;    
    int    buf[BUF_SIZE];
    int    head;
    int    tail;
};

struct Shared {
    Channel ch[2];
};

static void sem_wait_retry(sem_t* s) {
    while (sem_wait(s) == -1) {
        if (errno != EINTR) {
            perror("sem_wait");
            _exit(1);
        }
    }
}


static sem_t* make_sem(const char* tag, int idx, unsigned value) {
    char name[32];  
    std::snprintf(name, sizeof(name), "/p_%s%d_%d", tag, idx, getpid());
    sem_unlink(name);  
    sem_t* s = sem_open(name, O_CREAT | O_EXCL, 0600, value);
    if (s == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }
    sem_unlink(name);  
    return s;
}

static void channel_init(Channel& c, int idx) {
    c.empty = make_sem("e", idx, BUF_SIZE);
    c.full  = make_sem("f", idx, 0);
    c.head = c.tail = 0;
}

static void channel_put(Channel& c, int value) {
    sem_wait_retry(c.empty);
    c.buf[c.tail] = value;
    c.tail = (c.tail + 1) % BUF_SIZE;
    sem_post(c.full);
}

static int channel_get(Channel& c) {
    sem_wait_retry(c.full);
    int value = c.buf[c.head];
    c.head = (c.head + 1) % BUF_SIZE;
    sem_post(c.empty);
    return value;
}

static void run_console_consumer(Channel& c) {
    for (;;) {
        int v = channel_get(c);
        if (v == STOP_VALUE) break;
        std::printf("[p1] %d\n", v);
        std::fflush(stdout);
    }
}

static void run_file_consumer(Channel& c) {
    FILE* f = std::fopen(OUT_FILE, "w");
    if (!f) {
        perror("fopen");
    }
    for (;;) {
        int v = channel_get(c);
        if (v == STOP_VALUE) break;
        if (f) std::fprintf(f, "%d\n", v);
    }
    if (f) std::fclose(f);
}

int main() {
    char name[64];
    std::snprintf(name, sizeof(name), "/p_shm_%d", getpid());

    int fd = shm_open(name, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (fd == -1) { perror("shm_open"); return 1; }
    if (ftruncate(fd, sizeof(Shared)) == -1) { perror("ftruncate"); return 1; }

    void* mem = mmap(nullptr, sizeof(Shared), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mem == MAP_FAILED) { perror("mmap"); return 1; }
    close(fd);
    shm_unlink(name);

    Shared* sh = new (mem) Shared;
    channel_init(sh->ch[0], 0);
    channel_init(sh->ch[1], 1);

    pid_t p1 = fork();
    if (p1 == -1) { perror("fork p1"); return 1; }
    if (p1 == 0) {
        run_console_consumer(sh->ch[0]);
        _exit(0);
    }

    pid_t p2 = fork();
    if (p2 == -1) { perror("fork p2"); return 1; }
    if (p2 == 0) {
        run_file_consumer(sh->ch[1]);
        _exit(0);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 999);

    for (int i = 0; i < COUNT; ++i) {
        int x = dist(gen);
        channel_put(sh->ch[0], x);
        channel_put(sh->ch[1], x);
    }
    channel_put(sh->ch[0], STOP_VALUE);
    channel_put(sh->ch[1], STOP_VALUE);

    waitpid(p1, nullptr, 0);
    waitpid(p2, nullptr, 0);

    for (auto& c : sh->ch) {
        sem_close(c.empty);
        sem_close(c.full);
    }
    munmap(mem, sizeof(Shared));
    return 0;
}


