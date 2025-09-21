
#include"ramfs.h"
#include"video.h"
#include"types.h"
#define NODES 128
#define NAME  32
typedef enum { N_DIR, N_FILE } kind_t;
typedef struct { int id; kind_t k; int parent; char name[NAME]; uint32_t off,len; } node_t;
static node_t nodes[NODES];
static unsigned char data[1<<16];
static uint32_t brk=0;
static int root=0;
int ramfs_init(void){
    for(int i=0;i<NODES;i++) nodes[i].id=-1;
    nodes[0].id=0; nodes[0].k=N_DIR; nodes[0].parent=-1; nodes[0].name[0]='/'; nodes[0].name[1]=0;
    root=0; brk=0; return 0;
}
static int newnode(kind_t k,int parent,const char*name){
    for(int i=1;i<NODES;i++) if(nodes[i].id==-1){ nodes[i].id=i; nodes[i].k=k; nodes[i].parent=parent;
        int j=0; while(name[j] && j<NAME-1){ nodes[i].name[j]=name[j]; j++; } nodes[i].name[j]=0; return i; }
    return -1;
}
int ramfs_mkdir(int parent, const char* name){ return newnode(N_DIR,parent,name); }
int ramfs_create(int parent,const char*name,const void*buf,uint32_t len){
    if(len > sizeof(data)-brk) return -1;
    int id=newnode(N_FILE,parent,name); if(id<0) return -1;
    nodes[id].off=brk; nodes[id].len=len;
    for(uint32_t i=0;i<len;i++) data[brk+i]=((const unsigned char*)buf)[i];
    brk+=len; return id;
}
int ramfs_find(int parent,const char*name){
    for(int i=0;i<NODES;i++) if(nodes[i].id!=-1 && nodes[i].parent==parent){
        int j=0; for(; j<NAME && name[j] && nodes[i].name[j]==name[j]; j++);
        if(name[j]==0 && nodes[i].name[j]==0) return i;
    }
    return -1;
}
int ramfs_read(int id, void*buf, uint32_t maxlen){
    if(id<0 || nodes[id].id==-1 || nodes[id].k!=N_FILE) return -1;
    uint32_t n = nodes[id].len < maxlen ? nodes[id].len : maxlen;
    for(uint32_t i=0;i<n;i++) ((unsigned char*)buf)[i]=data[nodes[id].off+i];
    return (int)n;
}
void ramfs_list(int parent){
    print_string("FS listing:\\n");
    for(int i=0;i<NODES;i++) if(nodes[i].id!=-1 && nodes[i].parent==parent){
        print_string(nodes[i].name); print_string("\\n"); }
}
