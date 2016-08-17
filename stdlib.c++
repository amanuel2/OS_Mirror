#include "stdlib.h"

extern void printf(char *str,...);

void panic(const char* exception)
{
	printf(" \n PANIC : %s \n" , exception);
	while(true) {};
}