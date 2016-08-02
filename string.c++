#include "string.h"

#define ALPHABET_LETTERS 26

SerialPort str_mem_lib;

enum compare
{
	STR1,
	STR2,
	SAME
};

enum compare cmp;


size_t Lib::str::strlen(char* str)
{
    size_t i;
    for (i = 0; str[i] != '\0'; i++) ;
    return i;
}

int Lib::str::toLower(int chr)
{
    return (chr >='A' && chr<='Z') ? (chr + 32) : (chr);
}

void Lib::str::strcpy(char *dest, const char *src, size_t n)
{
	for(int i=0; i<(int)n; i++)
		dest[i] = src[i];
}


char* Lib::str::strchr(const char *str, int c, size_t n)
{
  char* ret = "";
  int ret_loop=0;
	for(int i=0; i<(int)n; i++)
	{
		if(str[i]==(char)c)
		{
			for(int x=i; str[x]!='\0';x++)
			{
				ret[ret_loop]=str[x];
				ret_loop++;
			}
			break;
		}
	}
  return ret;
}

int Lib::str::strcmp(const char *str1, const char *str2)
{
    while(*str1 && (*str1==*str2))
        str1++,str2++;
    return *(const unsigned char*)str1-*(const unsigned char*)str2;
}

int Lib::str::strncmp(const char *str1, const char *str2, size_t n)
{
    while(n--)
        str1++,str2++;
    return *(const unsigned char*)str1-*(const unsigned char*)str2;
}
