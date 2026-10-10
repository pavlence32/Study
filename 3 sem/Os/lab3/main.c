#include <stdio.h>
#include "mmemory.h"

int main(void)
{
    if (_init(16, 64) != MM_OK) { puts("init failed"); return 1; }
    mm_config(4, 2);

    VA p;
    if (_malloc(&p, 500) != MM_OK) { puts("malloc failed"); return 1; }

    char msg[] = "Hello, paged memory!";
    _write(p + 100, msg, sizeof msg);

    char out[sizeof msg];
    _read(p + 100, out, sizeof out);
    printf("read: %s\n", out);

    char c;
    for (size_t i = 0; i < 500; i += 64) _read(p + i, &c, 1);

    mm_stats s;
    mm_get_stats(&s);
    printf("accesses=%lu faults=%lu disk_reads=%lu disk_writes=%lu prefetched=%lu\n",
           s.accesses, s.page_faults, s.disk_reads, s.disk_writes, s.prefetched);

    _free(p);
    mm_destroy();
    return 0;
}
