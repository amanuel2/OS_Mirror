#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_ 1

#include <stddef.h>
#include <stdint.h>
#include "port.h"


class VideoGraphicsArray
{

        public:
            VideoGraphicsArray();
            ~VideoGraphicsArray();

            bool SupportsMode(uint32_t width, uint32_t height, uint32_t colordepth);
            bool SetMode(uint32_t width, uint32_t height, uint32_t colordepth);
            void PutPixel(int32_t x, int32_t y,  uint8_t r, uint8_t g, uint8_t b);
            void PutPixel(int32_t x, int32_t y, uint8_t colorIndex);

            void FillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h,   uint8_t r, uint8_t g, uint8_t b);
            void FillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t colorHex);

            /* only valid for 800x600x32bpp */
        private:
            PORT::Port8Bits miscPort;
            PORT::Port8Bits crtcIndexPort;
            PORT::Port8Bits crtcDataPort;
            PORT::Port8Bits sequencerIndexPort;
            PORT::Port8Bits sequencerDataPort;
            PORT::Port8Bits graphicsControllerIndexPort;
            PORT::Port8Bits graphicsControllerDataPort;
            PORT::Port8Bits attributeControllerIndexPort;
            PORT::Port8Bits attributeControllerReadPort;
            PORT::Port8Bits attributeControllerWritePort;
            PORT::Port8Bits attributeControllerResetPort;

                    void WriteRegisters(uint8_t* registers);
                    uint8_t* GetFrameBufferSegment();

                    uint8_t GetColorIndex(uint8_t r, uint8_t g, uint8_t b);

};


#endif
