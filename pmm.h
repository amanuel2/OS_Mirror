#ifndef _PMM_H_
#define _PMM_H_

#include <stdint.h>
#include "bitset.h"
#include "stdio.h"
#include "multiboot.h"
#include "stdlib.h"


typedef uint32_t paddr_t;

enum status_mem
{
	FREE,
	RESERVED
};

typedef struct
{
	uint32_t start_byte;
	uint32_t size;
	uint32_t end_byte;
	enum status_mem status;
}MemoryPart;

class PhyiscalMemoryManager
{
public:
	PhyiscalMemoryManager(multiboot_info_t *multiboot_structure);
	PhyiscalMemoryManager();
	~PhyiscalMemoryManager();
	void map_physical_virtual(uint32_t physical_address,uint32_t virtual_address);
private:
	void generate_pas();
	Bit bit;
	uint32_t bytes_usable;
};

#endif
