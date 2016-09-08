#include "task.h"

Task::Task(gdt *GlobalDescriptorTable, void entrypoint())
{
    cpustate = (CPUState*)(stack + 4096 - sizeof(CPUState));

    cpustate -> eax = 0;
    cpustate -> ebx = 0;
    cpustate -> ecx = 0;
    cpustate -> edx = 0;

    cpustate -> esi = 0;
    cpustate -> edi = 0;
    cpustate -> ebp = 0;

    /*
    cpustate -> gs = 0;
    cpustate -> fs = 0;
    cpustate -> es = 0;
    cpustate -> ds = 0;
    */

    // cpustate -> error = 0;

    // cpustate -> esp = ;
    cpustate -> eip = (uint32_t)entrypoint;
    cpustate -> cs = GlobalDescriptorTable->CodeSegmentSelector();
    // cpustate -> ss = ;
    cpustate -> eflags = 0x202;

}

Task::~Task()
{
}


TaskManager::TaskManager()
{
    num_task = 0;
    current_task = -1;
}

TaskManager::~TaskManager()
{
}

bool TaskManager::AddTask(Task* task)
{
    if(num_task >= 256)
        return false;
    tasks[num_task++] = task;
    return true;
}

CPUState* TaskManager::Schedule(CPUState* cpustate)
{
    if(num_task <= 0)
        return cpustate;

    if(current_task >= 0)
        tasks[current_task]->cpustate = cpustate;

    if(++current_task >= num_task)
    	current_task %= num_task;
    return tasks[current_task]->cpustate;
}

