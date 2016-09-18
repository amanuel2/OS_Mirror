
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
#include "flpdisk.h"
#include "filealgorithms.h"
#include "vata.h"


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

flpydsk_install(6);
      printf("\nHello :) \n");
uint8_t* sector = 0;
     //! read sector from disk
  sector = flpydsk_read_sector ( 0 );

  printf("%x",sector);
// 	   	cls();





//         int *int_ptr = (int*)heap.k_malloc(4);
//         int_ptr[2] = 2;
//         printf("\nk_malloc returned %x \n" , int_ptr);
//         heap.k_free(int_ptr);


        cls();
        PCI_CONTROLLER pci;
        pci.printDrivers();

        cls();
 	    init_tasking(&heap);
 	  // doIt();

#ifdef GRAPHICS_MODE
        Desktop desktop(0x23);
#endif


       cls();

     // Sound sound;
     // sound.beep(2);
     FileAlgo filealgo;
     File sampleFile; 
     File anotherSampleFile;
     anotherSampleFile.header.name="WkstMathsTODO";
     sampleFile.header.name = "FileName";
     Vata vata;

    

 // char* already_read = vata.return_ata().Read28(0);
  char* file_contents=filealgo.File_to_char(sampleFile);
 // char* added_up = Lib::str::strcat(already_read,file_contents);
 //  printf("\n\nADDED_UP: %s",added_up);

 //  added_up = "Amanuel";

// char* prev_result_prev = Lib::str::strcat(vata.return_ata().Read28(0),"DOUBLEAWESOME");
// //printf("STR : %s" , prev_result_prev);

   vata.return_ata().Write28(0, file_contents,0, Lib::str::strlen(file_contents));
   vata.return_ata().Flush();

    char* result_sector_one = vata.return_ata().Read28(0);

   //printf("READ : %s",prev_result);

     Terminal terminal;
     terminal.initalize(0x00,result_sector_one);

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
