#ifndef _WIDGET_H_
#define _WIDGET_H_ 1

#include <stdarg.h>
#include <stdint.h>
#include "graphicsctx.h"
#include "color.h"

/*
 * @class Widget
 *
 * 	 Class Used To Create Widget or
 *   'Gadget' in Windows.
 *
 */
class Widget
{
public:
	/*
	 * @constructor Widget
	 * 	 Sets Protected Members
	 * 	 	@member x,y,w,h
	 * 	 	@member backgroud
	 * 	 	@member Focusable
	 */
	Widget(int32_t x,int32_t y,int32_t w,
		   int32_t h,uint8_t colorBackground);

	Widget(int32_t x,int32_t y,int32_t w,
			   int32_t h,RGB rgb_back);

	/*
	 * @deconstructor
	 * 	Converts Folowing Members
	 * 	to NULLPTR
	 * 		@member x,y,w,h
	 * 	 	@member r,g,b
	 * 	 	@member Focusable
	 */
	~Widget();

private:

	void __constructor__(int32_t x,int32_t y,int32_t w,
			   int32_t h,uint8_t colorBackground);

	void DRAW_ORIGINAL_WIDGET(int32_t x,int32_t y,int32_t w,
			   int32_t h,uint8_t colorBackground);

	int32_t x;
	int32_t y;
	int32_t w;
	int32_t h;

	GraphicsContext *gr;
	uint8_t colorBack;
};
#endif
