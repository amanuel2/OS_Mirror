#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_ 1

#include <stddef.h>
#include <stdint.h>
#include "port.h"
#include "stdio.h"


/*
 *
 */

class VideoGraphicsArray
{

        public:
            VideoGraphicsArray();
            ~VideoGraphicsArray();

            bool SupportsMode(uint32_t width, uint32_t height, uint32_t colordepth);
            bool SetMode(uint32_t width, uint32_t height, uint32_t colordepth);
            void PutPixel(int32_t x, int32_t y,  uint8_t r, uint8_t g, uint8_t b);
            void PutPixel(int32_t x, int32_t y, uint8_t colorIndex);

            void FillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t r, uint8_t g, uint8_t b);
            void FillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t colorHex);

     	   /*
     		* @class Resolutions
     		*
     		* Serves as a storage of all
     		* the diffrent resolutions
     		* data. So we can write this data
     		* to identfied port. Comments Above
     		* WriteRegister Function Explains this
     		*
     		*/

            class Resolutions
            {
            	public:
					 uint8_t g_320x200x256[61] =
					  {
							  /* Miscellaneous */
								0x63,
							  /* Sequencer */
								0x03, 0x01, 0x0F, 0x00, 0x0E,
							  /*Cathode Ray Tube Controller*/
								0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
								0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x9C, 0x0E, 0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3,
								0xFF,
							  /*Graphics Controller*/
								0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
								0xFF,
							  /*Attribute Controller*/
								0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
								0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
								0x41, 0x00, 0x0F, 0x00, 0x00
						};
            };

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
            Resolutions res;

                    void WriteRegisters(uint8_t* register_);
                    uint8_t* GetFrameBufferSegment();

                    uint8_t GetColorIndex(uint8_t r, uint8_t g, uint8_t b);

};


#endif
