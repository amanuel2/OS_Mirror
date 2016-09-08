#include "graphics.h"

#define RES_1_WIDTH 320
#define RES_1_HEIGHT 200
#define RES_1_COLORDEPTH 8


MOUSE_DIMENSIONS_DRAW MDD;

static SerialPort sp;


VideoGraphicsArray::VideoGraphicsArray()
{
}

VideoGraphicsArray::~VideoGraphicsArray()
{
}



void VideoGraphicsArray::WriteRegisters(uint8_t* register_)
{

    //  misc
    miscPort.out(*(register_++),0x3c2);


    // sequencer
    for(uint8_t i = 0; i < 5; i++)
    {
        sequencerIndexPort.out(i,0x3c4);
        sequencerDataPort.out(*(register_++),0x3c5);
    }

    // cathode ray tube controller
    crtcIndexPort.out(0x03,0x3d4);
    crtcDataPort.out(crtcDataPort.in(0x3d5) | 0x80,0x3d5);
    crtcIndexPort.out(0x11,0x3d4);
    crtcDataPort.out(crtcDataPort.in(0x3d5) & ~0x80,0x3d5);

    register_[0x03] = register_[0x03] | 0x80;
    register_[0x11] = register_[0x11] & ~0x80;

    for(uint8_t i = 0; i < 25; i++)
    {
        crtcIndexPort.out(i,0x3d4);
        crtcDataPort.out(*(register_++),0x3d5);
    }

    // graphics controller
    for(uint8_t i = 0; i < 9; i++)
    {
        graphicsControllerIndexPort.out(i,0x3ce);
        graphicsControllerDataPort.out(*(register_++),0x3cf);
    }

    // attribute controller
    for(uint8_t i = 0; i < 21; i++)
    {
        attributeControllerResetPort.in(0x3da);
        attributeControllerIndexPort.out(i,0x3c0);
        attributeControllerWritePort.out(*(register_++),0x3c0);
    }

    attributeControllerResetPort.in(0x3da);
    attributeControllerIndexPort.out(0x20,0x3c0);

}

bool VideoGraphicsArray::SupportsMode(uint32_t width, uint32_t height, uint32_t colordepth)
{
    return width == RES_1_WIDTH && height == RES_1_HEIGHT && colordepth == RES_1_COLORDEPTH;
}

bool VideoGraphicsArray::SetMode(uint32_t width, uint32_t height, uint32_t colordepth)
{
    if(!SupportsMode(width, height, colordepth))
        return false;


    WriteRegisters(res.g_320x200x256);
    return true;
}



uint8_t* VideoGraphicsArray::GetFrameBufferSegment()
{
    graphicsControllerIndexPort.out(0x06,0x3ce);
    uint8_t segmentNumber = graphicsControllerDataPort.in(0x3cf) & (3<<2);
    switch(segmentNumber)
    {
        default:
        case 0<<2: return (uint8_t*)0xC0000000;
        case 1<<2: return (uint8_t*)0xA0000 + 0xC0000000;
        case 2<<2: return (uint8_t*)0xB0000 + 0xC0000000;
        case 3<<2: return (uint8_t*)0xB8000 + 0xC0000000;
    }
}


void VideoGraphicsArray::PutPixel(int32_t x, int32_t y,  uint8_t colorIndex)
{
    if(x < 0 || RES_1_WIDTH <= x
    || y < 0 || RES_1_HEIGHT<= y)
        return;

    uint8_t* pixelAddress = GetFrameBufferSegment() + RES_1_WIDTH*y + x;
    *pixelAddress = colorIndex;
}

void VideoGraphicsArray::PutPixelE(int32_t x, int32_t y,  uint8_t colorIndex)
{
    if(x < 0 || RES_1_WIDTH <= x
    || y < 0 || RES_1_HEIGHT<= y)
        return;

    uint8_t* pixelAddress = GetFrameBufferSegment() + RES_1_WIDTH*y + x;


	    if(
	    		!(*pixelAddress == 0x00 ) && !(*pixelAddress == 0x3F) && !(*pixelAddress == 0x29)
	    		&& !(*pixelAddress == 0x2C) && !(*pixelAddress == 0x15)
				&& !(*pixelAddress == 0x21) && !(*pixelAddress == 0x13)
			 )
	    	*pixelAddress = colorIndex;;

	   // *pixelAddress = colorIndex;


}

void VideoGraphicsArray::PutPixelRestrictBackground(int32_t x, int32_t y,  uint8_t colorIndex)
{
	 if(x < 0 || RES_1_WIDTH <= x
	    || y < 0 || RES_1_HEIGHT<= y)
	        return;

	    uint8_t* pixelAddress = GetFrameBufferSegment() + RES_1_WIDTH*y + x;

		    if(!(*pixelAddress == 0x23))
		    	*pixelAddress = colorIndex;;

}

uint8_t VideoGraphicsArray::GetPixel(int32_t x, int32_t y)
{
    uint8_t* pixelAddress = GetFrameBufferSegment() + RES_1_WIDTH*y + x;

 	return *pixelAddress;
}

uint8_t VideoGraphicsArray::GetColorIndex(RGB rgb)
{
    if(rgb.r == 0x00 && rgb.g == 0x00 && rgb.b == 0x00) return 0x00; // black
    if(rgb.r == 0x00 && rgb.g == 0x00 && rgb.b == 0xA8) return 0x01; // blue
    if(rgb.r == 0x00 && rgb.g == 0xA8 && rgb.b == 0x00) return 0x02; // green
    if(rgb.r == 0xA8 && rgb.g == 0x00 && rgb.b == 0x00) return 0x04; // red
    if(rgb.r == 0xFF && rgb.g == 0xFF && rgb.b == 0xFF) return 0x3F; // white
	return ((rgb.r<<16) | (rgb.g<<8) | rgb.b);
}

void VideoGraphicsArray::PutPixel(int32_t x, int32_t y,RGB rgb)
{
    PutPixel(x,y, GetColorIndex(rgb));

}

void VideoGraphicsArray::DrawMouse(uint8_t colorHex)
{
	MDD.hex_square = colorHex;
	MDD.hex_a_s = colorHex;
	MDD.top_hex = colorHex;
	MDD.right_hex = colorHex;
	MDD.left_hex = colorHex;

	for(MDD.y_square =  MDD.square_ident[0]; MDD.y_square<=MDD.y_square_limit; MDD.y_square++)
	      for(MDD.x_square = MDD.square_ident[1]; MDD.x_square<=MDD.x_square_limit; MDD.x_square++)
	    	  this->PutPixel(MDD.x_square,MDD.y_square,MDD.hex_square);


	 for( ;MDD.i_a_s<=MDD.i_a_s_limit; MDD.i_a_s++)
		 this->PutPixel(MDD.i_a_s,MDD.y_a_s,MDD.hex_a_s);


	 this->PutPixel(MDD.top_x,MDD.top_y,MDD.top_hex); //top
	 this->DrawLine(MDD.right_x1,MDD.right_y1,MDD.right_x2, MDD.right_y2 ,MDD.right_hex,false); //right
	 this->DrawLine(MDD.left_x1,MDD.left_y1,MDD.left_x2, MDD.left_y2 ,MDD.left_hex,false); //left

}


void VideoGraphicsArray::DrawMouse(RGB rgb)
{
	this->DrawMouse(this->GetColorIndex(rgb));
}


void VideoGraphicsArray::DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint8_t colorHex,bool e)
{

  int32_t x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;

  dx=x2-x1;
  dy=y2-y1;
  dx1=math::fabs(dx);
  dy1=math::fabs(dy);
  px=2*dy1-dx1;
  py=2*dx1-dy1;

  if(dy1<=dx1)
  {

	  if(dx>=0)
	  {

	    x=x1;
	    y=y1;
	    xe=x2;

	   }

	   else
	   {
	     x=x2;
	     y=y2;
	     xe=x1;
	   }

	  if(e)
	  this->PutPixelE(x,y,colorHex);
	  else
		  this->PutPixel(x,y,colorHex);

	  for(i=0;x<xe;i++)
	  {
	     x=x+1;
	      if(px<0)
	      {
	    	  px=px+2*dy1;
	      }
	      else
	      {
	    	  if((dx<0 && dy<0) || (dx>0 && dy>0))
	    	  {
	    		  y=y+1;
	    	  }
	    	  else
	    	  {
	    		  y=y-1;
	    	  }
	    	px=px+2*(dy1-dx1);
	      }
	    if(e)
	    PutPixelE(x,y,colorHex);
	    else
	    	PutPixel(x,y,colorHex);
	  }

	 }

	 else
	 {
		 if(dy>=0)
		 {
			 x=x1;
			 y=y1;
			 ye=y2;
		 }
		 else
		 {
			 x=x2;
			 y=y2;
			 ye=y1;
		 }
		 if(e)
		 PutPixelE(x,y,colorHex);
		 else
			 PutPixel(x,y,colorHex);

		 for(i=0;y<ye;i++)
		 {
			 y=y+1;
			 	 if(py<=0)
			 	 {
			 		 py=py+2*dx1;
			 	 }
			 	 else
			 	 {
			 		 if((dx<0 && dy<0) || (dx>0 && dy>0))
			 		 {
			 			 x=x+1;
			 		 }
			 		 else
			 		 {
			 			 x=x-1;
			 		 }

			 	  py=py+2*(dx1-dy1);

			 	 }
			 if(e)
			  PutPixelE(x,y,colorHex);
			 else
				 PutPixel(x,y,colorHex);

		 }

	 }
}


void VideoGraphicsArray::DrawMouseCrossOLD(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
	this->DrawLine(x,y,x,y+h,this->GetPixel(x,y),true);
	this->DrawLine((x-(w/1.9)),(y+(w/2)),((x-(w/1.9))+w),(y+(w/2)), this->GetPixel(x,y),true);
}


void VideoGraphicsArray::DrawMouseCross(uint32_t x, uint32_t y, uint32_t w, uint32_t h , uint8_t colorHex, bool e)
{
	this->DrawLine(x,y,x,y+h,colorHex,e);
	this->DrawLine((x-(w/1.9)),(y+(w/2)),((x-(w/1.9))+w),(y+(w/2)), colorHex,e);
}

void VideoGraphicsArray::FillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h,  RGB rgb)
{
    for(uint32_t Y = y; Y < y+h; Y++)
        for(uint32_t X = x; X < x+w; X++)
            PutPixel(X, Y, rgb);
}

void VideoGraphicsArray::FillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t colorHex)
{
    for(uint32_t Y = y; Y < y+h; Y++)
        for(uint32_t X = x; X < x+w; X++)
            PutPixel(X, Y, colorHex);
}

void VideoGraphicsArray::FillRectangleRestrictBackgroud(uint32_t x, uint32_t y, uint32_t w, uint32_t h,  RGB rgb)
{
    for(uint32_t Y = y; Y < y+h; Y++)
        for(uint32_t X = x; X < x+w; X++)
        	PutPixelRestrictBackground(X, Y, GetColorIndex(rgb));
}

void VideoGraphicsArray::FillRectangleRestrictBackgroud(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t colorHex)
{
    for(uint32_t Y = y; Y < y+h; Y++)
        for(uint32_t X = x; X < x+w; X++)
            PutPixelRestrictBackground(X, Y, colorHex);
}


void VideoGraphicsArray::FillRectangleE(uint32_t x, uint32_t y, uint32_t w, uint32_t h,  RGB rgb)
{
    for(uint32_t Y = y; Y < y+h; Y++)
        for(uint32_t X = x; X < x+w; X++)
        	PutPixelE(X, Y, GetColorIndex(rgb));
}

void VideoGraphicsArray::FillRectangleE(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t colorHex)
{
    for(uint32_t Y = y; Y < y+h; Y++)
        for(uint32_t X = x; X < x+w; X++)
            PutPixelE(X, Y, colorHex);
}
