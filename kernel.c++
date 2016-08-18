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
#include "terminal.h"
#include "multiboot.h"




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


extern "C" void kernelMain(multiboot_info_t* multiboot_structure,uint32_t magicnumber,uint32_t kernel_start_virtual,
							uint32_t kernel_start_physical , uint32_t kernel_end_virtual ,
							uint32_t kernel_end_physical)
{
	   cls();
	   //printf("KEN_ST_V %x \n KEN_ST_P %x \n KEN_EN_V %x \n KEN_EN_P %x" , kernel_start_virtual,kernel_start_physical,
	   //		   kernel_end_virtual , kernel_end_physical );
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

	   	//int x = 5/0;
	   // Terminal terminal;
	   // terminal.terminal_initalize();
	   	//cls();


	   	printf("\n %x" , multiboot_structure);

	    /*
	     * While Loop In terminal.initalize() .. Never ending
	     * */

   while(1);	
   err:
   	   while(1);
}
