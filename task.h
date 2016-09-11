#ifndef _TASK_H_
#define _TASK_H_ 1

#include <stdarg.h>
#include <stdint.h>
#include "gdt.h"
#include "stdio.h"
#include "heap.h"
#include "pmm.h"

#define TASK_STACK_SIZE 0x2000

extern void init_tasking(Heap *heap_task);
extern void doIt();

#endif
