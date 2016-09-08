#ifndef _TASK_H_
#define _TASK_H_ 1

#include <stdarg.h>
#include <stdint.h>
#include "gdt.h"

struct CPUState
{
   uint32_t eax;
   uint32_t ebx;
   uint32_t ecx;
   uint32_t edx;

   uint32_t esi;
   uint32_t edi;
   uint32_t ebp;

   /*
	uint32_t gs;
	uint32_t fs;
    uint32_t es;
    uint32_t ds;
    */
    uint32_t error;

    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t esp;
    uint32_t ss;
} __attribute__((packed));


class Task
{
  friend class TaskManager;
  	  private:
  	  	  uint8_t stack[4096]; // 4 KiB
  	  	  CPUState* cpustate;
  	  public:
  	  	  Task(gdt *GlobalDescriptorTable, void entrypoint());
  	  	  ~Task();
};


class TaskManager
{
    	private:
        	Task* tasks[256];
        	uint32_t num_task;
        	uint32_t current_task;
    	public:
        	TaskManager();
        	~TaskManager();
        	bool AddTask(Task* task);
        	CPUState* Schedule(CPUState* cpustate);
};

#endif
