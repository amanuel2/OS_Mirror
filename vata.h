#ifndef _VATA_H_
#define _VATA_H_ 1

#include "ata.h"

#define PRIMARY_BUS_ATA 0x1F0
#define SECONDARY_BUS_ATA 0x170

class Vata
{
public:
	Vata();
	~Vata();
    AdvancedTechnologyAttachment return_ata();
private:
	int x;
};



#endif