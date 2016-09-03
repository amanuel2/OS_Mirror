#include "desktop.h"

VideoGraphicsArray vga_desktopD;
//void redraw_desktop();
Desktop::Desktop(uint8_t background)
{
	vga_desktop.SetMode(320,200,8);
	vga_desktop.FillRectangle(0,0,320,200,background);

	Widget widget_f(20,30,120,100,0x00,TOOL_WINDOW_ORIGNAL);


	//vga_desktop.DrawMouse(0x3F);

	this->background_desktop = background;
}

Desktop::~Desktop()
{

}

void redraw_desktop(int x, int y)
{
		vga_desktopD.FillRectangle(0,0,320,200,0x23);
		vga_desktopD.FillRectangle(x,y,10,10,0x10);
		Widget widget_f(20,30,120,100,0x00,TOOL_WINDOW_ORIGNAL);
}
