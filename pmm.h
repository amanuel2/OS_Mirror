#ifndef _PMM_H_
#define _PMM_H_

#include <stdint.h>
#include "bitset.h"


typedef uint32_t paddr_t;


class PhyiscalMemoryManager
{
public:
	PhyiscalMemoryManager();
	~PhyiscalMemoryManager();

private:
	Bit bit;
};

#endif
