#ifndef _TASK_H_
#define _TASK_H_ 1

#include <stdarg.h>
#include <stdint.h>
#include "gdt.h"
#include "stdio.h"
#include "heap.h"
#include "pmm.h"

#define TASK_STACK_SIZE 0x2000

typedef struct {
	    uint32_t eax, ebx, ecx, edx, esi, edi,
				 esp, ebp, eip, eflags, cr3;
} Registers;

typedef struct task_q {
		    Registers regs;
		    struct task_q *next;
} task_q;

class Task
{
	friend class TaskManager;
public:
	Task();
	~Task();
private:
};

class TaskManager
{
public:
	TaskManager(Heap *heap);
	~TaskManager();
	void init_tasking();
	static void createTask(task_q* task, void(*task_main)(), uint32_t flags, uint32_t* pageDir);
	void preempt();
private:
	void switchTask(Registers *old, Registers *new_);
	void otherMain();
};

#endif
