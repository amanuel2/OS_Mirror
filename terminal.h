#ifndef _TERMINAL_H_
#define _TERMINAL_H_ 1

#include "stdio.h"
#include "string.h"
#include "time.h"
#include "mem.h"
#include "filealgorithms.h"
//extern FileAlgo filealgo;

class Terminal
{
public:
	Terminal();
	~Terminal();
	void initalize(uint8_t FLAGS,char* result_sector_one);
private:
	uint8_t FLAGS;
	void print_logo();
	void handle_input();
	char* result_sector_one;
	FileAlgo filealgo;
};

#endif
