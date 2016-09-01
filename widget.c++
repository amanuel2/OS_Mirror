#include "widget.h"

#define TOOL_WINDOW_ORIGNAL 0x1 << 0

void Widget::__constructor__(int32_t x,int32_t y,int32_t w,
		   int32_t h,uint8_t colorBackground,uint32_t FLAGS)
{
	this->x = x;
	this->y = y;
	this->h = h;
	this->w = w;
	this->colorBack = colorBackground;
	this->GIVEN_FLAGS = FLAGS;

	this->DRAW_ORIGINAL_WIDGET();
}
Widget::Widget(int32_t x,int32_t y,int32_t w,
		   int32_t h,uint8_t colorBackground,uint32_t FLAGS)
{

	this->__constructor__(x,y,w,h,colorBackground,FLAGS);
}

Widget::Widget(int32_t x,int32_t y,int32_t w,
			   int32_t h,RGB rgb_back,uint32_t FLAGS)
{
	this->__constructor__(x,y,w,h,gr->GetColorIndex(rgb_back),FLAGS);

}

void Widget::DRAW_ORIGINAL_WIDGET()
{
	this->gr->FillRectangle(this->x,this->y,this->w,this->h,this->colorBack);

	if(this->GIVEN_FLAGS & TOOL_WINDOW_ORIGNAL)
		this->DRAW_ORIGINAL_TOOLWINDOW();

}

void Widget::DRAW_ORIGINAL_TOOLS()
{
	this->Draw_Minimize_Tool(0x15,0x11);
}

void Widget::Draw_Minimize_Tool(uint8_t background_color,uint8_t foreground_color)
{
	this->gr->FillRectangle(((this->w+this->x)-(this->w/7)),this->y,(this->w/7),(this->h/6),background_color);
	//Drawing Minimize Button
	this->gr->FillRectangle(((this->w+this->x)-(this->w/7)),(this->y+(this->h/16)),(this->w/7),(this->h/12),foreground_color);
}

void Widget::DRAW_ORIGINAL_TOOLWINDOW()
{
	this->gr->FillRectangle(this->x,this->y,this->w,(this->h/6),0x3F);
	this->DRAW_ORIGINAL_TOOLS();
}


Widget::~Widget(void)
{
}
