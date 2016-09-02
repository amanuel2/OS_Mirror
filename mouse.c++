#include "mouse.h"


typedef void(*regs_func)(struct regs *r);

extern void install_handler_irq(int irq, regs_func handler);

static PORT::Port8Bits p8b_mouse_drv;

#ifdef GRAPHICS_MODE
	GraphicsContext gtx;
#endif


inline void mouse_wait(byte a_type) //unsigned char
{
	 dword _time_out=100000; //unsigned int
	  if(a_type==0)
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

inline void mouse_write(byte a_write) //unsigned char
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

byte mouse_read()
{
  //Get's response from mouse
  mouse_wait(0);
  return p8b_mouse_drv.in(0x60);
}




//static int count = 0;
//static byte mouse_cycle=0;     //unsigned char
//static sbyte mouse_byte[3];    //signed char
//static int32_t mouse_x=0;         //signed char
//static int32_t mouse_y=0;         //signed char


static uint8_t buffer[3]={0};
static uint8_t offset=0;
static int8_t x, y;

//Mouse functions
void mouse_ps2_handler(struct regs *a_r) //struct regs *a_r (not used but just there)
{

    uint8_t status = p8b_mouse_drv.in(0x64);
    	if (!(status & 0x20))
    		goto end;

    	 buffer[offset] = p8b_mouse_drv.in(0x60);
    	 offset = (offset + 1) % 3;

        if(offset == 0)
        {
            if(buffer[1] != 0 || buffer[2] != 0)
            {
                x = x + buffer[1];
                y = y - buffer[2];
                gtx.PutPixel(x,y,0xFF);
            }
        }

  end:;
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
