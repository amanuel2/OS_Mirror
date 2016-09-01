#ifndef _MOUSE_H_
#define _MOUSE_H_ 1

//#define GRAPHICS_MODE 1
#include "stdio.h"
#include "port.h"
#include "stdint.h"
#ifdef GRAPHICS_MODE
	#include "graphicsctx.h"
#endif

typedef uint8_t byte;
typedef int8_t sbyte;
typedef uint32_t dword;


class MOUSE
{
private:
public:
	void install_mouse_driver();
};


#endif
