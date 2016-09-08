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
		this->gtx.DrawLine(x,y+height,x+width,y+height,colorHex,e);
		this->gtx.DrawLine(x+width,y+height,x+width,y+(height/2),colorHex,e);
		this->gtx.DrawLine(x+width,y+(height/2),x,y+(height/2),colorHex,e);
		break;
	case 'c':
		this->gtx.DrawLine(x,y,x,y+height,colorHex,e);
		this->gtx.DrawLine(x,y+height,x+width,y+height,colorHex,e);
		this->gtx.DrawLine(x,y,x+width,y,colorHex,e);
		break;
	case 'd':
		this->gtx.DrawLine(x,y+(height/2),x,y+height,colorHex,e);
		this->gtx.DrawLine(x,y+height,x+width,y+height,colorHex,e);
		this->gtx.DrawLine(x+width,y+height,x+width,y-(height/2),colorHex,e);
		this->gtx.DrawLine(x+width,y+(height/2),x,y+(height/2),colorHex,e);
		this->gtx.DrawLine(x+width,y-(height/2),x+width,y,colorHex,e);
		break;
	case 'e':
		this->gtx.DrawLine(x,y,x,y+(height/1.5),colorHex,e);
		this->gtx.DrawLine(x,y,x+width,y,colorHex,e);
		this->gtx.DrawLine(x+width,y,x+width,y+(height/1.5),colorHex,e);
		this->gtx.DrawLine(x+width,y+(height/1.5),x,y+(height/1.5),colorHex,e);
		this->gtx.DrawLine(x,y+(height/1.5),x,y+height,colorHex,e);
		this->gtx.DrawLine(x,y+height,x+width,y+height,colorHex,e);
		break;
	case 'f':
		this->gtx.DrawLine(x,y,x+(width/2),y,colorHex,e);
		this->gtx.DrawLine(x,y,x,y+height,colorHex,e);
		this->gtx.DrawLine(x-(width/3),y+(height/3),x+(width/3),y+(height/3),colorHex,e);
		break;
	case 'g':
		this->gtx.DrawLine(x,y,x+width,y,colorHex,e);
		this->gtx.DrawLine(x,y,x,y+(height/1.5),colorHex,e);
		this->gtx.DrawLine(x,y+(height/1.5),x+width,y+(height/1.5),colorHex,e);
		this->gtx.DrawLine(x+width,y,x+width,y+(height/1.5),colorHex,e);
		this->gtx.DrawLine(x+width,y,x+width,y+width,colorHex,e);
		this->gtx.DrawLine(x+width,y+height,x,y+height,colorHex,e);
		break;
	case 'h':
		this->gtx.DrawLine(x,y,x,y+(height/1.5),colorHex,e);
		this->gtx.DrawLine(x,y+(height/1.5),x+width/1.5,y+(height/1.5),colorHex,e);
		this->gtx.DrawLine(x+width/1.5,y+(height/1.5),x+width/1.5,y+height,colorHex,e);
		this->gtx.DrawLine(x,y,x,y+height,colorHex,e);
		break;
	case 'i':
		this->gtx.PutPixel(x,y,colorHex);
		this->gtx.DrawLine(x,y+height/2,x,y+height,colorHex,e);
		break;
	case 'j':
		this->gtx.PutPixel(x+width/2,y,colorHex);
		this->gtx.DrawLine(x+width/2,y+height/2,x+width/2,y+height,colorHex,e);
		this->gtx.DrawLine(x+width/2,y+height,x,y+height,colorHex,e);
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
