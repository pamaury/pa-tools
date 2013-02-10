#include "lcd.h"
#include "pinctrl.h"
#include "clkctrl.h"
#include "stddef.h"
#include "logf.h"
#include "pwm.h"
#include "dma.h"
#include "stddef.h"

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
    udelay(100);
    __REG_CLR(HW_LCDIF_CTRL1) = HW_LCDIF_CTRL1__RESET;
    udelay(100);
    __REG_SET(HW_LCDIF_CTRL1) = HW_LCDIF_CTRL1__RESET;
    #ifdef SANSA_FUZEPLUS
    g_lcdif_word_length = HW_LCDIF_CTRL__WORD_LENGTH_18_BIT;
    HW_LCDIF_CTRL = g_lcdif_word_length | HW_LCDIF_CTRL__LCD_DATABUS_WIDTH_18_BIT;
    HW_LCDIF_TIMING = (1 << HW_LCDIF_TIMING__DATA_SETUP_BP) |
        (2 << HW_LCDIF_TIMING__DATA_HOLD_BP) |
        (2 << HW_LCDIF_TIMING__CMD_SETUP_BP) |
        (2 << HW_LCDIF_TIMING__CMD_HOLD_BP);
    #elif defined(CREATIVE_ZENXFI2)
    g_lcdif_word_length = HW_LCDIF_CTRL__WORD_LENGTH_18_BIT;
    HW_LCDIF_CTRL = g_lcdif_word_length | HW_LCDIF_CTRL__LCD_DATABUS_WIDTH_18_BIT;
    HW_LCDIF_TIMING = (2 << HW_LCDIF_TIMING__DATA_SETUP_BP) |
        (2 << HW_LCDIF_TIMING__DATA_HOLD_BP) |
        (3 << HW_LCDIF_TIMING__CMD_SETUP_BP) |
        (3 << HW_LCDIF_TIMING__CMD_HOLD_BP);
    #elif defined(SONY_NWZE360)
    g_lcdif_word_length = HW_LCDIF_CTRL__WORD_LENGTH_8_BIT;
    HW_LCDIF_CTRL = g_lcdif_word_length | HW_LCDIF_CTRL__LCD_DATABUS_WIDTH_8_BIT;
    HW_LCDIF_TIMING = (1 << HW_LCDIF_TIMING__DATA_SETUP_BP) |
        (1 << HW_LCDIF_TIMING__DATA_HOLD_BP) |
        (1 << HW_LCDIF_TIMING__CMD_SETUP_BP) |
        (1 << HW_LCDIF_TIMING__CMD_HOLD_BP);
    #elif defined(CREATIVE_ZENXFI3)
    g_lcdif_word_length = HW_LCDIF_CTRL__WORD_LENGTH_16_BIT;
    HW_LCDIF_CTRL = g_lcdif_word_length | HW_LCDIF_CTRL__LCD_DATABUS_WIDTH_16_BIT;
    HW_LCDIF_TIMING = (2 << HW_LCDIF_TIMING__DATA_SETUP_BP) |
        (2 << HW_LCDIF_TIMING__DATA_HOLD_BP) |
        (3 << HW_LCDIF_TIMING__CMD_SETUP_BP) |
        (3 << HW_LCDIF_TIMING__CMD_HOLD_BP);
    #elif defined(INSIGNIA_INFOCAST35)
    #define LCD_DOTCLK
    g_lcdif_word_length = HW_LCDIF_CTRL__WORD_LENGTH_16_BIT;
    HW_LCDIF_CTRL = g_lcdif_word_length | HW_LCDIF_CTRL__LCD_DATABUS_WIDTH_18_BIT |
        HW_LCDIF_CTRL__DATA_SELECT | HW_LCDIF_CTRL__DOTCLK_MODE |
        HW_LCDIF_CTRL__BYPASS_COUNT;
    HW_LCDIF_TIMING = (1 << HW_LCDIF_TIMING__DATA_SETUP_BP) |
        (1 << HW_LCDIF_TIMING__DATA_HOLD_BP) |
        (1 << HW_LCDIF_TIMING__CMD_SETUP_BP) |
        (1 << HW_LCDIF_TIMING__CMD_HOLD_BP);
    HW_LCDIF_VDCTRL0 = 0x1c300003;
    HW_LCDIF_VDCTRL1 = 0x000000f9;
    HW_LCDIF_VDCTRL2 = 0x28000179;
    HW_LCDIF_VDCTRL3 = 0x00340006;
    HW_LCDIF_VDCTRL4 = 0x00040140;
    #elif defined(SONY_NWZE360)
    #else
    #error 
    #endif
}

static void setup_lcd_pin(bool use_lcdif)
{
    logf("setup_lcd\n");
    if(use_lcdif)
    {
#if defined(LCD_DOTCLK)
        int dotclk_func = PINCTRL_FUNCTION_MAIN;
#else
        int dotclk_func = PINCTRL_FUNCTION_GPIO;
#endif
        imx233_set_pin_function(1, 25, dotclk_func); /* lcd_vsync */
        imx233_set_pin_function(1, 22, dotclk_func); /* lcd_dotclk */
        imx233_set_pin_function(1, 23, dotclk_func); /* lcd_enable */
        imx233_set_pin_function(1, 24, dotclk_func); /* lcd_hsync */
        imx233_set_pin_function(1, 21, PINCTRL_FUNCTION_MAIN); /* lcd_cs */
        imx233_set_pin_function(1, 18, PINCTRL_FUNCTION_MAIN); /* lcd_reset */
        imx233_set_pin_function(1, 19, PINCTRL_FUNCTION_MAIN); /* lcd_rs */
        imx233_set_pin_function(1, 16, PINCTRL_FUNCTION_MAIN); /* lcd_d16 */
        imx233_set_pin_function(1, 17, PINCTRL_FUNCTION_MAIN); /* lcd_d17 */
        imx233_set_pin_function(1, 20, PINCTRL_FUNCTION_MAIN); /* lcd_wr */
        if((HW_LCDIF_CTRL & HW_LCDIF_CTRL__LCD_DATABUS_WIDTH_BM) != HW_LCDIF_CTRL__LCD_DATABUS_WIDTH_8_BIT)
            __REG_CLR(HW_PINCTRL_MUXSEL(2)) = 0xffff0000; /* lcd_d{8-15} */
        __REG_CLR(HW_PINCTRL_MUXSEL(2)) = 0x0000ffff; /* lcd_d{0-7} */
    }
    else
    {
        if((HW_LCDIF_CTRL & HW_LCDIF_CTRL__LCD_DATABUS_WIDTH_BM) != HW_LCDIF_CTRL__LCD_DATABUS_WIDTH_8_BIT)
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

static void lcdif_enable(bool enable)
{
    if(enable)
        __REG_CLR(HW_LCDIF_CTRL) = __BLOCK_CLKGATE;
    else
        __REG_SET(HW_LCDIF_CTRL) = __BLOCK_CLKGATE;
    setup_lcd_pin(enable);
}

static void lcdif_enable_bus_master(bool enable)
{
    if(enable)
        __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__LCDIF_MASTER;
    else
        __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__LCDIF_MASTER;
}

static void setup_lcd_subsystem(void)
{
    logf("setup_lcd_subsystem\n");
    setup_lcdif_parameters();
    lcdif_enable(true);
    lcdif_enable_bus_master(true);
    /* enable irq ? */
}

void lcdif_wait_ready(void)
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
    imx233_set_clock_divisor(CLK_PIX, 2);
    imx233_set_bypass_pll(CLK_PIX, true); /* use XTAL */
    imx233_enable_clock(CLK_PIX, true);
}

void lcd_init(void)
{
    logf("setup_lcd_clocks\n");
    setup_lcd_clocks();
    logf("setup_lcd_subsystem\n");
    setup_lcd_subsystem();
    logf("imx233_pwm_init\n");
    imx233_pwm_init();
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
}

#ifdef CREATIVE_ZENXFI2
static void lcdif_send_cmd(bool is_data, uint16_t _cmd)
{
    uint32_t cmd = _cmd;
    logf("lcdif_send_cmd_data\n");
    /* get back to 18-bit word length */
    #if 0
    if(g_lcdif_word_length == HW_LCDIF_CTRL__WORD_LENGTH_24_BIT)
    {
        g_lcdif_word_length = HW_LCDIF_CTRL__WORD_LENGTH_18_BIT;
        __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__WORD_LENGTH_BM;
        __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__WORD_LENGTH_18_BIT;
        __REG_CLR(HW_LCDIF_CTRL1) = HW_LCDIF_CTRL1__BYTE_PACKING_FORMAT_BM;
        __REG_SET(HW_LCDIF_CTRL1) = 0xf << HW_LCDIF_CTRL1__BYTE_PACKING_FORMAT_BP;
    }

    if(g_lcdif_word_length == HW_LCDIF_CTRL__WORD_LENGTH_18_BIT)
        cmd = encode_16_to_18(cmd);
    #else
    if(g_lcdif_word_length != HW_LCDIF_CTRL__WORD_LENGTH_18_BIT)
    {
        g_lcdif_word_length = HW_LCDIF_CTRL__WORD_LENGTH_18_BIT;
        __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__WORD_LENGTH_BM;
        __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__WORD_LENGTH_18_BIT;
        __REG_CLR(HW_LCDIF_CTRL1) = HW_LCDIF_CTRL1__BYTE_PACKING_FORMAT_BM;
        __REG_SET(HW_LCDIF_CTRL1) = 0xf << HW_LCDIF_CTRL1__BYTE_PACKING_FORMAT_BP;
    }
    cmd = encode_16_to_18(cmd);
    #endif

    lcdif_send(is_data, 2, (void *)&cmd);
}

void lcd_enable(bool enable)
{
    if(enable)
    {
        lcdif_send_cmd(false, 0);
        lcdif_send_cmd(false, 0);
        lcdif_send_cmd(false, 0);
        lcdif_send_cmd(false, 0);
        udelay(10000);
        lcdif_send_cmd(false, 8);
        lcdif_send_cmd(true, 0x808);
        lcdif_send_cmd(false, 0x10);
        lcdif_send_cmd(true, 0x10);
        lcdif_send_cmd(false, 0x400);
        lcdif_send_cmd(true, 0x6200);
        lcdif_send_cmd(false, 0x300);
        lcdif_send_cmd(true, 0xc0a);
        lcdif_send_cmd(false, 0x301);
        lcdif_send_cmd(true, 0x4c11);
        lcdif_send_cmd(false, 0x302);
        lcdif_send_cmd(true, 0x906);
        lcdif_send_cmd(false, 0x303);
        lcdif_send_cmd(true, 0x1417);
        lcdif_send_cmd(false, 0x304);
        lcdif_send_cmd(true, 0x3333);
        lcdif_send_cmd(false, 0x305);
        lcdif_send_cmd(true, 0x150d);
        lcdif_send_cmd(false, 0x306);
        lcdif_send_cmd(true, 0x740a);
        lcdif_send_cmd(false, 0x307);
        lcdif_send_cmd(true, 0x100c);
        lcdif_send_cmd(false, 0x308);
        lcdif_send_cmd(true, 0x60c);
        lcdif_send_cmd(false, 0x309);
        lcdif_send_cmd(true, 0);
        lcdif_send_cmd(false, 0x100);
        lcdif_send_cmd(true, 0x730);
        lcdif_send_cmd(false, 0x101);
        lcdif_send_cmd(true, 0x237);
        lcdif_send_cmd(false, 0x103);
        lcdif_send_cmd(true, 0x2b00);
        lcdif_send_cmd(false, 0x280);
        lcdif_send_cmd(true, 0x4000);
        lcdif_send_cmd(false, 0x102);
        lcdif_send_cmd(true, 0x81b0);
        udelay(40000);
        lcdif_send_cmd(false, 1);
        lcdif_send_cmd(true, 0x100);
        lcdif_send_cmd(false, 2);
        lcdif_send_cmd(true, 0x100);
        lcdif_send_cmd(false, 3);
        lcdif_send_cmd(true, 0x5028); /* 0x1023 ? 0x5028 ? */

        lcdif_send_cmd(false, 9);
        lcdif_send_cmd(true, 1);
        lcdif_send_cmd(false, 0xc);
        lcdif_send_cmd(true, 0);
        lcdif_send_cmd(false, 0x11);
        lcdif_send_cmd(true, 0x202);
        lcdif_send_cmd(false, 0x12);
        lcdif_send_cmd(true, 0x101);
        lcdif_send_cmd(false, 0x13);
        lcdif_send_cmd(true, 1);
        lcdif_send_cmd(false, 0x90);
        lcdif_send_cmd(true, 0x8000);
        lcdif_send_cmd(false, 0x210);
        lcdif_send_cmd(true, 0);
        lcdif_send_cmd(false, 0x211);
        lcdif_send_cmd(true, 0xef);
        lcdif_send_cmd(false, 0x212);
        lcdif_send_cmd(true, 0);
        lcdif_send_cmd(false, 0x213);
        lcdif_send_cmd(true, 0x18f);
        lcdif_send_cmd(false, 0x200);
        lcdif_send_cmd(true, 0);
        lcdif_send_cmd(false, 0x201);
        lcdif_send_cmd(true, 0);
        lcdif_send_cmd(false, 0x401);
        lcdif_send_cmd(true, 1);
        lcdif_send_cmd(false, 0x404);
        lcdif_send_cmd(true, 0);
        udelay(40000);
        lcdif_send_cmd(false, 7);
        lcdif_send_cmd(true, 0x100);
        udelay(40000);

        lcdif_send_cmd(false, 3);
        lcdif_send_cmd(true, 0x1028); /* 0x1023 ? 0x5028 ? */
    }
    else
    {
    }
}

#if 0
void lcdif_schedule_refresh(void *buffer, unsigned h_count, unsigned v_count)
{
    logf("refresh %dx%d\n", h_count, v_count);
    lcdif_send_cmd_data(0x50, 0);
    lcdif_send_cmd_data(0x51, h_count - 1);
    lcdif_send_cmd_data(0x52, 0);
    lcdif_send_cmd_data(0x53, v_count - 1);
    lcdif_send_cmd_data(0x20, 0);
    lcdif_send_cmd_data(0x21, 0);
    lcdif_send_cmd_data(0x22, 0);
    lcdif_wait_ready();
    HW_LCDIF_CUR_BUF = (uint32_t)buffer;
    if(g_lcdif_word_length != HW_LCDIF_CTRL__WORD_LENGTH_24_BIT)
    {
        logf("lcdif_schedule_refresh: don't handle word_length=%x\n", g_lcdif_word_length);
        return;
    }
    HW_LCDIF_TRANSFER_COUNT = 0;
    HW_LCDIF_TRANSFER_COUNT = (v_count << 16) | h_count;
    __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__RUN;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__DATA_SELECT;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__RUN;
    logf("refresh done\n");
}
#else
void lcdif_schedule_refresh(void *buffer, unsigned h_count, unsigned v_count)
{
    logf("refresh %dx%d\n", h_count, v_count);
    lcdif_send_cmd(false, 0x210);
    lcdif_send_cmd(true, 0);
    lcdif_send_cmd(false, 0x211);
    lcdif_send_cmd(true, h_count - 1);
    lcdif_send_cmd(false, 0x212);
    lcdif_send_cmd(true, 0);
    lcdif_send_cmd(false, 0x213);
    lcdif_send_cmd(true, v_count - 1);
    lcdif_send_cmd(false, 0x200);
    lcdif_send_cmd(true, 0);
    lcdif_send_cmd(false, 0x201);
    lcdif_send_cmd(true, 0);
    lcdif_send_cmd(false, 0x202);
    
    lcdif_wait_ready();
    __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__WORD_LENGTH_BM;
    __REG_CLR(HW_LCDIF_CTRL1) = HW_LCDIF_CTRL1__BYTE_PACKING_FORMAT_BM;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__WORD_LENGTH_16_BIT;
    __REG_SET(HW_LCDIF_CTRL1) = 0xf << HW_LCDIF_CTRL1__BYTE_PACKING_FORMAT_BP;
    g_lcdif_word_length = HW_LCDIF_CTRL__WORD_LENGTH_16_BIT;
    HW_LCDIF_CUR_BUF = (uint32_t)buffer;
    HW_LCDIF_TRANSFER_COUNT = 0;
    HW_LCDIF_TRANSFER_COUNT = (v_count << 16) | h_count;
    __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__RUN;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__DATA_SELECT;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__RUN;
    logf("refresh done\n");
}
#endif

#elif defined(SONY_NWZE360)

static void lcdif_write_byte(bool is_data, uint8_t v)
{
    uint32_t cmd = v;
    logf("lcdif_write_byte\n");
    __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__WORD_LENGTH_BM;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__WORD_LENGTH_8_BIT;
    g_lcdif_word_length = HW_LCDIF_CTRL__WORD_LENGTH_8_BIT;
    __REG_CLR(HW_LCDIF_CTRL1) = HW_LCDIF_CTRL1__BYTE_PACKING_FORMAT_BM;
    __REG_SET(HW_LCDIF_CTRL1) = 0xf << HW_LCDIF_CTRL1__BYTE_PACKING_FORMAT_BP;
    __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__INPUT_DATA_SWIZZLE_BM;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__INPUT_DATA_SWIZZLE__NO_SWAP;

    lcdif_send(is_data, 1, (void *)&cmd);
}

static void lcdif_write_reg(uint8_t reg, uint8_t val)
{
    lcdif_write_byte(false, reg);
    lcdif_write_byte(true, val);
}

void lcd_init_seq(void)
{
    lcdif_write_reg(0xEA, 0);
    lcdif_write_reg(0xEB, 0x20);
    lcdif_write_reg(0xEC, 0xC);
    lcdif_write_reg(0xED, 0xC4);
    lcdif_write_reg(0xE8, 0x38);
    lcdif_write_reg(0xE9, 0xE);
    lcdif_write_reg(0xF1, 1);
    lcdif_write_reg(0xF2, 8);
    lcdif_write_reg(0x2E, 0x86);
    lcdif_write_reg(0x29, 0xFF);
    lcdif_write_reg(0xE4, 1);
    lcdif_write_reg(0xE5, 0x20);
    lcdif_write_reg(0xE7, 1);
    lcdif_write_reg(0x40, 0);
    lcdif_write_reg(0x41, 0);
    lcdif_write_reg(0x42, 0);
    lcdif_write_reg(0x43, 0x14);
    lcdif_write_reg(0x44, 0x14);
    lcdif_write_reg(0x45, 0x28);
    lcdif_write_reg(0x46, 0x11);
    lcdif_write_reg(0x47, 0x57);
    lcdif_write_reg(0x48, 5);
    lcdif_write_reg(0x49, 0x16);
    lcdif_write_reg(0x4A, 0x19);
    lcdif_write_reg(0x4B, 0x1A);
    lcdif_write_reg(0x4C, 0x1A);
    lcdif_write_reg(0x50, 0x17);
    lcdif_write_reg(0x51, 0x2B);
    lcdif_write_reg(0x52, 0x2B);
    lcdif_write_reg(0x53, 0x3F);
    lcdif_write_reg(0x54, 0x3F);
    lcdif_write_reg(0x55, 0x3F);
    lcdif_write_reg(0x56, 0x28);
    lcdif_write_reg(0x57, 0x6E);
    lcdif_write_reg(0x58, 5);
    lcdif_write_reg(0x59, 5);
    lcdif_write_reg(0x5A, 6);
    lcdif_write_reg(0x5B, 9);
    lcdif_write_reg(0x5C, 0x1A);
    lcdif_write_reg(0x5D, 0xCC);
    lcdif_write_reg(0x1B, 0x1B);
    lcdif_write_reg(0x1A, 1);
    lcdif_write_reg(0x24, 0x2F); // something special here
    lcdif_write_reg(0x25, 0x57); // something special here
    lcdif_write_reg(0x23, 0x8A);
    lcdif_write_reg(0x2F, 1);
    lcdif_write_reg(0x60, 0);
    lcdif_write_reg(0x16, 8);
    lcdif_write_reg(0x18, 0x36); // something special here
    lcdif_write_reg(0x19, 1);
    udelay(5000);
    lcdif_write_reg(1, 0);
    lcdif_write_reg(0x1F, 0x88);
    udelay(5000);
    lcdif_write_reg(0x1F, 0x80);
    udelay(5000);
    lcdif_write_reg(0x1F, 0x90);
    udelay(5000);
    lcdif_write_reg(0x1F, 0xD0);
    udelay(5000);
    lcdif_write_reg(0x17, 6);
    lcdif_write_reg(0x37, 0);
    lcdif_write_reg(0x28, 0x38);
    udelay(40000);
    lcdif_write_reg(0x28, 0x3C);
}

void lcd_enable(bool enable)
{
    static bool init_seq = false;
    if(!init_seq)
    {
        lcd_init_seq();
        init_seq = true;
    }
    
    if(!enable)
    {
        lcdif_write_reg(0x1F, 0xD1);
        lcdif_write_reg(1, 0x40);
        lcdif_write_reg(1, 0xC0);
        lcdif_write_reg(0x19, 1);
    }
    else
    {
        lcdif_write_reg(0x19, 0x81);
        udelay(5000);
        lcdif_write_reg(1, 0x40);
        udelay(20000);
        lcdif_write_reg(1, 0);
        lcdif_write_reg(0x1F, 0xD0);
    }
}

void lcdif_schedule_refresh(void *buffer, unsigned w, unsigned h)
{
    int x = 0;
    int y = 0;
    logf("refresh %dx%d\n", w, h);
    lcdif_write_reg(2, x >> 8);
    lcdif_write_reg(3, x & 0xff);
    lcdif_write_reg(4, (x + w - 1) >> 8);
    lcdif_write_reg(5, (x + w - 1) & 0xff);
    lcdif_write_reg(6, y >> 8);
    lcdif_write_reg(7, y & 0xff);
    lcdif_write_reg(8, (y + h - 1) >> 8);
    lcdif_write_reg(9, (y + h - 1) & 0xff);
    lcdif_write_byte(false, 0x22);

    lcdif_wait_ready();
    __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__WORD_LENGTH_BM;
    __REG_CLR(HW_LCDIF_CTRL1) = HW_LCDIF_CTRL1__BYTE_PACKING_FORMAT_BM;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__WORD_LENGTH_16_BIT;
    __REG_SET(HW_LCDIF_CTRL1) = 0xf << HW_LCDIF_CTRL1__BYTE_PACKING_FORMAT_BP;
    g_lcdif_word_length = HW_LCDIF_CTRL__WORD_LENGTH_16_BIT;
    __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__INPUT_DATA_SWIZZLE_BM;
    //__REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__INPUT_DATA_SWIZZLE__BIG_ENDIAN_SWAP;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__INPUT_DATA_SWIZZLE__NO_SWAP;
    HW_LCDIF_CUR_BUF = (uint32_t)buffer;
    HW_LCDIF_TRANSFER_COUNT = 0;
    HW_LCDIF_TRANSFER_COUNT = (h << 16) | w;
    __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__RUN;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__DATA_SELECT;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__RUN;
    logf("refresh done\n");
}

#elif defined(CREATIVE_ZENXFI3)

static void lcdif_write_data(bool is_data, uint16_t v)
{
    uint32_t cmd = v;
    logf("lcdif_write_byte\n");
    __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__WORD_LENGTH_BM;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__WORD_LENGTH_16_BIT;
    g_lcdif_word_length = HW_LCDIF_CTRL__WORD_LENGTH_16_BIT;
    __REG_CLR(HW_LCDIF_CTRL1) = HW_LCDIF_CTRL1__BYTE_PACKING_FORMAT_BM;
    __REG_SET(HW_LCDIF_CTRL1) = 0xf << HW_LCDIF_CTRL1__BYTE_PACKING_FORMAT_BP;
    __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__INPUT_DATA_SWIZZLE_BM;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__INPUT_DATA_SWIZZLE__NO_SWAP;

    lcdif_send(is_data, 2, (void *)&cmd);
}

static void lcdif_write_reg(uint16_t reg, uint16_t val)
{
    lcdif_write_data(false, reg);
    lcdif_write_data(true, val);
}

void lcd_init_seq(void)
{
    lcdif_write_reg(1, 0x11c);
    lcdif_write_reg(2, 0x100);
    lcdif_write_reg(3, 0x1030);
    lcdif_write_reg(8, 0x808);
    lcdif_write_reg(0xc, 0);
    lcdif_write_reg(0xf, 0xc01);
    lcdif_write_reg(0x20, 0);
    lcdif_write_reg(0x21, 0);
    udelay(30);
    lcdif_write_reg(0x10, 0xa00);
    lcdif_write_reg(0x11, 0x1038);
    lcdif_write_reg(0x000, 0x000);
    udelay(30);
    lcdif_write_reg(0x12, 0x1010);
    lcdif_write_reg(0x13, 0x50);
    lcdif_write_reg(0x14, 0x4f58);
    lcdif_write_reg(0x30, 0);
    lcdif_write_reg(0x31, 0xdb);//
    lcdif_write_reg(0x32, 0);
    lcdif_write_reg(0x33, 0);
    lcdif_write_reg(0x34, 0xdb);//
    lcdif_write_reg(0x35, 0);
    lcdif_write_reg(0x36, 0xaf);//
    lcdif_write_reg(0x37, 0);
    lcdif_write_reg(0x38, 0xdb);//
    lcdif_write_reg(0x39, 0);
    lcdif_write_reg(0x50, 0);
    lcdif_write_reg(0x51, 0x705);
    lcdif_write_reg(0x52, 0xe0a);
    lcdif_write_reg(0x53, 0x300);
    lcdif_write_reg(0x54, 0xa0e);
    lcdif_write_reg(0x55, 0x507);
    lcdif_write_reg(0x56, 0);
    lcdif_write_reg(0x57, 3);
    lcdif_write_reg(0x58, 0x90a);
    lcdif_write_reg(0x59, 0xa09);
    udelay(30);
    lcdif_write_reg(7, 0x1017);
    udelay(40);
    /*
    lcdif_write_data(false, 0x22);
    for(int i = 0; i < 0x9740; i++)
        lcdif_write_data(true, 0);
    */
}

void lcd_enable(bool enable)
{
    static bool init_seq = false;
    if(!init_seq)
    {
        lcd_init_seq();
        init_seq = true;
    }

    if(!enable)
    {
    }
    else
    {
    }
}

void lcdif_schedule_refresh(void *buffer, unsigned w, unsigned h)
{
    logf("refresh %dx%d\n", w, h);
    
    lcdif_write_reg(0x36, w - 1);
    lcdif_write_reg(0x37, 0);
    lcdif_write_reg(0x38, h - 1);
    lcdif_write_reg(0x39, 0);
    lcdif_write_reg(0x20, 0);
    lcdif_write_reg(0x21, 0);
    lcdif_write_data(false, 0x22);
    lcdif_wait_ready();
    __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__WORD_LENGTH_BM;
    __REG_CLR(HW_LCDIF_CTRL1) = HW_LCDIF_CTRL1__BYTE_PACKING_FORMAT_BM;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__WORD_LENGTH_16_BIT;
    __REG_SET(HW_LCDIF_CTRL1) = 0xf << HW_LCDIF_CTRL1__BYTE_PACKING_FORMAT_BP;
    g_lcdif_word_length = HW_LCDIF_CTRL__WORD_LENGTH_16_BIT;
    __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__INPUT_DATA_SWIZZLE_BM;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__INPUT_DATA_SWIZZLE__NO_SWAP;
    HW_LCDIF_CUR_BUF = (uint32_t)buffer;
    HW_LCDIF_TRANSFER_COUNT = 0;
    HW_LCDIF_TRANSFER_COUNT = (h << 16) | w;
    __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__RUN;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__DATA_SELECT;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__RUN;
    logf("refresh done\n");
}

struct lcdif_dma_command_t
{
    struct apb_dma_command_t cmd;
    /* pio */
    uint32_t ctrl;
} __attribute__((packed,aligned(16)));

#define NR_CMDS 3
struct lcdif_dma_command_t lcdif_dma[NR_CMDS];

void lcdif_schedule_continuous_refresh(void *buffer, unsigned w, unsigned h)
{
    logf("refresh %dx%d\n", w, h);

    lcdif_write_reg(0x36, w - 1);
    lcdif_write_reg(0x37, 0);
    lcdif_write_reg(0x38, h - 1);
    lcdif_write_reg(0x39, 0);
    lcdif_write_reg(0x20, 0);
    lcdif_write_reg(0x21, 0);
    lcdif_write_data(false, 0x22);
    lcdif_wait_ready();
    __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__WORD_LENGTH_BM;
    __REG_CLR(HW_LCDIF_CTRL1) = HW_LCDIF_CTRL1__BYTE_PACKING_FORMAT_BM;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__WORD_LENGTH_16_BIT;
    __REG_SET(HW_LCDIF_CTRL1) = 0xf << HW_LCDIF_CTRL1__BYTE_PACKING_FORMAT_BP;
    g_lcdif_word_length = HW_LCDIF_CTRL__WORD_LENGTH_16_BIT;
    __REG_CLR(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__INPUT_DATA_SWIZZLE_BM;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__INPUT_DATA_SWIZZLE__NO_SWAP;

    HW_LCDIF_TRANSFER_COUNT = (h << 16) | w;

    int rem_size = w * h * 2;
    for(int i = 0; i < NR_CMDS; i++)
    {
        int xfer_size = MIN(rem_size, IMX233_MAX_SINGLE_DMA_XFER_SIZE);
        lcdif_dma[i].cmd.next = &lcdif_dma[(i + 1) % NR_CMDS].cmd;
        lcdif_dma[i].cmd.buffer = buffer;
        lcdif_dma[i].cmd.cmd = HW_APB_CHx_CMD__COMMAND__READ |
            HW_APB_CHx_CMD__CHAIN |
            xfer_size << HW_APB_CHx_CMD__XFER_COUNT_BP;
        logf("rem_size=0x%x xfer_size=0x%x\n", rem_size, xfer_size);
        logf("cmd[%d][0x%x] nxt=0x%x buf=0x%x cmd=0x%x\n", i,
             (uint32_t)&lcdif_dma[i].cmd, lcdif_dma[i].cmd.next,
             lcdif_dma[i].cmd.buffer, lcdif_dma[i].cmd.cmd);
        rem_size -= xfer_size;
        buffer += xfer_size;
    }

    lcdif_dma[0].cmd.cmd |= 1 << HW_APB_CHx_CMD__CMDWORDS_BP;
    lcdif_dma[0].ctrl = HW_LCDIF_CTRL__RUN | HW_LCDIF_CTRL__DATA_SELECT;
    lcdif_dma[NR_CMDS - 1].cmd.cmd |= HW_APB_CHx_CMD__WAIT4ENDCMD;

    dma_clkgate_channel(APB_LCDIF, true);
    dma_reset_channel(APB_LCDIF);
    dma_start_command(APB_LCDIF, &lcdif_dma[0].cmd);
}

#elif defined(INSIGNIA_INFOCAST35)

#define LCD_HEIGHT  240
#define LCD_WIDTH   320

uint16_t framebuffer[LCD_HEIGHT * LCD_WIDTH];

void lcd_enable(bool enable)
{
    static bool init_seq = false;
    if(!init_seq)
    {
        init_seq = true;
    }

    if(!enable)
    {
    }
    else
    {
    }
}

void lcdif_schedule_refresh(void *buffer, unsigned w, unsigned h)
{
    uint16_t *buf = buffer;
    for(int y = 0; y < MIN(h, LCD_HEIGHT); y++)
        for(int x = 0; x < MIN(w, LCD_WIDTH); x++)
            framebuffer[y * LCD_WIDTH + x] = buf[y * w + x];

    HW_LCDIF_CUR_BUF = framebuffer;
    HW_LCDIF_NEXT_BUF = framebuffer;

    HW_LCDIF_TRANSFER_COUNT = LCD_HEIGHT << 16 | LCD_WIDTH;
    HW_LCDIF_CTRL1 = 0xf << HW_LCDIF_CTRL1__BYTE_PACKING_FORMAT_BP |
        HW_LCDIF_CTRL1__RECOVER_ON_UNDERFLOW | HW_LCDIF_CTRL1__RESET;
    __REG_SET(HW_LCDIF_CTRL) = HW_LCDIF_CTRL__RUN;
}

#endif

void lcd_set_backlight(int steps)
{
#if defined(CREATIVE_ZENXFI2)
    imx233_pwm_setup_channel(4, 1024, HW_PWM_PERIODx__CDIV__DIV_1,
        0, HW_PWM_PERIODx__STATE__HIGH,
        (steps * 1024) / 100, HW_PWM_PERIODx__STATE__LOW);
    imx233_pwm_enable_channel(4, true);
#elif defined(CREATIVE_ZENXFI3)
    imx233_pwm_setup_channel(2, 1024, HW_PWM_PERIODx__CDIV__DIV_1,
        0, HW_PWM_PERIODx__STATE__HIGH,
        (steps * 1024) / 100, HW_PWM_PERIODx__STATE__LOW);
    imx233_pwm_enable_channel(2, true);
#elif defined(SONY_NWZE360)
    imx233_set_pin_function(0, 10, PINCTRL_FUNCTION_GPIO);
    imx233_enable_gpio_output(0, 10, true);
    imx233_set_gpio_output(0, 10, false);
    imx233_pwm_setup_channel(2, 2400, HW_PWM_PERIODx__CDIV__DIV_1,
        0, HW_PWM_PERIODx__STATE__HIGH,
        (steps * 2400) / 100, HW_PWM_PERIODx__STATE__LOW);
    imx233_pwm_enable_channel(2, true);
    imx233_set_gpio_output(0, 10, true);
#elif defined(INSIGNIA_INFOCAST35)
    imx233_pwm_setup_channel(2, 1024, HW_PWM_PERIODx__CDIV__DIV_64,
        0, HW_PWM_PERIODx__STATE__HIGH,
        (steps * 1024) / 100, HW_PWM_PERIODx__STATE__LOW);
    imx233_pwm_enable_channel(2, true);
#endif
}
