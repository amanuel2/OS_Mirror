#include "guiletter.h"

static SerialPort sp;

GUI_Letter::GUI_Letter()
{

}
GUI_Letter::~GUI_Letter()
{

}


void GUI_Letter::GUI_Letter::Draw_Letter(uint8_t letter,uint32_t x , uint32_t y, uint32_t height,
		uint32_t width,uint8_t colorHex,bool e)
{
	switch(letter)
	{
	case 'a':
		this->gtx.DrawLine(x,y,x,y+height,colorHex,e);
		this->gtx.DrawLine(x,y+height,x+width,y+height,colorHex,e);
		this->gtx.DrawLine(x+width,y+height,x+width,y,colorHex,e);
		this->gtx.DrawLine(x+width,y,x,y,colorHex,e);
		this->gtx.DrawLine(x+width,y, (x+width + (width/2)) , y+height , colorHex,e);
		break;
	case 'b':
		this->gtx.DrawLine(x,y,x,y+height,colorHex,e);
		break;
	case 'c':
		break;
	case 'd':
		break;
	case 'e':
		break;
	case 'f':
		break;
	case 'g':
		break;
	case 'h':
		break;
	case 'i':
		break;
	case 'j':
		break;
	case 'k':
		break;
	case 'l':
		break;
	case 'm':
		break;
	case 'n':
		break;
	case 'o':
		break;
	case 'p':
		break;
	case 'q':
		break;
	case 'r':
		break;
	case 's':
		break;
	case 't':
		break;
	case 'u':
		break;
	case 'v':
		break;
	case 'w':
		break;
	case 'x':
		break;
	case 'y':
		break;
	case 'z':
		break;
	default:
		printf("LETTER NOT FOUND");
		while(true);
	}
}
