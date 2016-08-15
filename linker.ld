/* The bootloader will look at this image and start execution at the symbol
   designated as the entry point. */
ENTRY(loader)

/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{
	/* Begin putting sections at 1 MiB, a conventional place for kernels to be
	   loaded at by the bootloader. */
	. = 0xC0100000;

	/* First put the multiboot header, as it is required to be put very early
	   early in the image or the bootloader won't recognize the file format.
	   Next we'll put the .text section. */
	.text ALIGN (0x1000) : AT(ADDR(.text)-0xC0000000)
	{
		*(.multiboot)
		*(.text)
	}

	/* Read-only data. */
	.rodata ALIGN (0x1000) : AT(ADDR(.text)-0xC0000000)
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data ALIGN (0x1000) : AT(ADDR(.text)-0xC0000000)
	{
	    start_ctors = .;
	    KEEP(*( .init_array ));
	    KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )));
	    end_ctors = .;
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss ALIGN (0x1000) : AT(ADDR(.text)-0xC0000000)
	{
		*(COMMON)
		*(.bss)
	}

}

