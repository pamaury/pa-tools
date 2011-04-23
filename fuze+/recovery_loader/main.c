#include "config.h"
#include "stdint.h"
#include "system-arm.h"
#include "system.h"
#include "timer.h"
#include "pinctrl.h"
#include "lcd.h"
#include "usb.h"
#include "logf.h"

#define HW_DIGCTL_STATUS    (*(volatile uint32_t *)(HW_DIGCTL_BASE + 0x10))

void power_off(void);
void system_init(void);

void software_whatchdog(void)
{
    if(current_tick > 10 * HZ)
    {
        disable_irq();
        disable_fiq();
        power_off();
    }
}

void main()
{
    system_init();
    enable_irq();
    enable_fiq();
    timer_init();
    register_timer_function(&software_whatchdog);
    pinctrl_init();
    usb_init();
    lcd_init();

    while(1)
        usb_task();
    
    disable_irq();
    disable_fiq();
    power_off();
}
