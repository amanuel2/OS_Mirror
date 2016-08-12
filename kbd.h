#ifndef _KBD_H_
#define _KBD_H_ 1

#include "stdio.h"
#include "port.h"
#include "serial.h"
#include "string.h"



 struct enter_pressed_structure
 {
      int bit;
      char* value;
 };

class KBD
{
private:
public:
	void install_kbd_driver();
};


#endif
