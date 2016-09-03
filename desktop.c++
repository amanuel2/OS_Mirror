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

static int old_x = 0;
static int old_y = 0;
static int old_w = 0;
static int old_h = 0;

void redraw_desktop(int x, int y, int w, int h)
{
	vga_desktopD.FillRectangle(old_x,old_y,old_w,old_h,0x23);
	vga_desktopD.FillRectangle(x,y,w,h,0x10);

	//Widget widget_f(20,30,120,100,0x00,TOOL_WINDOW_ORIGNAL);
		old_x = x;
		old_y = y;
		old_h = h;
		old_w = w;
}
