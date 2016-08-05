#include "timer.h"

/* This will keep track of how many ticks that the system
*  has been running for */

    static int32_t timer_ticks = 0;

/* Handles the timer. In this case, it's very simple: We
*  increment the 'Timer::timer_ticks' variable every time the
*  timer fires. By default, the timer fires 18.222 times
*  per second. Why 18.222Hz? Some engineer at IBM must've
*  been smoking something funky */
static void timer_handler(struct regs *r)
{
    /* Increment our 'tick count' */
    timer_ticks++;

    /* Every 18 clocks (approximately 1 second), we will
    *  display a message on the screen */
    if (timer_ticks % 18 == 0)
    {
        printf("One second has passed\n");
    }
}

Timer::Timer()
{
    /* Installs 'timer_handler' to IRQ0 */
    install_handler_irq(0, timer_handler);
}

/* This will continuously loop until the given time has
*  been reached */
void Timer::timer_wait(int ticks)
{
    unsigned long eticks;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks);
}

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
Timer::~Timer()
{

}
