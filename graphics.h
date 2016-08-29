#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_ 1

#include <stddef.h>
#include <stdint.h>
#include "port.h"
#include "stdio.h"
#include "color.h"
#include "math.h"


/*
 * @class VideoGraphicsArray VGA Head
 *
 *  The VideoGraphicsArray class contains
 *  the necessary utilities to start
 *  graphics mode of-course on VGA
 *
 * @example
 * 	 VideoGraphicsArray <instance>;
 * 	 <instance>.SetMode(<width>,<height>,<color-depth>);
 * 	 <instance>.<function>({parameters});
 *
 */

class VideoGraphicsArray
{

        public:
            VideoGraphicsArray();
            ~VideoGraphicsArray();

            /*
             * @function SupportsMode : Checks Compatibility
             *
             * 	This Function Checks if the Screen Size and
             * 	Color Depth is compatible to what we have
             * 	available. As of right now, we only have
             * 	320*200 width and height respectively, and a
             * 	color depth of 8.
             *
             * @function SetMode : Switches to VGA Mode
             *
             *	This Function Switches to VGA Mode. You must ive it
             *	a supported width height and color depth so it actually
             *	switches to VGA Mode.
             *
             * @function PutPixel : Puts Pixel
             *
             *	This Function Serves as puting a single pixel in the screen.
             *	Only Purpose. PolyMorphed by RGB Or Hex.
             *
             * @function Fill Rectangle : Fills a Rectangle
             *
             *	Fills a rectangle based on giving it Starting Coordinates(x,y)
             *	width, height , {{r,g,b} , colorHex}.
             *
             *	@example:
             *		<VideoGraphicsArrayInstance>.FillRectangle(150,150,50,50,0x23);
             *
             *	@function DrawMouse
             *
             *		Self Explanatory Draws Mouse on the screen
             *
             *		@params uint8_t colorHex:
             *
             *			What Hex Color To Draw the Mouse
             *
             *	@function DrawLine
             *
             *		Draws Line Given Endpoints x1,y1 being the beggining
             *		coordinates and x2,y2 being the end coordinates. Ofcourse
             *		With color of your choice by changing colorHex
             *
             */
            bool SupportsMode(uint32_t width, uint32_t height, uint32_t colordepth);
            bool SetMode(uint32_t width, uint32_t height, uint32_t colordepth);
            void PutPixel(int32_t x, int32_t y,  RGB rgb);
            void PutPixel(int32_t x, int32_t y, uint8_t colorIndex);

            void FillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, RGB rgb);
            void FillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t colorHex);

            void DrawMouse(uint8_t colorHex);

            void DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint8_t colorHex);

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
            /*
             * @instance Port8Bits : Ports
             *
             * 	Ports that aid to switching
             * 	to VGA Mode. The Alternative
             * 	from int 0x13; and going to
             * 	Real Mode or Virtual 8086 Mode
             *
             *	@instance Resolutions res
             *
             *	 instance used in the class
             *	 to give info about all the
             *	 resolutions available!
             */
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

            /* @function WriteRegisters : Writing to Ports
             *
             * Write Registers Function Serves to write register
             * data identified in Resolutions struct with instance <res>
             * to the ports identified. For Example the Miscellaneous
             * Port, Sequencer Ports, etc . . .
             *
             * @param uint8_t* register_
             *   Array That contains the
             *   data needed for the
             *   "port initalization".
             *
             */
            void WriteRegisters(uint8_t* register_);
            uint8_t* GetFrameBufferSegment();

            /* @function GetColorIndex : Get Hex
             *
             * 	function that gives the color index
             * 	or Hex from a RGB Formatted Color.
             * 	Usefull to graphics mode programming.
             *
             * @param uint8_t r : Red Buffer
             * @param uint8_t g : Green Buffer
             * @param uint8_t b : Blue Buffer
             */
            uint8_t GetColorIndex(RGB rgb);

};


#endif
