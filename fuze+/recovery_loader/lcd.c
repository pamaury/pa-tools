#include "lcd.h"
#include "pinctrl.h"
#include "clkctrl.h"

/**
 * LCD parameters:
 *  busy_enable: no
 *  word_length: 2/3 (18-bits/24-bits per pixel)
 *  bus_data_width: 2 (18-bits)
 *  input_data_swizzle: no
 *  mode86: no
 *  data_format_24_bits: yes
 *  csc_data_swizzle: no
 *  data_setup_timing: 1
 *  data_hold_timing: 2
 *  cmd_setup_timing: 2
 *  cmd_hold_timing: 2
 */

static unsigned int g_lcdif_word_length;

static void reset_lcdif()
{
    __REG_CLR(HW_LCDIF_CTRL) = __BLOCK_SFTRST;
    while(HW_LCDIF_CTRL & __BLOCK_SFTRST);
    __REG_CLR(HW_LCDIF_CTRL) = __BLOCK_CLKGATE;
    __REG_SET(HW_LCDIF_CTRL) = __BLOCK_SFTRST;
    while(!(HW_LCDIF_CTRL & __BLOCK_CLKGATE));
    __REG_CLR(HW_LCDIF_CTRL) = __BLOCK_SFTRST;
    while(HW_LCDIF_CTRL & __BLOCK_SFTRST);
    __REG_CLR(HW_LCDIF_CTRL) = __BLOCK_CLKGATE;
    while(HW_LCDIF_CTRL & __BLOCK_CLKGATE);
}

static void setup_lcdif_parameters(void)
{
    reset_lcdif();
    HW_LCDIF_CTRL = HW_LCDIF_CTRL__DATA_FORMAT_24_BIT |
        g_lcdif_word_length | HW_LCDIF_CTRL__LCD_DATABUS_WIDTH_18_BIT;
    HW_LCDIF_TIMING = (1 << HW_LCDIF_TIMING__DATA_SETUP_BP) |
        (2 << HW_LCDIF_TIMING__DATA_HOLD_BP) |
        (2 << HW_LCDIF_TIMING__CMD_SETUP_BP) |
        (2 << HW_LCDIF_TIMING__CMD_HOLD_BP);
}

static void setup_lcd(bool use_gpio)
{
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
        __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__RUN;
    else
        __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__RUN;
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
    __REG_CLR(HW_LCDIF_CTRL1) = irq_bm << HW_LCDIF_CTRL_1__IRQ_BP;
    /* disable irqs */
    __REG_CLR(HW_LCDIF_CTRL1) = HW_LCDIF_CTRL_1__IRQ_EN_BM;
    /* enable irqs */
    __REG_SET(HW_LCDIF_CTRL1) = irq_bm << HW_LCDIF_CTRL_1__IRQ_EN_BP;
}

static void setup_lcd_subsystem()
{
    g_lcdif_word_length = HW_LCDIF_CTRL__WORD_LENGTH_18_BIT;
    setup_lcdif_parameters();
    lcd_enable(false);
    lcdif_enable_bus_master(true);
    lcdif_enable_irqs(HW_LCDIF__CUR_FRAME_DONE_IRQ);
    /* enable irq ? */
}

static inline uint32_t encode_16_to_18(uint32_t a)
{
    return ((a & 0xff) << 1) | (((a >> 8) & 0xff) << 10);
}

static inline uint32_t decode_18_to_16(uint32_t a)
{
    return ((a >> 1) & 0xff) | ((a >> 2) & 0xff00);
}

static void setup_lcd_clocks()
{
    /* the LCD seems to works at 24Mhz, so use the xtal clock with no divider */
    imx233_enable_clock(CLK_PIX, false);
    imx233_set_clock_divisor(CLK_PIX, 1);
    imx233_set_bypass_pll(CLK_PIX, false); /* use XTAL */
    imx233_enable_clock(CLK_PIX, true);
}

static void lcdif_write_read_single_gpio(uint32_t data_out, uint32_t *data_in)
{
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
    imx233_set_gpio_output_mask(1, 0x3ffff, false); /* lcd_d{0-17} */
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
}

static void lcdif_send_cmd_data(uint32_t cmd, uint32_t data)
{
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

static void lcd_init_1(uint32_t data_out, uint32_t *data_in)
{
    setup_lcd_ter(true);
    lcdif_write_read_single_gpio(encode_16_to_18(data_out), data_in);
    *data_in = decode_18_to_16(*data_in);
    setup_lcd_ter(false);
    lcdif_send_cmd_data(0x22, 0);
}

void lcd_init(void)
{
    setup_lcd_subsystem();
    setup_lcd_clocks();
    /* lcd_init_1(?); */
}
