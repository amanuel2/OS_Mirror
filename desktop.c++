#include "desktop.h"

VideoGraphicsArray vga_desktopD;
static SerialPort sp;



static const uint32_t default_num_widget=3;

int32_t x_containers[default_num_widget] = {40,70,20};
int32_t y_containers[default_num_widget] = {50,100,30};
int32_t w_containers[default_num_widget] = {70,70,30};
int32_t h_containers[default_num_widget] = {40,30,30};
uint8_t color_back_containers[default_num_widget] = {0x21,0x13,0x00};
uint32_t flags_containers[default_num_widget] = {TOOL_WINDOW_ORIGNAL,TOOL_WINDOW_ORIGNAL , TOOL_WINDOW_ORIGNAL};



Widget widgets[default_num_widget];

Desktop::Desktop(uint8_t background)
{

	vga_desktop.SetMode(320,200,8);
	vga_desktop.FillRectangle(0,0,320,200,background);


	for(uint32_t i=0; i<=default_num_widget-1; i++)
	{
		widgets[i].__constructor__(
										x_containers[i],y_containers[i],
										w_containers[i], h_containers[i],
										color_back_containers[i],
										flags_containers[i]
									);
	}

	this->background_desktop = background;

	gui_letter.Draw_Letter('r',100,160,5,5,0x16,false);

}

Desktop::~Desktop()
{

}

static int old_x = 0;
static int old_y = 0;
static int old_w = 0;
static int old_h = 0;
static bool DRAW_REPEATEDLY_WIDGET_MOVED = false;
static uint32_t index_widget_selected = -1;

void redraw_desktop(int x, int y, int w, int h)
{
	vga_desktopD.DrawMouseCross(old_x,old_y,old_w,old_h,0x23,true);
		vga_desktopD.DrawMouseCross(x,y,w,h,0x10,true);

	if(DRAW_REPEATEDLY_WIDGET_MOVED == true)
	{
		widgets[index_widget_selected].ReDraw(x,y);
	}


	old_x = x;old_y = y;old_h = h;old_w = w;
}




void redraw_desktop_button_click(int x , int y, bool up)
{
	for(uint32_t i=0; i<=default_num_widget-1; i++)
	{
		sp.write_string_serial("New NUM : ");
		sp.write_number_serial(i);
		if(widgets[i].ContainsCoordinate(x,y))
		{
			index_widget_selected = i;
			if(up!=true)
			{
				if(widgets[i].Exit_Clicked(x,y))
				{
					if(widgets[i].CheckFlags(TOOL_WINDOW_ORIGNAL))
						widgets[i].DeletePrevious();
				}

				else if(widgets[i].Add_Clicked(x,y))
				{
					if(widgets[i].CheckFlags(TOOL_WINDOW_ORIGNAL))
						widgets[i].DeletePrevious();
				}

				else
				{
					DRAW_REPEATEDLY_WIDGET_MOVED = true;
				}
			}

			if(up==true)
			{
				DRAW_REPEATEDLY_WIDGET_MOVED = false;
			}
		}
		else
		{
			; // Not it
		}
	}


}
