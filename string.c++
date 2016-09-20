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


char* Lib::str::strcat(char *dest, char *src)
{
   size_t dest_len = strlen(dest);
   size_t src_len = strlen(src);
   char* return_str="";
   uint32_t count_return_str=0;
    for(uint32_t i=0;i<=dest_len;i++)
   		return_str[count_return_str++] = dest[i];
   	count_return_str=dest_len;
     for(uint32_t i=0;i<=src_len;i++)
     		return_str[count_return_str++] = src[i];
   	return return_str;
}

char *
strstr(char* string, char* substring)	
{
    register char *a, *b;
    b = substring;
    if (*b == 0) {
	return string;
    }
    for ( ; *string != 0; string += 1) {
	if (*string != *b) {
	    continue;
	}
	a = string;
	while (1) {
	    if (*b == 0) {
		return string;
	    }
	    if (*a++ != *b++) {
		break;
	    }
	}
	b = substring;
    }
    return (char *) 0;
}

int Lib::str::startswith(char* P, char* T){
	    int n = Lib::str::strlen(T);
	    int m = Lib::str::strlen(P);
	    for (int i = 0; i <= n-m; ++i) {
	        int j = 0;
	        while (j < m && T[i+j] == P[j]) {
	            ++j;
	        }
	        if (j == m) { // match found
	            return i;
	        }
	    }
	    return -1;
}

int Lib::str::count_substr(char *str, char* substr, bool overlap) {
  if (strlen(substr) == 0) return -1; 

  int count = 0;
  int increment = overlap ? 1 : strlen(substr);
  for (char* s = (char*)str; (s = strstr(s, substr)); s += increment)
    ++count;
  return count;
}

int Lib::str::find_occurence_chr(char* val, char other)
{
  int count=0;    
    for(int i=0; i<(signed)strlen(val);i++)
        if(val[i]==other)
            count++;
    return count;
}


uint32_t Lib::str::hex2dec(char* hex)
{
	return -1;
}
