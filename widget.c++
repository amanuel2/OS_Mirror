#include "widget.h"

#define TOOL_WINDOW_ORIGNAL 0x1 << 0

SerialPort sp;

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

void Widget::__constructor__()
{
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

void Widget::DrawForMouse()
{
	this->__constructor__(this->x,this->y,this->w,this->h,this->colorBack,this->GIVEN_FLAGS);
}

bool Widget::ContainsCoordinate(int x, int y)
{
	return ( x >= this->x && x<= this->w + this->x && y>= this->y && y<= this->h + this->y);

}

void Widget::DRAW_ORIGINAL_WIDGET()
{
	this->gr->FillRectangle(this->x,this->y,this->w,this->h,this->colorBack);

	if(this->GIVEN_FLAGS & TOOL_WINDOW_ORIGNAL)
		this->DRAW_ORIGINAL_TOOLWINDOW();

}

bool Widget::CheckFlags(uint8_t FlagCheck)
{
	return (this->GIVEN_FLAGS & FlagCheck);
}

void Widget::DeletePrevious()
{
	this->gr->FillRectangle(this->x,this->y,this->w,this->h,0x23);
}

void Widget::ReDraw(int x, int y)
{
	this->DeletePrevious();
	this->__constructor__(x,y,this->w,this->h,this->colorBack,this->GIVEN_FLAGS);
	this->x = x;
	this->y = y;
}
void Widget::DRAW_ORIGINAL_TOOLS()
{
	this->Draw_Minimize_Tool(0x15,0x29);
	this->Draw_Exit_Tool(0x15,0x2C);
	this->Draw_Add_Tool(0x15,0x06);
}


void Widget::Draw_Minimize_Tool(uint8_t background_color,uint8_t foreground_color)
{
	this->gr->FillRectangle(((this->w+this->x)-(this->w/7)),this->y,(this->w/7),(this->h/6),background_color);
	//Drawing Minimize Button
	this->gr->FillRectangle(((this->w+this->x)-(this->w/7)),(this->y+(this->h/16)),(this->w/7),
			(this->h/12),foreground_color);
}

bool Widget::Exit_Clicked(int x, int y)
{
	return ( x >= ((this->x)) && x<= (this->w/7) + this->x && y>= this->y && y<= (this->h/6) + this->y);
}
void Widget::Draw_Exit_Tool(uint8_t background_color,uint8_t foreground_color)
{
	this->gr->FillRectangle(((this->x)),this->y,(this->w/7),(this->h/6),background_color);
	//start from bottom
	this->gr->DrawLine( (this->x + (this->w/7)),(this->y),(this->x),((this->y)+(this->h/6)),foreground_color,false);
	//start from top
	this->gr->DrawLine( (this->x + (this->w/7)),(this->y+(this->h/6)),(this->x),((this->y)),foreground_color,false);
}
void Widget::Draw_Add_Tool(uint8_t background_color,uint8_t foreground_color)
{
	this->gr->FillRectangle(((this->w+this->x)-(this->w/3.5)),this->y,(this->w/7),(this->h/6),background_color);

	this->gr->DrawLine( (((this->w+this->x)-(this->w/3.5)) + ( (this->w/7) /2)) , (this->y+(this->h/6) - 1),
			(((this->w+this->x)-(this->w/3.5)) + ((this->w/7)/2)) ,
						(this->y) , foreground_color, false);

	this->gr->DrawLine(
			((this->w+this->x)-(this->w/3.5)),
			(this->y + (this->h/12)) ,
			(((this->w+this->x)-(this->w/3.5))) + (this->w/7),
			(this->y + (this->h/12)),
			foreground_color,
			false);
}

bool Widget::Add_Clicked(int x, int y)
{
	return ( x >= (((this->w+this->x)-(this->w/3.5)))
			&& x<= ((this->w/7) + (((this->w+this->x)-(this->w/3.5))))
			&& y>= this->y && y<= (this->h/6) + this->y);
}
void Widget::DRAW_ORIGINAL_TOOLWINDOW()
{
	this->gr->FillRectangle(this->x,this->y,this->w,(this->h/6),0x3F);
	this->DRAW_ORIGINAL_TOOLS();
}


Widget::~Widget(void)
{
}
