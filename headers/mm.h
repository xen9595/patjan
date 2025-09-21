
#ifndef MM_H
#define MM_H
#include"types.h"
void mm_init(void);
void* kmalloc(uint32_t size);
void kfree(void* p);
#endif
