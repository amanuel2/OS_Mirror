#include "terminal.h"



extern size_t terminal_row;
extern size_t terminal_column;
extern void terminal_bg_fg_ccolor(size_t width, size_t height, int bg, int fg);
extern void pong_color(int pong_ping);
extern void update_cursor(int row, int col);
extern void clear_color();

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
		printf_color(0x10," ************     **********       **       * 	 ********		");
		printf("\n");
		printf_color(0x10," *		  *     *	    *       * *      *      *				");
		printf("\n");
		printf_color(0x10," *		  *     *	    *       *  *     *      *				");
		printf("\n");
		printf_color(0x10," *	  	*     *	    *       *   *    *      *					");
		printf("\n");
		printf_color(0x10," *   ********     *	    *       *    *   *      *****		    ");
		printf("\n");
		printf_color(0x10," *	  	*     *	    *       *     *  *      *					");
		printf("\n");
		printf_color(0x10," *	  	*     *	    *       *      * *      *					");
		printf("\n");
		printf_color(0x10," *	  	*     *	    *       *       **      *					");
		printf("\n");
		printf_color(0x10," ************     **********       *        *      ******** 	");
		printf("\n");
	}
	void Terminal::initalize(uint8_t FLAGS)
	{
		printf_color(0x20,"[GDT LOADED]");
		printf("\n");
		delay(0.1);
		printf_color(0x30,"[IRQ'S LOADED]");
		printf("\n");
		delay(0.1);
		printf_color(0x40,"[ISR'S LOADED]");
		printf("\n");
		delay(0.1);
		printf_color(0x18,"[IDT  LOADED]");
		printf("\n");
		delay(0.1);
		printf_color(0x15,"[INTERRUPTS READY]");
		printf("\n");
		delay(0.1);
		printf_color(0x13,"[GRAPHICS LOADED]");
		printf("\n");
		delay(0.1);
		printf_color(0x14,"[TIME LOADED]");
		printf("\n");
		delay(0.1);
		printf_color(0x15,"[SOUND LOADED]");
		printf("\n");
		delay(0.1);
		printf_color(0x16,"[ATA LOADED]");
		printf("\n");
		delay(0.1);
		printf_color(0x17,"[TERMINAL INITALIZED]");
		update_cursor(terminal_row,terminal_column);
		printf("\n");
		printf("TERMIAL WILL RUN SOON!");
		delay(2.1);
		cls();
		this->print_logo();
	}