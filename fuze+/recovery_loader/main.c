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
    if(current_tick > 60 * HZ)
    {
        disable_irq();
        disable_fiq();
        power_off();
    }
}

extern struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[240 * 320 * 4 + 1];
} rockbox_logo;

#define swap8(a, b) ({unsigned char c = a; a = b; b = c;})

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

    uint32_t *p = (uint32_t *)&rockbox_logo.pixel_data;
    for(unsigned y = 0; y < rockbox_logo.height; y++)
        for(unsigned x = 0; x < rockbox_logo.width; x++)
        {
            uint32_t v = p[y * rockbox_logo.width + x];
            p[y * rockbox_logo.width + x] =
                ((v >> 16) & 0xff) | (v & 0xff00) | ((v & 0xff) << 16);
        }

    lcdif_schedule_refresh(rockbox_logo.pixel_data, rockbox_logo.width, rockbox_logo.height);
    lcdif_schedule_refresh(rockbox_logo.pixel_data, rockbox_logo.width, rockbox_logo.height);
    lcdif_schedule_refresh(rockbox_logo.pixel_data, rockbox_logo.width, rockbox_logo.height);

    while(1);
    
    disable_irq();
    disable_fiq();
    power_off();
}
