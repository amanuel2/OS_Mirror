#include "types.h"
#include "gdt.h"
#include "stdio.h"
#include "serial.h"
#include "mem.h"
#include "idt.h"



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
   gdt gt;
   SerialPort sp;
   IDT idt;

   printf("Hello World. My name is %s  and I am %d years old" , "Amanuel",100);

//   int x = 5/0;
   while(1);
   err:
   	   while(1);
}
