
#ifndef SCHED_H
#define SCHED_H
#include"types.h"
typedef void (*task_fn)(void*);
int task_create(const char* name, int prio, task_fn fn, void* arg);
void scheduler_init(void);
void scheduler_run_once(void);   // wywołuj w pętli głównej (kooperacyjnie)
#endif
