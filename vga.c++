#include "vga.h"



uint8_t make_color(int fg, int bg)
{
	return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color)
{

	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}
