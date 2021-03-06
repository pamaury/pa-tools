#include "config.h"
#include "stdint.h"
#include "s3c2440.h"
#include "s3c2440_ext.h"
#include "usb_ch9.h"
#include "sysfont.h"

#define PAGE_SIZE     2048

/* GPIOS:
 * Keys:
 *  Minus (-)  <=> GPG5 (low)
 *  Plus (+) <=> GPG4 (low)
 *  Menu <=> GPG3 (low)
 *  Power <=> GPF0 (low)
 *  Reset <=> GPF2 (low)
 * USB:
 *   GPG1 (low)
 * SD:
 *   GPF7 (low)
 * Jack:
 *   GPE12 (low)
 * Battery:
 *   Charging <=> GPG9 (unsure)
 * Chargin led:
 *   orange <=> GPG11 (low)
 *   green <=> GPG11 (high
 *   other effect ?
 */

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define RGB565(r,g,b)   (((r) << 11) | ((g) << 5) | (b))

#define SCREEN_WIDTH    240
#define SCREEN_HEIGHT   320
#define SCREEN_DEPTH    2

#define TRANSPARENT     0x10000

#define BLACK           RGB565(0, 0, 0)
#define RED             RGB565(0x1F, 0, 0)
#define GREEN           RGB565(0, 0x3F, 0)
#define BLUE            RGB565(0, 0, 0x1F)
#define YELLOW          RGB565(0x1F, 0x3F, 0)
#define CYAN            RGB565(0, 0x3F, 0x1F)
#define MAGENTA         RGB565(0x1F, 0, 0x1F)
#define WHITE           RGB565(0x1F, 0x3F, 0x1F)

#define KEY_MINUS()     !(GPGDAT & (1 << 5))
#define KEY_PLUS()      !(GPGDAT & (1 << 4))
#define KEY_MENU()      !(GPGDAT & (1 << 3))
#define KEY_POWER()     !(GPFDAT & (1 << 0))
#define KEY_RESET()     !(GPFDAT & (1 << 2))
#define EVT_USB()       !(GPGDAT & (1 << 1))
#define EVT_SD()        !(GPFDAT & (1 << 7))
#define EVT_HACK()      !(GPEDAT & (1 << 12))
#define EVT_CHARGING()  ((GPBDAT & (1 << 9)) >> 9)

/********
 * Font *
 ********/

unsigned strlen(const char *s)
{
    unsigned i = 0;
    while(*s++)
        i++;
    return i;
}

unsigned get_string_font_length(const char *str)
{
    return strlen(str) * sysfont_width;
}

inline void put_pixel_xy(unsigned x, unsigned y, unsigned col)
{
    if(col != TRANSPARENT)
        FRAME[y * SCREEN_WIDTH + x] = col;
}

void clear_screen_rect(int x, int y, int w, int h, uint16_t color)
{
    for(unsigned dy = 0; dy < h; dy++)
        for(unsigned dx = 0; dx < w; dx++)
            FRAME[(y + dy) * SCREEN_WIDTH + (x + dx)] = color;
}

unsigned print_char_xy(char c, unsigned x, unsigned y, unsigned fcol, unsigned bcol)
{
    const unsigned char *data = &sysfont_bits[sysfont_offset[(unsigned)c]];
    for(unsigned dx = 0; dx < sysfont_width; dx++)
        for(unsigned dy = 0; dy < sysfont_height; dy++)
                put_pixel_xy(x + dx, y + dy, (data[dx] >> dy) & 1 ? fcol : bcol);
    return 1;
}

unsigned print_str_xy(const char *str, unsigned x, unsigned y, unsigned fcol, unsigned bcol)
{
    unsigned len = 0;
    while(*str)
    {
        print_char_xy(*str++, x, y, fcol, bcol);
        x += sysfont_width;
        len++;
    }
    return len;
}

unsigned print_num_xy(uint32_t num, unsigned x, unsigned y, unsigned fcol, unsigned bcol)
{
    char tmp[16];
    tmp[15] = 0;
    char *ptr = &tmp[14];

    if(num != 0)
    {
        while(num)
        {
            *ptr-- = (num & 0xf) + ((num & 0xf) < 10 ? '0' : 'A' - 10);
            num >>= 4;
        }
    }
    else
        *ptr-- = '0';
    return print_str_xy(ptr + 1, x, y, fcol, bcol);
}

unsigned print_str_num_xy(const char *str, uint32_t num, unsigned x, unsigned y, unsigned fcol, unsigned bcol)
{
    unsigned len = print_str_xy(str, x, y, fcol, bcol);
    return len + print_num_xy(num, x + get_string_font_length(str), y, fcol, bcol);
}

/***********
 * Console *
 ***********/
int g_console_lx, g_console_ty, g_console_by, g_console_y, g_console_x;
uint16_t g_console_fcol, g_console_bcol;

void setup_console(int lx, int ty, int by, uint16_t fcol, uint16_t bcol)
{
    g_console_lx = lx;
    g_console_ty = ty;
    g_console_by = by;
    g_console_y = ty;
    g_console_x = g_console_lx;
    g_console_fcol = fcol;
    g_console_bcol = bcol;
}

#define console_x() g_console_x
#define console_y() g_console_y
#define console_skip(dx) g_console_x += dx *sysfont_width
#define console_fcol() g_console_fcol
#define console_bcol() g_console_bcol
#define console_params() g_console_x, g_console_y, g_console_fcol, g_console_bcol

void console_newline()
{
    g_console_x = g_console_lx;
    g_console_y += sysfont_height;
    if((g_console_y + sysfont_height) > g_console_by)
        g_console_y = g_console_ty;
    clear_screen_rect(g_console_x, g_console_y, SCREEN_WIDTH - g_console_x,
        sysfont_height, g_console_bcol);
}

void print_str(const char *str)
{
    console_skip(print_str_xy(str, console_params()));
}

void print_char(char c)
{
    console_skip(print_char_xy(c, console_params()));
}

void print_str_intelligent(const char *str)
{
    while(*str)
    {
        char c = *str++;
        if(c == '\r')
            console_newline();
        else if(c == '\n')
            ;
        else
        {
            int nx = g_console_x + sysfont_width;
            if(nx > SCREEN_WIDTH)
                console_newline();
            print_char(c);
        }
    }
}

void print_num(uint32_t n)
{
    console_skip(print_num_xy(n, console_params()));
}

void print_str_num(const char *str, uint32_t n)
{
    print_str(str);
    print_num(n);
}

#if 0
#define dbg_console_newline console_newline
#define dbg_print_str print_str
#define dbg_print_num print_num
#define dbg_print_str_num print_str_num
#else
#define dbg_console_newline()
#define dbg_print_str(s)
#define dbg_print_num(n)
#define dbg_print_str_num(s,n)
#endif

/***********
 * Display *
 ***********/
extern void wait(unsigned int t);

void clear_screen(uint16_t color)
{
    for(unsigned y = 0; y < SCREEN_HEIGHT; y++)
        for(unsigned x = 0; x < SCREEN_WIDTH; x++)
            FRAME[y * SCREEN_WIDTH + x] = color;
}

void init_display()
{
    clear_screen(BLUE);

    GPGCON &= ~0xc00000;
    wait(0x32);
    GPCUP = 0xffffffff;
    GPCCON &= 0x3FFC03;
    GPCCON |= 0xAA8002A8;
    GPDUP = 0xffffffff;
    GPDCON &= 0x3F000F;
    GPDCON |= 0xAA80AAA0;
    GPBUP = 0xffffffff;
    GPBCON = (GPBCON & ~3) | 1;
    GPBDAT &= ~1;
    GPJDAT &= ~8;
    GPJDAT |= 4;
    GPJUP = 0xffff;
    GPJCON &= ~0xCF0;
    GPJCON |= 0x50;
    GPJDAT &= ~4;
    wait(1);
    GPJDAT |= 8;
    wait(1);
    /*
    INTMSK |= 0x400;
    SRCPND = 0x400;
    INTPND = 0x400;
    */
    TCFG0 &= ~0xff;
    TCFG0 |= 0x20;
    TCFG1 &= ~0xf;
    TCNTB0 = 0x2FF;
    TCMPB0 = 0xE6;
    TCON &= ~0xF;
    TCON |= 2;
    TCON &= ~0xF;
    TCON |= 9;
    wait(1);

    LCDCON1 = 0x978;
    LCDCON2 = 0x24FC080;
    LCDCON3 = 0x80EF0A;
    LCDCON4 = 0xD04;
    LCDCON5 = 0xB01;
    LCDSADDR1 = LCD_FRAME_ADDR / 2; /* assume properly aligned */
    LCDSADDR2 = ((LCD_FRAME_ADDR + SCREEN_WIDTH * SCREEN_HEIGHT * SCREEN_DEPTH) & 0x3FFFFF) / 2;
    LCDSADDR3 = 240;
    TPAL = 0;
    LCDCON1 |= 1;
    wait(0x64);

    GPBCON = (GPBCON & ~3) | 2;
    GPCCON &= ~0xC00;
    GPGCON &= ~0xC00000;
    GPGCON |= 0x400000;
}

extern void arm_clock_select();
extern void arm_clock_wait();

void init_clocks()
{
    /* fixme: doc says to set UPLLCON first and MPLLCON second,
     * WinCE does the reverse */
    /* fixme:
     * input: 16.9344MHz
     * mpll: 399.65 MHz ~ 400Mhz (for core)
     * upll: 47.98 MHz ~ 48Mhz (for USB)
     * fclk: mpll ~ 400MHz
     * hclk: fclk / 4 ~ 100MHz
     * pclk: hclk / 2 ~ 50MHz */
    CLKDIVN = 0x5;
    arm_clock_select();
    LOCKTIME = 0xffffffff;
    MPLLCON = 0x6E031;
    UPLLCON = 0x3C042;
    arm_clock_wait();
    /* setup timer 4 to tick every second:
     * we have PCLK @ 50Mhz (cf above)
     * we set the prescaler to 50-1
     * and the mux divider to 16
     * so we get a pwm input @ 62500Hz
     * by using a counter value of 62500 we
     * get a tick frequency @ 1Hz
     */
    TCFG0 &= ~(0xff << 8);
    TCFG0 |= ((50 - 1) << 8);
    TCFG1 &= ~(0xf << 16);
    TCFG1 |= 3 << 16; /* 3 is 1/16 divider */
    TCNTB4 = 62500;
    TCON = (TCON & ~0x100000) | 0x600000; /* timer 4: stop, auto reload, update */
    TCON = (TCON & ~0x200000) | 0x100000; /* timer 4: clear updater, start */
}

/***********
 * Battery *
 ***********/
#define VOLTAGE_NOT_AVAILABLE   -1

enum voltage_reading_state_t
{
    VOLTAGE_IDLE,
    VOLTAGE_WAIT_START,
    VOLTAGE_WAIT_END
};

int g_battery_voltage = VOLTAGE_NOT_AVAILABLE;
 
void update_battery_voltage()
{
    static enum voltage_reading_state_t state = VOLTAGE_IDLE;

    switch(state)
    {
        case VOLTAGE_IDLE:
            ADCCON = PRSCEN | (9 << PRSCVL_bitp);
            ADCTSC &= ~(UD_SEN | AUTO_PST);
            ADCCON |= ENABLE_START;
            state = VOLTAGE_WAIT_START;
            break;
        case VOLTAGE_WAIT_START:
            if(!(ADCCON & ENABLE_START))
                state = VOLTAGE_WAIT_END;
            break;
        case VOLTAGE_WAIT_END:
            if(ADCCON & ECFLG)
            {
                state = VOLTAGE_IDLE;
                g_battery_voltage = ADCDAT0 & XPDATA_bitm;
            }
            break;
        default:
            state = VOLTAGE_IDLE;
    }
}

int battery_voltage()
{
    return g_battery_voltage;
}

/*******
 * RTC *
 *******/
#define BCD2DEC(x)      ((((x) >> 4) & 0xf) * 10 + ((x) & 0xf))

struct tm
{
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

void rtc_init()
{
    RTCCON |= 1;
}

void rtc_read(struct tm *tm)
{
    tm->tm_sec = BCD2DEC(BCDSEC);
    tm->tm_min = BCD2DEC(BCDMIN);
    tm->tm_hour = BCD2DEC(BCDHOUR);
    tm->tm_wday = BCD2DEC(BCDDAY) - 1; /* timefuncs wants 0..6 for wday */
    tm->tm_mday = BCD2DEC(BCDDATE);
    tm->tm_mon = BCD2DEC(BCDMON) - 1;
    tm->tm_year = BCD2DEC(BCDYEAR) + 100;
}

/***************
 * GPIO screen *
 ***************/

void gpio_screen()
{
    clear_screen(BLUE);
    
    print_str_xy("<Kernel>", 70, 10, WHITE, TRANSPARENT);

    GPGCON |= 0x400000; /* GPG11 as output */
    bool set_gpg11 = false;
    bool key_menu = false;
    int ref_tcnto4 = TCNTO4;
    int last_tcnto4 = TCNTO4;
    int tick_count = 0;

    while(1)
    {
        int tcnto4 = TCNTO4;
        if(last_tcnto4 < ref_tcnto4 && ref_tcnto4 <= tcnto4)
            tick_count++;
        last_tcnto4 = tcnto4;
        
        update_battery_voltage();
        
        unsigned h = (sysfont_height * 3) >> 1;
        uint16_t fcol = YELLOW;
        uint16_t bcol = BLUE;
        print_str_num_xy(" GPA: ", GPADAT, 0, 20, fcol, bcol);
        print_str_num_xy(" GPB: ", GPBDAT, 0, 20 + h, fcol, bcol);
        print_str_num_xy(" GPC: ", GPCDAT, 0, 20 + 2 * h, fcol, bcol);
        print_str_num_xy(" GPD: ", GPDDAT, 0, 20 + 3 * h, fcol, bcol);
        print_str_num_xy(" GPE: ", GPEDAT, 0, 20 + 4 * h, fcol, bcol);
        print_str_num_xy(" GPF: ", GPFDAT, 0, 20 + 5 * h, fcol, bcol);
        print_str_num_xy(" GPG: ", GPGDAT, 0, 20 + 6 * h, fcol, bcol);
        print_str_num_xy(" GPH: ", GPHDAT, 0, 20 + 7 * h, fcol, bcol);
        print_str_num_xy(" GPJ: ", GPJDAT, 0, 20 + 8 * h, fcol, bcol);

        fcol = RED;
        bcol = BLACK;
        h = sysfont_height;
        print_str_xy("Keys:", 80, 20, fcol, bcol);
        print_str_num_xy(" Minus: ", KEY_MINUS(), 80, 20 + h, fcol, bcol);
        print_str_num_xy(" Plus: ", KEY_PLUS(), 80, 20 + 2 * h, fcol, bcol);
        print_str_num_xy(" Menu: ", KEY_MENU(), 80, 20 + 3 * h, fcol, bcol);
        print_str_num_xy(" Power: ", KEY_POWER(), 80, 20 + 4 * h, fcol, bcol);
        print_str_num_xy(" Reset: ", KEY_RESET(), 80, 20 + 5 * h, fcol, bcol);

        fcol = GREEN;
        bcol = BLACK;
        h = sysfont_height;
        print_str_xy("Hardware:", 160, 20, fcol, bcol);
        print_str_num_xy(" USB: ", EVT_USB(), 160, 20 + h, fcol, bcol);
        print_str_num_xy(" SD: ", EVT_SD(), 160, 20 + 2 * h, fcol, bcol);
        print_str_num_xy(" Jack: ", EVT_HACK(), 160, 20 + 3 * h, fcol, bcol);

        fcol = MAGENTA;
        bcol = BLACK;
        print_str_xy("Battery:", 80, 70, fcol, bcol);
        print_str_num_xy(" Charging: ", EVT_CHARGING() && EVT_USB(), 80, 70 + h, fcol, bcol);
        if(battery_voltage() == VOLTAGE_NOT_AVAILABLE)
            print_str_xy(" Voltage: N/A", 80, 70 + 2 * h, fcol, bcol);
        else
            print_str_num_xy(" Voltage: ", battery_voltage(), 80, 70 + 2 * h, fcol, bcol);

        fcol = YELLOW;
        bcol = BLACK;
        print_str_xy("Misc:", 80, 100, fcol, bcol);
        print_str_num_xy(" CLKCON: ", CLKCON, 80, 100 + h, fcol, bcol);

        fcol = WHITE;
        bcol = BLACK;
        print_str_xy("Tick:", 80, 120, fcol, bcol);
        print_str_num_xy("TCNTO4: ", TCNTO4, 80, 120 + h, fcol, bcol);
        print_str_num_xy("ticks: ", tick_count, 80, 120 + 2 * h, fcol, bcol);

        if(KEY_MENU())
        {
            key_menu = true;
        }
        if(key_menu && !KEY_MENU())
        {
            key_menu = false;
            set_gpg11 = !set_gpg11;
            if(set_gpg11)
                GPGDAT |= 0x800;
            else
                GPGDAT &= ~0x800;
        }

        if(KEY_POWER())
            break;
    }
}

/********
 * UART *
 ********/

/*
 * UART configs:
 * - config 1:
 *   - UART: 1
 *   - DRT: GPH6
 *   - DSR: GPH7
 * - config 2:
 *   - UART: 2
 *
 */

void uart1_init()
{
    // GPH{4,5} as {T,R}XD[1]
    GPHCON &= ~0xF00;
    GPHCON |= 0xA00;
    GPHUP |= 0x30;
    
    //UCON1 = 0x245; // int/polling rx/tx mode, rx timeout, UEXTCLOCK
    UCON1 = 0x45; // int/polling rx/tx mode, rx timeout, PCLK
    UFCON1 = 0x1; // FIFO enable: 16 bytes RX
    UMCON1 = 0;
    ULCON1 = 3; // 8-bits, one stop bit, no parity, normal mode
    UTRSTAT1 = 0;
    UERSTAT1 = 0;
    UFSTAT1 = 0;
    UMSTAT1 = 0;
    // PCLK ~ 50MHz, we want 9600bps so UBRDIV = 50000000 / (9600 x 16) - 1
    /* |   BPS  | DIV
     * | 4800   | 650
     * | 9600   | 324
     * | 14400  | 216
     * | 19200  | 161
     * | 38400  | 80
     * | 57600  | 53
     * | 115200 | 26
     */
    UBRDIV1 = 650;
}

void gps_init()
{
}

void gps_enable(bool enable)
{
    if(enable)
    {
        GPJDAT &= ~0x100;
        GPJDAT &= ~0x1000;
        GPJDAT |= 0x400;
        GPJDAT |= 1;
        GPJDAT |= 0x80;

        GPJDAT &= ~1;
        GPJDAT &= ~0x1000;
        wait(260);
        GPJDAT |= 0x1000;
        
        GPJDAT |= 0x80;
    }
    else
    {
        GPJDAT &= ~0x80;
        GPJDAT |= 1;
        GPJDAT &= ~0x1000;
    }
}

void uart2_init()
{
    // GPH{5,6} as {T,R}XD[2]
    GPHCON &= ~0xF000;
    GPHUP |= 0xC0;
    GPHCON |= 0xA000;
    GPJDAT &= ~0x80;
    GPHUP |= 0x80;
    GPJCON |= 0x4000;
}

int uart1_receive(unsigned char *buf, int size)
{
    int read = 0;
    if(UERSTAT1)
        UFCON1 |= 1; /* flush fifo */
    while((UFSTAT1 & 0x3f) > 0)
    {
        if(read++ < size)
            *buf++ = URXH1;
        else
            (void) URXH1;
    }
    return MIN(read, size);
}

unsigned char gps_buffer[10000];

void gps_screen()
{
    gps_init();
    while(1)
    {
        uint16_t fcol = YELLOW;
        uint16_t bcol = BLUE;
        
        clear_screen(bcol);
        print_str_xy("<GPS screen>", 70, 10, fcol, TRANSPARENT);
        setup_console(10, 20, SCREEN_HEIGHT, fcol, bcol);
        gps_enable(true);
        uart1_init();
        while(1)
        {
            int gps_size = uart1_receive(gps_buffer, sizeof(gps_buffer) - 1);
            gps_buffer[gps_size] = 0;

            print_str_intelligent(gps_buffer);

            if(KEY_MENU())
                break;
        }
        //gps_enable(false);
        console_newline();
        print_str("STOP");
        while(!KEY_POWER())
            ;
    }
}

/*******
 * GPS *
 *******/

#define CMD_READ                    0x30
#define CMD_READID                  0x90        //  ReadID
#define CMD_STATUS                  0x70        //  Status read
#define CMD_RESET                   0xff        //  Reset

//  Status bit pattern
#define STATUS_READY                0x40        //  Ready
#define STATUS_ERROR                0x01        //  Error

#define NF_CMD(cmd)	    {NFCMD  = (cmd); }
#define NF_ADDR(addr)	{NFADDR = (addr); }	
#define NF_nFCE_L()	    {NFCONT &= ~(1<<1); }
#define NF_nFCE_H()	    {NFCONT |= (1<<1); }
#define NF_RSTECC()	    {NFCONT |= (1<<4); }
#define NF_RDDATA() 	(NFDATA)
#define NF_WRDATA(data) {NFDATA = (data); }
#define NF_WAITRB()     {while(!(NFSTAT&(1<<0)));} 
#define NF_CLEAR_RB()	{NFSTAT |= (1<<2); }
#define NF_DETECT_RB()	{while(!(NFSTAT&(1<<2)));}
#define NF_MECC_UnLock()	{NFCONT &= ~(1<<5);}
#define NF_MECC_Lock()		{NFCONT |= (1<<5);}

#define NF_CE_L()     NF_nFCE_L()
#define NF_CE_H()     NF_nFCE_H()
#define NF_DATA_R()   NFDATA
#define NF_DATA_RH()  NFDATA_H
#define NF_DATA_RB()  NFDATA_B

void nand_reset()
{                       
    NF_CE_L();
    NF_CLEAR_RB();
    NF_CMD(CMD_RESET);  
    NF_CE_H();          
}

void nand_read_id(uint8_t *resp)
{
    NF_CE_L();
    NF_CLEAR_RB();
    NF_CMD(CMD_READID);
    NF_ADDR(0x00);
    
    NF_WAITRB();

    for(int i = 0; i < 5; i++)
        *resp++ = NF_DATA_RB();

    NF_CE_H();
}

void nand_read(unsigned column, unsigned row, bool ecc, uint8_t *buf, unsigned size,
    uint8_t (*data_ecc)[3])
{
    if(ecc)
    {
        NF_RSTECC();
        NF_MECC_UnLock();
    }
    NF_nFCE_L();
    NF_CLEAR_RB();
    NF_CMD(0x00);
    NF_ADDR(column & 0xff);
    NF_ADDR(column >> 8);
    NF_ADDR(row & 0xff);
    NF_ADDR((row >> 8) & 0xff);
    NF_ADDR((row >> 16) & 0xff);
    NF_CMD(CMD_READ);

    NF_WAITRB();

    for(int i = 0; i < size; i++)
        *buf++ = NF_DATA_RB();

    if(ecc)
    {
        NF_MECC_Lock();
        (*data_ecc)[0] = NFMECCSTAT0 & 0xff;
        (*data_ecc)[1] = (NFMECCSTAT0 >> 8) & 0xff;
        (*data_ecc)[2] = (NFMECCSTAT0 >> 16) & 0xff;
    }
}

void nand_read_sector(unsigned page, unsigned sec, uint8_t *buf)
{
    uint8_t data_ecc[3];
    nand_read(sec << 9, page, true, buf, 512, &data_ecc);
    uint8_t flash_ecc[3];
    nand_read(2048 + 8 + 16 * sec, page, false, flash_ecc, 3, NULL);

    if(data_ecc[0] != flash_ecc[0] || data_ecc[1] != flash_ecc[1] ||
            data_ecc[2] != flash_ecc[2])
    {
        print_str_num("Page ", page);
        print_str_num(" Sector ", sec);
        print_str(": ECC error");
        console_newline();
        print_num(data_ecc[0]);
        print_str_num(" ", data_ecc[1]);
        print_str_num(" ", data_ecc[2]);
        print_str_num(" -- ", flash_ecc[0]);
        print_str_num(" ", flash_ecc[1]);
        print_str_num(" ", flash_ecc[2]);
        console_newline();
    }
}

void nand_read_page(unsigned page_num, uint8_t *buf)
{
    #if 0
    NF_RSTECC();
    NF_MECC_UnLock();
    NF_nFCE_L();
    NF_CLEAR_RB();
    NF_CMD(0x00);
    NF_ADDR(0x00);
    NF_ADDR(0x00);
    NF_ADDR(sec_num & 0xff);
    NF_ADDR((sec_num >> 8) & 0xff);
    NF_ADDR((sec_num >> 16) & 0xff);
    NF_CMD(CMD_READ);

    NF_WAITRB();

    unsigned data_ecc[4][3];
    for(int i = 0; i < 4; i++)
    {
        
        for(int i = 0; i < 512; i++)
            *buf++ = NF_DATA_RB();
        data_ecc[i][0] = NFMECC0 & 0xff;
        data_ecc[i][1] = (NFMECC0 >> 16) & 0xff;
        data_ecc[i][2] = NFMECC1 & 0xff;
    }

    NF_MECC_Lock();

    unsigned flash_ecc[4][3];
    for(int i = 0; i < 4; i++)
    {
        /* skip 8 bytes */
        for(int j = 0; j < 8; j++)
            (void)NF_DATA_RB();
        /* read ECC */
        for(int j = 0; j < 3; j++)
            flash_ecc[i][j] = NF_DATA_RB();
        /* skip 5 bytes */
        for(int j = 0; j < 5; j++)
            (void)NF_DATA_RB();
    }

    NF_nFCE_H();

    bool error = false;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 3; j++)
            if(flash_ecc[i][j] != data_ecc[i][j])
                error = true;

    if(error)
    {
        print_str("ECC error:");
        console_newline();
        for(int i = 0; i <  4; i++)
        {
            print_str_num("S", i);
            for(int j = 0; j < 3; j++)
                print_str_num(" ", flash_ecc[i][j]);
            print_str(" --");
            for(int j = 0; j < 3; j++)
                print_str_num(" ", data_ecc[i][j]);
            console_newline();
        }
    }
    #else
    nand_read_sector(page_num, 0, buf);
    nand_read_sector(page_num, 1, buf + 512);
    nand_read_sector(page_num, 2, buf + 1024);
    nand_read_sector(page_num, 3, buf + 1536);
    #endif
}

uint8_t nand_buffer[PAGE_SIZE];

void nand_screen()
{
    clear_screen(BLUE);
    setup_console(0, 0, SCREEN_HEIGHT, WHITE, BLUE);
    print_str("NAND screen");
    console_newline();
    print_str_num("NFCONF: ", NFCONF);
    print_str_num(" NFCONT: ", NFCONT);
    console_newline();

    /* HCLK = 100Mhz
     * tALE=tCLE >= 12ns
     *
     */
    NFCONF = 0x1530;
    NFCONT = 0x13;
    NFSTAT = 0;
    /* Read ID */
    uint8_t id[5];
    nand_read_id(id);
    print_str_num("Maker: ", id[0]);
    print_str_num(" Device: ", id[1]);
    print_str_num(" 3rd: ", id[2]);
    console_newline();
    print_str_num("4th: ", id[3]);
    print_str_num(" 5th: ", id[4]);
    console_newline();
    /* Read first sector */
    nand_read_page(0, nand_buffer);
    print_str("First page:");
    console_newline();
    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            uint8_t v = nand_buffer[i * 12 + j];
            char str[4];
            str[0] = (v >> 4);
            if(str[0] >= 10) str[0] += 'A' - 10; else str[0] += '0';
            str[1] = (v & 0xf);
            if(str[1] >= 10) str[1] += 'A' - 10; else str[1] += '0';
            str[2] = ' ';
            str[3] = 0;
            print_str(str);
        }
        console_newline();
    }
}

/*******
 * USB *
 *******/

#define EP0_PKT_LEN     8
#define EP1_PKT_LEN     64

uint8_t *g_send_data_ptr = NULL;
unsigned g_send_data_size = 0;
bool g_send_zpl = false;
uint8_t ep1_data[EP1_PKT_LEN];
uint8_t nand_usb_buffer[PAGE_SIZE];
int g_nand_usb_buf_rem_len = 0;
uint8_t *g_nand_usb_buf_ptr = NULL;
uint32_t g_checksum_buf[2];
bool g_verbose = true;

static struct usb_device_descriptor device_descriptor=
{
    .bLength            = sizeof(struct usb_device_descriptor),
    .bDescriptorType    = USB_DT_DEVICE,
    .bcdUSB             = 0x0110,
    .bDeviceClass       = USB_CLASS_PER_INTERFACE,
    .bDeviceSubClass    = 0,
    .bDeviceProtocol    = 0,
    .bMaxPacketSize0    = EP0_PKT_LEN,
    .idVendor           = 0x5345,
    .idProduct          = 0x1234,
    .bcdDevice          = 0x0100,
    .iManufacturer      = 0,
    .iProduct           = 0,
    .iSerialNumber      = 0,
    .bNumConfigurations = 1
};

#define USB_MAX_CURRENT     500

struct
{
    struct usb_config_descriptor config_desc;
    struct usb_interface_descriptor intf_desc;
    struct usb_endpoint_descriptor ep_desc;
} config_descriptor =
{
    .config_desc =
    {
        .bLength             = sizeof(struct usb_config_descriptor),
        .bDescriptorType     = USB_DT_CONFIG,
        .wTotalLength        = sizeof(config_descriptor),
        .bNumInterfaces      = 1,
        .bConfigurationValue = 1,
        .iConfiguration      = 0,
        .bmAttributes        = USB_CONFIG_ATT_ONE | USB_CONFIG_ATT_SELFPOWER,
        .bMaxPower           = (USB_MAX_CURRENT + 1) / 2, /* In 2mA units */
    },
    .intf_desc =
    {
        .bLength            = sizeof(struct usb_interface_descriptor),
        .bDescriptorType    = USB_DT_INTERFACE,
        .bInterfaceNumber   = 0,
        .bAlternateSetting  = 0,
        .bNumEndpoints      = 1,
        .bInterfaceClass    = USB_CLASS_VENDOR_SPEC,
        .bInterfaceSubClass = 0,
        .bInterfaceProtocol = 0,
        .iInterface         = 0
    },
    .ep_desc =
    {
        .bLength          = sizeof(struct usb_endpoint_descriptor),
        .bDescriptorType  = USB_DT_ENDPOINT,
        .bEndpointAddress = 0x81,
        .bmAttributes     = USB_ENDPOINT_XFER_BULK,
        .wMaxPacketSize   = EP1_PKT_LEN,
        .bInterval        = 0
    }
};

void memcpy(void *dst, const void *src, unsigned size)
{
    while(size--)
        *(uint8_t *)dst++ = *(uint8_t *)src++;
}

unsigned usb_fifo_size_out(int ep)
{
    INDEX_REG = ep;
    return OUT_FIFO_CNT1_REG | (OUT_FIFO_CNT2_REG << 8);
}

unsigned usb_fifo_read(int ep, void *ptr, unsigned size)
{
    unsigned fifo_size = usb_fifo_size_out(ep);
    dbg_print_str_num("**fifo read: ", fifo_size);
    dbg_console_newline();
    if(fifo_size > size)
        size = fifo_size;
    INDEX_REG = ep;
    volatile uint8_t *reg = &EPx_FIFO(ep);
    while(fifo_size--)
        *(uint8_t *)ptr++ = *reg;
    return size;
}

void usb_fifo_write(int ep, void *ptr, unsigned size)
{
    INDEX_REG = ep;
    volatile uint8_t *reg = &EPx_FIFO(ep);
    while(size--)
        *reg = *(uint8_t *)ptr++;
}

void usb_flush_tx_fifo(int ep)
{
    INDEX_REG = ep;
    IN_CSR1_REG |= FIFO_FLUSH;
}

void usb_stall_ep0()
{
    dbg_print_str("**stall");
    dbg_console_newline();
    INDEX_REG = 0;
    EP0_CSR |= SEND_STALL | SRV_OUT_PKT_RDY;
}

void usb_stall_ep1()
{
    dbg_print_str("**stall ep1");
    dbg_console_newline();
    INDEX_REG = 1;
    OUT_CSR1_REG |= SEND_STALL | OUT_PKT_RDY;
}

void continue_send_data()
{
    dbg_print_str("continue send");
    dbg_console_newline();
            
    if(g_send_data_ptr == NULL)
        return;

    if(g_send_data_size == 0)
    {
        dbg_print_str("**send ZLP");
        dbg_console_newline();
        if(g_send_zpl)
        {
            INDEX_REG = 0;
            EP0_CSR = IN_PKT_RDY | DATA_END;
        }
        g_send_data_ptr = NULL;
        g_send_zpl = false;
        return;
    }

    int i = MIN(g_send_data_size, EP0_PKT_LEN);
    dbg_print_str_num("**fifo write: ", i);
    dbg_console_newline();
    g_send_data_size -= i;
    while(i-- > 0)
        EP0_FIFO = *g_send_data_ptr++;

    INDEX_REG = 0;
    if(g_send_data_size == 0)
    {
        EP0_CSR = IN_PKT_RDY | DATA_END;
        g_send_data_ptr = NULL;
    }
    else
        EP0_CSR = IN_PKT_RDY;
}

void send_data(void *data, unsigned size)
{
    g_send_data_ptr = data;
    g_send_data_size = size;
    g_send_zpl = (size % EP0_PKT_LEN) == 0;

    continue_send_data();
}

void send_done_data()
{
    INDEX_REG = 0;
    EP0_CSR = SRV_OUT_PKT_RDY;
}

void send_done_nodata()
{
    INDEX_REG = 0;
    EP0_CSR = SRV_OUT_PKT_RDY | DATA_END;
}

void usb_get_desc(struct usb_ctrlrequest setup)
{
    void *desc = NULL;
    unsigned desc_size = 0;
    
    switch(setup.wValue >> 8)
    {
        case USB_DT_DEVICE:
            send_done_data();
            print_str("device desc");
            console_newline();
            desc = &device_descriptor;
            desc_size = sizeof(struct usb_device_descriptor);
            break;
        case USB_DT_CONFIG:
            send_done_data();
            print_str("config desc");
            console_newline();
            desc = &config_descriptor;
            desc_size = config_descriptor.config_desc.wTotalLength;
            break;
        default:
            break;
    }

    if(desc == NULL)
        usb_stall_ep0();
    else
        send_data(desc, MIN(setup.wLength, desc_size));
}

void usb_get_status()
{
    usb_stall_ep0();
}

int usb_config_set = 0;

void usb_handle_setup(struct usb_ctrlrequest setup)
{
    if(g_verbose)
    {
        print_str("setup: ");
        print_str_num("bRequestType=", setup.bRequestType);
        print_str_num(" bRequest=", setup.bRequest);
        console_newline();
        print_str_num("wValue=", setup.wValue);
        print_str_num(" wIndex=", setup.wIndex);
        print_str_num(" wLength=", setup.wLength);
        console_newline();
    }

    if((setup.bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD &&
            (setup.bRequestType & USB_RECIP_MASK) == USB_RECIP_DEVICE)
    {
        switch(setup.bRequest)
        {
            case USB_REQ_GET_STATUS: return usb_get_status();
            case USB_REQ_SET_ADDRESS:
                print_str_num("set address: ", setup.wValue);
                console_newline();
                FUNC_ADDR_REG = setup.wValue;
                FUNC_ADDR_REG |= ADDR_UPDATE;
                send_done_nodata();
                break;
            case USB_REQ_GET_DESCRIPTOR: return usb_get_desc(setup);
            case USB_REQ_SET_CONFIGURATION:
                print_str_num("set config: ", setup.wValue);
                console_newline();
                usb_config_set = 1;
                send_done_nodata();
                break;
            default:
                usb_stall_ep0();
        }
    }
    else if(setup.bRequestType == (USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE) &&
            setup.bRequest == 0xf1)
    {
        print_str_num("Verbose set: ", setup.wValue);
        console_newline();
        send_done_nodata();
        g_verbose = setup.wValue;
    }
    else if(setup.bRequestType == (USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE) &&
            setup.bRequest == 0x2e)
    {
        if(g_verbose)
        {
            print_str_num("Read page: ", setup.wValue);
            console_newline();
        }
        send_done_nodata();

        nand_read_page(setup.wValue, nand_usb_buffer);
        g_nand_usb_buf_rem_len = PAGE_SIZE;
        g_nand_usb_buf_ptr = nand_usb_buffer;
        g_checksum_buf[0] = 0;
        g_checksum_buf[1] = 0;
        uint32_t *tmp_ptr = (uint32_t *)nand_usb_buffer;
        for(int i = 0; i < PAGE_SIZE / 4; i++)
        {
            g_checksum_buf[0] += tmp_ptr[i];
            g_checksum_buf[1] ^= tmp_ptr[i];
        }
    }
    else if(setup.bRequestType == (USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE) &&
            setup.bRequest == 0x2f)
    {
        if(g_verbose)
        {
            print_str_num("Read checksums: ", g_checksum_buf[0]);
            print_str_num(" ", g_checksum_buf[1]);
            console_newline();
        }
        send_done_data();
        send_data(g_checksum_buf, MIN(8, setup.wLength));
    }
    else if(setup.bRequestType == (USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE) &&
            setup.bRequest == 0x2d)
    {
        if(g_verbose)
        {
            print_str("Transfer page");
            console_newline();
        }
        send_done_data();
        send_data(nand_usb_buffer, MIN(setup.wLength, PAGE_SIZE));
    }
    else
    {
        usb_stall_ep0();
    }
}

void usb_bus_reset()
{
    g_send_data_ptr = NULL;
    g_send_data_size = 0;
    g_send_zpl = false;

    FUNC_ADDR_REG = 0;

    /* EP 0 */
    INDEX_REG = 0;
    MAXP_REG = EP0_PKT_LEN >> 3;
    INDEX_REG = 0;
    EP0_CSR |= SRV_OUT_PKT_RDY | SETUP_END;
    /* EP 1 */
    INDEX_REG = 1;
    MAXP_REG = EP1_PKT_LEN >> 3;
    INDEX_REG = 1;
    IN_CSR1_REG = 0;
    INDEX_REG = 1;
    IN_CSR2_REG = MODE_IN;
}

void usb_init()
{
    GPGUP |= 0x100;
    GPGCON &= ~0x30000;
    GPGUP |= 2;
    GPGCON &= ~0xC;
    GPJDAT &= ~0x200;
}

void usb_power_on()
{
    CLKCON |= CLKCON_USBD;
    MISCCR &= ~0x3008;
    /* fixme: why does the OF fiddle with non-existent pins ? */
    GPBCON &= ~0xC0000000;
    GPBCON |= 0x40000000;
    GPBUP &= ~0x8000;
    GPBDAT |= 0x8000;
}

void usb_connect()
{
    GPJDAT |= 0x200;
}

void usb_disconnect()
{
    GPJDAT &= ~0x200;
}

void usb_power_off()
{
    CLKCON &= ~CLKCON_USBD;
    MISCCR |= 0x3000;
    /* fixme: why does the OF fiddle with non-existent pins ? */
    GPBCON &= ~0xC0000000;
    GPBCON |= 0x40000000;
    GPBUP |= 0x8000;
    GPBDAT &= ~0x8000;
}

void usb_screen()
{
    usb_init();
    
    while(1)
    {
        uint16_t fcol = YELLOW;
        uint16_t bcol = BLUE;
        
        clear_screen(bcol);
        print_str_xy("<Rockbox USB mode>", 70, 10, fcol, TRANSPARENT);
        setup_console(10, 20, SCREEN_HEIGHT, fcol, bcol);
        
        usb_config_set = 0;

        usb_power_on();

        PWR_REG = 0;
        EP_INT_REG = EP0_INTERRUPT | EP1_INTERRUPT;
        USB_INT_REG = RESET_INT;
        EP_INT_EN_REG = EP0_INTERRUPT | EP1_INTERRUPT;
        USB_INT_EN_REG = RESET_INT;

        usb_connect();
        
        while(1)
        {
            if(USB_INT_REG & RESET_INT)
            {
                print_str("reset interrupt");
                console_newline();

                usb_bus_reset();

                USB_INT_REG = RESET_INT;
            }
            else if(EP_INT_REG & EP0_INTERRUPT)
            {
                EP_INT_REG = EP0_INTERRUPT;
                
                //print_str_num("EP0 interrupt: ", EP0_CSR);
                //console_newline();
                INDEX_REG = 0;
                unsigned long ep0_csr = EP0_CSR;

                if(ep0_csr & SETUP_END)
                {
                    g_send_data_ptr = NULL;
                    //print_str("<<setup end>>");
                    //console_newline();
                    INDEX_REG = 0;
                    EP0_CSR = SRV_SETUP_END; 
                }
                if(!(ep0_csr & IN_PKT_RDY) && g_send_data_ptr != NULL)
                {
                    //print_str("<<continue send>>");
                    //console_newline();
                    continue_send_data();
                }
                if(ep0_csr & OUT_PKT_RDY)
                {
                    //print_str("<<setup packet>>");
                    //console_newline();
                    struct usb_ctrlrequest setup;
                    if(usb_fifo_read(0, &setup, sizeof(struct usb_ctrlrequest)) == sizeof(struct usb_ctrlrequest))
                        usb_handle_setup(setup);
                }
                if(ep0_csr & SENT_STALL)
                {
                    print_str("**ack stall");
                    INDEX_REG = 0;
                    console_newline();
                    EP0_CSR &= ~SEND_STALL;
                }
            }
            else if(!EVT_USB())
                break;

            INDEX_REG = 1;
            if(usb_config_set && !(IN_CSR1_REG & IN_PKT_RDY_EPx) &&
                    g_nand_usb_buf_rem_len > 0)
            {
                int size = MIN(g_nand_usb_buf_rem_len, EP1_PKT_LEN);
                usb_fifo_write(1, g_nand_usb_buf_ptr, size);
                g_nand_usb_buf_ptr += size;
                g_nand_usb_buf_rem_len -= size;

                INDEX_REG = 1;
                IN_CSR1_REG |= IN_PKT_RDY_EPx;
            }
        }

        usb_disconnect();
        usb_power_off();

        print_str("Disconnect");
        console_newline();

        while(!KEY_POWER());
    }
}

void mem_screen(void)
{
    uint16_t fcol = YELLOW;
    uint16_t bcol = BLUE;
    
    clear_screen(bcol);
    print_str_xy("<MEM Setup>", 70, 10, fcol, TRANSPARENT);
    setup_console(10, 20, SCREEN_HEIGHT, fcol, bcol);
    print_str_num("GPACON: ", GPACON);
    console_newline();
    print_str_num("MISCCR: ", MISCCR);

    while(!KEY_POWER());
}

void main()
{
    /* Power down useless peripherals */
    CLKCON &= ~(CLKCON_USBH | CLKCON_USBD | CLKCON_SDI |
                CLKCON_UART0 | CLKCON_UART2 |
                CLKCON_I2C | CLKCON_I2S | CLKCON_SPI | CLKCON_CAM |
                CLKCON_AC97);
    CLKCON |= CLKCON_NAND | CLKCON_UART1;
    init_clocks();
    /* Without this, SD detection doesn't work with GPF7,
     * but on the other hand GPF6 seems to do the job.
     * WinCE does it this way, so let's do it. */
    GPFDAT = 0x60; 
    init_display();

    mem_screen();
    //gpio_screen();
    //usb_screen();
    //gps_screen();
    
    while(1);
}
