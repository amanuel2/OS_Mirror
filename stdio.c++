#include "stdio.h"


static size_t terminal_row = 0;
static size_t terminal_column = 0;
static  uint16_t* VideoMemory =((uint16_t*)0xb8000);
static bool continue_ex = false;


SerialPort sp_std_io;
//80 * 25


void cls()		
{
	terminal_column=0;
	terminal_row=0;
	char space = ' ';
	for(int i=0; i<=80; i++)
	{
		for(int y=0; y<=125; y++)
		{
	           const size_t index =  (terminal_row * VGA_WIDTH +  terminal_column); 	
	    	   terminal_column++;
 	
		   VideoMemory[index]= (VideoMemory[index] & 0xFF00)|space;
		}
	
	}
	for(int i=0; i<=80; i++)
	{
		for(int y=0; y<=125; y++)
		{
		  const size_t index =  (terminal_row * VGA_WIDTH +  terminal_column);
		  terminal_column--;

		  VideoMemory[index]= (VideoMemory[index] & 0xFF00)|space;
		}
	}
}


void printf(char *str, ...)
{
	va_list arg;
	va_start(arg, str);

	for(int32_t i=0;str[i]!='\0'; ++i)
        {
            putchar(str[i],str[i+1],arg);
        }

	va_end(arg);
}

void strcat(char *destination, const char *source)
{
    int x = 0;
    while (destination[x] != '\0')
    {
        x++;
    }
    for (int i=0; source[i] != '\0'; i++)
    {
        destination[x++] = source[i];
    }
    destination[x] = '\0';
}

void put_char_helper_neg(char chr)
{
	const size_t index =  (terminal_row * VGA_WIDTH +  terminal_column);
    terminal_column++;
    VideoMemory[index]= (VideoMemory[index] & 0xFF00)|chr;
}


void putchr_t(char str)
{
	       size_t index =  (terminal_row * VGA_WIDTH +  terminal_column);
		   terminal_column++;
		   VideoMemory[index]= (VideoMemory[index] & 0xFF00)|str;
}


void putchar(char str,char next_str, va_list &arg)
{
	if(!continue_ex)
	{
	  uint32_t ch_per;
	  char* str_use;
	  const char per = '%';
		 if(str == '\b')
		    {
		      terminal_column--;
		    }
		    const size_t index =  (terminal_row * VGA_WIDTH +  terminal_column);
		    char space = ' ';
		    int ch_per_chr;
		    char *c_per_str;
		    switch(str)
		    {
		        case '\n':
		          terminal_row++;
		          terminal_column = 0;
		          break;
		        case '\b':
		          VideoMemory[index]= (VideoMemory[index] & 0xFF00)|space;
		          break;
		        case '\t':
		          for(int32_t t=0;t<=3;t++)terminal_column++;
		          break;
		        case '%':
		        	switch(next_str)
		        	{
		        	case 'd':
		        		ch_per = va_arg(arg,int);
		        		if(ch_per<0)
		        		{
		        			ch_per = -ch_per;
		        			put_char_helper_neg('-');
		        		}
		        		str_use = itoa(ch_per);
		     		    terminal_column++;

		     		   for(int32_t i=0;str_use[i]!='\0'; ++i)
		     		   {
		     			  putchr_t(str_use[i]);
		     		   }

//		        		sp_std_io.write_number_serial(ch_per);
//		        		sp_std_io.write_string_serial(str_use);
		        		continue_ex = true;
		        		break;
		        	case 'c':
		        		ch_per_chr = va_arg(arg,int);
		        		put_char_helper_neg(ch_per_chr);
		        		continue_ex = true;
		        		break;


		        	case 's':
		        		c_per_str = va_arg(arg,char *);
		        		for(int32_t i=0;c_per_str[i]!='\0'; ++i)
		        		{
		        		  putchr_t(c_per_str[i]);
		        		}
		        		continue_ex = true;
		        		break;
		        	case 'x':
		        	case 'o':
		        	   ch_per = va_arg(arg,unsigned int);
		        	   str_use = itoa(ch_per);
		        	   terminal_column++;

		        		for(int32_t i=0;str_use[i]!='\0'; ++i)
		        		{
		        			putchr_t(str_use[i]);
		        		}
		        		continue_ex = true;
		        		break;
		        	default:
		        		terminal_column++;
		        		VideoMemory[index]= (VideoMemory[index] & 0xFF00)|per;
		        	}
		        	break;
		        default:
		          terminal_column++;
		          VideoMemory[index]= (VideoMemory[index] & 0xFF00)|str;
		          break;
		    }
	}
	else
	{
		continue_ex = false;
	}

}




int32_t strlen(int8_t* str)
{
	int32_t l=0;
	while(str[l]!='\0')l++;
	return l;
}


char *itoa(int val)

{
	uint8_t *ptr;
    static uint8_t buffer[16];
    ptr = buffer + sizeof(buffer);
    *--ptr = '\0';

    if (val == 0)
    {
    	*--ptr = '0';
    }
    else while (val != 0)
    {
    	*--ptr = (val % 10) + '0';
    	val = val / 10;
    }
    return((char*)ptr);
}



