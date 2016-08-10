#include "mouse.h"


typedef void(*regs_func)(struct regs *r);

extern void install_handler_irq(int irq, regs_func handler);

static PORT::Port8Bits p8b_mouse_drv;


void mouse_ps2_handler(struct regs *r)
{
	printf("Hello");
}


void MOUSE::install_mouse_driver()
{
  install_handler_irq(12, mouse_ps2_handler);
}