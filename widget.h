#ifndef _WIDGET_H_
#define _WIDGET_H_ 1

#include <stdarg.h>
#include <stdint.h>
#include "graphicsctx.h"
#include "color.h"

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


	/*
	 * @function draw
	 * 		Draws A Widget to
	 * 		the screen. given the
	 * 		Graphics Context / VGA
	 *
	 * 		@member GraphicsContext gtx
	 * 			instance of the graphics
	 * 			context needed to draw
	 * 			a widget. VGA As of now
	 *
	 * 		@member x,y,width,height,colorHex
	 * 			Rest of the variables needed to
	 * 			draw the Widget. Information about
	 * 			the Widget
	 *
	 * 		@overide member RGB rgb
	 * 			Allows the framework to have a RGB Color
	 * 			Format
	 *
	 * 	@function ModelToScreen
	 * 		Converts absolute to relative path
	 *
	 * 	@function GetFocus
	 *
	 * 		Adjusts the focus
	 * 		for the widget
	 *
	 */
	void Draw(GraphicsContext gtx, uint32_t x, uint32_t y, uint32_t width, uint32_t height,
			  uint8_t colorHex);

	void Draw(GraphicsContext gtx, uint32_t x, uint32_t y, uint32_t width, uint32_t height,
				  RGB rgb);

	void ModelToScreen(uint8_t &x, uint8_t &y);

	void GetFocus(Widget *widget);

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
