#include "pmm.h"

PhyiscalMemoryManager::PhyiscalMemoryManager(void)
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
