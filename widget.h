#ifndef _WIDGET_H_
#define _WIDGET_H_ 1

#include <stdarg.h>
#include <stdint.h>
#include "graphicsctx.h"
#include "color.h"
#include "serial.h"

#define TOOL_WINDOW_ORIGNAL 0x1 << 0

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
	 */
	Widget(int32_t x,int32_t y,int32_t w,
		   int32_t h,uint8_t colorBackground
		   ,uint32_t FLAGS);

	Widget(int32_t x,int32_t y,int32_t w,
		   int32_t h,RGB rgb_back
		   ,uint32_t FLAGS);

	/*
	 * @deconstructor
	 * 	Converts Folowing Members
	 * 	to NULLPTR
	 * 		@member x,y,w,h
	 * 	 	@member r,g,b
	 */
	~Widget();

	void __constructor__(int32_t x,int32_t y,int32_t w,
				   int32_t h,uint8_t colorBackground,
				   uint32_t FLAGS);

	void DrawForMouse();
	bool ContainsCoordinate(int x, int y);

	void ReDraw(int x, int y);
	void __constructor__();
	void DeletePrevious();

private:

	/*
	 * @function __constructor__
	 *
	 * 	Gets Treated as constructor.
	 * 	All Contrcturors Call this
	 * 	function
	 *
	 *
	 * 	@param SAME AS ORIGINAL CONTRUCTOR
	 *
	 *
	 *
	 * @function 	DRAW_ORIGINAL_WIDGET
	 *
	 *	Draw Original WIDGET
	 */



	void DRAW_ORIGINAL_WIDGET();

	void DRAW_ORIGINAL_TOOLWINDOW();

	void Draw_Minimize_Tool(uint8_t background_color,uint8_t foreground_color);
	void Draw_Exit_Tool(uint8_t background_color,uint8_t foreground_color);

	void DRAW_ORIGINAL_TOOLS();


	int32_t x;
	int32_t y;
	int32_t w;
	int32_t h;

	GraphicsContext *gr;
	uint8_t colorBack;
	uint32_t GIVEN_FLAGS;
};
#endif
