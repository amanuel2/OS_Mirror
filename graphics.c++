#include "graphics.h"


VideoGraphicsArray::VideoGraphicsArray()
{
}

VideoGraphicsArray::~VideoGraphicsArray()
{
}

/* Writing to Ports
 *
 * Write Registers Function Serves to write register
 * data identified in some form of struct or array,
 * to the ports identified. For Example the Miscellaneous
 * Port, Sequencer Ports, etc . . .
 *
 * @param
 *
 */

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
    return width == 320 && height == 200 && colordepth == 8;
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
    if(x < 0 || 320 <= x
    || y < 0 || 200 <= y)
        return;

    uint8_t* pixelAddress = GetFrameBufferSegment() + 320*y + x;
    *pixelAddress = colorIndex;
}

uint8_t VideoGraphicsArray::GetColorIndex(uint8_t r, uint8_t g, uint8_t b)
{
//    if(r == 0x00 && g == 0x00 && b == 0x00) return 0x00; // black
//    if(r == 0x00 && g == 0x00 && b == 0xA8) return 0x01; // blue
//    if(r == 0x00 && g == 0xA8 && b == 0x00) return 0x02; // green
//    if(r == 0xA8 && g == 0x00 && b == 0x00) return 0x04; // red
//    if(r == 0xFF && g == 0xFF && b == 0xFF) return 0x3F; // white
//    return 0x00;
	return ((r<<16) | (g<<8) | b);
}

void VideoGraphicsArray::PutPixel(int32_t x, int32_t y,  uint8_t r, uint8_t g, uint8_t b)
{
    PutPixel(x,y, GetColorIndex(r,g,b));

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
