
#ifndef _MATH_H_
#define _MATH_H_ 1
#include<stdint.h>

namespace math
{
	#define IS_NAN(x) (((x) < 0) == ((x) >= 0))

	int static inline pow(int base , int pow)
	{
		int num = 1;
		for(int i=0; i<= pow; i++)
		{
			num*=base;
		}

		return num;
	}
}

#endif
