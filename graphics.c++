#include "graphics.h"

#define RES_1_WIDTH 320
#define RES_1_HEIGHT 200
#define RES_1_COLORDEPTH 8

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

uint8_t VideoGraphicsArray::GetColorIndex(uint8_t r, uint8_t g, uint8_t b)
{
    if(r == 0x00 && g == 0x00 && b == 0x00) return 0x00; // black
    if(r == 0x00 && g == 0x00 && b == 0xA8) return 0x01; // blue
    if(r == 0x00 && g == 0xA8 && b == 0x00) return 0x02; // green
    if(r == 0xA8 && g == 0x00 && b == 0x00) return 0x04; // red
    if(r == 0xFF && g == 0xFF && b == 0xFF) return 0x3F; // white
	return ((r<<16) | (g<<8) | b);
}

void VideoGraphicsArray::PutPixel(int32_t x, int32_t y,  uint8_t r, uint8_t g, uint8_t b)
{
    PutPixel(x,y, GetColorIndex(r,g,b));

}

void VideoGraphicsArray::DrawMouse(uint8_t colorHex)
{
	 for(int y=20; y<=25; y++)
	                	for(int x=19; x<=21; x++)
	                		this->PutPixel(x,y,colorHex);

	        this->PutPixel(20.9,15,colorHex); //top
	        this->PutPixel(24.9,20.5,colorHex); //right
	        this->PutPixel(16.9,20.5,colorHex); //left

	        for(int32_t i = 16.9; i<=24.9; i++)
	        	this->PutPixel(i,20.5,colorHex);


	        this->PutPixel(23.9,19.5,colorHex); //right
	        /**/this->PutPixel(23.4,19.0,colorHex); //right
	        this->PutPixel(22.9,18.5,colorHex); //right
	        /**/this->PutPixel(22.4,18.0,colorHex); //right
	        this->PutPixel(21.9,17.5,colorHex); //right
	        /**/this->PutPixel(21.4,17.0,colorHex); //right
	        this->PutPixel(20.9,16.5,colorHex); //top
	        /**/this->PutPixel(20.4,16.0,colorHex); //right

	        this->PutPixel(17.9,19.5,colorHex);
	        /**/this->PutPixel(17.6,19.2,colorHex);
	        /**/this->PutPixel(17.4,19.0,colorHex);
	        /**/this->PutPixel(17.0,18.6,colorHex);
	        this->PutPixel(18.9,18.5,colorHex);
	        /**/this->PutPixel(18.4,18.0,colorHex);
	        /**/this->PutPixel(18.0,17.6,colorHex);
	        this->PutPixel(19.9,17.5,colorHex);
	        /**/this->PutPixel(19.4,17.0,colorHex);
	        /**/this->PutPixel(19.0,16.6,colorHex);
	        this->PutPixel(20.9,16.5,colorHex);
	        /**/this->PutPixel(20.4,16.0,colorHex);
	        /**/this->PutPixel(20.0,15.6,colorHex);
}

void VideoGraphicsArray::FillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h,   uint8_t r, uint8_t g, uint8_t b)
{
    for(uint32_t Y = y; Y < y+h; Y++)
        for(uint32_t X = x; X < x+w; X++)
            PutPixel(X, Y, r, g, b);
}

void VideoGraphicsArray::FillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t colorHex)
{
    for(uint32_t Y = y; Y < y+h; Y++)
        for(uint32_t X = x; X < x+w; X++)
            PutPixel(X, Y, colorHex);
}
