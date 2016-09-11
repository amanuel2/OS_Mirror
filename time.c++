#include "time.h"


extern int32_t timer_ticks;
extern int second_passed();

void delay(uint32_t seconds)
{
	timer_ticks = 0;
	for(uint32_t i = 0 ; i<=seconds; i++)
		second_passed();
}