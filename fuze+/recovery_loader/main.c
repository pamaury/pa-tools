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

void main(void)
{
    system_init();
    enable_irq();
    enable_fiq();
    timer_init();
    register_timer_function(&software_whatchdog);
    usb_init();
    pinctrl_init();
    lcd_init();
    lcd_set_backlight(100);
    lcd_enable(false);
    udelay(500000);
    lcd_enable(true);
    udelay(500000);
    lcd_enable(false);
    udelay(500000);
    lcd_enable(true);

    while(1)
        usb_task();
    
    disable_irq();
    disable_fiq();
    power_off();
}
