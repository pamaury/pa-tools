#include "config.h"
#include "stdint.h"
#include "system-arm.h"
#include "system.h"
#include "timer.h"
#include "pinctrl.h"
#include "lcd.h"
#include "usb.h"
#include "logf.h"
#include "serial.h"
#include "dma.h"

#define HW_DIGCTL_STATUS    (*(volatile uint32_t *)(HW_DIGCTL_BASE + 0x10))

void power_off(void);
void system_init(void);

void software_whatchdog(void)
{
    if(current_tick > 20 * HZ && false)
    {
        disable_irq();
        disable_fiq();
        power_off();
    }
}

extern unsigned short rockbox_logo[];
extern unsigned short rockbox_logo2[];
extern unsigned short rockbox_logo3[];
extern unsigned short rockbox_logo4[];

#define swap8(a, b) ({unsigned char c = a; a = b; b = c;})

void main(void)
{
    serial_init();
    logf("[%lu] system_init\n", HW_DIGCTL_MICROSECONDS);
    system_init();
    logf("[%lu] enable_irq\n", HW_DIGCTL_MICROSECONDS);
    enable_irq();
    logf("[%lu] enable_fiq\n", HW_DIGCTL_MICROSECONDS);
    enable_fiq();
    logf("[%lu] timer_init\n", HW_DIGCTL_MICROSECONDS);
    timer_init();
    logf("[%lu] register_timer_function\n", HW_DIGCTL_MICROSECONDS);
    register_timer_function(&software_whatchdog);
    logf("[%lu] usb_init\n", HW_DIGCTL_MICROSECONDS);
    usb_init();
    logf("[%lu] pinctrl_init\n", HW_DIGCTL_MICROSECONDS);
    pinctrl_init();
    logf("[%lu] dma_init\n", HW_DIGCTL_MICROSECONDS);
    dma_init();
    logf("[%lu] lcd_init\n", HW_DIGCTL_MICROSECONDS);
    lcd_init();
    logf("[%lu] lcd_set_backlight\n", HW_DIGCTL_MICROSECONDS);
    lcd_set_backlight(100);

    /*
    lcd_enable(false);
    udelay(500000);
    lcd_enable(true);
    udelay(500000);
    lcd_enable(false);
    udelay(500000);
    lcd_enable(true);
    */
    logf("[%lu] lcd_enable\n", HW_DIGCTL_MICROSECONDS);
    lcd_enable(true);
    
    #if 0
    unsigned width = 176;
    unsigned height = 220;

    #define RGB(r, g, b) ((r) | ((g) << 6) | ((b) << 11))
    
    uint16_t *p = (uint16_t *)&rockbox_logo2;
    for(unsigned y = 0; y < height; y++)
        for(unsigned x = 0; x < width; x++)
        {
            p[y * width + x] = RGB(0, 0, 0);
        }
    
    for(unsigned y = 0; y < 30; y++)
        for(unsigned x = 0; x < width; x++)
            p[y * width + x] = RGB(x, 0, 0);
    for(unsigned y = 30; y < 60; y++)
        for(unsigned x = 0; x < width; x++)
            p[y * width + x] = RGB(x & 0xf8, 0, 0);
    for(unsigned y = 60; y < 90; y++)
        for(unsigned x = 0; x < width; x++)
            p[y * width + x] = RGB(0, 0, x);
    for(unsigned y = 90; y < 120; y++)
        for(unsigned x = 0; x < width; x++)
            p[y * width + x] = RGB(0, 0, x & 0xf8);
    for(unsigned y = 120; y < 150; y++)
        for(unsigned x = 0; x < width; x++)
            p[y * width + x] = RGB(0, x, 0);
    for(unsigned y = 150; y < 180; y++)
        for(unsigned x = 0; x < width; x++)
            p[y * width + x] = RGB(0, x & 0xfc, 0);
    
    lcdif_schedule_refresh(rockbox_logo2, width, height);
    #elif 0
    lcdif_schedule_refresh(rockbox_logo, 240, 320);
    #elif 1
    //lcdif_schedule_refresh(rockbox_logo3, 176, 220);
    #elif 1
    lcdif_schedule_refresh(rockbox_logo4, 320, 240);
    udelay(500000);
    int offset = 320;
    while(true)
    {
        for(int y = 0; y < 240; y++)
            for(int x = 0; x < 320; x++)
                rockbox_logo2[y * 320 + x] = rockbox_logo4[y * 320 + (x + offset) % 320];
        lcdif_schedule_refresh(rockbox_logo2, 320, 240);
        offset--;
        if(offset == 0)
            offset = 320;
        udelay(100);
    }
    #else
    lcdif_schedule_refresh(rockbox_logo2, 400, 240);
    #endif

    #if 1
    int width = 176;
    int height = 220;
    uint16_t *fb = rockbox_logo3;
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            fb[i * width + j] = fb[i * width + j] & 0xff00;

    lcdif_schedule_continuous_refresh(fb, width, height);
    for(int i = 0; i < 40; i++)
    {
        logf("ctrl=0x%x, ctrl1=0x%x, count=0x%x debug1=0x%x state=0x%x ",
             HW_LCDIF_CTRL, HW_LCDIF_CTRL1, HW_LCDIF_TRANSFER_COUNT,
             HW_LCDIF_DEBUG1, HW_LCDIF_STAT);
        logf("cmd addr=0x%x\n", HW_APBH_CHx_CURCMDAR(0));
        udelay(300);
    }
    while(true)
    {
        for(int i = 0; i < height; i++)
        {
            uint16_t px = fb[i * width];
            memmove(&fb[i * width], &fb[i * width + 1], sizeof(fb[0]) * (width - 1));
            fb[(i + 1) * width - 1] = px;
        }
        //lcdif_wait_ready();
        //lcdif_schedule_continuous_refresh(fb, width, height);
    }
    #endif

    logf("[%lu] hang\n", HW_DIGCTL_MICROSECONDS);
    while(1);
    
    disable_irq();
    disable_fiq();
    power_off();
}
