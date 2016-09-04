#include "desktop.h"

VideoGraphicsArray vga_desktopD;
static SerialPort sp;
//void redraw_desktop();

Widget widget_s(20,30,120,100,0x00,TOOL_WINDOW_ORIGNAL);

Desktop::Desktop(uint8_t background)
{
	vga_desktop.SetMode(320,200,8);
	vga_desktop.FillRectangle(0,0,320,200,background);

	Widget widget_f(20,30,120,100,0x00,TOOL_WINDOW_ORIGNAL);

	//vga_desktop.DrawMouse(0x3F);

	this->background_desktop = background;

	vga_desktop.PutPixelE(50,100,0x32);
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
	vga_desktopD.DrawMouseCross(old_x,old_y,old_w,old_h,vga_desktopD.GetPixel(x,y),true);
	vga_desktopD.DrawMouseCross(x,y,w,h,0x10,true);
//	vga_desktopD.FillRectangleE(old_x,old_y,old_w,old_h,0x23);
//	vga_desktopD.FillRectangleE(x,y,w,h,0x10);

	old_x = x;old_y = y;old_h = h;old_w = w;
}

static bool HOLD_WIDGET = false;

static int old_x_widget_button = -1;
static int old_y_widget_button = -1;

static bool constructor_called_widget_s = false;

void call_widget_constructor()
{
	if(constructor_called_widget_s == false)
	{
		widget_s.__constructor__(20,30,120,100,0x00,TOOL_WINDOW_ORIGNAL);
		constructor_called_widget_s = true;
	}
}

void redraw_desktop_button_click(int x , int y, bool up)
{
	call_widget_constructor();
	if(widget_s.ContainsCoordinate(x,y))
	{
		if(up!=true)
		{
			if(widget_s.Exit_Clicked(x,y))
				widget_s.DeletePrevious();
			else
				HOLD_WIDGET = true;
		}
	}

	if(up==true)
	{
		if(HOLD_WIDGET == true)
		{

			vga_desktopD.FillRectangle(old_x_widget_button,old_y_widget_button,120,100,0x23);

			widget_s.ReDraw(x,y);
			old_x_widget_button = x;
			old_y_widget_button = y;
			HOLD_WIDGET = false;
		}

	}

}
