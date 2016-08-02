#include "types.h"
#include "gdt.h"
#include "stdio.h"
#include "serial.h"
#include "mem.h"



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

   printf("Hello People \b");
   printf("s %d %d %d %d %c %o %s \t %x" , 12, 150, 230, 560, 'H', 23323, "TestingString", 0xBADBEEF);


   cls();
   printf("Hello World");
   sp.write_string_serial("Hello World");
   while(1);
   err:
   	   while(1);
}
