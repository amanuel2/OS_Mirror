#ifndef _BITMAP_H_
#define _BITMAP_H_ 1

typedef struct _KHEAPBLOCKBM {
	struct _KHEAPBLOCKBM	    *next;
	uint32_t					size;
	uint32_t					used;
	uint32_t					bsize;
    uint32_t                    lfb;
} KHEAPBLOCKBM;

typedef struct _KHEAPBM {
	KHEAPBLOCKBM			*fblock;
} KHEAPBM;

class Bitmap
{
public:
	void k_heapBMInit(KHEAPBM *heap);
	void *k_heapBMAlloc(KHEAPBM *heap, uint32_t size);
	void k_heapBMFree(KHEAPBM *heap, void *ptr);
	Bitmap();
	~Bitmap();
private:
	uint8_t k_heapBMGetNID(uint8_t a, uint8_t b);
};

#endif
