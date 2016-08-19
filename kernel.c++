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


extern "C" void kernelMain(uint32_t kernel_start_virtual,
		uint32_t kernel_start_physical , uint32_t kernel_end_virtual ,
		uint32_t kernel_end_physical,	multiboot_info_t multiboot_structure,uint32_t magicnumber
		)
{
	   cls();
	   printf("******KERNEL INFO********\n");
	   printf("KERNEL START VIRTUAL 0x%x\n " , kernel_start_virtual);
	   printf("KERNEL START PHYSICAL 0x%x\n" , kernel_start_physical);
	   printf("KERNEL END VIRTUAL 0x%x\n" , kernel_end_virtual);
	   printf("KERNEL END PHYSICAL 0x%x\n" , kernel_end_physical);
	   printf("*************************\n");
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

	   uint32_t total_mem_lo = ((uint32_t)multiboot_structure.mem_lower + (uint32_t)multiboot_structure.mem_upper);
	   	printf("\n MemLower : %d \n Upper Memory: %d \n \n TOTAL MEMORY : %d" , multiboot_structure.mem_lower,
	   			multiboot_structure.mem_upper,(total_mem_lo));


	   	PhyiscalMemoryManager pmm;


	    /*
	     * While Loop In terminal.initalize() .. Never ending
	     * */

   while(1);	
   err:
   	   while(1);
}
