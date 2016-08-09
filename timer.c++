#include "timer.h"

/* This will keep track of how many ticks that the system
*  has been running for */

typedef void(*regs_func)(struct regs *r);


static int32_t timer_ticks = 0;

static PORT::Port8Bits p8b_timer_drv;

extern void install_handler_irq(int irq, regs_func handler);

 void timer_phase(int hz)
{
    int divisor = 1193180 / hz;       /* Calculate our divisor */
    p8b_timer_drv.out(0x36,0x43);             /* Set our command byte 0x36 */
    p8b_timer_drv.out(divisor & 0xFF,0x40);   /* Set low byte of divisor */
    p8b_timer_drv.out(divisor >> 8,0x40);     /* Set high byte of divisor */
}

/* Handles the timer. In this case, it's very simple: We
*  increment the 'Timer::timer_ticks' variable every time the
*  timer fires. By default, the timer fires 18.222 times
*  per second. Why 18.222Hz? Some engineer at IBM must've
*  been smoking something funky */
void timer_handler_driver(struct regs *r)
{
    /* Increment our 'tick count' */
    timer_ticks++;

    /* Every 18 clocks (approximately 1 second), we will
    *  display a message on the screen */
    if (timer_ticks % 18 == 0)
    {
        update_clock_time_taken(timer_ticks/18);
    }
}

Timer::Timer()
{
}

/* This will continuously loop until the given time has
*  been reached */
void Timer::timer_wait(int ticks)
{
    unsigned long eticks;

    eticks = timer_ticks + ticks;
    while((unsigned)timer_ticks < eticks);
}

void Timer::install_timer()
{
    //timer_phase(18);
    install_handler_irq(0, timer_handler_driver);
}

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
Timer::~Timer()
{

}
