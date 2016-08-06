#ifndef _IRQ_H_
#define _IRQ_H_ 1

#include "port.h"
#include "stdio.h"
#include "serial.h"
#include "timer.h"
#include "stdlib.h"
	/* The state of the CPU when an interrupt is triggered. */
struct regs {
     uint32_t ds; /* pushed the segs last */
     uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /* pushed by 'pusha' */
     uint32_t int_no, err_code; /* our 'push byte #' and ecodes do this */
     uint32_t eip, cs, eflags, useresp, ss; /* pushed by the processor automatically */
};


class IRQ
{

public:
	IRQ();
	~IRQ();
	void install_irqs();
private:
	void irq_remap();
};
	void install_handler_irq(int irq, void (*handler)(struct regs *r));	
	void uninstall_handler_irq(int irq);	

#endif