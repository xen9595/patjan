
#include"sched.h"
#include"video.h"
#define MAX_TASKS 16
typedef struct { int used; int prio; task_fn fn; void* arg; } task_t;
static task_t tasks[MAX_TASKS];
static int rr = 0;
void scheduler_init(void){ for(int i=0;i<MAX_TASKS;i++) tasks[i].used=0; }
int task_create(const char* name, int prio, task_fn fn, void* arg){
    (void)name; (void)prio;
    for(int i=0;i<MAX_TASKS;i++) if(!tasks[i].used){ tasks[i].used=1; tasks[i].fn=fn; tasks[i].arg=arg; return i; }
    return -1;
}
void scheduler_run_once(void){
    for(int n=0;n<MAX_TASKS;n++){
        rr = (rr+1)%MAX_TASKS;
        if(tasks[rr].used && tasks[rr].fn){ tasks[rr].fn(tasks[rr].arg); break; }
    }
}
