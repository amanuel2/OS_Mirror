#ifndef _VGA_H_
#define _VGA_H_ 1

#include <stddef.h>
#include <stdint.h>

uint16_t* VideoMemory =((uint16_t*)0xc00b8000);

const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;


/* Hardware text mode color constants. */
enum vga_color{
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};

vga_color VGA_COLOR;

namespace Vga
{
	uint8_t make_color(int fg, int bg);
	uint16_t make_vgaentry(char c, uint8_t color);
};

#endif
