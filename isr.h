#ifndef _ISR_H_
#define _ISR_H_ 1

#include <stdint.h>
#include "stdio.h"

class ISR
{
public:
	ISR();
	~ISR();
	void install_isrs();
};


#endif