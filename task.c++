#include "task.h"



void preempt();

typedef struct {
	    uint32_t eax, ebx, ecx, edx, esi, edi,
				 esp, ebp, eip, eflags, cr3;
} Registers;

typedef struct task_q {
		    Registers regs;
		    struct task_q *next;
} task_q;


static task_q *runningTask;
static task_q mainTask;
static task_q otherTask;


extern "C" void switch_task_a(Registers *old, Registers *new_);


void otherMain()
{
	    printf("Hello multitasking world!"); // Not implemented here...
	    preempt();
}

void doIt() {
    printf("\nSwitching to otherTask... \n");
	    preempt();
	    printf("\nReturned to mainTask!\n");
}


void createTask(task_q* task, void(*task_main)(), uint32_t flags, uint32_t* pageDir, Heap *heap_task)
{
	    task->regs.ebx = 0;
	    task->regs.ecx = 0;
	    task->regs.edx = 0;
	    task->regs.esi = 0;
	    task->regs.edi = 0;
	    task->regs.eflags = flags;
	    task->regs.eip = (uint32_t) task_main;
	    task->regs.cr3 = (uint32_t) pageDir;
	    task->regs.esp = (uint32_t) (heap_task->k_malloc(TASK_STACK_SIZE)) + 0x1000; // Not implemented here
	    task->next = 0;
}

void init_tasking(Heap *heap_task)
{
	 // Get EFLAGS and CR3
	    __asm __volatile("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(mainTask.regs.cr3)::"%eax");
	    __asm __volatile("pushfl; movl (%%esp), %%eax; movl %%eax, %0; popfl;":"=m"(mainTask.regs.eflags)::"%eax");

	    createTask(&otherTask, otherMain, mainTask.regs.eflags, (uint32_t*)mainTask.regs.cr3,heap_task);
	    mainTask.next = &otherTask;
	    otherTask.next = &mainTask;

	    runningTask = &mainTask;
}

void switchTask(Registers *old, Registers *new_)
{
	switch_task_a(old,new_);
}

void preempt()
{
	task_q *last = runningTask;
	runningTask = runningTask->next;
    switchTask(&last->regs, &runningTask->regs);
}
