#include "pmm.h"


static const uint32_t TOTAL_RAM_BYTES = 3586139904;
static const uint32_t TOTAL_RAM_GB = 3.586139904;

MemoryPart** mempat;

PhyiscalMemoryManager::PhyiscalMemoryManager(multiboot_info_t *multiboot_structure)
{
	/*
	 * 0xC0100000  -  0xFFFFFFFF
	 */
	bytes_usable = 0;

	 multiboot_structure->mmap_addr += 0xC0000000;
		   		multiboot_mmap_entry* mmap = (multiboot_mmap_entry*) multiboot_structure->mmap_addr ;
		   		printf("\n********RAM INFO*********\n");
		   		for(size_t i=0 ;
		   				i<multiboot_structure->mmap_length/(sizeof(multiboot_mmap_entry));
		   				i++)
		   		{
		   			if(mmap[i].type == MULTIBOOT_MEMORY_AVAILABLE)
		   			{

		   				uintptr_t addr = ((uintptr_t)mmap[i].addr);
		   				uintptr_t length=((uintptr_t)mmap[i].len);
		   				uintptr_t size=((uintptr_t)mmap[i].size);
		   				uintptr_t type=((uintptr_t)mmap[i].type);

		   				 printf("Entry #%d \n" , i);
		   				 printf("ADDRESS : 0x%x \n",addr);
		   				 printf("LENGTH  : %d \n"  ,length);
		   				 printf("SIZE	 : %d \n"  ,size);
		   				 printf("TYPE 	 : %d \n"  ,type);
		   				 bytes_usable+=length;
		   			}
		   		}
		   		printf("**************************\n");
		   		printf("%d MB Of Usable RAM" , bytes_usable/1000000);



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
