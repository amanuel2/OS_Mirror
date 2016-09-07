#include "guiletter.h"

static SerialPort sp;

GUI_Letter::GUI_Letter()
{

}
GUI_Letter::~GUI_Letter()
{

}


void GUI_Letter::GUI_Letter::Draw_Letter(uint8_t letter,uint32_t x , uint32_t y, uint32_t dimensions
		, uint8_t colorHex, bool e)
{
	switch(letter)
	{
	case 'a':
		this->DrawASmall(x,y,dimensions,colorHex,e);break;
	case 'b':
		this->DrawBSmall(x,y,dimensions,colorHex,e);break;
	case 'c':
		this->DrawCSmall(x,y,dimensions,colorHex,e);break;
	case 'd':
		this->DrawDSmall(x,y,dimensions,colorHex,e);break;
	case 'e':
		this->DrawESmall(x,y,dimensions,colorHex,e);break;
	case 'f':
		this->DrawFSmall(x,y,dimensions,colorHex,e);break;
	case 'g':
		this->DrawGSmall(x,y,dimensions,colorHex,e);break;
	case 'h':
		this->DrawHSmall(x,y,dimensions,colorHex,e);break;
	case 'i':
		this->DrawISmall(x,y,dimensions,colorHex,e);break;
	case 'j':
		this->DrawJSmall(x,y,dimensions,colorHex,e);break;
	case 'k':
		this->DrawKSmall(x,y,dimensions,colorHex,e);break;
	case 'l':
		this->DrawLSmall(x,y,dimensions,colorHex,e);break;
	case 'm':
		this->DrawMSmall(x,y,dimensions,colorHex,e);break;
	case 'n':
		this->DrawNSmall(x,y,dimensions,colorHex,e);break;
	case 'o':
		this->DrawOSmall(x,y,dimensions,colorHex,e);break;
	case 'p':
		this->DrawPSmall(x,y,dimensions,colorHex,e);break;
	case 'q':
		this->DrawQSmall(x,y,dimensions,colorHex,e);break;
	case 'r':
		this->DrawRSmall(x,y,dimensions,colorHex,e);break;
	case 's':
		this->DrawSSmall(x,y,dimensions,colorHex,e);break;
	case 't':
		this->DrawTSmall(x,y,dimensions,colorHex,e);break;
	case 'u':
		this->DrawUSmall(x,y,dimensions,colorHex,e);break;
	case 'v':
		this->DrawVSmall(x,y,dimensions,colorHex,e);break;
	case 'w':
		this->DrawWSmall(x,y,dimensions,colorHex,e);break;
	case 'x':
		this->DrawXSmall(x,y,dimensions,colorHex,e);break;
	case 'y':
		this->DrawYSmall(x,y,dimensions,colorHex,e);break;
	case 'z':
		this->DrawZSmall(x,y,dimensions,colorHex,e);break;
	default:
		printf("LETTER NOT FOUND");
		while(true);
	}
}

void GUI_Letter::DrawASmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e)
{
	this->gtx.DrawLine( ( x- (dimensions/4) ) , y , x + 5 ,20, colorHex , e );
}
void GUI_Letter::DrawBSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawCSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawDSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawESmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawFSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawGSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawHSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawISmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawJSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawKSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawLSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawMSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawNSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawOSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawPSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawQSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawRSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawSSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawTSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawUSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawVSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawWSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawXSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawYSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
void GUI_Letter::DrawZSmall(uint32_t x , uint32_t y, uint32_t dimensions, uint8_t colorHex,bool e){}
