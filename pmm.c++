#include "pmm.h"


static const uint32_t TOTAL_RAM_BYTES = 3586139904;
static const uint32_t TOTAL_RAM_GB = 3.586139904;

MemoryPart** mempat;

PhyiscalMemoryManager::PhyiscalMemoryManager()
{
	/*
	 * 0xC0100000  -  0xFFFFFFFF
	 */


}

void PhyiscalMemoryManager::allocate(MemoryPart vas)
{
	if(vas.status != FREE)
	{
		//Not Suppose to Reach here.
	 //	panic("NOT FREE VIRTUAL ADRESS SPACE");
	}

	else
	{



	}
}

void PhyiscalMemoryManager::generate_pas()
{


}




PhyiscalMemoryManager::~PhyiscalMemoryManager(void)
{

}


static inline uint32_t get_page_index(uint32_t adress)
{
	return (adress >> 22);
}

static inline uint32_t get_page_base(uint32_t index)
{
	return (index << 22);
}
