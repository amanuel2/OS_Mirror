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


void get_scan_code_terminal();

static uint8_t alphabet[26] =
{
		'q','w','e','r','t','y',
		'u','i','o','p','a','s',
		'd','f','g','h','j','k'
		,'l','z','x','c','v','b',
		'n','m'
};

char val_terminal[] = "";
int val_terminal_index = 0;

uint32_t backspace_offset = 0;

void increase_val_term(char val)
{
	val_terminal[val_terminal_index] = val;
	printf("Herre");
	val_terminal_index++;
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
{
		

}

void Terminal::initalize(uint8_t FLAGS)
{
		// printf_color_fg_bg(1,0,"[GDT LOADED]");
		// printf("\n");
		// delay(0.1);
		// printf_color_fg_bg(2,0,"[IRQ'S LOADED]");
		// printf("\n");
		// delay(0.1);
		// printf_color_fg_bg(3,0,"[ISR'S LOADED]");
		// printf("\n");
		// delay(0.1);
		// printf_color_fg_bg(4,0,"[IDT  LOADED]");
		// printf("\n");
		// delay(0.1);
		// printf_color_fg_bg(5,0,"[INTERRUPTS READY]");
		// printf("\n");
		// delay(0.1);
		// printf_color_fg_bg(6,0,"[GRAPHICS LOADED]");
		// printf("\n");
		// delay(0.1);
		// printf_color_fg_bg(7,0,"[TIME LOADED]");
		// printf("\n");
		// delay(0.1);
		// printf_color_fg_bg(8,0,"[SOUND LOADED]");
		// printf("\n");
		// delay(0.1);
		// printf_color_fg_bg(9,0,"[ATA LOADED]");
		// printf("\n");
		// delay(0.1);
		// printf_color_fg_bg(10,0,"[MOUSE READY]");
		// printf("\n");
		// delay(0.1);
		// printf_color_fg_bg(11,0,"[KEYBOARD READY]");
		// printf("\n");
		// delay(0.1);
		// printf_color_fg_bg(12,0,"[LIBRARIES SET]");
		// printf("\n");
		// delay(0.1);
		// printf_color_fg_bg(13,0,"[TERMINAL INITALIZED]");
		// update_cursor(terminal_row,terminal_column);
		// printf("\n");
		// printf("TERMIAL WILL RUN SOON!");
		// delay(2.1);
		cls();
		this->print_logo();
		printf("\n\n\n");
		while(true)
		{
		   printf_color_fg_bg(2,0,"root@boneos / ");
		   get_scan_code_terminal();
		   enter_fini:
		   printf("\nCommand Not Found\n");
	    }
}

void OnKeyUp(uint8_t scancode)
{
	
}
void control_key_handler()
{

}

/*
char* val_terminal = (char)0;
uint32_t val_terminal_index = 0;

*/
void OnKeyDown(uint8_t scancode)
{
	uint8_t letter_key_press=(char)0;
	bool pressed_recognize = false;
	//printf("%d" , (int)scancode);
	if(scancode == 29)
	{
		//backspace_offset++;
		control_key_handler();
	}
	if(scancode == 28)
	{
		printf("Enter Pressed");
	}
	else if(scancode == 42)
	{
		int h; // Not Needed / Shi
	}
	else if((int) scancode>=16 && (int) scancode <= 50 && (!( scancode > 27 && scancode <30 )) && (!(scancode>41 && scancode<43)))
	{
		char* val_ptr;
		backspace_offset++;
		pressed_recognize = true;
		uint8_t letter_key_press = return_pressed_letter(scancode);
		val_ptr[0] = letter_key_press;

		increase_val_term(val_ptr[0]);
	    printf("%c" , letter_key_press);
	}
	else if(scancode == 12)
	{
		backspace_offset++;
		pressed_recognize = true;
		if(shift==false)
		{
			//increase_val_term('-');
			printf("-");
		}
		else
		{
			//increase_val_term('_');
			printf("_");
		}

	}
	else if(scancode == 13)
	{
		backspace_offset++;
		pressed_recognize = true;
		if(shift==false)
		{
			//increase_val_term('=');
			printf("=");
		}
		else
		{
			//increase_val_term('+');
			printf("+");
		}
	}
	else if(scancode == 14)
	{
		if(!(backspace_offset==0))
		{
			backspace_offset--;
			pressed_recognize = true;
			printf("\b");
		}
		
	}

	else if(scancode == 15)
	{
		backspace_offset++;
		pressed_recognize = true;
		// for(int32_t t=0;t<=3;t++)
		// {
		// 	val_terminal[val_terminal_index] = ' ';
		// 	val_terminal_index++;
		// }
		printf("\t");
	}
	else if(scancode == 52)
	{
		backspace_offset++;
		pressed_recognize = true;
		if(shift==false)
		{
			//increase_val_term('.');
			printf(".");
		}
		else
		{
			//increase_val_term('>');
			printf(">");
		}
	}

	else if(scancode == 91)
	{
		//Windows Key :)
	}

	else if(scancode >= 1 && scancode <= 11)
	{
		backspace_offset++;
		pressed_recognize = true;
		control_char();
	}
	
	else if(scancode == 57)
	{
		backspace_offset++;
		pressed_recognize = true;
		//increase_val_term(' ');
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
		    	{
		    		printf("Enter Pressed");
		    		break;
		    	}
		    	OnKeyDown(scancode_term);
		    }
				
		}
	}
  done:;	
}	