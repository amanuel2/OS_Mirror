#include "types.h"
#include "gdt.h"
#include "stdio.h"
#include "serial.h"
#include "mem.h"
#include "idt.h"
#include "timer.h"
#include "isr.h"
#include "irq.h"




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



extern "C" void kernelMain(void* multiboot_structure,uint32_t magicnumber)
{
 //  cls();
   gdt gt;
   IDT idt;
   ISR isr;
   IRQ irq;
   for( ; ; ) asm("hlt");
   SerialPort sp;
   isr.install_isrs();
   irq.install_irqs();
   	Timer timer;
   	timer.install_timer();	
   __asm__ __volatile__ ("sti");



//  int x = 5/0;
   while(1);	
   err:
   	   while(1);
}
