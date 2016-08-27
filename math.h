
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

	uint32_t static hex2int(char *hex)
	{
	    uint32_t val = 0;
	    while (*hex)
	    {
	        // get current character then increment
	        char byte = *hex++;
	        // transform hex character to the 4bit equivalent number, using the ascii table indexes
	        if (byte >= '0' && byte <= '9')
	        	byte = byte - '0';
	        else if (byte >= 'a' && byte <='f')
	        	byte = byte - 'a' + 10;
	        else if (byte >= 'A' && byte <='F')
	        	byte = byte - 'A' + 10;
	        // shift 4 to make space for new digit, and add the 4 bits of the new digit
	        val = (val << 4) | (byte & 0xF);
	    }
	    return val;
	}

	inline double fabs(double i)
	{
	   return (i < 0 ? -i : i);
	}
}

#endif
