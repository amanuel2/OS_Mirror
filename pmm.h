#ifndef _PMM_H_
#define _PMM_H_

#include <stdint.h>
#include "bitset.h"


typedef uint32_t paddr_t;

enum status_mem
{
	FREE,
	RESERVED
};

typedef struct
{
	uint32_t start_adress;
	uint32_t length;
	enum status_mem status;
}MemoryPart;

class PhyiscalMemoryManager
{
public:
	PhyiscalMemoryManager(uint32_t adress_p , MemoryPart part);
	~PhyiscalMemoryManager();

private:
	Bit bit;
};

#endif
