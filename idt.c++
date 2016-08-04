#include "idt.h"

// Definitions of locations of the PIC ports.
// The Programmable Interrupt Controller, or PIC, has two parts, the master and
// the slave.
#define PIC_MASTER_CONTROL 0x20
#define PIC_MASTER_MASK 0x21
#define PIC_SLAVE_CONTROL 0xa0
#define PIC_SLAVE_MASK 0xa1

#define IDT_GATE_PRESENT (1<<7)

/* The Interrupt Descriptor Table and its entries.
 * The Interrupt Descriptor Table, or IDT, describes the code called when an
 * interrupt occurs.
 * It has a few important fields:
 * 
 * @base_lo: The lower half of a pointer to the code which will be called when
 * the interrupt is triggered.
 * @base_hi: The higher half of that same pointer.
 * @sel: The interrupt routine will be called with this <gdt> segment.
 * @always0: Reserved.
 * @flags: Contains the present flag, as well as the Descriptor Privilege
 * Level. The DPL indicates what ring code needs to be running as in order to
 * issue this interrupt, or in our case whether use mode code can issue this
 * interrupt.
 * For more information, read Volume 3 Chapter 6 of the Intel Manual.
 */
struct idt_entry {
    uint16_t base_lo;
    uint16_t sel; // Kernel segment goes here.
    uint8_t always0;
    uint8_t flags; // Set using the table.
    uint16_t base_hi;
}__attribute__((packed));



/*
 * Similar to the <gdt_ptr>, this is a special pointer to the <idt>.
 */
struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

 struct idt_entry idt[IDT_SIZE];
 struct idt_ptr idtp;


/* The state of the CPU when an interrupt is triggered. */
struct regs {
     uint32_t ds; /* pushed the segs last */
     uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /* pushed by 'pusha' */
     uint32_t int_no, err_code; /* our 'push byte #' and ecodes do this */
     uint32_t eip, cs, eflags, useresp, ss; /* pushed by the processor automatically */
};


/* A wrapper around lidt.
 * Load the provided <idt_ptr> onto the CPU.
 */
extern "C" void idt_load(struct idt_ptr);

extern "C" void _service_interrupt(void);

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
extern "C" void isr32(void);
extern "C" void isr33(void);
extern "C" void isr34(void);

/* Set an entry in the <idt>.
 */
static void idt_set_gate(uint8_t num, void(*handler)(void), uint16_t sel,
        uint8_t flags) {
    idt[num].base_lo = (uintptr_t)handler >> 0 & 0xFFFF;
    idt[num].base_hi = (uintptr_t)handler >> 16 & 0xffff;
    idt[num].always0 = 0;
    idt[num].sel = sel;
    idt[num].flags = flags;
}


IDT::IDT(void) {
    // 256 is the number of entries in the table.
    idtp.limit = (sizeof(idt)) - 1;
    idtp.base = (uint32_t) & idt;

    Lib::Mem::memset(&idt, 0, sizeof(struct idt_entry) * 256);

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
    idt_set_gate(32, isr32, 0x08, 0x8e);
    idt_set_gate(33, isr33, 0x08, 0x8e);
    idt_set_gate(34, isr34, 0x08, 0x8e);

    // ICW1 - begin initialization
    p8b.out((uint8_t)PIC_MASTER_CONTROL, (uint16_t)0x11);
    p8b.out((uint8_t)PIC_SLAVE_CONTROL, (uint16_t)0x11);

    // Remap interrupts beyond 0x20 because the first 32 are cpu exceptions
    p8b.out((uint8_t)PIC_MASTER_MASK, (uint16_t)0x21);
    p8b.out((uint8_t)PIC_SLAVE_MASK, (uint16_t)0x28);

    // ICW3 - setup cascading
    p8b.out((uint8_t)PIC_MASTER_MASK, (uint16_t)0x00);
    p8b.out((uint8_t)PIC_SLAVE_MASK, (uint16_t)0x00);

    // ICW4 - environment info
    p8b.out((uint8_t)PIC_MASTER_MASK, (uint16_t)0x01);
    p8b.out((uint8_t)PIC_SLAVE_MASK, (uint16_t)0x01);

    // mask interrupts
    p8b.out((uint8_t)PIC_MASTER_MASK, (uint16_t)0xff);
    p8b.out((uint8_t)PIC_SLAVE_MASK, (uint16_t)0xff);

    idt_load(idtp);
}

IDT::~IDT()
{

}
/* Dispatch event handler or, if none exists, log information and kernel panic.
 */
extern "C" void common_interrupt_handler(struct regs r) {
        printf("Unhandled Interrupt Triggered!\nRegisters");
}