#include "idt.h"

// Definitions of locations of the PIC ports.
// The Programmable Interrupt Controller, or PIC, has two parts, the master and
// the slave.
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


/* A wrapper around lidt.
 * Load the provided <idt_ptr> onto the CPU.
 */
extern "C" void idt_load(struct idt_ptr);



IDT::IDT() {
    // 256 is the number of entries in the table.
    idtp.limit = (sizeof(idt)) - 1; //Number of IDT's = 256-1; (index starts by 0)
    idtp.base = (uint32_t) & idt; //Base = Pointer to Interupt Desciptor Table

    Lib::Mem::memset(&idt, 0, sizeof(struct idt_entry) * 256); //Clear the 256 Entries First

    idt_load(idtp);
}

IDT::~IDT()
{

}