
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

//flpydsk_install(6);
  //    printf("\nHello :) \n");
//uint8_t* sector = 0;
     //! read sector from disk
  //sector = flpydsk_read_sector ( 0 );

  //printf("%x",sector);
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
     File file1;
     File file2;
     File file3;
     file1.header.name = "FILE 1";
     file2.header.name = "FILE 2";
     file3.header.name = "FILE 3";
     anotherSampleFile.header.name="WkstMathsTODO";
     sampleFile.header.name = "FileName";
     Vata vata;

    

 
  ret_chr_arr file_contents=filealgo.File_to_char(sampleFile);
  ret_chr_arr math_wkst_file= filealgo.File_to_char(anotherSampleFile);

  ret_chr_arr file_1_contents = filealgo.File_to_char(file1);
  ret_chr_arr file_2_contents = filealgo.File_to_char(file2);
  ret_chr_arr file_3_contents = filealgo.File_to_char(file3);


  char* res_default = Lib::str::strcat(file_contents.str,math_wkst_file.str);
  res_default = Lib::str::strcat(res_default,file_1_contents.str);
  res_default = Lib::str::strcat(res_default,file_2_contents.str);
  res_default = Lib::str::strcat(res_default,file_3_contents.str);

//printf("\nres_default %s",res_default);

   vata.return_ata().Write28(0, res_default,0, Lib::str::strlen(res_default));
   vata.return_ata().Flush();

    char* result_sector_one = vata.return_ata().Read28(0);
    char_two_ret result_names = filealgo.return_file_names_from_encoded_char_multiple(result_sector_one);


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
