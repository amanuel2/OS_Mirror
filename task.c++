#include "task.h"



static task_q *runningTask;
static task_q mainTask;
static task_q otherTask;
static PhyiscalMemoryManager *pmm_task;
static 	Heap *heap_task;



extern void switch_task_a();

TaskManager::TaskManager(Heap *heap)
{
 heap_task = heap;
}
TaskManager::~TaskManager()
{}

Task::Task()
{}

Task::~Task()
{}
void TaskManager::otherMain()
{
	    printf("Hello multitasking world!"); // Not implemented here...
	    preempt();
}


void TaskManager::createTask(task_q* task, void(*task_main)(), uint32_t flags, uint32_t* pageDir)
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

void TaskManager::init_tasking()
{
	 // Get EFLAGS and CR3
	    __asm __volatile("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(mainTask.regs.cr3)::"%eax");
	    __asm __volatile("pushfl; movl (%%esp), %%eax; movl %%eax, %0; popfl;":"=m"(mainTask.regs.eflags)::"%eax");

	    this->createTask(&otherTask, this->otherMain, mainTask.regs.eflags, (uint32_t*)mainTask.regs.cr3);
	    mainTask.next = &otherTask;
	    otherTask.next = &mainTask;

	    runningTask = &mainTask;
}

void TaskManager::switchTask(Registers *old, Registers *new_)
{
	switch_task_a();
}

void TaskManager::preempt()
{
	task_q *last = runningTask;
	runningTask = runningTask->next;
    switchTask(&last->regs, &runningTask->regs);
}
