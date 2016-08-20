#include "heap.h"

extern "C" uint64_t BootPageDirectory[4] __attribute__((aligned(0x1000)));

void Heap::map_page(void* physaddr, void* virtualaddr, uint32_t flags)
{
	// Make sure that both addresses are page-aligned.

	//    uint32_t pdindex = (uint32_t)virtualaddr >> 22;
	    uint32_t ptindex = (uint32_t)virtualaddr >> 12 & 0x03FF;


	    //uint32_t * pd = (uint32_t *)0xFFFFF000;
	    // Here you need to check whether the PD entry is present.
	    // When it is not present, you need to create a new empty PT and
	    // adjust the PDE accordingly.

	    //uint32_t * pt = ((uint32_t *)0xFFC00000) + (0x400 * ptindex);
	    // Here you need to check whether the PT entry is present.
	    // When it is, then there is already a mapping present. What do you do now?

	    BootPageDirectory[ptindex] = ((uint32_t)physaddr) | (flags & 0xFFF) | 0x01; // Present

	    // Now you need to flush the entry in the TLB
	    // or you might not notice the change.
}


void Heap::init()
{
	printf("\n");


	// 512 entries
	uint64_t page_dir[512] __attribute__((aligned(0x1000)));  // must be aligned to page boundary
	uint64_t page_tab[512] __attribute__((aligned(0x1000)));

	BootPageDirectory[0] = (uint64_t)&page_dir | 1; // set the page directory into the PDPT and mark it present
	page_dir[0] = (uint64_t)&page_tab | 3; //set the page table into the PD and mark it present/writable


	unsigned int i, address = 0;
	for(i = 0; i < 512; i++)
	{
	    page_tab[i] = address | 3; // map address and mark it present/writable
	    address = address + 0x1000;
	}

	uint64_t * page_dir_l = (uint64_t*)BootPageDirectory[3]; // get the page directory (you should 'and' the flags away)
	page_dir_l[511] = (uint64_t)page_dir_l; // map pd to itself
	page_dir_l[510] = BootPageDirectory[2]; // map pd3 to it
	page_dir_l[509] = BootPageDirectory[1]; // map pd2 to it
	page_dir_l[508] = BootPageDirectory[0]; // map pd1 to it
	page_dir_l[507] = (uint64_t)&BootPageDirectory; /* map the PDPT to the directory*/

}


void* Heap::get_physaddr(void * virtualaddr)
{

    //uint32_t pdindex = (uint32_t)virtualaddr >> 22;
    uint32_t ptindex = (uint32_t)virtualaddr >> 12 & 0x03FF;


    //uint32_t * pd = (uint32_t *)0xFFFFF000;
    // Here you need to check whether the PD entry is present.


    //uint32_t * pt = ((uint32_t *)0xFFC00000) + (0x400 * pdindex);
    // Here you need to check whether the PT entry is present.

    return (void *)((BootPageDirectory[ptindex] & ~0xFFF) + ((uint32_t)virtualaddr & 0xFFF));

}
