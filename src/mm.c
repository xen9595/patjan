#include"mm.h"
static unsigned char *heap = (unsigned char*)0x01000000; // 16 MiB
static unsigned int brk = 0;
void mm_init(void){ brk = 0; }
void* kmalloc(uint32_t size){
    if(size==0) return (void*)0;
    size = (size + 7u) & ~7u;
    void* p = (void*)(heap + brk);
    brk += size;
    return p;
}
void kfree(void* p){ (void)p; /* bump allocator: brak free */ }
