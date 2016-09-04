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
	vga_desktopD.FillRectangleE(old_x,old_y,old_w,old_h,0x23);
	vga_desktopD.FillRectangleE(x,y,w,h,0x10);

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
	if(up!=true)
	{
		if(old_x_widget_button != -1 && old_y_widget_button != -1)
		{
			sp.write_string_serial("WIDGET X:");
								sp.write_number_serial(old_x_widget_button);
								sp.write_string_serial("MOUSE X:");
															sp.write_number_serial(x);
								sp.write_string_serial("DONE!");
			if(x >= old_x_widget_button && x<= 120 + old_x_widget_button && y >= old_y_widget_button &&
					y <= 100 + old_y_widget_button)
			{

					HOLD_WIDGET = true;

			}
		}
	}
	if(widget_s.ContainsCoordinate(x,y))
	{
		if(up!=true)
		{
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
