#ifndef _GUI_LETTER_H_
#define _GUI_LETTER_H_ 1

#include "stdarg.h"
#include "stdint.h"
#include "stdio.h"
#include "serial.h"
#include "graphicsctx.h"

/*
 * @class GUI_Letter
 * 	 Self Built Library Used
 * 	 To Create Letters off
 * 	 Graphics Mode.
 */

typedef void(*void_func)(void);



class GUI_Letter
{

public:
	GUI_Letter();
	~GUI_Letter();


	void Draw_Letter(uint8_t letter,uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);

private:

	GraphicsContext gtx;
	void DrawASmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawBSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawCSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawDSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawESmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawFSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawGSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawHSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawISmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawJSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawKSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawLSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawMSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawNSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawOSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawPSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawQSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawRSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawSSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawTSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawUSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawVSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawWSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawXSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawYSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);
	void DrawZSmall(uint32_t x , uint32_t y, uint32_t dimensions,uint8_t colorHex,bool e);

};

#endif
