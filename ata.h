#ifndef _ATA_H_
#define _ATA_H_ 1

#include "port.h"
#include "stdio.h"

#define ERROR_ATA_IDENTIFY 0x01

typedef 
enum
{
	SLAVE,
	MASTER
}ata_type;

class AdvancedTechnologyAttachment
{
public:
	AdvancedTechnologyAttachment(uint16_t portBase,ata_type type);
	~AdvancedTechnologyAttachment();

	void Identify();
	char* Read28(uint8_t sectorNum,uint32_t count = 512);
	void Write28(uint8_t sectorNum, char* data,uint32_t start, uint32_t count);
	void Flush();
	bool accesible = true;
private:
	ata_type type;
	uint16_t port_def;
};

#endif
