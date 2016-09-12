#include "bfs.h"

typedef 
struct 
{
	uint32_t sig;//File Signature
	uint32_t size; //Size of header per byte
	uint8_t label[8]; //Name Of File
	uint8_t SectorsPerTrack;
	uint8_t TrackPerHead;
	uint16_t Heads;
}BFSHeader;


BFS::BFS()
{

}

void BFS::fast_format(uint8_t *label)
{
	BFSHeader header; 
	Lib::str::strcpy((char*)&header.sig,"BFS1",sizeof((char*)&header.sig));
	header.size = sizeof(BFSHeader);
	if(Lib::str::strlen((char*)label)>8)
	{
		printf("Name To Long\n");
		while(true);
	}
	Lib::str::strcpy((char*)header.label,(char*)label,sizeof((char*)header.label));
}

BFS::~BFS()
{

}