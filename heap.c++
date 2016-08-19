#include "heap.h"

void Heap::map_page(void* physaddr, void* virtualaddr, uint32_t flags)
{
	// Make sure that both addresses are page-aligned.

	    uint32_t pdindex = (uint32_t)virtualaddr >> 22;
	    uint32_t ptindex = (uint32_t)virtualaddr >> 12 & 0x03FF;


	    //uint32_t * pd = (uint32_t *)0xFFFFF000;
	    // Here you need to check whether the PD entry is present.
	    // When it is not present, you need to create a new empty PT and
	    // adjust the PDE accordingly.

	    uint32_t * pt = ((uint32_t *)0xFFC00000) + (0x400 * pdindex);
	    // Here you need to check whether the PT entry is present.
	    // When it is, then there is already a mapping present. What do you do now?
	    printf("Here");
	    pt[ptindex] = ((uint32_t)physaddr) | (flags & 0xFFF) | 0x01; // Present

	    // Now you need to flush the entry in the TLB
	    // or you might not notice the change.
}
extern "C" uint64_t BootPageDirectory[1024] __attribute__((aligned(0x1000)));

void Heap::init()
{
	uint32_t start_heap_virtual __attribute__((aligned(0x1000))) = 0xC0200000;
	uint32_t start_heap_physical __attribute__((aligned(0x1000))) = 0x2BB00000;
	this->map_page(&start_heap_physical,&start_heap_virtual,0);
	start_heap_physical = (uint32_t)this->get_physaddr(&start_heap_virtual);
	printf("%d" , BootPageDirectory[0]);
	printf("START HEAP VIRTUAL : %x \nSTART HEAP PHYSICAL: %x" , start_heap_virtual , start_heap_physical);
}


void* Heap::get_physaddr(void * virtualaddr)
{

    uint32_t pdindex = (uint32_t)virtualaddr >> 22;
    uint32_t ptindex = (uint32_t)virtualaddr >> 12 & 0x03FF;


    //uint32_t * pd = (uint32_t *)0xFFFFF000;
    // Here you need to check whether the PD entry is present.

    printf("Here");
    uint32_t * pt = ((uint32_t *)0xFFC00000) + (0x400 * pdindex);
    // Here you need to check whether the PT entry is present.
    printf("Here");
    return (void *)((pt[ptindex] & ~0xFFF) + ((uint32_t)virtualaddr & 0xFFF));

}
