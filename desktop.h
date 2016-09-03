#ifndef _DESKTOP_H_
#define _DESKTOP_H_ 1

#include "widget.h"
#include "serial.h"
#include "graphicsctx.h"

#ifndef GRAPHICS_MODE
	#define GRAPHICS_MODE
#endif





class Desktop
{
public:
	Desktop(uint8_t background);
	~Desktop();
private:
	uint8_t background_desktop;
	VideoGraphicsArray vga_desktop;
};

#endif
