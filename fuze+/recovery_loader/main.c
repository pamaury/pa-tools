#include "config.h"
#include "stdint.h"
#include "system-arm.h"
#include "system.h"
#include "timer.h"

#define USB_BASE            0x80080000
#define REG_USBCMD          (*(volatile unsigned int *)(USB_BASE+0x140))

#define USBCMD_RUN          0x00000001

void power_off(void);
void system_init(void);

void main()
{
    system_init();
    enable_irq();
    enable_fiq();

    timer_init();
    
    while(current_tick < 5 * HZ)
        ;
    
    REG_USBCMD &= ~USBCMD_RUN;
    for(int i = 0; i < 1000; i++)
        __asm__ volatile("nop");

    disable_irq();
    disable_fiq();
    power_off();
}
