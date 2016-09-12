#ifndef _BFS_H_
#define _BFS_H_ 1

#include <stdarg.h>
#include <stdint.h>
#include "string.h"


/*
* Bone File System
*/

class BFS
{
public:
	BFS();
	~BFS();
	void fast_format(uint8_t *label);
};


#endif