#include "mouse.h"


typedef void(*regs_func)(struct regs *r);

extern void install_handler_irq(int irq, regs_func handler);

static PORT::Port8Bits p8b_mouse_drv;


void mouse_ps2_handler(struct regs *r)
{
  printf("IRQ 12 \n ");
}
void mouse_wait(unsigned char type)
{
  unsigned int _time_out=100000;
  if(type==0)
  {
    while(_time_out--) //Data
    {
      if((p8b_mouse_drv.in(0x64) & 1)==1)
      {
        return;
      }
    }
    return;
  }
  else
  {
    while(_time_out--) //Signal
    {
      if((p8b_mouse_drv.in(0x64) & 2)==0)
      {
        return;
      }
    }
    return;
  }
}

unsigned char mouse_read()
{
//Get response from mouse
mouse_wait(0);
return p8b_mouse_drv.in(0x60);
}


void mouse_write(unsigned char a_write)
{
//Wait to be able to send a command
mouse_wait(1);
//Tell the mouse we are sending a command
p8b_mouse_drv.out(0xD4,0x64);
//Wait for the final part
mouse_wait(1);
//Finally write
p8b_mouse_drv.out(a_write,0x60);
}

void MOUSE::install_mouse_driver()
{
   mouse_wait(1);
   p8b_mouse_drv.out(0xA8,0x64);

   mouse_wait(1);
	p8b_mouse_drv.out(0x20,0x64);

	unsigned char status_byte;
	mouse_wait(0);
	status_byte = (p8b_mouse_drv.in(0x60) | 2);


	mouse_wait(1);
	p8b_mouse_drv.out(0x60,0x64);


	mouse_wait(1);
	p8b_mouse_drv.out(status_byte,0x60);


	mouse_write(0xF6);
	mouse_read();

	mouse_write(0xF4);
	mouse_read();

  	install_handler_irq(12, mouse_ps2_handler);
}