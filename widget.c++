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


void Widget::Draw(GraphicsContext gtx, uint32_t x, uint32_t y, uint32_t width, uint32_t height,
			  uint8_t colorHex)
{
	//this->ModelToScreen(x,y);
	gtx.FillRectangle(x,y,width,height,colorHex);
}

void Widget::Draw(GraphicsContext gtx, uint32_t x, uint32_t y, uint32_t width, uint32_t height,
			  RGB rgb)
{
	this->Draw(gtx,x,y,width,height,gtx.GetColorIndex(rgb));
}

void Widget::ModelToScreen(uint32_t &x, uint32_t &y)
{
	if(this->parent != 0)
		this->parent->ModelToScreen(x,y);
	x+=this->x;
	x-=this->y;
}

inline bool Widget::ContainsCoordinates(int32_t x, int32_t y)
{
	if (((this->x > x) && ((this->x + this->w) < x)))
		if(((this->y > y) && ((this->y + this->h) < y)))
			return true;
		else
			return false;
	else
		return false;
}

void Widget::GetFocus(Widget *widget)
{
	if(this->parent != 0)
		this->parent->GetFocus(widget);
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
