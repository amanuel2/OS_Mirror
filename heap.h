#ifndef _HEAP_H_
#define _HEAP_H_ 1
#include "stdio.h"
#include <stdint.h>

#define KHEAPFLAG_USED			0x80000000

typedef struct _KHEAPHDRLCAB {
	uint32_t				prevsize;
	uint32_t				flagsize;
} KHEAPHDRLCAB;

typedef struct _KHEAPBLOCKLCAB {
	uint32_t					size;
	uint32_t					used;
	struct _KHEAPBLOCKLCAB	                *next;
	uint32_t					lastdsize;
	KHEAPHDRLCAB			        *lastdhdr;
} KHEAPBLOCKLCAB;

typedef struct _KHEAPLCAB {
	KHEAPBLOCKLCAB		       *fblock;
	uint32_t				bcnt;
} KHEAPLCAB;

typedef KHEAPLCAB KHEAP;


class Heap
{
public:
		Heap(KHEAPLCAB *heap);
		~Heap();
		int k_addBlock(KHEAPLCAB *heap, uintptr_t addr, uint32_t size);
		void* k_malloc(KHEAPLCAB *heap, uint32_t size);
		void k_free(KHEAPLCAB *heap, void *ptr);
		inline void* operator new(size_t size,Heap heap_obj,KHEAPLCAB *heap)
		{
			return (heap_obj.k_malloc(heap,size));
		}
private:

};

#endif
