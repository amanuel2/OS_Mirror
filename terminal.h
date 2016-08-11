#ifndef _TERMINAL_H_
#define _TERMINAL_H_ 1

#include "stdio.h"
#include "string.h"

class Terminal{

public:
	Terminal();
	~Terminal();		
	void recieve_input();
	void terminal_initalize();
private:
	void char_handler(char* val);
};

#endif