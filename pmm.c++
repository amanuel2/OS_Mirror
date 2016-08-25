#include "pmm.h"

extern "C" uint32_t BootPageDirectory[1024];
extern "C" void invalidate_page_vm (void *virt_addr);


PhyiscalMemoryManager::PhyiscalMemoryManager():bytes_usable(0)
{

}

PhyiscalMemoryManager::PhyiscalMemoryManager(multiboot_info_t *multiboot_structure)
{
	/*
	 * 0xC0100000  -  0xFFFFFFFF
	 * NO.	ADDRESS	 LENGTH	 SIZE  TYPE
	 */
	bytes_usable = 0;

	 multiboot_structure->mmap_addr += 0xC0000000;
		   		multiboot_mmap_entry* mmap = (multiboot_mmap_entry*) multiboot_structure->mmap_addr ;
		   		printf("********RAM INFO*********\n");
		   		printf("No.\t\tADDRESS\t\tLENGTH\t\t\t\tSIZE\t\tTYPE\n");
		   		for(size_t i=0 ;
		   				i<multiboot_structure->mmap_length/(sizeof(multiboot_mmap_entry));
		   				i++)
		   		{
		   			if(mmap[i].type == MULTIBOOT_MEMORY_AVAILABLE)
		   			{

		   				uintptr_t addr = ((uintptr_t)mmap[i].addr);
		   				uintptr_t length=((uintptr_t)mmap[i].len);
		   				uintptr_t size=((uintptr_t)mmap[i].size);
		   				//uintptr_t type=((uintptr_t)mmap[i].type);

		   				 printf("#%d" , i);
		   				 printf("\t\t0x%x",addr);
		   				 printf("\t\t%x"  ,length);
		   				 printf("\t\t\t\t\t\t%d\n"  ,size);
		   				// printf("\t\t\t\t\t\t\t\t%d\n"  ,type);
		   				 bytes_usable+=length;
		   			}
		   		}
		   		printf("**************************\n");


		   		printf("%d MB Of Usable RAM" , bytes_usable/(1024*1024));




}


static inline uint32_t get_base_address(uint32_t index_page)
{
	return((uint32_t)(index_page << 22));
}

static inline uint32_t get_page_index(uint32_t virtual_address)
{
	return((uint32_t)(virtual_address >> 22));
}

void PhyiscalMemoryManager::map_physical_virtual(uint32_t physical_address,uint32_t virtual_address)
{
	bit.set_adress(physical_address);
	bit.setbit(7);
	bit.setbit(1);
	bit.setbit(0);
	BootPageDirectory[get_page_index(virtual_address)]=bit.get_address();
	invalidate_page_vm((void *)virtual_address);
}

void PhyiscalMemoryManager::generate_pas()
{


}




PhyiscalMemoryManager::~PhyiscalMemoryManager(void)
{

}

