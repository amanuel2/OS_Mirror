#include "irq.h"

#define PIC_MASTER_CONTROL 0x20
#define PIC_MASTER_MASK 0x21
#define PIC_SLAVE_CONTROL 0xa0
#define PIC_SLAVE_MASK 0xa1



/*Get all irq's*/
extern "C" void irq0(void);
extern "C" void irq1(void);
extern "C" void irq2(void);
extern "C" void irq3(void);
extern "C" void irq4(void);
extern "C" void irq5(void);
extern "C" void irq6(void);
extern "C" void irq7(void);
extern "C" void irq8(void);
extern "C" void irq9(void);
extern "C" void irq10(void);
extern "C" void irq11(void);
extern "C" void irq12(void);
extern "C" void irq13(void);
extern "C" void irq14(void);
extern "C" void irq15(void);

void* irq_routines[16] = {
	0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
	0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
	0
};

static inline void idt_set_gate(uint8_t num, void(*handler)(void), uint16_t sel,
        	  uint8_t flags) 
{
    idt[num].base_lo = (uintptr_t)handler >> 0 & 0xFFFF;
    idt[num].base_hi = (uintptr_t)handler >> 16 & 0xffff;
    idt[num].always0 = 0;
    idt[num].sel = sel;
    idt[num].flags = flags;
}

IRQ::IRQ(){}; 
IRQ::~IRQ(){};

void IRQ::install_handler_irq(int irq, (*handler)(struct regs *r))
{
	irq_routines[irq] = handler;
}

void IRQ::uninstall_handler_irq(int irq)
{
	irq_routines[irq] = 0;
}


/* Normally, IRQs 0 to 7 are mapped to entries 8 to 15. This
*  is a problem in protected mode, because IDT entry 8 is a
*  Double Fault! Without remapping, every time IRQ0 fires,
*  you get a Double Fault Exception, which is NOT actually
*  what's happening. We send commands to the Programmable
*  Interrupt Controller (PICs - also called the 8259's) in
*  order to make IRQ0 to 15 be remapped to IDT entries 32 to
*  47 */
void IRQ::remap()
{
	    // ICW1 - begin initialization
    p8b.out(0x11,PIC_MASTER_CONTROL);
    p8b.out(0x11,PIC_SLAVE_CONTROL);

    // Remap interrupts beyond 0x20 because the first 32 are cpu exceptions
    p8b.out(0x21,PIC_MASTER_MASK);
    p8b.out(0x28,PIC_SLAVE_MASK);

    // ICW3 - setup cascading
    p8b.out(0x00,PIC_MASTER_MASK);
    p8b.out(0x00,PIC_SLAVE_MASK);

    // ICW4 - environment info
    p8b.out(0x01,PIC_MASTER_MASK);
    p8b.out(0x01,PIC_SLAVE_MASK);

    // mask interrupts
    p8b.out(0xff,PIC_MASTER_MASK);
    p8b.out(0xff,PIC_SLAVE_MASK);
}

/* First remap the interrupt controllers, and then we install
*  the appropriate ISRs to the correct entries in the IDT. This
*  is just like installing the exception handlers */

void IRQ::install_irqs()
{
	this->irq_remap();
    idt_set_gate(32, (unsigned)irq0, 0x08, 0x8E);
    idt_set_gate(33, (unsigned)irq1, 0x08, 0x8E);
    idt_set_gate(34, (unsigned)irq2, 0x08, 0x8E);
    idt_set_gate(35, (unsigned)irq3, 0x08, 0x8E);
    idt_set_gate(36, (unsigned)irq4, 0x08, 0x8E);
    idt_set_gate(37, (unsigned)irq5, 0x08, 0x8E);
    idt_set_gate(38, (unsigned)irq6, 0x08, 0x8E);
    idt_set_gate(39, (unsigned)irq7, 0x08, 0x8E);
    idt_set_gate(40, (unsigned)irq8, 0x08, 0x8E);
    idt_set_gate(41, (unsigned)irq9, 0x08, 0x8E);
    idt_set_gate(42, (unsigned)irq10, 0x08, 0x8E);
    idt_set_gate(43, (unsigned)irq11, 0x08, 0x8E);
    idt_set_gate(44, (unsigned)irq12, 0x08, 0x8E);
    idt_set_gate(45, (unsigned)irq13, 0x08, 0x8E);
    idt_set_gate(46, (unsigned)irq14, 0x08, 0x8E);    
    idt_set_gate(47, (unsigned)irq15, 0x08, 0x8E);
}

/* Each of the IRQ ISRs point to this function, rather than
*  the 'fault_handler' in 'isrs.c'. The IRQ Controllers need
*  to be told when you are done servicing them, so you need
*  to send them an "End of Interrupt" command (0x20). There
*  are two 8259 chips: The first exists at 0x20, the second
*  exists at 0xA0. If the second controller (an IRQ from 8 to
*  15) gets an interrupt, you need to acknowledge the
*  interrupt at BOTH controllers, otherwise, you only send
*  an EOI command to the first controller. If you don't send
*  an EOI, you won't raise any more IRQs */
extern "C" void irq_handler(struct regs *r)
{
    /* This is a blank function pointer */
    void (*handler)(struct regs *r);

    /* Find out if we have a custom handler to run for this
    *  IRQ, and then finally, run it */
    handler = irq_routines[r->int_no - 32];
    if (handler)
    {
        handler(r);
    }

    /* If the IDT entry that was invoked was greater than 40
    *  (meaning IRQ8 - 15), then we need to send an EOI to
    *  the slave controller */
    if (r->int_no >= 40)
    {
        p8b.out(PIC_MASTER_CONTROL,PIC_SLAVE_CONTROL);
    }

    /* In either case, we need to send an EOI to the master
    *  interrupt controller too */
    p8b.out(PIC_MASTER_CONTROL, PIC_MASTER_CONTROL);
}
	