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
static struct idt_entry {
    uint16_t base_lo;
    uint16_t sel; // Kernel segment goes here.
    uint8_t always0;
    uint8_t flags; // Set using the table.
    uint16_t base_hi;
} __attribute((packed)) idt[IDT_SIZE] = {{0}};

/*
 * Similar to the <gdt_ptr>, this is a special pointer to the <idt>.
 */
struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute((packed));

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
extern "C" void idt_load();

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
static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel,
        uint8_t flags) {
    idt[num].base_lo = base & 0xffff;
    idt[num].base_hi = (base >> 16) & 0xffff;
    idt[num].always0 = 0;
    idt[num].sel = sel;
    idt[num].flags = flags;
}


void IDT::idt_install(void) {
    // 256 is the number of entries in the table.
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (uint32_t) & idt;

    //memset(&idt, 0, sizeof(struct idt_entry) * 256);

    idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8e);
    idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8e);
    idt_set_gate(2, (uint32_t)isr2, 0x08, 0x8e);
    idt_set_gate(3, (uint32_t)isr3, 0x08, 0x8e);
    idt_set_gate(4, (uint32_t)isr4, 0x08, 0x8e);
    idt_set_gate(5, (uint32_t)isr5, 0x08, 0x8e);
    idt_set_gate(6, (uint32_t)isr6, 0x08, 0x8e);
    idt_set_gate(7, (uint32_t)isr7, 0x08, 0x8e);
    idt_set_gate(8, (uint32_t)isr8, 0x08, 0x8e);
    idt_set_gate(9, (uint32_t)isr9, 0x08, 0x8e);
    idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8e);
    idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8e);
    idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8e);
    idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8e);
    idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8e);
    idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8e);
    idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8e);
    idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8e);
    idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8e);
    idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8e);
    idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8e);
    idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8e);
    idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8e);
    idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8e);
    idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8e);
    idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8e);
    idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8e);
    idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8e);
    idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8e);
    idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8e);
    idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8e);
    idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8e);
    idt_set_gate(32, (uint32_t)isr32, 0x08, 0x8e);
    idt_set_gate(33, (uint32_t)isr33, 0x08, 0x8e);
    idt_set_gate(34, (uint32_t)isr34, 0x08, 0x8e);

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

    idt_load();
}

/* Dispatch event handler or, if none exists, log information and kernel panic.
 */
extern "C" void common_interrupt_handler(struct regs r) {
        printf("Unhandled Interrupt Triggered!\nRegisters");
}