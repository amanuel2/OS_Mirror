#ifndef _PAGING_H_
#define _PAGING_H_ 1

#include <stdint.h>
#include "stdio.h"


class Paging
{


private:

	void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys);
	void paging_enable();
public:
	void paging_init();

};

#endif