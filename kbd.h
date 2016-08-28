#ifndef _KBD_H_
#define _KBD_H_ 1

#include "stdio.h"
#include "port.h"
#include "serial.h"
#include "string.h"

typedef void(*regs_func)(struct regs *r);

struct enter_pressed_structure
{
     int bit;
     char* value;
};

namespace KBD_NAME
{
	void OnKeyDown(uint8_t scancode);
	void OnKeyUp(uint8_t scancode);
	void keyboard_handler(struct regs *r);
}
class KBD
{
public:
	void install_kbd_driver();
};


#endif
