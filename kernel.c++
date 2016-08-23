#include "types.h"
#include "gdt.h"
#include "stdio.h"
#include "serial.h"
#include "mem.h"
#include "idt.h"
#include "timer.h"
#include "isr.h"
#include "kbd.h"
#include "mouse.h"
#include "irq.h"
#include "string.h"
#include "terminal.h"
#include "multiboot.h"
#include "pmm.h"
#include "heap.h"




//Call all class constructor
//for global objects before
//calling the kernel
typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
       (*i)();
}




void hextodec(uint32_t hex)
{
	 uint32_t digit;
	    if (hex < 0) hex = -hex;

	    do
	    {
	      digit = hex % 10;
	      printf("%d" , digit);
	    } while ((hex/=10) > 0);
}

uint32_t check(uint32_t address, uint32_t bit_to_check)
{
	return ((address>>bit_to_check)&1);
}

extern "C" void memory(multiboot_info_t multiboot_structure)
{
	printf("Memory Upper : %d \n \n", multiboot_structure.mem_upper);
}


extern "C" void kernelMain(uint32_t kernel_virtual_end,
	    uint32_t  kernel_physical_end,
		uint32_t placeholder,
		uint32_t kernel_physical_start, uint32_t  kernel_virtual_start,
		multiboot_info_t *multiboot_structure,uint32_t magicnumber
		)


{


	   cls();
	   printf("******KERNEL INFO********\n");
	   printf("KERNEL START VIRTUAL 0x%x\n" , kernel_virtual_start);
	   printf("KERNEL START PHYSICAL 0x%x\n" , kernel_physical_start);
	   printf("KERNEL END VIRTUAL 0x%x\n" , kernel_virtual_end);
	   printf("KERNEL END PHYSICAL 0x%x\n" , kernel_physical_end);
	   printf("MAGIC 0x%x\n" , magicnumber);
	   printf("*************************");
//	   printf("********RAM INFO*********\n");
//
//
//	   printf("Memory Upper : %d \n", multiboot_structure->mem_upper);
//	   printf("Memory Lower : %d \n", multiboot_structure->mem_lower);
//
//	   printf("*************************\n");



	   gdt gt;
	   IDT idt;
	   ISR isr;
	   IRQ irq;
	   SerialPort sp;
	   isr.install_isrs();
	   irq.install_irqs();
	   	Timer timer;
	   	timer.install_timer();
	   	KBD kbd;

	   	kbd.install_kbd_driver();


	   	MOUSE mouse;
	   	mouse.install_mouse_driver();
	   	__asm__ __volatile__ ("sti");


	   	PhyiscalMemoryManager pmm(multiboot_structure);

	    KHEAP       kheap;
	    char        *ptr;

	    Heap heap((&kheap));
	    heap.k_addBlock(&kheap, 0xC0300000, 0xC0500000);
	    ptr = (char*)heap.k_malloc(&kheap, 256);
	    heap.k_free(&kheap, ptr);

   while(1);
   err:
   	   while(1);
}
