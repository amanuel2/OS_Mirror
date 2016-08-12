#include "vga.h"

Vga::Vga()
{

}


Vga::~Vga()
{

}

inline uint8_t Vga::make_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

inline uint16_t Vga::make_vgaentry(char c, uint8_t color)
{

	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}
