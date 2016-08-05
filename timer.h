#ifndef _TIMER_H_
#define _TIMER_H_ 1

#include <stdint.h>
#include "irq.h"


class Timer
{
public:
	Timer();
	~Timer();
private:
	void timer_wait(int ticks);
};

#endif