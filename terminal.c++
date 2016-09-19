#include "terminal.h"



extern size_t terminal_row;
extern size_t terminal_column;
extern void terminal_bg_fg_ccolor(size_t width, size_t height, int bg, int fg);
extern void pong_color(int pong_ping);
extern void update_cursor(int row, int col);
extern void clear_color();
extern void printf_color_fg_bg(int fg,int bg, char* str);
extern uint8_t get_scan_code();
extern bool shift;
extern char return_pressed_letter(int scancode);
extern void control_char();
extern void terminal_scroll(int scroll_by);

extern size_t terminal_row;
extern size_t terminal_column;

bool terminal_scroll_ready = false;


void get_scan_code_terminal();

static uint8_t alphabet[26] =
{
		'q','w','e','r','t','y',
		'u','i','o','p','a','s',
		'd','f','g','h','j','k'
		,'l','z','x','c','v','b',
		'n','m'
};

char val_total[999999] = "";
int val_total_index=0;
int backspace_offset=0;

void add_char_val_term(uint8_t data)
{
	val_total[val_total_index] = data;
	val_total_index++;
	backspace_offset++;
}

Terminal::Terminal()
{

}
Terminal::~Terminal()
{

}
void Terminal::print_logo()
{
		clear_color();
		cls();
		printf(" ************     **********       **       * 	 ********		");
		printf("\n");
		printf(" *		  *     *	    *       * *      *      *				");
		printf("\n");
		printf(" *		  *     *	    *       *  *     *      *				");
		printf("\n");
		printf(" *	  	*     *	    *       *   *    *      *					");
		printf("\n");
		printf(" *   ********     *	    *       *    *   *      *****		    ");
		printf("\n");
		printf(" *	  	*     *	    *       *     *  *      *					");
		printf("\n");
		printf(" *	  	*     *	    *       *      * *      *					");
		printf("\n");
		printf(" *	  	*     *	    *       *       **      *					");
		printf("\n");
		printf(" ************     **********       *        *      ******** 	");
		printf("\n");
}

void Terminal::handle_input()
{//
	if(Lib::str::strcmp(val_total,"help")==0)
	{
		if(terminal_scroll_ready==true)
		{
		   	terminal_scroll(4);
		   	terminal_scroll_ready=false;
		   	printf("\n**********HELP*********\n");
		   	printf("[Commands] : ls");
			printf("\n***********************\n");
		}
		else
		{
        	printf("\n**********HELP*********\n");
			printf("[Commands] : ls");
			printf("\n***********************\n");
		}  
	
	}
	else if(Lib::str::strcmp(val_total,"Help")==0)
	{
		if(terminal_scroll_ready==true)
		{
		   	terminal_scroll(2);
		   	terminal_scroll_ready=false;
		   	printf("\nDid you mean 'help' ?\n");
		}
		else
		{
        	printf("\nDid you mean 'help' ?\n");
		}  
		
	}
	else if(Lib::str::strcmp(val_total,"help")==0)
	{
		if(terminal_scroll_ready==true)
		{
		   	terminal_scroll(2);
		   	terminal_scroll_ready=false;
		   	printf("\nDid you mean 'help' ?\n");
		}
		else
		{
        	printf("\nDid you mean 'help' ?\n");
		}  
	}
	else if(Lib::str::strcmp(val_total,"help")==0)
	{
		if(terminal_scroll_ready==true)
		{
		   	terminal_scroll(2);
		   	terminal_scroll_ready=false;
		   	printf("\nDid you mean 'help' ?\n");
		}
		else
		{
        	printf("\nDid you mean 'help' ?\n");
		}  
	}
	else if(Lib::str::strcmp(val_total,"help")==0)
	{
		if(terminal_scroll_ready==true)
		{
		   	terminal_scroll(2);
		   	terminal_scroll_ready=false;
		   	printf("\nDid you mean 'help' ?\n");
		}
		else
		{
        	printf("\nDid you mean 'help' ?\n");
		}  
	}	
	else if(Lib::str::strcmp(val_total,"ls")==0)
	{
		char* answer = this->filealgo.return_file_names_from_encoded_char(this->result_sector_one);
		if(terminal_scroll_ready==true)
		{
		   	terminal_scroll(2);
		   	terminal_scroll_ready=false;
		   	printf("\n%s\n",answer);
		}
		else
		{
        	printf("\n%s\n",answer);
		}  
		
	}	
	else
	{
		if(terminal_scroll_ready==true)
		{
		   	terminal_scroll(2);
		   	terminal_scroll_ready=false;
		   	printf("\n%s Command Not Found\n", val_total);
		}
		else
		{
        	printf("\n%s Command Not Found\n", val_total);
		}  
		
	}

}

void Terminal::initalize(uint8_t FLAGS,char* result_sector_one)
{
	this->result_sector_one = result_sector_one;
		printf_color_fg_bg(1,0,"[GDT LOADED]");
		printf("\n");
		sleep(0.1);
		printf_color_fg_bg(2,0,"[IRQ'S LOADED]");
		printf("\n");
		sleep(0.1);
		printf_color_fg_bg(3,0,"[ISR'S LOADED]");
		printf("\n");
		sleep(0.1);
		printf_color_fg_bg(4,0,"[IDT  LOADED]");
		printf("\n");
		sleep(0.1);
		printf_color_fg_bg(5,0,"[INTERRUPTS READY]");
		printf("\n");
		sleep(0.1);
		printf_color_fg_bg(6,0,"[GRAPHICS LOADED]");
		printf("\n");
		sleep(0.1);
		printf_color_fg_bg(7,0,"[TIME LOADED]");
		printf("\n");
		sleep(0.1);
		printf_color_fg_bg(8,0,"[SOUND LOADED]");
		printf("\n");
		sleep(0.1);
		printf_color_fg_bg(9,0,"[ATA LOADED]");
		printf("\n");
		sleep(0.1);
		printf_color_fg_bg(10,0,"[MOUSE READY]");
		printf("\n");
		sleep(0.1);
		printf_color_fg_bg(11,0,"[KEYBOARD READY]");
		printf("\n");
		sleep(0.1);
		printf_color_fg_bg(12,0,"[LIBRARIES SET]");
		printf("\n");
		sleep(0.1);
		printf_color_fg_bg(13,0,"[TERMINAL INITALIZED]");
		update_cursor(terminal_row,terminal_column);
		printf("\n");
		printf("TERMIAL WILL RUN SOON!");
		sleep(2.1);
		cls();
		this->print_logo();
		printf("\n\n\n");
		while(true)
		{
		   printf_color_fg_bg(2,0,"[root@boneos");
		   printf("<%d,%d>",terminal_row,terminal_column);
		   

		   if(terminal_row>=24 && terminal_column>=12)
		   	terminal_scroll_ready = true;
		   printf_color_fg_bg(2,0," /] ");
		   
		   get_scan_code_terminal();
		   enter_fini:
		   this->handle_input();
		   Lib::Mem::memset(val_total,0,sizeof(val_total));
		   val_total_index = 0;
	    }
}

void OnKeyUp(uint8_t scancode)
{
	
}
void control_key_handler()
{

}
void OnKeyDown(uint8_t scancode)
{
	uint8_t letter_key_press=(char)0;
	bool pressed_recognize = false;
	//printf("%d" , (int)scancode);
	if(scancode == 29)
	{
		control_key_handler();
	}
	if(scancode == 28)
	{
	
	}
	else if(scancode == 42)
	{
		int h; // Not Needed / Shi
	}
	else if((int) scancode>=16 && (int) scancode <= 50 && (!( scancode > 27 && scancode <30 )) && (!(scancode>41 && scancode<43)))
	{
		pressed_recognize = true;
		uint8_t letter_key_press = return_pressed_letter(scancode);
		add_char_val_term(letter_key_press);
		//printf("VALTOTAL=%s",val_total);
	    printf("%c" , letter_key_press);
	}
	else if(scancode == 12)
	{
		pressed_recognize = true;
		if(shift==false)
		{
			add_char_val_term('-');
			printf("-");
		}
		else
		{
			add_char_val_term('_');
			printf("_");
		}

	}
	else if(scancode == 13)
	{
		pressed_recognize = true;
		if(shift==false)
		{
			add_char_val_term('=');
			printf("=");
		}
		else
		{
			add_char_val_term('+');
			printf("+");
		}
	}
	else if(scancode == 14)
	{
		if(backspace_offset!=0)
		{
			pressed_recognize = true;
		    printf("\b");
		   // printf("%d",backspace_offset);
		    val_total[val_total_index-1] = 0;
			val_total_index--;
			backspace_offset--;
		}
		
	}

	else if(scancode == 15)
	{
		//for(int i=0;i<=3;i++)add_char_val_term(' ');
		pressed_recognize = true;
		//printf("\t");
	}
	else if(scancode == 52)
	{
		pressed_recognize = true;
		if(shift==false)
		{
			add_char_val_term('.');
			printf(".");
		}
		else
		{
			add_char_val_term('>');
			printf(">");
		}
	}

	else if(scancode == 91)
	{
		//Windows Key :)
	}

	else if(scancode >= 1 && scancode <= 11)
	{
		
		pressed_recognize = true;
		control_char();
	}
	
	else if(scancode == 57)
	{
		pressed_recognize = true;
		add_char_val_term(' ');
		printf(" ");
	}
}
void get_scan_code_terminal()
{
	while(true)
	{
		uint8_t scancode_term =get_scan_code();
		if(scancode_term!=0)
		{
			if (scancode_term & 0x80)
		    	OnKeyUp(scancode_term);
		    else
		    {
		    	if(scancode_term==28)
		    		return;
		    	OnKeyDown(scancode_term);
		    }
				
		}
	}
}	