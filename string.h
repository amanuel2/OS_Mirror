#ifndef _STRING_H_
#define _STRING_H_ 1

#include <stdint.h>
#include "types.h"
#include "serial.h"
#include "math.h"

namespace Lib
{

	namespace str
	{

			size_t strlen(char* str);
			void strcpy(char *dest, const char *src, size_t n);
			int  strcmp(const char *str1, const char *str2);
			int  strncmp(const char *str1, const char *str2, size_t n);
			char*strchr(const char *str, int c, size_t n);
			uint32_t hex2dec(char* hex);
			int startswith(char* P, char* T);
			int toLower(int chr);

	}

}




#endif
