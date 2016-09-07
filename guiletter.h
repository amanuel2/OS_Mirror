#ifndef _GUI_LETTER_H_
#define _GUI_LETTER_H_ 1

#include "stdarg.h"
#include "stdint.h"
#include "stdio.h"
#include "serial.h"
#include "graphicsctx.h"

/*
 * @class GUI_Letter
 * 	 Self Built Library Used
 * 	 To Create Letters off
 * 	 Graphics Mode.
 */

typedef void(*void_func)(void);



class GUI_Letter
{

public:
	GUI_Letter();
	~GUI_Letter();


	void Draw_Letter(uint8_t letter,uint32_t x , uint32_t y, uint32_t height,
			uint32_t width,uint8_t colorHex,bool e);

private:

	GraphicsContext gtx;

};

#endif
