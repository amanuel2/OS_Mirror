#ifndef _VGA_H_
#define _VGA_H_ 1

#include <stddef.h>
#include <stdint.h>
#include "port.h"

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

uint8_t make_color(int fg, int bg);
uint16_t make_vgaentry(char c, uint8_t color);

class VideoGraphicsArray
{

        public:
            VideoGraphicsArray();
            ~VideoGraphicsArray();

            bool SupportsMode(uint32_t width, uint32_t height, uint32_t colordepth);
            bool SetMode(uint32_t width, uint32_t height, uint32_t colordepth);
            void PutPixel(int32_t x, int32_t y,  uint8_t r, uint8_t g, uint8_t b);
            void PutPixel(int32_t x, int32_t y, uint8_t colorIndex);

            void FillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h,   uint8_t r, uint8_t g, uint8_t b);

        private:
            PORT::Port8Bits miscPort;
            PORT::Port8Bits crtcIndexPort;
            PORT::Port8Bits crtcDataPort;
            PORT::Port8Bits sequencerIndexPort;
            PORT::Port8Bits sequencerDataPort;
            PORT::Port8Bits graphicsControllerIndexPort;
            PORT::Port8Bits graphicsControllerDataPort;
            PORT::Port8Bits attributeControllerIndexPort;
            PORT::Port8Bits attributeControllerReadPort;
            PORT::Port8Bits attributeControllerWritePort;
            PORT::Port8Bits attributeControllerResetPort;

                    void WriteRegisters(uint8_t* registers);
                    uint8_t* GetFrameBufferSegment();

                    uint8_t GetColorIndex(uint8_t r, uint8_t g, uint8_t b);

};

#endif
