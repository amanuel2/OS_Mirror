#include "stdlib.h"

extern void printf(char *str,...);

void panic(const char* exception)
{
	printf(" \n PANIC : %s \n" , exception);
	__asm__ volatile ( "cli" );
	while(true) {};
}