#ifndef _IDT_H_
#define _IDT_H_ 1

#include <stddef.h>
#include <stdint.h>

#include "port.h"
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
		private:
			// Interrupt Service Routine function signature.
			// ISRs with this signature are installed to a dispatch table.
			typedef void (*isr_t)(struct regs*);	
			/* Install an interrupt handler.
			 * The handler will have the interrupt number @num, and when triggered it will
			 * execute @function. If @privileged is set to false, the interrupt will be
			 * able to be raised by ring 3 code. If false, it will only be able to be
			 * raised by ring 0 code. @return 0 if the interrupt is successfully installed
			 * and -1 if that interrupt number has already been registered.
			 */
			//int install_interrupt(uint8_t num, isr_t function);

			PORT::Port8Bits p8b;

};


#endif