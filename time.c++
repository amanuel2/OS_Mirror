#include "time.h"


extern int32_t timer_ticks_delay;
extern bool second_passed;

void delay(uint32_t seconds)
{
	timer_ticks_delay = 0;
	for(uint32_t i = 0 ; i<=seconds; i++)
	{
		ret_delay_func:;
		if(second_passed==true)
			second_passed=false;
		else
			goto ret_delay_func;	
	}
}