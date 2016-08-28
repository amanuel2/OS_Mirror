#include "widget.h"

Widget::Widget(Widget *parent ,int32_t x,int32_t y,int32_t w,int32_t h,uint8_t r,uint8_t g,uint8_t b)
{
	this->parent = parent;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->r = r;
	this->g = g;
	this->b = b;
	this->Focusable = true;
}

Widget::~Widget(void)
{
	this->parent = nullptr;
	this->x = 0;
	this->y = 0;
	this->w = 0;
	this->h = 0;
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->Focusable = 0;
}
