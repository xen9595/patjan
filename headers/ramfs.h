
#ifndef RAMFS_H
#define RAMFS_H
#include"types.h"
int ramfs_init(void);
int ramfs_mkdir(int parent, const char* name);
int ramfs_create(int parent, const char* name, const void* data, uint32_t len);
int ramfs_find(int parent, const char* name);
int ramfs_read(int id, void* buf, uint32_t maxlen);
void ramfs_list(int parent);
#endif
