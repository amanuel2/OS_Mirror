#include "mem.h"

SerialPort ser_mem_lib;


void* Lib::Mem::memset(void *str, int c, size_t n)
{
    unsigned char* p=(unsigned char*)str;
    while(n--)
        *p++ = (unsigned char)c;
    return str;
}

void* Lib::Mem::memcpy(void *dest, const void *src, size_t n)
{
	 char *dp = (char *)dest;
	 const char *sp = (const char*) src;
	 while (n--)
	    *dp++ = *sp++;
	 return dest;
}

void* Lib::Mem::memmove(void *dest, const void *src, size_t n)
{
    unsigned char *pd = (unsigned char *)dest;
    const unsigned char *ps = (const unsigned char*)src;
    if ((ps < pd))
        for (pd += n, ps += n; n--;)
            *--pd = *--ps;
    else
        while(n--)
            *pd++ = *ps++;
    return dest;
}

char* Lib::Mem::memchr(const void *str, int c, size_t n)
{
	 unsigned char *p = (unsigned char*)str;
	    while( n-- )
	        if( *p != (unsigned char)c )
	            p++;
	        else
	            return (char *)p;
	 return 0;
}



int Lib::Mem::memcmp(const void *str1, const void *str2, size_t n)
{
	const unsigned char *p1 = (const unsigned char*)str1, *p2 =  (const unsigned char*)str2;
	    while(n--)
	        if( *p1 != *p2 )
	            return *p1 - *p2;
	        else
	            p1++,p2++;
	    return 0;
}
