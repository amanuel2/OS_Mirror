/* The bootloader will look at this image and start execution at the symbol
   designated as the entry point. */
ENTRY(loader)
OUTPUT_FORMAT(elf32-i386)

SECTIONS {
   /* The kernel will live at 3GB + 1MB in the virtual
      address space, which will be mapped to 1MB in the
      physical address space. */
   . = 0xC0100000;
   
   kernel_start_virtual = .;
   kernel_start_physical =  . - 0xC0000000;

			
   .text ALIGN (0x1000) : AT(ADDR(.text) - 0xC0000000) {
       *(.multiboot)
       *(.text)
       *(.rodata*)
   }

   .data ALIGN (0x1000) : AT(ADDR(.data) - 0xC0000000) {
   		start_ctors = .;
        KEEP(*( .init_array ));
        KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )));
        end_ctors = .;
        *(.data)
   }

   .bss : AT(ADDR(.bss) - 0xC0000000) {
       _sbss = .;
       *(COMMON)
       *(.bss)
       _ebss = .;
   }
   
   kernel_end_virtual = .;
   kernel_end_physical =  . - 0xC0000000;
}
