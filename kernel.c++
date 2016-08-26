#include "types.h"
#include "gdt.h"
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
#include "pci.h"
#include "graphics.h"



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

extern void printf(char *str, ...);


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




        Heap heap(kernel_virtual_end);




        int *int_ptr = (int*)heap.k_malloc(4);
        int_ptr[2] = 2;
        printf("\nk_malloc returned %x \n" , int_ptr);
        heap.k_free(int_ptr);


        cls();
        PCI_CONTROLLER pci;
        pci.printDrivers();

        VideoGraphicsArray vga;

        vga.SetMode(320,200,8);
        for(int y=0; y<=270; y++)
        	for(int x=0; x<=320; x++)
        		vga.PutPixel(x,y,0x23);

        vga.FillRectangle(0,0,50,50,30,50,15);
        vga.FillRectangle(50,50,50,50,244,67,54);
        vga.FillRectangle(100,100,50,50,255,87,34);
        vga.FillRectangle(150,150,50,50,0x23);


   while(1);
   err:
   	   while(1);
}
