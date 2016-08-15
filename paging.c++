#include "paging.h"



uint32_t page_directory[1024] __attribute__((aligned(4096)));

uint32_t page_table[1024] __attribute__((aligned(4096)));

extern "C" void pages_init()
{
	for(int i = 0; i < 1024; i++)
	{
	    // This sets the following flags to the pages:
	    //   Supervisor: Only kernel-mode can access them
	    //   Write Enabled: It can be both read from and written to
	    //   Not Present: The page table is not present
	    page_directory[i] = 0x00000003 | 3;
	}


	//we will fill all 1024 entries in the table, mapping 4 megabytes
	for(unsigned int i = 0; i < 1024; i++)
	{
	    // As the address is page aligned, it will always leave 12 bits zeroed.
	    // Those bits are used by the attributes ;)
		page_table[i] = (i * 0x1000) | 3; // attributes: supervisor level, read/write, present.
	}

	// attributes: supervisor level, read/write, present
	page_directory[0] = ((unsigned int)page_table) | 3;
}

Paging::Paging()
{

}

Paging::~Paging()
{

}
