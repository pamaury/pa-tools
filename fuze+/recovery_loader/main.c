#include "config.h"
#include "stdint.h"
#include "system-arm.h"
#include "system.h"

#define USB_BASE            0x80080000
#define REG_USBCMD          (*(volatile unsigned int *)(USB_BASE+0x140))

#define USBCMD_RUN          0x00000001

void power_off(void);
void system_init(void);

volatile int irq_fired = 0;

void INT_TIMER0(void)
{
    irq_fired = 1;
}

void main()
{
    system_init();
    enable_irq();
    enable_fiq();

    imx233_enable_interrupt(INT_SRC_TIMER0, 1);
    imx233_softirq(INT_SRC_TIMER0, 1);
    while(!irq_fired);
    imx233_softirq(INT_SRC_TIMER0, 0);

    REG_USBCMD &= ~USBCMD_RUN;
    for(int i = 0; i < 1000; i++)
        __asm__ volatile("nop");

    power_off();
}
