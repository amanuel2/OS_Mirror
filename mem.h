#ifndef _MEM_H_
#define _MEM_H_ 1

#include<stdint.h>
#include "types.h"
#include "serial.h"

namespace Lib
{
	namespace Mem
	{

		void* memset(void *str, int c, size_t n);
		void* memcpy(void *dest, const void *src, size_t n);
		int  memcmp(const void *str1, const void *str2, size_t n);
		void* memmove(void *dest, const void *src, size_t n);
		char* memchr(const void *str, int c, size_t n);


	}
}

#endif
