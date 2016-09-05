#include "desktop.h"

VideoGraphicsArray vga_desktopD;
static SerialPort sp;
//void redraw_desktop();

Widget widget_s(20,30,120,100,0x00,TOOL_WINDOW_ORIGNAL);

Desktop::Desktop(uint8_t background)
{
	vga_desktop.SetMode(320,200,8);
	vga_desktop.FillRectangle(0,0,320,200,background);

	widget_s.__constructor__(20,30,30,30,0x00,TOOL_WINDOW_ORIGNAL);
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
static bool DRAW_REPEATEDLY_WIDGET_MOVED = false;

void redraw_desktop(int x, int y, int w, int h)
{
	vga_desktopD.DrawMouseCross(old_x,old_y,old_w,old_h,0x23,true);
	vga_desktopD.DrawMouseCross(x,y,w,h,0x10,true);

	if(DRAW_REPEATEDLY_WIDGET_MOVED == true)
	{
		widget_s.ReDraw(x,y);
	}

	old_x = x;old_y = y;old_h = h;old_w = w;
}




void redraw_desktop_button_click(int x , int y, bool up)
{
	if(widget_s.ContainsCoordinate(x,y))
	{
		if(up!=true)
		{
			if(widget_s.Exit_Clicked(x,y))
			{
				if(widget_s.CheckFlags(TOOL_WINDOW_ORIGNAL))
					widget_s.DeletePrevious();
			}

			else if(widget_s.Add_Clicked(x,y))
			{
				if(widget_s.CheckFlags(TOOL_WINDOW_ORIGNAL))
					widget_s.DeletePrevious();
			}

			else
			{
				DRAW_REPEATEDLY_WIDGET_MOVED = true;
			}
		}
	}

	if(up==true)
	{
		DRAW_REPEATEDLY_WIDGET_MOVED = false;

	}

}
