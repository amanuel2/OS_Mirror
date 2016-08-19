#ifndef _HEAP_H_
#define _HEAP_H_ 1
#include <stdint.h>

class Heap
{

private:
	void map_page(void* physaddr, void* virtualaddr, uint32_t flags);
	void* get_physaddr(void * virtualaddr);
};

#endif
