#include "heap.h"

extern "C" uint32_t BootPageDirectory[1024];
extern "C" void invalidate_page_vm (void *virt_addr);

int Heap::k_addBlock(KHEAPLCAB *heap, uintptr_t addr, uint32_t size)
{
	 this->get_page_index(0xC0400000);
		KHEAPBLOCKLCAB			*hb;
		KHEAPHDRLCAB			*hdr;

		hb = (KHEAPBLOCKLCAB*)addr;
		hb->size = size;
		hb->used = 0;
		hb->next = heap->fblock;
		heap->fblock = hb;

		hdr = (KHEAPHDRLCAB*)&hb[1];
		hdr->flagsize = hb->size - (sizeof(KHEAPBLOCKLCAB) + 32);

		++heap->bcnt;

		hb->lastdsize = 0;
		hb->lastdhdr = 0;

		return 1;
}


/*
	Look behind and forward to see if we can merge back into some chunks.
*/
void Heap::k_free(KHEAPLCAB *heap, void *ptr)
{
	KHEAPHDRLCAB				*hdr, *phdr, *nhdr;
	KHEAPBLOCKLCAB				*hb;
	//uint32_t						sz;
	//uint8_t						fg;


	hdr = (KHEAPHDRLCAB*)ptr;
	hdr[-1].flagsize &= ~0x80000000;


	phdr = 0;
	/* find the block we are located in */
	for (hb = heap->fblock; hb; hb = hb->next)
	{
		if (((uintptr_t)ptr > (uintptr_t)hb) && ((uintptr_t)ptr < (uintptr_t)hb + hb->size))
		{

			hdr = (KHEAPHDRLCAB*)((uintptr_t)ptr - sizeof(KHEAPHDRLCAB));


			hdr->flagsize &= ~0x80000000;

			hb->used -= hdr->flagsize;


			if (hdr->prevsize)
			{
				phdr = (KHEAPHDRLCAB*)((uintptr_t)&hdr - (sizeof(KHEAPHDRLCAB) + hdr->prevsize));
			}
			else
			{
				phdr = 0;
			}

			/* get next header */
			nhdr = (KHEAPHDRLCAB*)((uintptr_t)&hdr[1] + hdr->flagsize);
			if ((uintptr_t)nhdr >= ((uintptr_t)hb + hb->size))
			{
				nhdr = 0;
			}

			if (nhdr)
			{
				if (!(nhdr->flagsize & 0x80000000))
				{
					/* combine with it */
					hdr->flagsize += sizeof(KHEAPHDRLCAB) + nhdr->flagsize;
					hb->used -= sizeof(KHEAPHDRLCAB);
					/* set next header prevsize */
					nhdr = (KHEAPHDRLCAB*)((uintptr_t)&hdr[1] + hdr->flagsize);
					nhdr->prevsize = hdr->flagsize;
				}
			}


			if (phdr)
			{
				if (!(phdr->flagsize & 0x80000000))
				{
					phdr->flagsize += sizeof(KHEAPHDRLCAB) + hdr->flagsize;
					hb->used -= sizeof(KHEAPHDRLCAB);
					hdr = phdr;
					nhdr = (KHEAPHDRLCAB*)((uintptr_t)&hdr[1] + hdr->flagsize);
					if ((uintptr_t)nhdr < (uintptr_t)hb + sizeof(KHEAPBLOCKLCAB) + hb->size)
					{
						nhdr->prevsize = hdr->flagsize;
					}
				}
			}

			/* optimization */
			if (hdr->flagsize > hb->lastdsize)
			{
				hb->lastdsize = hdr->flagsize;
				hb->lastdhdr = hdr;
			}

			return;
		}
	}

	printf("uhoh ptr:%p\n", ptr);
	for (hb = heap->fblock; hb; hb = hb->next) {
		printf("lcab free looking at block:%p next:%p ptr:%p end:%p\n", hb, hb->next, ptr, (uintptr_t)hb + hb->size);
		if (((uintptr_t)ptr > (uintptr_t)hb)) {
			printf("above\n");
			if (((uintptr_t)ptr < ((uintptr_t)hb + hb->size))) {
				printf("found\n");
			}
		}
	}
	for (;;);
	/* uhoh.. this should not happen.. */
	return;
}

/*
	This will allocate a chunk of memory by the specified size, and if
	no memory chunk can be found it will return zero.
*/


void* Heap::k_malloc(KHEAPLCAB *heap, uint32_t size)
{
	KHEAPBLOCKLCAB		*hb;
	KHEAPHDRLCAB		*hdr, *_hdr, *phdr;
	uint32_t			sz;
	uint8_t				fg;
	uint32_t			checks;
	uint32_t			bc;

	checks = 0;
	bc =0;


	for (hb = heap->fblock; hb; hb = hb->next) {
		if ((hb->size - hb->used) >= (size + sizeof(KHEAPHDRLCAB))) {
			++bc;

			hdr = (KHEAPHDRLCAB*)&hb[1];


			phdr = 0;
			while ((uintptr_t)hdr < ((uintptr_t)hb + hb->size)) {
				++checks;

				fg = hdr->flagsize >> 31;
				sz = hdr->flagsize & 0x7fffffff;

				if (!fg)
				{

					if (sz >= size)
					{

						if (sz > (size + sizeof(KHEAPHDRLCAB) + 16))
						{

							_hdr = (KHEAPHDRLCAB*)((uintptr_t)&hdr[1] + size);
							_hdr->flagsize = sz - (size + sizeof(KHEAPHDRLCAB));
							_hdr->prevsize = size;
							hdr->flagsize = 0x80000000 | size;
							hb->used += sizeof(KHEAPHDRLCAB);

						}
						else
						{
							hdr->flagsize |= 0x80000000;
						}
						hb->used += size;


						return &hdr[1];
					}
				}
				phdr = hdr;
				hdr = (KHEAPHDRLCAB*)((uintptr_t)&hdr[1] + sz);
			}

		}
	}

	return 0;
}


void Heap::get_page_index(uint32_t virt_address)
{
//TODO
}
void* Heap::get_base_address(uint32_t index_page)
{
	return((void*)(index_page << 22));
}



Heap::Heap(KHEAPLCAB *heap)
{
	heap->fblock = 0;
	heap->bcnt = 0;

   /*
	* RESERVE 4MB TO THE HEAP
	* Map 4MB page frame at physical address 0x400000
	* to 0xC0400000. In order for the change to be seen
	* invalidate the page which flushes the associated
	* TLB entry(ies)
   */

	BootPageDirectory[769]=0x400083;
	invalidate_page_vm((void *)0xC0400000);

	/* At this point 0xC0000000 to 0xC0800000 have been
	 *  added to paging tables and associated with physical
	 *  memory pages
	 */
}

Heap::~Heap()
{

}



