#ifndef _WIDGET_H_
#define _WIDGET_H_ 1

#include <stdarg.h>
#include <stdint.h>

/*
 * @class Widget
 *
 * 		Class Used To Create Widget or
 * 		'Gadget' in Windows.
 *
 */
class Widget
{
public:
	/*
	 * @constructor Widget
	 * 	 Sets Protected Members
	 * 	 	@member parent
	 * 	 	@member x,y,w,h
	 * 	 	@member r,g,b
	 * 	 	@member Focusable
	 */
	Widget(Widget *parent ,int32_t x,int32_t y,int32_t w,
		   int32_t h,uint8_t r,uint8_t g,uint8_t b);

	/*
	 * @deconstructor
	 * 	Converts Folowing Members
	 * 	to NULLPTR
	 * 		@member parent
	 * 		@member x,y,w,h
	 * 	 	@member r,g,b
	 * 	 	@member Focusable
	 */
	~Widget();

protected:
	Widget *parent;

	int32_t x;
	int32_t y;
	int32_t w;
	int32_t h;

	uint8_t r;
	uint8_t g;
	uint8_t b;
	bool Focusable;
};
#endif
