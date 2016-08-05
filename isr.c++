
#include "isr.h"

ISR::ISR(){}

ISR::~ISR(){}


/* The state of the CPU when an interrupt is triggered. */
struct regs {
     uint32_t ds; /* pushed the segs last */
     uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /* pushed by 'pusha' */
     uint32_t int_no, err_code; /* our 'push byte #' and ecodes do this */
     uint32_t eip, cs, eflags, useresp, ss; /* pushed by the processor automatically */
};

//Basically a declaration of IDT_ENTRY in 
//idt.c++
struct idt_entry {
    uint16_t base_lo;
    uint16_t sel; // Kernel segment goes here.
    uint8_t always0;
    uint8_t flags; // Set using the table.
    uint16_t base_hi;
}__attribute__((packed));

//Get the Exact IDT array from idt.c++
extern struct idt_entry idt[256];

extern void panic(const char* exception);

//Extern the ISR Handlers
extern "C" void isr0(void);
extern "C" void isr1(void);
extern "C" void isr2(void);
extern "C" void isr3(void);
extern "C" void isr4(void);
extern "C" void isr5(void);
extern "C" void isr6(void);
extern "C" void isr7(void);
extern "C" void isr8(void);
extern "C" void isr9(void);
extern "C" void isr10(void);
extern "C" void isr11(void);
extern "C" void isr12(void);
extern "C" void isr13(void);
extern "C" void isr14(void);
extern "C" void isr15(void);
extern "C" void isr16(void);
extern "C" void isr17(void);
extern "C" void isr18(void);
extern "C" void isr19(void);
extern "C" void isr20(void);
extern "C" void isr21(void);
extern "C" void isr22(void);
extern "C" void isr23(void);
extern "C" void isr24(void);
extern "C" void isr25(void);
extern "C" void isr26(void);
extern "C" void isr27(void);
extern "C" void isr28(void);
extern "C" void isr29(void);
extern "C" void isr30(void);
extern "C" void isr31(void);

/* Set an entry in the <idt>.
 */
static inline void idt_set_gate(uint8_t num, void(*handler)(void), uint16_t sel,
        	  uint8_t flags) 
{
    idt[num].base_lo = (uintptr_t)handler >> 0 & 0xFFFF;
    idt[num].base_hi = (uintptr_t)handler >> 16 & 0xffff;
    idt[num].always0 = 0;
    idt[num].sel = sel;
    idt[num].flags = flags;
}

static const char *exception_messages[32] = {
	"Division by zero",
	"Debug",
	"Non-maskable interrupt",
	"Breakpoint",
	"Detected overflow",
	"Out-of-bounds",
	"Invalid opcode",
	"No coprocessor",
	"Double fault",
	"Coprocessor segment overrun",
	"Bad TSS",
	"Segment not present",
	"Stack fault",
	"General protection fault",
	"Page fault",
	"Unknown interrupt",
	"Coprocessor fault",
	"Alignment check",
	"Machine check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

/*
 * Install the ISR Handlers to Interupt Descriptor Table
 */
void ISR::install_isrs()

{
	idt_set_gate(0, isr0, 0x08, 0x8e);
    idt_set_gate(1, isr1, 0x08, 0x8e);
    idt_set_gate(2, isr2, 0x08, 0x8e);
    idt_set_gate(3, isr3, 0x08, 0x8e);
    idt_set_gate(4, isr4, 0x08, 0x8e);
    idt_set_gate(5, isr5, 0x08, 0x8e);
    idt_set_gate(6, isr6, 0x08, 0x8e);
    idt_set_gate(7, isr7, 0x08, 0x8e);
    idt_set_gate(8, isr8, 0x08, 0x8e);
    idt_set_gate(9, isr9, 0x08, 0x8e);
    idt_set_gate(10, isr10, 0x08, 0x8e);
    idt_set_gate(11, isr11, 0x08, 0x8e);
    idt_set_gate(12, isr12, 0x08, 0x8e);
    idt_set_gate(13, isr13, 0x08, 0x8e);
    idt_set_gate(14, isr14, 0x08, 0x8e);
    idt_set_gate(15, isr15, 0x08, 0x8e);
    idt_set_gate(16, isr16, 0x08, 0x8e);
    idt_set_gate(17, isr17, 0x08, 0x8e);
    idt_set_gate(18, isr18, 0x08, 0x8e);
    idt_set_gate(19, isr19, 0x08, 0x8e);
    idt_set_gate(20, isr20, 0x08, 0x8e);
    idt_set_gate(21, isr21, 0x08, 0x8e);
    idt_set_gate(22, isr22, 0x08, 0x8e);
    idt_set_gate(23, isr23, 0x08, 0x8e);
    idt_set_gate(24, isr24, 0x08, 0x8e);
    idt_set_gate(25, isr25, 0x08, 0x8e);
    idt_set_gate(26, isr26, 0x08, 0x8e);
    idt_set_gate(27, isr27, 0x08, 0x8e);
    idt_set_gate(28, isr28, 0x08, 0x8e);
    idt_set_gate(29, isr29, 0x08, 0x8e);
    idt_set_gate(30, isr30, 0x08, 0x8e);
    idt_set_gate(31, isr31, 0x08, 0x8e);
}

/* Dispatch event handler 
 */
extern "C" void common_interrupt_handler(struct regs *r) {
	if(r->int_no < 32)
	{	
		panic(exception_messages[r->int_no]);
	}
}