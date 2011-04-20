#include "timer.h"
#include "clocks.h"

volatile long current_tick = 0;

void INT_TIMER0(void)
{
    current_tick++;
    __REG_CLR(HW_TIMROT_TIMCTRL(0)) = HW_TIMROT_TIMCTRL__IRQ;
}

void timer_init(void)
{
    __REG_CLR(HW_TIMROT_ROTCTRL) = __BLOCK_CLKGATE;
    __REG_CLR(HW_TIMROT_ROTCTRL) = __BLOCK_SFTRST;
    /* enable xtal path to timrot */
    imx233_enable_timrot_xtal_clk32k(true);
    /* disable irq, update, reload, 1KHz xtal src */
    HW_TIMROT_TIMCTRL(0) =
        HW_TIMROT_TIMCTRL__UPDATE |
        HW_TIMROT_TIMCTRL__RELOAD |
        HW_TIMROT_TIMCTRL__SELECT_1KHZ_XTAL;
    /* set count so that it reaches 0 HZ times per seconds. Since the source runs
     * at 1KHz, setting the count to X will trigger an interrupt at 1/X Khz
     * or 1000/X Hz. We 1000/X = HZ so we take X=1000/HZ */
    HW_TIMROT_TIMCOUNT(0) = 1000 / HZ - 1;
    /* enable timer0 interrupt */
    imx233_enable_interrupt(INT_SRC_TIMER0, true);
    /* clear irq bit */
    __REG_CLR(HW_TIMROT_TIMCTRL(0)) = HW_TIMROT_TIMCTRL__IRQ;
    /* enable irq */
    __REG_SET(HW_TIMROT_TIMCTRL(0)) = HW_TIMROT_TIMCTRL__IRQ_EN;
}
