#include "lcd.h"
#include "pinctrl.h"
#include "clkctrl.h"
#include "stddef.h"
#include "logf.h"

/**
 * LCD parameters:
 *  busy_enable: no
 *  word_length: 2/3 (18-bits/24-bits per pixel)
 *  bus_data_width: 2 (18-bits)
 *  input_data_swizzle: no
 *  mode86: no
 *  reset: yes
 *  csc_data_swizzle: no
 *  data_setup_timing: 1
 *  data_hold_timing: 2
 *  cmd_setup_timing: 2
 *  cmd_hold_timing: 2
 */

static unsigned int g_lcdif_word_length;
static enum lcd_kind_t g_lcd_kind;

enum lcd_kind_t get_lcd_kind(void)
{
    return g_lcd_kind;
}

static void reset_lcdif(void)
{
    logf("reset_lcdif\n");
    //imx233_reset_block(&HW_LCDIF_CTRL);
    while(HW_LCDIF_CTRL & __BLOCK_CLKGATE)
        HW_LCDIF_CTRL &= ~__BLOCK_CLKGATE;
    while(!(HW_LCDIF_CTRL & __BLOCK_SFTRST))
        HW_LCDIF_CTRL |= __BLOCK_SFTRST;
    while(HW_LCDIF_CTRL & __BLOCK_CLKGATE)
        HW_LCDIF_CTRL &= ~__BLOCK_CLKGATE;
    while(HW_LCDIF_CTRL & __BLOCK_SFTRST)
        HW_LCDIF_CTRL &= ~__BLOCK_SFTRST;
    while(HW_LCDIF_CTRL & __BLOCK_CLKGATE)
        HW_LCDIF_CTRL &= ~__BLOCK_CLKGATE;
}

static void setup_lcdif_parameters(void)
{
    logf("setup_lcdif_parameters\n");
    reset_lcdif();
    __REG_SET(HW_LCDIF_CTRL1) = HW_LCDIF_CTRL1__RESET;
    HW_LCDIF_CTRL = g_lcdif_word_length | HW_LCDIF_CTRL__LCD_DATABUS_WIDTH_18_BIT;
    HW_LCDIF_TIMING = (1 << HW_LCDIF_TIMING__DATA_SETUP_BP) |
        (2 << HW_LCDIF_TIMING__DATA_HOLD_BP) |
        (2 << HW_LCDIF_TIMING__CMD_SETUP_BP) |
        (2 << HW_LCDIF_TIMING__CMD_HOLD_BP);
}

static void setup_lcd(bool use_gpio)
{
    logf("setup_lcd\n");
    if(!use_gpio)
    {
        imx233_set_pin_function(1, 25, PINCTRL_FUNCTION_GPIO); /* lcd_vsync */
        imx233_set_pin_function(1, 21, PINCTRL_FUNCTION_MAIN); /* lcd_cs */
        imx233_set_pin_function(1, 22, PINCTRL_FUNCTION_GPIO); /* lcd_dotclk */
        imx233_set_pin_function(1, 23, PINCTRL_FUNCTION_GPIO); /* lcd_enable */
        imx233_set_pin_function(1, 24, PINCTRL_FUNCTION_GPIO); /* lcd_hsync */
        imx233_set_pin_function(1, 18, PINCTRL_FUNCTION_MAIN); /* lcd_reset */
        imx233_set_pin_function(1, 19, PINCTRL_FUNCTION_MAIN); /* lcd_rs */
        imx233_set_pin_function(1, 16, PINCTRL_FUNCTION_MAIN); /* lcd_d16 */
        imx233_set_pin_function(1, 17, PINCTRL_FUNCTION_MAIN); /* lcd_d17 */
        imx233_set_pin_function(1, 20, PINCTRL_FUNCTION_MAIN); /* lcd_wr */
        __REG_CLR(HW_PINCTRL_MUXSEL(2)) = 0xffffffff; /* lcd_d{0-15} */
    }
    else
    {
        if((HW_LCDIF_CTRL & HW_LCDIF_CTRL__WORD_LENGTH_BM) == HW_LCDIF_CTRL__WORD_LENGTH_16_BIT)
        {
            __REG_SET(HW_PINCTRL_MUXSEL(2)) = 0xffff0000; /* lcd_d{8-15} */
            __REG_CLR(HW_PINCTRL_DOE(1)) = 0xff00; /* lcd_d{8-15} */
        }
        __REG_SET(HW_PINCTRL_MUXSEL(2)) = 0xffff; /* lcd_d{0-7} */
        __REG_CLR(HW_PINCTRL_DOE(1)) = 0xff; /* lcd_d{0-7} */
        __REG_CLR(HW_PINCTRL_DOE(1)) = 0x3ff0000; /* lcd_{d16,d17,reset,rs,wr,cs,dotclk,enable,hsync,vsync} */
        imx233_set_pin_function(1, 16, PINCTRL_FUNCTION_GPIO); /* lcd_d16 */
        imx233_set_pin_function(1, 17, PINCTRL_FUNCTION_GPIO); /* lcd_d17 */
        imx233_set_pin_function(1, 19, PINCTRL_FUNCTION_GPIO); /* lcd_rs */
        imx233_set_pin_function(1, 20, PINCTRL_FUNCTION_GPIO); /* lcd_wr */
        imx233_set_pin_function(1, 21, PINCTRL_FUNCTION_GPIO); /* lcd_cs */
        imx233_set_pin_function(1, 22, PINCTRL_FUNCTION_GPIO); /* lcd_dotclk */
        imx233_set_pin_function(1, 23, PINCTRL_FUNCTION_GPIO); /* lcd_enable */
        imx233_set_pin_function(1, 24, PINCTRL_FUNCTION_GPIO); /* lcd_hsync */
        imx233_set_pin_function(1, 25, PINCTRL_FUNCTION_GPIO); /* lcd_vsync */
    }
}

static void setup_lcd_ter(bool use_gpio)
{
    logf("setup_lcd_ter\n");
    if(use_gpio)
    {
        imx233_set_pin_drive_strength(1, 19, PINCTRL_DRIVE_12mA); /* lcd_rs */
        imx233_set_pin_drive_strength(1, 20, PINCTRL_DRIVE_12mA); /* lcd_wr */
        imx233_set_pin_drive_strength(1, 21, PINCTRL_DRIVE_12mA); /* lcd_cs */
        imx233_set_pin_drive_strength(1, 23, PINCTRL_DRIVE_12mA); /* lcd_enable */
        imx233_set_pin_function(1, 19, PINCTRL_FUNCTION_GPIO); /* lcd_rs */
        imx233_set_pin_function(1, 20, PINCTRL_FUNCTION_GPIO); /* lcd_wr */
        imx233_set_pin_function(1, 21, PINCTRL_FUNCTION_GPIO); /* lcd_cs */
        imx233_set_pin_function(1, 23, PINCTRL_FUNCTION_GPIO); /* lcd_enable */
        /* lcd_{rs,wr,cs,enable} */
        imx233_enable_gpio_output_mask(1, (1 << 19) | (1 << 20) | (1 << 21) | (1 << 23), true);
        imx233_set_gpio_output_mask(1, (1 << 19) | (1 << 20) | (1 << 21) | (1 << 23), true);

        imx233_enable_gpio_output_mask(1, 0x3ffff, false); /* lcd_d{0-17} */
        __REG_SET(HW_PINCTRL_MUXSEL(2)) = 0xffffffff; /* lcd_d{0-15} as GPIO */
        imx233_set_pin_function(1, 16, PINCTRL_FUNCTION_GPIO); /* lcd_d16 */
        imx233_set_pin_function(1, 17, PINCTRL_FUNCTION_GPIO); /* lcd_d17 */
        imx233_set_pin_function(1, 18, PINCTRL_FUNCTION_GPIO); /* lcd_reset */
        imx233_set_pin_function(1, 19, PINCTRL_FUNCTION_GPIO); /* lcd_rs */
    }
    else
    {
        imx233_set_gpio_output_mask(1, (1 << 19) | (1 << 20) | (1 << 21) | (1 << 23), true);
        imx233_set_pin_drive_strength(1, 19, PINCTRL_DRIVE_4mA); /* lcd_rs */
        imx233_set_pin_drive_strength(1, 20, PINCTRL_DRIVE_4mA); /* lcd_wr */
        imx233_set_pin_drive_strength(1, 21, PINCTRL_DRIVE_4mA); /* lcd_cs */
        imx233_set_pin_drive_strength(1, 23, PINCTRL_DRIVE_4mA); /* lcd_enable */
        imx233_set_pin_function(1, 19, PINCTRL_FUNCTION_MAIN); /* lcd_rs */
        imx233_set_pin_function(1, 20, PINCTRL_FUNCTION_MAIN); /* lcd_wr */
        imx233_set_pin_function(1, 21, PINCTRL_FUNCTION_MAIN); /* lcd_cs */
        imx233_enable_gpio_output_mask(1, 0x3ffff, false); /* lcd_d{0-17} */
        __REG_CLR(HW_PINCTRL_MUXSEL(2)) = 0xffffffff; /* lcd_d{0-15} as lcd_d{0-15} */
        imx233_set_pin_function(1, 16, PINCTRL_FUNCTION_MAIN); /* lcd_d16 */
        imx233_set_pin_function(1, 17, PINCTRL_FUNCTION_MAIN); /* lcd_d17 */
        imx233_set_pin_function(1, 18, PINCTRL_FUNCTION_MAIN); /* lcd_reset */
        imx233_set_pin_function(1, 19, PINCTRL_FUNCTION_MAIN); /* lcd_rs */
    }
}

static void lcd_enable(bool enable)
{
   if(enable)
        __REG_SET(HW_LCDIF_CTRL) = __BLOCK_CLKGATE;
    else
        __REG_CLR(HW_LCDIF_CTRL) = __BLOCK_CLKGATE;
    setup_lcd(enable);
}

static void lcdif_enable_bus_master(bool enable)
{
    if(enable)
        __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__LCDIF_MASTER;
    else
        __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__LCDIF_MASTER;
}

static void lcdif_enable_irqs(unsigned irq_bm)
{
    /* clear irq status */
    __REG_CLR(HW_LCDIF_CTRL1) = irq_bm << HW_LCDIF_CTRL1__IRQ_BP;
    /* disable irqs */
    __REG_CLR(HW_LCDIF_CTRL1) = HW_LCDIF_CTRL1__IRQ_EN_BM;
    /* enable irqs */
    __REG_SET(HW_LCDIF_CTRL1) = irq_bm << HW_LCDIF_CTRL1__IRQ_EN_BP;
}

static void setup_lcd_subsystem(void)
{
    logf("setup_lcd_subsystem\n");
    g_lcdif_word_length = HW_LCDIF_CTRL__WORD_LENGTH_18_BIT;
    setup_lcdif_parameters();
    lcd_enable(false);
    lcdif_enable_bus_master(true);
    lcdif_enable_irqs(HW_LCDIF__CUR_FRAME_DONE_IRQ);
    /* enable irq ? */
}

static void lcdif_wait_ready(void)
{
    logf("lcdif_wait_ready\n");
    while(HW_LCDIF_CTRL & HW_LCDIF_CTRL__RUN);
}

static inline uint32_t encode_16_to_18(uint32_t a)
{
    return ((a & 0xff) << 1) | (((a >> 8) & 0xff) << 10);
}

static inline uint32_t decode_18_to_16(uint32_t a)
{
    return ((a >> 1) & 0xff) | ((a >> 2) & 0xff00);
}

static void setup_lcd_clocks(void)
{
    logf("setup_lcd_clocks\n");
    /* the LCD seems to works at 24Mhz, so use the xtal clock with no divider */
    imx233_enable_clock(CLK_PIX, false);
    imx233_set_clock_divisor(CLK_PIX, 1);
    imx233_set_bypass_pll(CLK_PIX, true); /* use XTAL */
    imx233_enable_clock(CLK_PIX, true);
}

static void lcdif_write_read_single_gpio(uint32_t data_out, uint32_t *data_in)
{
    logf("lcdif_write_read_single_gpio\n");
    imx233_set_gpio_output(1, 21, true); /* lcd_cs */
    imx233_set_gpio_output(1, 19, true); /* lcd_rs */
    imx233_set_gpio_output(1, 23, true); /* lcd_enable */
    imx233_set_gpio_output(1, 20, true); /* lcd_wr */
    imx233_enable_gpio_output_mask(1, 0x3ffff, true); /* lcd_d{0-17} */
    udelay(2);
    imx233_set_gpio_output(1, 19, false); /* lcd_rs */
    udelay(1);
    imx233_set_gpio_output(1, 21, false); /* lcd_cs */
    udelay(1);
    imx233_set_gpio_output(1, 20, false); /* lcd_wr */
    udelay(1);
    imx233_set_gpio_output_mask(1, data_out & 0x3ffff, true); /* lcd_d{0-17} */
    udelay(1);
    imx233_set_gpio_output(1, 20, true); /* lcd_wr */
    udelay(3);
    imx233_enable_gpio_output_mask(1, 0x3ffff, false); /* lcd_d{0-17} */
    udelay(2);
    imx233_set_gpio_output(1, 23, false); /* lcd_enable */
    udelay(1);
    imx233_set_gpio_output(1, 19, true); /* lcd_rs */
    udelay(1);
    imx233_set_gpio_output(1, 23, true); /* lcd_enable */
    udelay(3);
    imx233_set_gpio_output(1, 23, false); /* lcd_enable */
    udelay(2);
    *data_in = imx233_get_gpio_input_mask(1, 0x3ffff); /* lcd_d{0-17} */
    udelay(1);
    imx233_set_gpio_output(1, 23, true); /* lcd_enable */
    udelay(1);
    imx233_set_gpio_output(1, 21, true); /* lcd_cs */
    udelay(1);
}

static void lcdif_send(bool data_mode, unsigned len, uint32_t *buf)
{
    logf("lcdif_send\n");
    unsigned max_xfer_size = 0xffff;
    if(len == 0)
        return;
    if(g_lcdif_word_length == HW_LCDIF_CTRL__WORD_LENGTH_16_BIT)
        max_xfer_size = 0x1fffe;
    lcdif_wait_ready();
    lcdif_enable_irqs(0);
    lcdif_enable_bus_master(false);

    do
    {
        unsigned burst = MIN(len, max_xfer_size);
        len -= burst;
        unsigned count = burst;
        if(g_lcdif_word_length != HW_LCDIF_CTRL__WORD_LENGTH_8_BIT)
        {
            if(burst & 1)
                burst++;
            count = burst / 2;
        }
        else
            count = burst;
        HW_LCDIF_TRANSFER_COUNT = 0;
        HW_LCDIF_TRANSFER_COUNT = 0x10000 | count;
        __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__DATA_SELECT | HW_LCDIF_CTRL__RUN;
        if(data_mode)
            __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__DATA_SELECT;
        __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__RUN;
        burst = (burst + 3) / 4;
        while(burst-- > 0)
        {
            while(HW_LCDIF_STAT & HW_LCDIF_STAT__LFIFO_FULL);
            HW_LCDIF_DATA = *buf++;
        }
        while(HW_LCDIF_CTRL & HW_LCDIF_CTRL__RUN);
    }while(len > 0);
    lcdif_enable_bus_master(true);
    lcdif_enable_irqs(HW_LCDIF__CUR_FRAME_DONE_IRQ);
}

static void lcdif_send_cmd_data(uint32_t cmd, uint32_t data)
{
    logf("lcdif_send_cmd_data\n");
    uint32_t old_cmd = cmd;
    /* get back to 18-bit word length */
    if(g_lcdif_word_length == HW_LCDIF_CTRL__WORD_LENGTH_24_BIT)
    {
        g_lcdif_word_length = HW_LCDIF_CTRL__WORD_LENGTH_18_BIT;
        __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__WORD_LENGTH_BM;
        __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__WORD_LENGTH_18_BIT;
    }

    if(g_lcdif_word_length == HW_LCDIF_CTRL__WORD_LENGTH_18_BIT)
    {
        cmd = encode_16_to_18(cmd);
        data = encode_16_to_18(data);
    }
    
    lcdif_send(false, 2, &cmd);
    if(old_cmd == 0x22)
    {
        g_lcdif_word_length = HW_LCDIF_CTRL__WORD_LENGTH_24_BIT;
        __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__WORD_LENGTH_24_BIT;
        __REG_CLR(HW_LCDIF_CTRL1) = HW_LCDIF_CTRL1__BYTE_PACKING_FORMAT_BM;
        __REG_SET(HW_LCDIF_CTRL1) = 0x7 << HW_LCDIF_CTRL1__BYTE_PACKING_FORMAT_BP; /* unpacked 24-bit */
    }
    else
        lcdif_send(true, 2, &data);
}

static void lcd_find_kind(uint32_t data_out, uint32_t *data_in)
{
    logf("lcd_find_kind\n");
    setup_lcd_ter(true);
    lcdif_write_read_single_gpio(encode_16_to_18(data_out), data_in);
    *data_in = decode_18_to_16(*data_in);
    setup_lcd_ter(false);
    lcdif_send_cmd_data(0x22, 0);
}

static void setup_unk_pin(void)
{
    imx233_set_pin_function(1, 28, PINCTRL_FUNCTION_GPIO);
    imx233_set_pin_drive_strength(1, 28, PINCTRL_DRIVE_8mA);
    imx233_enable_gpio_output(1, 28, true);
    imx233_set_gpio_output(1, 29, true);
    udelay(600);
}

static void lcd_init_seq_7783(void)
{
    __REG_SET(HW_LCDIF_CTRL1) = HW_LCDIF_CTRL1__RESET;
    udelay(50);
    __REG_CLR(HW_LCDIF_CTRL1) = HW_LCDIF_CTRL1__RESET;
    udelay(10);
    __REG_SET(HW_LCDIF_CTRL1) = HW_LCDIF_CTRL1__RESET;
    udelay(200);
    lcdif_send_cmd_data(1, 0x100);
    lcdif_send_cmd_data(2, 0x700);
    lcdif_send_cmd_data(3, 0x1030);
    lcdif_send_cmd_data(7, 0x121);
    lcdif_send_cmd_data(8, 0x302);
    lcdif_send_cmd_data(9, 0x200);
    lcdif_send_cmd_data(0xa, 0);
    lcdif_send_cmd_data(0x10, 0x790);
    lcdif_send_cmd_data(0x11, 5);
    lcdif_send_cmd_data(0x12, 0);
    lcdif_send_cmd_data(0x13, 0);
    udelay(100);
    lcdif_send_cmd_data(0x10, 0x12b0);
    udelay(100);
    lcdif_send_cmd_data(0x11, 7);
    udelay(100);
    lcdif_send_cmd_data(0x12, 0x89);
    lcdif_send_cmd_data(0x13, 0x1d00);
    lcdif_send_cmd_data(0x29, 0x2f);
    udelay(50);
    lcdif_send_cmd_data(0x30, 0);
    lcdif_send_cmd_data(0x31, 0x505);
    lcdif_send_cmd_data(0x32, 0x205);
    lcdif_send_cmd_data(0x35, 0x206);
    lcdif_send_cmd_data(0x36, 0x408);
    lcdif_send_cmd_data(0x37, 0);
    lcdif_send_cmd_data(0x38, 0x504);
    lcdif_send_cmd_data(0x39, 0x206);
    lcdif_send_cmd_data(0x3c, 0x206);
    lcdif_send_cmd_data(0x3d, 0x408);
    lcdif_send_cmd_data(0x50, 0);
    lcdif_send_cmd_data(0x51, 0xef);
    lcdif_send_cmd_data(0x52, 0);
    lcdif_send_cmd_data(0x53, 0x13f);
    lcdif_send_cmd_data(0x20, 0);
    lcdif_send_cmd_data(0x21, 0);
    lcdif_send_cmd_data(0x60, 0xa700);
    lcdif_send_cmd_data(0x61, 1);
    lcdif_send_cmd_data(0x90, 0x33);
    lcdif_send_cmd_data(0x2b, 0xa);
    lcdif_send_cmd_data(9, 0);
    lcdif_send_cmd_data(7, 0x133);
    udelay(50);
    lcdif_send_cmd_data(0x22, 0);
}

static void lcd_init_seq_9325(void)
{
    
}

void lcd_init(void)
{
    uint32_t kind;
    logf("lcd_init\n");
    setup_lcd_subsystem();
    setup_lcd_clocks();
    
    for(int i = 0; i < 10; i++)
    {
        lcd_find_kind(0, &kind);
        if(kind == LCD_KIND_7783 || kind == LCD_KIND_9325)
        {
            g_lcd_kind = kind;
            break;
        }
        else
        {
            logf("unknown lcd kind: %x\n", kind);
            g_lcd_kind = LCD_KIND_OTHER;
        }
    }
    udelay(5);
    logf("lcd kind: %x\n", g_lcd_kind);
    setup_unk_pin();
    switch(g_lcd_kind)
    {
        case LCD_KIND_7783: lcd_init_seq_7783(); break;
        case LCD_KIND_9325: lcd_init_seq_9325(); break;
        default: lcd_init_seq_7783(); break;
    }
    logf("lcd initialized\n");
}
