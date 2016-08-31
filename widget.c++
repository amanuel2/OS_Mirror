#include "widget.h"

void Widget::__constructor__(int32_t x,int32_t y,int32_t w,
		   int32_t h,uint8_t colorBackground)
{
	this->x = x;
	this->y = y;
	this->h = h;
	this->w = w;
	this->colorBack = colorBackground;

	this->DRAW_ORIGINAL_WIDGET(x,y,w,h,colorBackground);
}
Widget::Widget(int32_t x,int32_t y,int32_t w,
		   int32_t h,uint8_t colorBackground)
{

	this->__constructor__(x,y,w,h,colorBackground);
}

Widget::Widget(int32_t x,int32_t y,int32_t w,
			   int32_t h,RGB rgb_back)
{
	this->__constructor__(x,y,w,h,gr->GetColorIndex(rgb_back));

}

void Widget::DRAW_ORIGINAL_WIDGET(int32_t x,int32_t y,int32_t w,
			   int32_t h,uint8_t colorBackground)
{
	this->gr->FillRectangle(x,y,w,h,colorBackground);
}


Widget::~Widget(void)
{
}
