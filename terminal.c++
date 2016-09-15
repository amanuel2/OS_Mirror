#include "terminal.h"



extern size_t terminal_row;
extern size_t terminal_column;
extern void terminal_bg_fg_ccolor(size_t width, size_t height, int bg, int fg);
extern void pong_color(int pong_ping);
extern void update_cursor(int row, int col);
extern void clear_color();
extern void printf_color_fg_bg(int fg,int bg, char* str);

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
	void Terminal::initalize(uint8_t FLAGS)
	{
		printf_color_fg_bg(1,0,"[GDT LOADED]");
		printf("\n");
		delay(0.1);
		printf_color_fg_bg(2,0,"[IRQ'S LOADED]");
		printf("\n");
		delay(0.1);
		printf_color_fg_bg(3,0,"[ISR'S LOADED]");
		printf("\n");
		delay(0.1);
		printf_color_fg_bg(4,0,"[IDT  LOADED]");
		printf("\n");
		delay(0.1);
		printf_color_fg_bg(5,0,"[INTERRUPTS READY]");
		printf("\n");
		delay(0.1);
		printf_color_fg_bg(6,0,"[GRAPHICS LOADED]");
		printf("\n");
		delay(0.1);
		printf_color_fg_bg(7,0,"[TIME LOADED]");
		printf("\n");
		delay(0.1);
		printf_color_fg_bg(8,0,"[SOUND LOADED]");
		printf("\n");
		delay(0.1);
		printf_color_fg_bg(9,0,"[ATA LOADED]");
		printf("\n");
		delay(0.1);
		printf_color_fg_bg(10,0,"[MOUSE READY]");
		printf("\n");
		delay(0.1);
		printf_color_fg_bg(11,0,"[KEYBOARD READY]");
		printf("\n");
		delay(0.1);
		printf_color_fg_bg(12,0,"[LIBRARIES SET]");
		printf("\n");
		delay(0.1);
		printf_color_fg_bg(13,0,"[TERMINAL INITALIZED]");
		update_cursor(terminal_row,terminal_column);
		printf("\n");
		printf("TERMIAL WILL RUN SOON!");
		delay(2.1);
		cls();
		this->print_logo();
		printf("\n\n\n");
		printf_color_fg_bg(2,0,"root@boneos / ");
	}