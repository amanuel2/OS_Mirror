#ifndef _IDT_H_
#define _IDT_H_ 1

#include <stddef.h>
#include <stdint.h>

#include "stdio.h"
#include "mem.h"

#define IDT_SIZE 256



class IDT
{

		public: 

			/* Initialize the <idt> and the 8259 Programmable Interrupt Controller.
			 * There are actually two PICs, a master and a slave. Each is controlled via a
			 * dedicated I/O port. We remap interrupts so that we can catch CPU exceptions.
			 * Interrupts 0 through 31 are CPU exceptions and currently get sent to the
			 * <common_interrupt_handler>. Interrupt 32 is used by the programmable timer
			 * which dispatches the <timer_handler>. Interrupt 33 is used by the keyboard,
			 * and dispatches the <keyboard_handler>.
			 */
			IDT();
			~IDT();
};


#endif