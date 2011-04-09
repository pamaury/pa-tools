#include "config.h"
#include "stdint.h"
#include "s3c2440.h"
#include "s3c2440_ext.h"
#include "usb_ch9.h"
#include "sysfont.h"

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
    if(g_console_y > g_console_by)
        g_console_y = g_console_ty;
}

void print_str(const char *str)
{
    console_skip(print_str_xy(str, console_params()));
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
     * pclk: hclk / 2
     * hclk: fclk / 4
     * fclk: mpll */
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
    print_str_xy("<Rockbox>", 70, 10, WHITE, TRANSPARENT);

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

/*******
 * USB *
 *******/

#define EP0_PKT_LEN     8
#define EP1_PKT_LEN     32

uint8_t *g_send_data_ptr = NULL;
unsigned g_send_data_size = 0;
bool g_send_zpl = false;
uint8_t ep1_data[EP1_PKT_LEN];

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
        .bEndpointAddress = 1,
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

void usb_stall_ep0()
{
    dbg_print_str("**stall");
    dbg_console_newline();
    INDEX_REG = 0;
    EP0_CSR |= SEND_STALL;
}

void usb_stall_ep1()
{
    dbg_print_str("**stall ep1");
    dbg_console_newline();
    INDEX_REG = 1;
    OUT_CSR1_REG |= SEND_STALL;
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
        EP0_CSR = IN_PKT_RDY | DATA_END;
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
            print_str("device desc");
            console_newline();
            desc = &device_descriptor;
            desc_size = sizeof(struct usb_device_descriptor);
            break;
        case USB_DT_CONFIG:
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
    {
        send_done_data();
        send_data(desc, MIN(setup.wLength, desc_size));
    }
}

void usb_get_status()
{
    usb_stall_ep0();
}

void usb_handle_setup(struct usb_ctrlrequest setup)
{
    print_str("setup: ");
    print_str_num("bRequestType=", setup.bRequestType);
    print_str_num(" bRequest=", setup.bRequest);
    console_newline();

    if((setup.bRequestType & USB_TYPE_MASK) != USB_TYPE_STANDARD)
        return usb_stall_ep0();

    if((setup.bRequestType & USB_RECIP_MASK ) == USB_RECIP_DEVICE)
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
                send_done_nodata();
                break;
            default:
                usb_stall_ep0();
        }
    }
    else if(setup.bRequestType == (USB_DIR_IN | USB_TYPE_STANDARD | USB_RECIP_INTERFACE))
    {
        usb_stall_ep0();
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
    IN_CSR2_REG = 0;
    INDEX_REG = 1;
    OUT_CSR1_REG = 0;
    INDEX_REG = 1;
    OUT_CSR2_REG = 0;
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

extern uint32_t _ramstart;

void usb_screen()
{
    usb_init();
    
    while(1)
    {
        uint16_t fcol = YELLOW;
        uint16_t bcol = BLUE;

        uint8_t *download_address = (uint8_t *)&_ramstart;
        bool download_finished = false;
        
        clear_screen(bcol);
        print_str_xy("<Rockbox USB mode>", 70, 10, fcol, TRANSPARENT);
        setup_console(10, 20, SCREEN_HEIGHT, fcol, bcol);

        print_str_num("download address: ", (uint32_t)download_address);
        console_newline();

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

                if(EP0_CSR & SETUP_END)
                {
                    INDEX_REG = 0;
                    EP0_CSR = SRV_SETUP_END; 
                }
                if(!(EP0_CSR & IN_PKT_RDY) && g_send_data_ptr != NULL)
                {
                    continue_send_data();
                }
                if(EP0_CSR & OUT_PKT_RDY)
                {
                    struct usb_ctrlrequest setup;
                    if(usb_fifo_read(0, &setup, sizeof(struct usb_ctrlrequest)) == sizeof(struct usb_ctrlrequest))
                        usb_handle_setup(setup);
                }
                if(EP0_CSR & SENT_STALL)
                {
                    print_str("**ack stall");
                    console_newline();
                    EP0_CSR &= ~SEND_STALL;
                }
            }
            /*
            else if(EP_INT_REG & EP1_INTERRUPT)
            {
                EP_INT_REG = EP1_INTERRUPT;
                
                INDEX_REG = 1;
                print_str_num("EP1 interrupt: ", OUT_CSR1_REG);
                console_newline();
                
                INDEX_REG = 1;
                while(OUT_CSR1_REG & OUT_PKT_RDY)
                {
                    int size = usb_fifo_size_out(1);
                    print_str_num("EP1 data: ", size);
                    console_newline();
                    
                    usb_fifo_read(1, ep1_data, size);
                    memcpy(download_address, ep1_data, size);
                    download_address += size;

                    INDEX_REG = 1;
                    OUT_CSR1_REG &= ~OUT_PKT_RDY;

                    if(size < EP1_PKT_LEN)
                    {
                        download_finished = true;
                        break;
                    }
                }
                if(OUT_CSR1_REG & SENT_STALL)
                {
                    print_str("**ack stall ep1");
                    console_newline();
                    INDEX_REG = 1;
                    OUT_CSR2_REG &= ~SEND_STALL;
                }

                INDEX_REG = 1;
                print_str_num("  after EP1: ", OUT_CSR1_REG);
                print_str_num(" fifo: ", usb_fifo_size_out(1));
                console_newline();
            }
            */
            else if(!EVT_USB())
                break;

            INDEX_REG = 1;
            if(OUT_CSR1_REG & OUT_PKT_RDY)
            {
                int size = usb_fifo_size_out(1);
                print_str_num("EP1 data: ", size);
                console_newline();
                
                usb_fifo_read(1, ep1_data, size);
                memcpy(download_address, ep1_data, size);
                download_address += size;

                INDEX_REG = 1;
                OUT_CSR1_REG &= ~OUT_PKT_RDY;

                if(size < EP1_PKT_LEN)
                {
                    download_finished = true;
                    break;
                }
            }
        }

        usb_disconnect();
        usb_power_off();

        fcol = WHITE;
        bcol = RED;
        clear_screen(bcol);
        setup_console(10, 20, SCREEN_HEIGHT, fcol, bcol);
        print_str("disconnect     ");
        console_newline();
        if(download_finished)
        {
            uint8_t *fw_addr = (uint8_t *)&_ramstart;
            print_str_num("firmware size: ", download_address - fw_addr);
            console_newline();
            print_str("check model string...");
            char str[5];
            memcpy(str, fw_addr + 4, 4);
            str[4] = 0;
            console_skip(print_str_xy(str, console_x(), console_y(), YELLOW, RED));
            if(str[0] == 'm' && str[1] == '2' && str[2] == '4' && str[3] == '4')
            {
                console_skip(print_str_xy("(OK)", console_x(), console_y(), WHITE, RED));
                console_newline();
            }
            else
            {
                console_skip(print_str_xy("(ERROR)", console_x(), console_y(), BLUE, RED));
                console_newline();
                goto Lerror;
            }
            
            print_str("compute checksum...");

            uint32_t chksum = 131; /* modelnum = 131 <=> mini 2440 */
            /* add 8 unsigned bits but keep a 32 bit sum */
            for(unsigned i = 8; i < download_address - fw_addr; i++)
                chksum += fw_addr[i];
            console_skip(print_num_xy(chksum, console_x(), console_y(), YELLOW, RED));

            /* checksum is in big-endian */
            uint32_t expected = (fw_addr[0] << 24) | (fw_addr[1] << 16) |
                (fw_addr[2] << 8) | fw_addr[3];

            if(chksum == expected)
            {
                console_skip(print_str_xy("(OK)", console_x(), console_y(), WHITE, RED));
                console_newline();
            }
            else
            {
                console_skip(print_str_num_xy("(ERROR)", expected, console_x(), console_y(), BLUE, RED));
                console_newline();
                goto Lerror;
            }

            print_str("Press menu to run...");
            console_newline();
            print_str("Press power to cancel...");
            console_newline();
            while(1)
            {
                if(KEY_POWER())
                    goto Lend;
                if(KEY_MENU())
                    break;
            }

            __asm volatile(
                "bx    %0   \n"
                : : "r"(fw_addr)
            );

            Lerror:
            print_str("Press power to continue...");
            console_newline();

            Lend:
            while(!KEY_POWER());
        }
        
        while(!EVT_USB());
    }
}

void main()
{
    /* Power down useless peripherals */
    CLKCON &= ~(CLKCON_NAND | CLKCON_USBH | CLKCON_USBD | CLKCON_SDI |
                CLKCON_UART0 | CLKCON_UART1 | CLKCON_UART2 |
                CLKCON_I2C | CLKCON_I2S | CLKCON_SPI | CLKCON_CAM |
                CLKCON_AC97);

    init_clocks();
    /* Without this, SD detection doesn't work with GPF7,
     * but on the other hand GPF6 seems to do the job.
     * WinCE does it this way, so let's do it. */
    GPFDAT = 0x60; 
    init_display();

    gpio_screen();
    usb_screen();
    
    while(1);
}
