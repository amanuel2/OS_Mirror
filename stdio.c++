#include "stdio.h"


size_t terminal_row = 0;
size_t terminal_column = 0;
extern uint16_t* VideoMemory;
extern const size_t VGA_WIDTH = 80;
extern const size_t VGA_HEIGHT = 25;
static bool continue_ex = false;

extern uint8_t make_color(int fg, int bg);
extern uint16_t make_vgaentry(char c, uint8_t color);


uint8_t terminal_color;
uint16_t* terminal_buffer;

static PORT::Port8Bits p8b_stdio_drv;



extern void emptyString(char* str);
char *convert(unsigned int num, int base);
	
SerialPort sp_std_io;
//80 * 25


void terminal_bg_fg_ccolor(size_t width, size_t height, int bg, int fg)
{
	terminal_color = make_color(bg, fg);
	terminal_buffer = (uint16_t*) 0xc00b8000;

	    for(int y=0; y<=(signed)(VGA_WIDTH*VGA_HEIGHT); y++)
		{
	    	const size_t index =  (terminal_row * VGA_WIDTH +  terminal_column)+y;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
}

void pong_color(int pong_ping)
{
	char* chr_p;
	if(pong_ping==0)
		chr_p = " pong";
	else
		chr_p = " ping";
	terminal_color = make_color(0, 15);
	terminal_buffer = (uint16_t*) 0xc00b8000;

	for(int y=0; y<=(signed)(4); y++)
	{
	  	const size_t index =  (terminal_row * VGA_WIDTH +  terminal_column)+y;
	  	terminal_buffer[index] = make_vgaentry(' ', terminal_color);
	  	VideoMemory[index]= (VideoMemory[index] & 0xFF00)|chr_p[y];
	}
}


void put_char_helper_neg(char str);

void printf_color(int color, char* str)
{
	terminal_color = make_color(color, 0);
	terminal_buffer = (uint16_t*) 0xc00b8000;

	for(int y=0; y<=1; y++)
	{
	  	const size_t index =  (terminal_row * VGA_WIDTH +  terminal_column);
	  	terminal_buffer[index] = make_vgaentry(' ', terminal_color);
	  	//terminal_buffer[index+1] = make_vgaentry(' ', terminal_color);
	  	VideoMemory[index]= (VideoMemory[index] & 0xFF00)|str[y];
	  	terminal_column++;
	}
}

void printf_color_fg_bg(int fg,int bg, char* str)
{//0x42
	terminal_color = make_color(fg,bg);
	terminal_buffer = (uint16_t*) 0xc00b8000;

	for(int y=0; str[y]!='\0'; y++)
	{
	  	const size_t index =  (terminal_row * VGA_WIDTH +  terminal_column);
	  	if((str[y+1]!='\0'))
	  	{
	  	terminal_buffer[index] = make_vgaentry(' ', terminal_color);
	  	
	  		terminal_buffer[index+1] = make_vgaentry(' ', terminal_color);
	  	}
	  	VideoMemory[index]= (VideoMemory[index] & 0xFF00)|str[y];
	  	terminal_column++;
	}
}


void clear_color()
{
	terminal_color = make_color(0x07, 0x10);
	terminal_buffer = (uint16_t*) 0xc00b8000;
	terminal_column=0;
	terminal_row=0;
	char space = ' ';
	for(int i=0; i<=80; i++)
	{
		for(int y=0; y<=125; y++)
		{

	           const size_t index =  (terminal_row * VGA_WIDTH +  terminal_column); 	
	    	   terminal_column++;
 	terminal_buffer[index] = make_vgaentry(' ', terminal_color);
	  	terminal_buffer[index+1] = make_vgaentry(' ', terminal_color);
		   VideoMemory[index]= (VideoMemory[index] & 0xFF00)|space;
		}
	
	}
	for(int i=0; i<=80; i++)
	{
		for(int y=0; y<=125; y++)
		{
		  const size_t index =  (terminal_row * VGA_WIDTH +  terminal_column);
		  terminal_column--;
		terminal_buffer[index] = make_vgaentry(' ', terminal_color);
	  	terminal_buffer[index+1] = make_vgaentry(' ', terminal_color);
		  VideoMemory[index]= (VideoMemory[index] & 0xFF00)|space;
		}
	}
}
/*
void clear_color()
{
	terminal_color = make_color(0, 0);
	terminal_buffer = (uint16_t*) 0xc00b8000;

	for(int y=0; 25; y++)
	{
		for(int x = 80; x++)
		{
			const size_t index =  (x * VGA_WIDTH +  y)+y;
		  	terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		  	terminal_buffer[index+1] = make_vgaentry(' ', terminal_color);
		  	VideoMemory[index]= (VideoMemory[index] & 0xFF00)|(char)0;
		  	terminal_column++;
		}
	  	
	}
}
*/

void update_cursor(int row, int col)
{
   unsigned short position=(row*80) + col;

   // cursor LOW port to vga INDEX register
   p8b_stdio_drv.out(0x0F,0x3D4);
   p8b_stdio_drv.out((unsigned char)(position&0xFF),0x3D5);
   // cursor HIGH port to vga INDEX register
   p8b_stdio_drv.out(0x0E,0x3D4);
   p8b_stdio_drv.out((unsigned char )((position>>8)&0xFF),0x3D5);
}

char toUpper(char sv)
{
	char sv_ret = 0;
	if(sv >= 'a' && sv <= 'z')
	{
		int sv_int = (int) sv-32;
		sv_ret = (char) sv_int;
	}

	return sv_ret;
}

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

char tbuf[32];
char bchars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void __itoa(unsigned i,unsigned base,char* buf) {
	int pos = 0;
	int opos = 0;
	int top = 0;

	if (i == 0 || base > 16) {
		buf[0] = '0';
		buf[1] = '\0';
		return;
	}

	while (i != 0) {
		tbuf[pos] = bchars[i % base];
		pos++;
		i /= base;
	}
	top=pos--;
	for (opos=0; opos<top; pos--,opos++)
		buf[opos] = tbuf[pos];
	buf[opos] = 0;
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
	if(chr == '\n')
	{
		terminal_row++;
	    terminal_column = 0;
	}
	else
	{
	    terminal_column++;
	    VideoMemory[index]= (VideoMemory[index] & 0xFF00)|chr;
	}
}


void putchr_t(char str)
{
	       size_t index =  (terminal_row * VGA_WIDTH +  terminal_column);
		   terminal_column++;
		   VideoMemory[index]= (VideoMemory[index] & 0xFF00)|str;
}

void mouse_move_print(int x, int y)
{
	size_t terminal_column_res = terminal_column;
	size_t terminal_row_res = terminal_row;

	terminal_row = y;
	terminal_column =x;
	 size_t index =  (terminal_row * VGA_WIDTH +  terminal_column);
	 

	char str[3] = "|";

//	for(int32_t i=0;str[i]!='\0'; ++i)
 //   {
 //   	mouse_prev_chr[i] = str[i];
 //   }
	for(int32_t i=0;str[i]!='\0'; ++i)
    {
        VideoMemory[index]= (VideoMemory[index] & 0xFF00)|str[i];
    }

    terminal_column = terminal_column_res;
	terminal_row = terminal_row_res;

}

void mouse_clear_print(int x, int y)
{
	size_t terminal_column_res = terminal_column;
	size_t terminal_row_res = terminal_row;

	terminal_row = y;
	terminal_column =x;
	 

	char* str = " ";

	for(int32_t i=0;str[i]!='\0'; ++i)
    {
    	size_t index =  (terminal_row * VGA_WIDTH +  terminal_column);
        VideoMemory[index]= (VideoMemory[index] & 0xFF00)|str[i];
        terminal_column++;
    }

    terminal_column = terminal_column_res;
	terminal_row = terminal_row_res;
}


void update_clock_time_taken(int sec)
{
	size_t terminal_column_res = terminal_column;
	size_t terminal_row_res = terminal_row;
	char* cust_msg = " Seconds Taken";
	char* sec_chr = itoa(sec);

	terminal_row = 0;
	terminal_column = 60;


	//Conversion
	for(int i=0;sec_chr[i]!='\0'; ++i)
	{
		const size_t index =  (terminal_row * VGA_WIDTH +  terminal_column);

    	VideoMemory[index]= (VideoMemory[index] & 0xFF00)|sec_chr[i];

    	terminal_column++;
	}

	for(int i=0;cust_msg[i]!='\0'; ++i)
	{
		const size_t index =  (terminal_row * VGA_WIDTH +  terminal_column);

    	VideoMemory[index]= (VideoMemory[index] & 0xFF00)|cust_msg[i];

    	terminal_column++;
	}
	
    terminal_column = terminal_column_res;
	terminal_row = terminal_row_res;
}

void check_color(char* str, uint8_t color)
{
	const size_t index =  (terminal_row * VGA_WIDTH +  terminal_column);

	for(int i=0; str!='\0';i++)
	{
		VideoMemory[index]= (VideoMemory[index] & 0xFF00)|str[i];
		VideoMemory[index]= (VideoMemory[index] & 0xFF00)|color;
	}

	terminal_column+=2;
}

void putchar(char str,char next_str, va_list &arg)
{
	if(!continue_ex)
	{
	  int32_t ch_per;  // MDP modified to fix bug
	  char* str_use;
	  const char per = '%';
		 if(str == '\b')
		    {
		      terminal_column--;
		    }
		    const size_t index =  (terminal_row * VGA_WIDTH +  terminal_column);
		    char space = ' ';
		    int ch_per_chr;
		    unsigned int uint_chr;
		    char *c_per_str;
		    char * uint_chr_use;
		    int ch_x;
		    char str_x[32]={0}; // MDP modified to fix bug
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

		        	case 'u':
		        		uint_chr=va_arg(arg,unsigned int);
		        		uint_chr_use = convert(uint_chr,10);
		        		for(int32_t i=0;uint_chr_use[i]!='\0'; ++i)
		        		{

		        				sp_std_io.write_serial(uint_chr_use[i]);
		        			putchr_t(uint_chr_use[i]);
		        		}
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
		        		ch_x = va_arg(arg, int);
//MDP		       		str_x[32]= {0};
		        		__itoa(ch_x, 16, str_x);
		        		for(int32_t i=0;str_x[i]!='\0'; ++i)
		        		{
		        		  putchr_t(str_x[i]);
		        		}
		        		continue_ex = true;
		        		break;
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

char *convert(unsigned int num, int base)
{
	static char buff[33];
	char *ptr;
	ptr=&buff[sizeof(buff)-1];
	*ptr='\0';
	do
	{
		*--ptr="0123456789abcdef"[num%base];
		num/=base;
	}while(num!=0);
	return(ptr);
}


