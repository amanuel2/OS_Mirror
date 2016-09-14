
//#define GRAPHICS_MODE 1
#define DEBUG_MODE 1
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
#include "rand.h"
#ifdef GRAPHICS_MODE
	#include "graphics.h"
	#include "widget.h"
	#include "desktop.h"
#endif
#include "task.h"
#ifdef DEBUG_MODE
	#include "vertex.h"
#endif
#include "time.h"
#include "sound.h"
#include "ata.h"

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


void taskA();
void taskB();

template <class T>
class TestList
{
public:
	TestList(){}
	~TestList(){};
};

extern "C" void kernelMain
		(
			uint32_t kernel_virtual_end,
			uint32_t  kernel_physical_end,
			uint32_t placeholder,
			uint32_t kernel_physical_start,
			uint32_t  kernel_virtual_start,
			multiboot_info_t *multiboot_structure,
			uint32_t magicnumber
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


	   PhyiscalMemoryManager pmm(multiboot_structure);



	   Heap heap(kernel_virtual_end);




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





        int *int_ptr = (int*)heap.k_malloc(4);
        int_ptr[2] = 2;
        printf("\nk_malloc returned %x \n" , int_ptr);
        heap.k_free(int_ptr);


        cls();
        PCI_CONTROLLER pci;
        pci.printDrivers();

        cls();
 	    init_tasking(&heap);
 	  // doIt();

#ifdef GRAPHICS_MODE
        Desktop desktop(0x23);
#endif

#ifdef DEBUG_MODE
        Vertex<int> vert;
        vert.insert_begin(3);
        vert.insert_begin(4);
        vert.insert_begin(5);
        vert.insert_end(20);
        vert.insert_end(70);
        vert.insert_index(3,1000);

        vert.insert_before_val(70,342);

   
    vert.sort(REVERSE);
         for(uint32_t i=0; i<vert.get_amount(); i++)
       		 printf("%d : %d \n" ,i, vert.get_val(i));


printf("***********\n");
	Vertex<char*> vert_check;
	vert_check.insert_begin("a");
	vert_check.insert_end("b");
	vert_check.sort(REVERSE);
 for(uint32_t i=0; i<vert_check.get_amount(); i++)
       		 printf("%d : %s \n" ,i, vert_check.get_val(i));



       	//vert.insert_index(5);	
#endif

       cls();

      //  printf("Delay 5 Seconds\n");
      // delay(5); 
      // printf("Delay Finished!");

      // printf("Delay 2Seconds\n");
      // delay(2); 
      // printf("Delay Finished!");

     Sound sound;
     sound.beep(2);

     AdvancedTechnologyAttachment atapm(0x1F0,MASTER);
     atapm.Identify();

     if(atapm.accesible)
     {
       printf("\nWritting Info In Primary Master\n");
     	 atapm.Write28(0, (char*)"Info Written to Hard Drive", 0,26);
    	 atapm.Flush();
     	 atapm.Read28(0);
     }

     AdvancedTechnologyAttachment ataps(0x1F0,SLAVE);
     ataps.Identify();
     if(ataps.accesible)
     {
       printf("\nWritting Info In Primary Slave\n");
     	 ataps.Write28(0, (char*)"Info Written to Hard Drive",0, 26);
    	 ataps.Flush();
     	 ataps.Read28(0);
     }
    

	 AdvancedTechnologyAttachment atasm(0x170,MASTER);
	 atasm.Identify();
     if(atasm.accesible)
     {
       printf("\nWritting Info In Secondary Master\n");
       atasm.Write28(0, (char*)"Info Written to Hard Drive", 0,26);
       atasm.Flush();
       atasm.Read28(0);
     }


     AdvancedTechnologyAttachment atass(0x170,SLAVE);
     atass.Identify();
     if(atass.accesible)
     {
       printf("\nWritting Info In Secondary Slave\n");
       atass.Write28(0, (char*)"Amanuel",7, 14);
       atass.Flush();
       atass.Read28(0);
     }

   while(1);
   err:
   	   while(1);
}

void taskA()
{
    while(true)
        printf("A");
}


void taskB()
{
    while(true)
        printf("B");
}
