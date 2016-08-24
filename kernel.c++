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
extern "C" uint32_t BootPageDirectory[1024];
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
       (*i)();
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
	   	cls();
	   	PhyiscalMemoryManager pmm(multiboot_structure);


	    KHEAP       kheap;
	    char        *ptr;
	    int 		*int_ptr;






        Heap heap((&kheap));
        printf("\n %u \n" , 0x9D248000);

        /* The heap can be placed anywhere starting in virtual
           memory between 0xC0000000 to 0xC0800000 which aren't
           already used by the kernel for other code and data.
           Whatever starting memory address is used in this
           region the base address of the heap + length can't
           be >= 0xC0800000 unless other pages are added to the
           page tables */

        /* This heap runs from 0xC0200000 to C04FFFFF - 3MB */
        //heap.k_addBlock(&kheap, 0xC0200000, 0x300000);

        /* This heap runs from the 4KB aligned memory boundary after
         *  the end of the kernel for a length of 3MB
        */
        heap.k_addBlock(&kheap, (kernel_virtual_end+4095)&0xFFFFF000, 0x300000);

        /* This example heap runs from 0xC0400000 to 0xC07FFFFF - 4MB */
        //heap.k_addBlock(&kheap, 0xC0400000,0x400000);

        /* Now call k_malloc to allocate memory from our heap area */
        ptr = (char*)heap.k_malloc(&kheap, 256);
        printf("\nk_malloc returned: %x", ptr);


        int_ptr = (int*)heap.k_malloc(&kheap,100);
        printf("\nk_malloc returned: %x", int_ptr);
        heap.k_free(&kheap, int_ptr);

        heap.k_free(&kheap, ptr);

   while(1);
   err:
   	   while(1);
}
