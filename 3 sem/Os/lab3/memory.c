#include "mmemory.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define VBASE ((uintptr_t)0x100000)   

typedef struct Block {
    size_t start, size;               
    struct Block* next;
} Block;

typedef struct {
    int present, dirty, frame;
    unsigned long long last_use;      
} PageEntry;

static int n_pages, page_sz, n_frames, pref_k;
static PageEntry* ptable;
static int* frame_page;               
static char* ram;                     
static char* disk;                    
static Block* blocks;                 /* занятые блоки, отсортированы по start */
static unsigned long long clk;
static mm_stats st;
static int inited;

void mm_destroy(void)
{
    while (blocks) { Block* t = blocks; blocks = blocks->next; free(t); }
    free(ptable); free(frame_page); free(ram); free(disk);
    ptable = NULL; frame_page = NULL; ram = NULL; disk = NULL;
    inited = 0; clk = 0;
    memset(&st, 0, sizeof st);
}

static int alloc_state(int frames)
{
    free(ptable); free(frame_page); free(ram);
    ptable = calloc((size_t)n_pages, sizeof(PageEntry));
    frame_page = malloc((size_t)frames * sizeof(int));
    ram = calloc((size_t)frames, (size_t)page_sz);
    if (!ptable || !frame_page || !ram) return MM_ERR_NOMEM;
    for (int i = 0; i < frames; i++) frame_page[i] = -1;
    n_frames = frames;
    return MM_OK;
}

int _init(int n, int szPage)
{
    if (n <= 0 || szPage <= 0) return MM_ERR_PARAM;
    mm_destroy();
    n_pages = n; page_sz = szPage; pref_k = 0;
    disk = calloc((size_t)n, (size_t)szPage);
    if (!disk) return MM_ERR_NOMEM;
    int frames = n / 2 > 0 ? n / 2 : 1;
    if (alloc_state(frames) != MM_OK) { mm_destroy(); return MM_ERR_NOMEM; }
    inited = 1;
    return MM_OK;
}

int mm_config(int frames, int k)
{
    if (!inited || frames <= 0 || frames > n_pages || k < 0 || k > frames - 1)
        return MM_ERR_PARAM;
    if (alloc_state(frames) != MM_OK) return MM_ERR_NOMEM;
    
    pref_k = k;
    return MM_OK;
}

void mm_get_stats(mm_stats* s) { if (s) *s = st; }
void mm_reset_stats(void) { memset(&st, 0, sizeof st); }


static int get_frame(int lo, int hi)
{
    int victim = -1;
    for (int f = 0; f < n_frames; f++) {
        if (frame_page[f] < 0) return f;
        int p = frame_page[f];
        if (p >= lo && p <= hi) continue;
        if (victim < 0 || ptable[p].last_use < ptable[frame_page[victim]].last_use)
            victim = f;
    }
    if (victim < 0) return -1;
    int vp = frame_page[victim];
    if (ptable[vp].dirty) {
        memcpy(disk + (size_t)vp * page_sz, ram + (size_t)victim * page_sz, (size_t)page_sz);
        st.disk_writes++;
    }
    ptable[vp].present = ptable[vp].dirty = 0;
    ptable[vp].frame = -1;
    frame_page[victim] = -1;
    return victim;
}

static int load_page(int p, int lo, int hi)
{
    int f = get_frame(lo, hi);
    if (f < 0) return -1;
    memcpy(ram + (size_t)f * page_sz, disk + (size_t)p * page_sz, (size_t)page_sz);
    st.disk_reads++;
    ptable[p].present = 1; ptable[p].dirty = 0;
    ptable[p].frame = f; ptable[p].last_use = ++clk;
    frame_page[f] = p;
    return f;
}


static int touch(int p)
{
    st.accesses++;
    if (ptable[p].present) { ptable[p].last_use = ++clk; return ptable[p].frame; }

    st.page_faults++;
    int hi = p + pref_k < n_pages ? p + pref_k : n_pages - 1;
    int f = load_page(p, p, hi);
    if (f < 0) return -1;
    for (int q = p + 1; q <= hi; q++) {
        if (ptable[q].present) continue;
        if (load_page(q, p, hi) < 0) break;
        st.prefetched++;
    }
    return f;
}


int _malloc(VA* ptr, size_t szBlock)
{
    if (!inited || !ptr || szBlock == 0) return MM_ERR_PARAM;
    size_t total = (size_t)n_pages * (size_t)page_sz;
    if (szBlock > total) return MM_ERR_NOMEM;

    Block *prev = NULL, *cur = blocks;
    size_t pos = 0;
    while (cur) {
        if (cur->start - pos >= szBlock) break;
        pos = cur->start + cur->size;
        prev = cur; cur = cur->next;
    }
    if (!cur && total - pos < szBlock) return MM_ERR_NOMEM;

    Block* b = malloc(sizeof(Block));
    if (!b) return MM_ERR_NOMEM;
    b->start = pos; b->size = szBlock; b->next = cur;
    if (prev) prev->next = b; else blocks = b;
    *ptr = (VA)(VBASE + pos);
    return MM_OK;
}

int _free(VA ptr)
{
    if (!inited) return MM_ERR_PARAM;
    uintptr_t a = (uintptr_t)ptr;
    if (a < VBASE) return MM_ERR_PARAM;
    size_t off = a - VBASE;
    Block *prev = NULL, *cur = blocks;
    while (cur && cur->start != off) { prev = cur; cur = cur->next; }
    if (!cur) return MM_ERR_PARAM;
    if (prev) prev->next = cur->next; else blocks = cur->next;
    free(cur);
    return MM_OK;
}


static int in_block(size_t off, size_t len)
{
    for (Block* b = blocks; b; b = b->next)
        if (off >= b->start && off - b->start <= b->size && len <= b->size - (off - b->start))
            return 1;
    return 0;
}

static int rw(VA ptr, void* buf, size_t len, int write)
{
    if (!inited || !buf || len == 0) return MM_ERR_PARAM;
    uintptr_t a = (uintptr_t)ptr;
    if (a < VBASE) return MM_ERR_PARAM;
    size_t off = a - VBASE;
    if (!in_block(off, len)) return MM_ERR_PARAM;

    char* b = (char*)buf;
    while (len > 0) {
        int p = (int)(off / (size_t)page_sz);
        size_t in_page = off % (size_t)page_sz;
        size_t chunk = (size_t)page_sz - in_page;
        if (chunk > len) chunk = len;

        int f = touch(p);
        if (f < 0) return MM_ERR_UNKNOWN;
        char* frame_addr = ram + (size_t)f * page_sz + in_page;
        if (write) { memcpy(frame_addr, b, chunk); ptable[p].dirty = 1; }
        else         memcpy(b, frame_addr, chunk);

        b += chunk; off += chunk; len -= chunk;
    }
    return MM_OK;
}

int _read(VA ptr, void* pBuffer, size_t szBuffer)  { return rw(ptr, pBuffer, szBuffer, 0); }
int _write(VA ptr, void* pBuffer, size_t szBuffer) { return rw(ptr, pBuffer, szBuffer, 1); }