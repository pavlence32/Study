#ifndef MMEMORY_H
#define MMEMORY_H

#include <stddef.h>


typedef char* VA;


#define MM_OK           0
#define MM_ERR_PARAM   -1   
#define MM_ERR_NOMEM   -2   
#define MM_ERR_UNKNOWN  1   


int _malloc(VA* ptr, size_t szBlock);
int _free(VA ptr);
int _read(VA ptr, void* pBuffer, size_t szBuffer);
int _write(VA ptr, void* pBuffer, size_t szBuffer);

int _init(int n, int szPage);


int mm_config(int frames, int prefetch_k);

typedef struct {
    unsigned long accesses;      
    unsigned long page_faults;   
    unsigned long disk_reads;    
    unsigned long disk_writes;  
    unsigned long prefetched;    
} mm_stats;

void mm_get_stats(mm_stats* s);
void mm_reset_stats(void);
void mm_destroy(void);

#endif