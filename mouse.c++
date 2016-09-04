#include "mouse.h"
#ifdef GRAPHICS_MODE
	#include "graphics.h"
	#include "widget.h"

	static VideoGraphicsArray vga;
#endif


typedef void(*regs_func)(struct regs *r);

extern void install_handler_irq(int irq, regs_func handler);

extern void redraw_desktop(int x, int y, int w, int h);

extern void redraw_desktop_button_click(int x , int y, bool up);

extern MOUSE_DIMENSIONS_DRAW MDD;

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





static uint8_t buffer[3]={0};
static uint8_t offset=0;
static uint8_t buttons;
int32_t x, y;
uint8_t x_vga,y_vga = 0;

//Mouse functions
void mouse_ps2_handler(struct regs *a_r)
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
                /* Convert 8 bit integer and 1-bit sign flag representing 
                   9-bit 2's complement value to a 32-bit signed integer */
                int32_t int_x, int_y;

                /* Bit 4 of buffer[0] is X's sign bit
                   Bit 5 of buffer[0] is Y's sign bit */
                int_x = buffer[1] - (0x100 & (buffer[0] << (8-4)));
                int_y = buffer[2] - (0x100 & (buffer[0] << (8-5)));

#ifdef GRAPHICS_MODE

                x += int_x;
                y -= int_y;



                if (x<=0) x=0;
                if (y<=0) y=0;
                if (x>=299) x=299;
                if (y>=179) y=179;

                redraw_desktop(x,y,5,5);
#else

                static uint16_t* VideoMemoryMouse = (uint16_t*)0xc00b8000;
                               VideoMemoryMouse[80*y_vga + x_vga] = (VideoMemoryMouse[80*y_vga + x_vga] & 0x0F00) << 4
                                                   | (VideoMemoryMouse[80*y_vga + x_vga] & 0xF000) >> 4
                                                   | (VideoMemoryMouse[80*y_vga + x_vga] & 0x00FF);

                               x_vga += buffer[1];
                               if(x_vga >= 80) x_vga = 79;
                               if(x_vga < 0) x_vga = 0;
                               y_vga -= buffer[2];
                               if(y_vga >= 25) y_vga = 24;
                               if(y_vga < 0) y_vga = 0;

                               VideoMemoryMouse[80*y_vga + x_vga] = (VideoMemoryMouse[80*y_vga + x_vga] & 0x0F00) << 4
                                                   | (VideoMemoryMouse[80*y_vga + x_vga] & 0xF000) >> 4
                                                   | (VideoMemoryMouse[80*y_vga + x_vga] & 0x00FF);






#endif
            }


            for(uint8_t i = 0; i < 3; i++)
            {
            	if((buffer[0] & (0x1<<i)) != (buttons & (0x1<<i)))
            	{
#ifdef GRAPHICS_MODE
            		if(buttons & (0x1<<i))
            			redraw_desktop_button_click(x,y,true);
            		else
            			redraw_desktop_button_click(x,y,false);
#else


            		if(buttons & (0x1<<i))
            			printf("Mouse UP");
                    else
                    	printf("Mouse DOWN");
#endif
        	}
     	 }

    buttons = buffer[0];
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
