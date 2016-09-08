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
		this->gtx.DrawLine(x,y,x,y+height,colorHex,e);
		this->gtx.DrawLine(x+width,y,x,y+height/2,colorHex,e);
		this->gtx.DrawLine(x,y+height/2,x+width,y+height,colorHex,e);
		break;
	case 'l':
		this->gtx.DrawLine(x,y,x,y+height,colorHex,e);
		break;
	case 'm':
		this->gtx.DrawLine(x,y,x,y+height,colorHex,e);
		this->gtx.DrawLine(x,y,x+width/2,y,colorHex,e);
		this->gtx.DrawLine(x+width/2,y,x+width/2,y+height,colorHex,e);
		this->gtx.DrawLine(x+width/2,y,x+width,y,colorHex,e);
		this->gtx.DrawLine(x+width,y,x+width,y+height,colorHex,e);
		break;
	case 'n':
		this->gtx.DrawLine(x,y,x,y+height,colorHex,e);
		this->gtx.DrawLine(x,y,x+width,y,colorHex,e);
		this->gtx.DrawLine(x+width,y,x+width,y+height,colorHex,e);
		break;
	case 'o':
		this->gtx.DrawLine(x,y,x,y+height,colorHex,e);
				this->gtx.DrawLine(x,y,x+width,y,colorHex,e);
				this->gtx.DrawLine(x+width,y,x+width,y+height,colorHex,e);
				this->gtx.DrawLine(x,y+height,x+width,y+height,colorHex,e);
		break;
	case 'p':
		this->gtx.DrawLine(x,y,x,y+height,colorHex,e);
				this->gtx.DrawLine(x,y,x+width,y,colorHex,e);
				this->gtx.DrawLine(x+width,y,x+width,y+height/2,colorHex,e);
				this->gtx.DrawLine(x+width,y+height/2,x,y+height/2,colorHex,e);
		break;
	case 'q':
		this->gtx.DrawLine(x+width,y,x+width,y+height,colorHex,e);
		this->gtx.DrawLine(x,y,x+width,y,colorHex,e);
		this->gtx.DrawLine(x,y,x,y+height/2,colorHex,e);
		this->gtx.DrawLine(x,y+height/2,x+width,y+height/2,colorHex,e);
		break;
	case 'r':
		this->gtx.DrawLine(x,y,x,y+height,colorHex,e);
		this->gtx.DrawLine(x,y+height/2,x+width/2,y,colorHex,e);
		this->gtx.DrawLine(x+width/2,y,x+width,y,colorHex,e);
		break;
	case 's':
		this->gtx.DrawLine(x,y,x+width,y,colorHex,e);
		this->gtx.DrawLine(x,y,x,y+height/2,colorHex,e);
		this->gtx.DrawLine(x,y+height/2,x+width,y+height/2,colorHex,e);
		this->gtx.DrawLine(x+width,y+height/2,x+width,y+height,colorHex,e);
		this->gtx.DrawLine(x+width,y+height,x,y+height,colorHex,e);
		break;
	case 't':
			this->gtx.DrawLine(x,y,x+width,y,colorHex,e);
			this->gtx.DrawLine(x+width/2,y,x+width/2,y+height,colorHex,e);
			break;
		case 'u':
			this->gtx.DrawLine(x,y,x,y+height,colorHex,e);
			this->gtx.DrawLine(x,y+height,x+width,y+height,colorHex,e);
			this->gtx.DrawLine(x+width,y+height,x+width,y,colorHex,e);
			break;
		case 'v':
			this->gtx.DrawLine(x, y, x + (width / 2), y + height, colorHex, e);
			this->gtx.DrawLine(x + width, y, x + (width / 2), y + height, colorHex, e);
			break;
		case 'w':
			this->gtx.DrawLine(x,y,x+width/2.5,y+height,colorHex,e);
			this->gtx.DrawLine(x+width/2.5,y+height,x+width/1.5,y+height/2,colorHex,e);
			this->gtx.DrawLine(x+width/1.5,y+height/2,x+width,y+height,colorHex,e);
			this->gtx.DrawLine(x+width,y+height,(x+((width*2))/1.5),y,colorHex,e);
//			this->gtx.DrawLine(x+width/3,y+height,x+width/2,y+height/2,colorHex,e);
//			this->gtx.DrawLine(x+width/2,y+height/2,x+width/1.2,y+height,colorHex,e);
//			this->gtx.DrawLine(x+width/1.2,y+height,x+width,y,colorHex,e);
			break;
		case 'x':
			this->gtx.DrawLine(x, y, x + width, y + height, colorHex, e);
			this->gtx.DrawLine(x, y + height, x + width, y, colorHex, e);
			break;
		case 'y':
			this->gtx.DrawLine(x, y, x + (width / 2), y + (height / 2), colorHex, e);
			this->gtx.DrawLine(x + width, y, x, y + height, colorHex, e);
			break;
		case 'z':
			this->gtx.DrawLine(x, y, x + width, y, colorHex, e);
			this->gtx.DrawLine(x + width, y, x, y + height, colorHex, e);
			this->gtx.DrawLine(x, y + height, x + width, y + height, colorHex, e);
			break;
	default:
		printf("LETTER NOT FOUND");
		while(true);
	}
}
