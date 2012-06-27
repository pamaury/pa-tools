#include <stdio.h>
#include <stdlib.h>
#include <libusb.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../protocol.h"
#include <unistd.h>

libusb_context *ctx;

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void usage(void)
{
    printf("usage: read_util <vid:pid> <action> [<parameters>]\n");
    printf("actions:\n");
    printf("  mem_read <addr> <len> <ofile>\n");
    printf("  mem_write32 <addr> <value>\n");
    printf("  otp_read <reg> <ofile>\n");
    printf("  ssp_cmd <ssp> read|write|nodata resp|noresp|longresp <cmd> <arg> <iofile>\n");
    printf("  lradc_read <hw chan> <div by 2> <acc> <num samples> <iofile>\n");
    printf("  i2c_poke <dev>\n");
    printf("  i2c_poke_generic <dev>\n");
    printf("  i2c_eeprom_read <dev> <addr> <length> <iofile>\n");
    printf("  i2c_eeprom_write <dev> <addr> <iofile>\n");
    printf("  pinctrl B<bank>P<pin> [<pin opt> list]\n");
    printf("  si4700_read <dev> [<reg>] <iofile>\n");
    printf("  si4700_write <dev> <reg> <value>\n");
    printf("  reset [clkctrl]\n");
    printf("  watchdog [<watchdog opt>]\n");
    printf("  stfm1000_read <dev> <reg> <iofile>\n");
    printf("  stfm1000_write <dev> <reg> <value>\n");
    printf("pin options:\n");
    printf("  function=main|alt1|alt2|gpio\n");
    printf("  drive=4|8|12|16\n");
    printf("  pull=yes|no\n");
    printf("  output=1|0\n");
    printf("  enable=yes|no\n");
    printf("watchdog options:\n");
    printf("  count=<count>\n");
    printf("  enable=yes|no\n");
    printf("If <ofile> is - then the output is pretty printed on stdout\n");
}

#define return_fatal(...) do{printf(__VA_ARGS__); return;}while(0)

FILE *g_output_file = NULL;
bool g_is_stdout = false;

void open_wrapper(const char *file)
{
    if(strcmp(file, "-") == 0)
    {
        g_is_stdout = true;
    }
    else
    {
        g_is_stdout = false;
        g_output_file = fopen(file, "wb");
        if(g_output_file == NULL)
            printf("Cannot open output file\n");
    }
}

void close_wrapper(void)
{
    if(!g_is_stdout)
        fclose(g_output_file);
}

void write_wrapper(void *buf, int len)
{
    if(!g_is_stdout)
    {
        fwrite(buf, len, 1, g_output_file);
    }
    else
    {
        uint8_t *b = buf;
        while(len > 0)
        {
            for(int i = 0; i < 16; i++)
            {
                if(i >= len)
                    printf("   ");
                else
                    printf("%02x ", b[i]);
            }
            for(int i = 0; i < 16; i++)
                printf("%c", i >= len ? '.' : isprint(b[i]) ? b[i] : '.');
            printf("\n");
            len -= 16;
            b += 16;
        }
    }
}

void mem_read(libusb_device_handle *handle, uint8_t int_ep, int argc, char **argv)
{
    if(argc != 3)
        return usage();
    char *end;
    unsigned long addr = strtoul(argv[0], &end, 0);
    if(*end != 0)
        return_fatal("Invalid address\n");
    unsigned long length = strtoul(argv[1], &end, 0);
    if(*end != 0)
        return_fatal("Invalid length\n");
    printf("Reading %#lx bytes at %#lx, writing to %s\n", length, addr, argv[2]);

    open_wrapper(argv[2]);
    
    uint8_t buffer[1024];
    int recv_size, ret;
    
    while(length > 0)
    {
        struct usb_cmd_mem_t cmd;
        cmd.hdr.cmd = CMD_MEMORY;
        cmd.hdr.flags = FLAGS_READ;
        cmd.addr = addr;
        cmd.length = MIN(length, 32);
        
        ret = libusb_control_transfer(handle,
                                      LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_DEVICE,
                                      USB_CMD_WRAPPED, 0, 0, (void *)&cmd, sizeof(cmd), 1000);
        if(ret < 0)
            return_fatal("transfer error at control stage\n");
        
        ret = libusb_interrupt_transfer(handle, int_ep, buffer, sizeof(buffer), &recv_size, 1000);
        if(ret < 0)
            return_fatal("transfer error at receive stage\n");
        write_wrapper(buffer, recv_size);
        
        addr += recv_size;
        length -= recv_size;
    }
    close_wrapper();
}

void mem_write32(libusb_device_handle *handle, uint8_t int_ep, int argc, char **argv)
{
    (void) int_ep;
    if(argc != 2)
        return usage();
    char *end;
    unsigned long addr = strtoul(argv[0], &end, 0);
    if(*end != 0)
        return_fatal("Invalid address\n");
    unsigned long value = strtol(argv[1], &end, 0);
    if(*end != 0)
        return_fatal("Invalid value\n");
    printf("Write 0x%lx at 0x%lx\n", value, addr);
    
    int ret;

    struct
    {
        struct usb_cmd_mem_t cmd;
        uint32_t data;
    }data;
    data.cmd.hdr.cmd = CMD_MEMORY;
    data.cmd.hdr.flags = FLAGS_WRITE;
    data.cmd.addr = addr;
    data.cmd.length = sizeof(data.data);
    data.data = value;

    ret = libusb_control_transfer(handle,
                                    LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_DEVICE,
                                    USB_CMD_WRAPPED, 0, 0, (void *)&data, sizeof(data), 1000);
    if(ret < 0)
        return_fatal("transfer error at control stage\n");
}

void otp_read(libusb_device_handle *handle, uint8_t int_ep, int argc, char **argv)
{
    if(argc != 2)
        return usage();
    char *end;
    unsigned long reg = strtoul(argv[0], &end, 0);
    if(*end != 0)
        return_fatal("Invalid register\n");
    printf("Reading OTP register %lu, writing to %s\n", reg, argv[2]);

    open_wrapper(argv[1]);

    uint8_t buffer[1024];
    int recv_size, ret;

    struct usb_cmd_read_otp_t cmd;
    cmd.hdr.cmd = CMD_OTP;
    cmd.hdr.flags = FLAGS_READ;
    cmd.reg = reg;

    ret = libusb_control_transfer(handle,
                                    LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_DEVICE,
                                    USB_CMD_WRAPPED, 0, 0, (void *)&cmd, sizeof(cmd), 1000);
    if(ret < 0)
        return_fatal("transfer error at control stage\n");

    ret = libusb_interrupt_transfer(handle, int_ep, buffer, sizeof(buffer), &recv_size, 1000);
    if(ret < 0)
        return_fatal("transfer error at receive stage\n");
    write_wrapper(buffer, recv_size);
    close_wrapper();
}

void ssp_cmd(libusb_device_handle *handle, uint8_t int_ep, int argc, char **argv)
{
    if(argc != 6)
        return usage();
    struct usb_cmd_ssp_t ssp;
    memset(&ssp, 0, sizeof(ssp));

    char *end;
    ssp.ssp = strtol(argv[0], &end, 0);
    if(*end != 0 || ssp.ssp < 1 || ssp.ssp > 2)
        return_fatal("Invalid ssp choice\n");

    ssp.hdr.cmd = CMD_SSP;
    if(strcmp(argv[1], "read") == 0)
        ssp.hdr.flags |= FLAGS_READ;
    else if(strcmp(argv[1], "write") == 0)
        ssp.hdr.flags |= FLAGS_WRITE;
    else if(strcmp(argv[1], "nodata") != 0)
        return_fatal("Invalid data mode choice\n");

    if(strcmp(argv[2], "noresp") == 0)
        ssp.hdr.flags |= FLAGS_SSP_NO_RESP;
    else if(strcmp(argv[2], "longresp") == 0)
        ssp.hdr.flags |= FLAGS_SSP_LONG_RESP;
    else if(strcmp(argv[2], "resp") != 0)
        return_fatal("Invalid response choice\n");
    
    
    ssp.cmd = strtol(argv[3], &end, 0);
    if(*end != 0)
        return_fatal("Invalid ssp command\n");
    ssp.arg = strtoul(argv[4], &end, 0);
    if(*end != 0)
        return_fatal("Invalid argument\n");

    if(ssp.hdr.flags & FLAGS_READ)
        open_wrapper("-");
    else
        open_wrapper(argv[5]);

    ssp.length = 512;
    int ret = libusb_control_transfer(handle,
                                  LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_DEVICE,
                                  USB_CMD_WRAPPED, 0, 0, (void *)&ssp, sizeof(ssp), 1000);
    if(ret < 0)
        return_fatal("transfer error at control stage\n");

    struct usb_resp_ssp_t resp;
    int recv_size;
    ret = libusb_interrupt_transfer(handle, int_ep, (void *)&resp, sizeof(resp), &recv_size, 1000);
    if(ret < 0)
        return_fatal("transfer error at first receive stage\n");
    write_wrapper(&resp, recv_size);
    if(ssp.hdr.flags & FLAGS_READ)
    {
        close_wrapper();
        open_wrapper(argv[5]);
    }
    while(resp.length > 0)
    {
        uint8_t buffer[64];
        ret = libusb_interrupt_transfer(handle, int_ep, (void *)buffer, sizeof(buffer), &recv_size, 1000);
        if(ret < 0)
            return_fatal("transfer error at data stage\n");
        write_wrapper(buffer, recv_size);
        resp.length -= recv_size;
    }
    
    close_wrapper();
}

void lradc_read(libusb_device_handle *handle, uint8_t int_ep, int argc, char **argv)
{
    if(argc != 5)
        return usage();
    struct usb_cmd_lradc_t lradc;
    memset(&lradc, 0, sizeof(lradc));

    char *end;
    long dummy = strtol(argv[0], &end, 0);
    if(*end != 0 || dummy < 0 || dummy > LRADC_NUM_CHANNELS)
        return_fatal("Invalid hw_chan choice\n");
    lradc.hw_chan = dummy;
    
    lradc.hdr.cmd = CMD_LRADC;
    lradc.hdr.flags |= FLAGS_READ;

    dummy = strtol(argv[1], &end, 0);
    if(*end != 0 || dummy < 0 || dummy > 1)
        return_fatal("Invalid div2 choice\n");
    if(dummy)
        lradc.hdr.flags |= FLAGS_LRADC_DIVIDE_BY_2;

    dummy = strtol(argv[2], &end, 0);
    if(*end != 0 || dummy < 0 || dummy > 1)
        return_fatal("Invalid acc choice\n");
    if(dummy)
        lradc.hdr.flags |= FLAGS_LRADC_ACCUMULATE;

    dummy = strtol(argv[3], &end, 0);
    if(*end != 0 || dummy < 0)
        return_fatal("Invalid num_samples choice\n");
    lradc.num_samples = dummy;
    
    open_wrapper(argv[4]);

    int ret = libusb_control_transfer(handle,
                                  LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_DEVICE,
                                  USB_CMD_WRAPPED, 0, 0, (void *)&lradc, sizeof(lradc), 1000);
    if(ret < 0)
        return_fatal("transfer error at control stage\n");

    struct usb_resp_lradc_t resp;
    int recv_size;
    ret = libusb_interrupt_transfer(handle, int_ep, (void *)&resp, sizeof(resp), &recv_size, 1000);
    if(ret < 0)
        return_fatal("transfer error at first receive stage\n");
    write_wrapper(&resp, recv_size);
    close_wrapper();
}

const char *i2c_errstr(uint32_t ctrl1)
{
    if(ctrl1 & HW_I2C_CTRL1__MASTER_LOSS_IRQ) return "master loss";
    if(ctrl1 & HW_I2C_CTRL1__NO_SLAVE_ACK_IRQ) return "no slave ack";
    if(ctrl1 & HW_I2C_CTRL1__DATA_ENGINE_COMPLT_IRQ) return "complete";
    if(ctrl1 & HW_I2C_CTRL1__SLAVE_STOP_IRQ) return "slave stop";
    if(ctrl1 & HW_I2C_CTRL1__EARLY_TERM_IRQ) return "early term";
    if(ctrl1 & HW_I2C_CTRL1__OVERSIZE_XFER_TERM_IRQ) return "oversize transfer";
    return "unknown";
}

bool i2c_success(uint32_t ctrl1)
{
    return (ctrl1 & HW_I2C_CTRL1__ALL_IRQ) == HW_I2C_CTRL1__DATA_ENGINE_COMPLT_IRQ;
}

void i2c_poke(libusb_device_handle *handle, uint8_t int_ep, int argc, char **argv)
{
    if(argc != 1)
        return usage();
    struct usb_cmd_i2c_poke_t i2c;
    memset(&i2c, 0, sizeof(i2c));

    char *end;
    long dummy = strtol(argv[0], &end, 0);
    if(*end != 0 || dummy < 0 || dummy > 255)
        return_fatal("Invalid dev_addr choice\n");
    i2c.dev_addr = dummy;

    i2c.hdr.cmd = CMD_I2C;
    i2c.hdr.flags |= FLAGS_I2C_POKE;

    open_wrapper(argv[4]);

    int ret = libusb_control_transfer(handle,
                                  LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_DEVICE,
                                  USB_CMD_WRAPPED, 0, 0, (void *)&i2c, sizeof(i2c), 1000);
    if(ret < 0)
        return_fatal("transfer error at control stage\n");

    struct usb_resp_i2c_poke_t resp;
    int recv_size;
    ret = libusb_interrupt_transfer(handle, int_ep, (void *)&resp, sizeof(resp), &recv_size, 1000);
    if(ret < 0)
        return_fatal("transfer error at first receive stage\n");
    write_wrapper(&resp, recv_size);
    close_wrapper();
    printf("status: %s\n", i2c_errstr(resp.ctrl1));
}

void i2c_poke_generic(libusb_device_handle *handle, uint8_t int_ep, int argc, char **argv)
{
    if(argc != 1)
        return usage();
    struct
    {
        struct usb_cmd_i2c_generic_t i2c;
        struct usb_cmd_i2c_stage_t stage;
        uint8_t dev_addr;
    }__attribute__((packed)) i2c;
    memset(&i2c, 0, sizeof(i2c));

    char *end;
    long dummy = strtol(argv[0], &end, 0);
    if(*end != 0 || dummy < 0 || dummy > 255)
        return_fatal("Invalid dev_addr choice\n");
    i2c.dev_addr = dummy;

    i2c.i2c.hdr.cmd = CMD_I2C;
    i2c.i2c.hdr.flags |= FLAGS_I2C_GENERIC;
    i2c.i2c.nr_stages = 1;
    i2c.stage.flags = FLAGS_I2C_STAGE_START | FLAGS_I2C_STAGE_STOP | FLAGS_I2C_STAGE_SEND;
    i2c.stage.length = 1;

    open_wrapper("-");

    int ret = libusb_control_transfer(handle,
                                  LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_DEVICE,
                                  USB_CMD_WRAPPED, 0, 0, (void *)&i2c, sizeof(i2c), 1000);
    if(ret < 0)
        return_fatal("transfer error at control stage\n");

    struct usb_resp_i2c_generic_t resp;
    int recv_size;
    ret = libusb_interrupt_transfer(handle, int_ep, (void *)&resp, sizeof(resp), &recv_size, 1000);
    if(ret < 0)
        return_fatal("transfer error at first receive stage\n");
    write_wrapper(&resp, recv_size);
    close_wrapper();
}

void i2c_eeprom_read(libusb_device_handle *handle, uint8_t int_ep, int argc, char **argv)
{
    if(argc != 4)
        return usage();
    struct
    {
        struct usb_cmd_i2c_generic_t i2c;
        struct usb_cmd_i2c_stage_t stage[3];
        uint8_t dev_addr;
        uint16_t addr;
        uint8_t dev_addr2;
    }__attribute__((packed)) i2c;
    memset(&i2c, 0, sizeof(i2c));

    char *end;
    long dummy = strtol(argv[0], &end, 0);
    if(*end != 0 || dummy < 0 || dummy > 0xff)
        return_fatal("Invalid dev_addr choice\n");
    i2c.dev_addr = dummy;
    i2c.dev_addr2 = dummy | 1;

    dummy = strtol(argv[1], &end, 0);
    if(*end != 0 || dummy < 0 || dummy > 0xffff)
        return_fatal("Invalid addr choice\n");
    i2c.addr = dummy << 8 | dummy >> 8;

    dummy = strtol(argv[2], &end, 0);
    if(*end != 0 || dummy < 0 || dummy > 0xffff)
        return_fatal("Invalid addr choice\n");
    unsigned length = dummy;

    i2c.i2c.hdr.cmd = CMD_I2C;
    i2c.i2c.hdr.flags |= FLAGS_I2C_GENERIC;
    i2c.i2c.nr_stages = 3;
    i2c.stage[0].flags = FLAGS_I2C_STAGE_START | FLAGS_I2C_STAGE_SEND;
    i2c.stage[0].length = 3;
    i2c.stage[1].flags = FLAGS_I2C_STAGE_START | FLAGS_I2C_STAGE_SEND;
    i2c.stage[1].length = 1;
    i2c.stage[2].flags = FLAGS_I2C_STAGE_STOP;
    i2c.stage[2].length = length;

    open_wrapper("-");

    int ret = libusb_control_transfer(handle,
                                  LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_DEVICE,
                                  USB_CMD_WRAPPED, 0, 0, (void *)&i2c, sizeof(i2c), 1000);
    if(ret < 0)
        return_fatal("transfer error at control stage\n");

    struct usb_resp_i2c_generic_t resp;
    int recv_size;
    ret = libusb_interrupt_transfer(handle, int_ep, (void *)&resp, sizeof(resp), &recv_size, 1000);
    if(ret < 0)
        return_fatal("transfer error at first receive stage\n");
    write_wrapper(&resp, recv_size);
    close_wrapper();
    open_wrapper(argv[3]);
    while(resp.length > 0)
    {
        uint8_t buffer[64];
        ret = libusb_interrupt_transfer(handle, int_ep, (void *)buffer, sizeof(buffer), &recv_size, 1000);
        if(ret < 0)
            return_fatal("transfer error at data stage\n");
        write_wrapper(buffer, recv_size);
        resp.length -= recv_size;
    }
    close_wrapper();
}

void i2c_eeprom_write(libusb_device_handle *handle, uint8_t int_ep, int argc, char **argv)
{
    if(argc != 3)
        return usage();
    struct
    {
        struct usb_cmd_i2c_generic_t i2c;
        struct usb_cmd_i2c_stage_t stage;
        uint8_t dev_addr;
        uint16_t addr;
        uint8_t buffer[1];
    }__attribute__((packed)) i2c;

    char *end;
    long dummy = strtol(argv[0], &end, 0);
    if(*end != 0 || dummy < 0 || dummy > 0xff)
        return_fatal("Invalid dev_addr choice\n");
    i2c.dev_addr = dummy;

    unsigned addr = strtol(argv[1], &end, 0);
    if(*end != 0 || dummy < 0 || dummy > 0xffff)
        return_fatal("Invalid addr choice\n");
    i2c.addr = addr << 8 | addr >> 8;

    FILE *f = fopen(argv[2], "rb");
    if(f == NULL)
        return_fatal("Cannot open iofile");
    open_wrapper("-");

    while(true)
    {
        unsigned xfer = sizeof(i2c.buffer);
        
        i2c.i2c.hdr.cmd = CMD_I2C;
        i2c.i2c.hdr.flags |= FLAGS_I2C_GENERIC;
        i2c.i2c.nr_stages = 1;
        i2c.stage.flags = FLAGS_I2C_STAGE_START | FLAGS_I2C_STAGE_STOP | FLAGS_I2C_STAGE_SEND;
        i2c.stage.length = 3;
        i2c.addr = addr << 8 | addr >> 8;
        addr++;

        xfer = fread(i2c.buffer, 1, xfer, f);
        i2c.stage.length += xfer;
        
        if(xfer == 0)
            break;
        printf("xfer=%d\n", xfer);
    
        int ret = libusb_control_transfer(handle,
                                    LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_DEVICE,
                                    USB_CMD_WRAPPED, 0, 0, (void *)&i2c, sizeof(i2c), 1000);
        if(ret < 0)
            return_fatal("transfer error at control stage\n");

        struct usb_resp_i2c_generic_t resp;
        int recv_size;
        ret = libusb_interrupt_transfer(handle, int_ep, (void *)&resp, sizeof(resp), &recv_size, 1000);
        if(ret < 0)
            return_fatal("transfer error at first receive stage\n");
        write_wrapper(&resp, recv_size);
        usleep(5000);
    }
    fclose(f);
    close_wrapper();
}

void pinctrl(libusb_device_handle *handle, uint8_t int_ep, int argc, char **argv)
{
    if(argc == 0)
        return usage();

    struct usb_cmd_pinctrl_t pinctrl;
    memset(&pinctrl, 0, sizeof(pinctrl));

    pinctrl.hdr.cmd = CMD_PINCTRL;

    if(argv[0][0] != 'B' && argv[0][0] != 'b') return usage();
    if(argv[0][1] < '0' || argv[0][1] > '3') return usage();
    pinctrl.pin |= (argv[0][1] -'0') << 5;
    if(argv[0][2] != 'P' && argv[0][2] != 'b') return usage();
    char *end;
    unsigned long dummy = strtoul(&argv[0][3], &end, 10);
    if(*end != 0 || dummy > 31) return usage();
    pinctrl.pin |= dummy;

    for(int i = 1; i < argc; i++)
    {
        char *p = strchr(argv[i], '=');
        if(p == NULL)
            return usage();
        *p++ = 0;
        if(strcmp(argv[i], "function") == 0)
        {
            pinctrl.flags |= FLAGS_PINCTRL_FUNCTION;
            if(strcmp(p, "main") == 0) pinctrl.function = 0;
            else if(strcmp(p, "alt1") == 0) pinctrl.function = 1;
            else if(strcmp(p, "alt2") == 0) pinctrl.function = 2;
            else if(strcmp(p, "gpio") == 0) pinctrl.function = 3;
            else return usage();
        }
        else if(strcmp(argv[i], "drive") == 0)
        {
            pinctrl.flags |= FLAGS_PINCTRL_DRIVE;
            if(strcmp(p, "4") == 0) pinctrl.drive = 0;
            else if(strcmp(p, "8") == 0) pinctrl.drive = 1;
            else if(strcmp(p, "12") == 0) pinctrl.drive = 2;
            else if(strcmp(p, "16") == 0) pinctrl.drive = 3;
            else return usage();
        }
        else if(strcmp(argv[i], "pull") == 0)
        {
            pinctrl.flags |= FLAGS_PINCTRL_PULL;
            if(strcmp(p, "no") == 0) pinctrl.pull = 0;
            else if(strcmp(p, "yes") == 0) pinctrl.pull = 1;
            else return usage();
        }
        else if(strcmp(argv[i], "output") == 0)
        {
            pinctrl.flags |= FLAGS_PINCTRL_OUTPUT;
            if(strcmp(p, "0") == 0) pinctrl.output = 0;
            else if(strcmp(p, "1") == 0) pinctrl.output = 1;
            else return usage();
        }
        else if(strcmp(argv[i], "enable") == 0)
        {
            pinctrl.flags |= FLAGS_PINCTRL_ENABLE;
            if(strcmp(p, "no") == 0) pinctrl.enable = 0;
            else if(strcmp(p, "yes") == 0) pinctrl.enable = 1;
            else return usage();
        }
        else
            return usage();
    }

    int ret = libusb_control_transfer(handle,
                                    LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_DEVICE,
                                    USB_CMD_WRAPPED, 0, 0, (void *)&pinctrl, sizeof(pinctrl), 1000);
    if(ret < 0)
        return_fatal("transfer error at control stage\n");

    struct usb_resp_pinctrl_t resp;
    int recv_size;
    ret = libusb_interrupt_transfer(handle, int_ep, (void *)&resp, sizeof(resp), &recv_size, 1000);
    if(ret < 0)
        return_fatal("transfer error at receive stage\n");
    open_wrapper("-");
    write_wrapper(&resp, recv_size);
    close_wrapper();

    printf("pin state:\n");
    if(resp.flags & FLAGS_PINCTRL_INPUT)
        printf("  input: %d\n", resp.input);
}

void si4700_read(libusb_device_handle *handle, uint8_t int_ep, int argc, char **argv)
{
    if(argc < 2 || argc > 3)
        return usage();

    struct usb_cmd_fm_i2c_t fm_i2c;
    memset(&fm_i2c, 0, sizeof(fm_i2c));

    fm_i2c.hdr.cmd = CMD_FM_I2C;
    fm_i2c.hdr.flags = FLAGS_READ;
    
    char *end;
    unsigned long dummy = strtoul(argv[0], &end, 0);
    if(*end != 0 || dummy > 0xff) return usage();
    fm_i2c.dev_addr = dummy;
    fm_i2c.size = 32;

    long reg = -1;
    char *iofile = NULL;
    if(argc == 3)
    {
        reg = strtoul(argv[1], &end, 0);
        if(*end != 0 || reg < 0 || reg > 15) return usage();
        iofile = argv[2];
    }
    else
        iofile = argv[1];

    int ret = libusb_control_transfer(handle,
                                    LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_DEVICE,
                                    USB_CMD_WRAPPED, 0, 0, (void *)&fm_i2c, sizeof(fm_i2c), 1000);
    if(ret < 0)
        return_fatal("transfer error at control stage\n");

    struct usb_resp_fm_i2c_t resp;
    
    int recv_size;
    ret = libusb_interrupt_transfer(handle, int_ep, (void *)&resp, sizeof(resp), &recv_size, 1000);
    if(ret < 0)
        return_fatal("transfer error at first receive stage\n");
    open_wrapper("-");
    write_wrapper(&resp, recv_size);

    bool valid_reg = false;
    uint16_t regs[16];
    if(resp.size > 0)
    {
        uint8_t data[32];
        int xfered = 0;
        while(xfered < resp.size)
        {
            ret = libusb_interrupt_transfer(handle, int_ep, (void *)&data[xfered], resp.size - xfered, &recv_size, 1000);
            if(ret < 0)
                return_fatal("transfer error at receive stage\n");
            printf("xfer=%d\n", recv_size);
            xfered += recv_size;
        }

        write_wrapper(&resp, recv_size);
        close_wrapper();
        open_wrapper(iofile);
        write_wrapper(&resp, recv_size);
        close_wrapper();

        valid_reg = true;
        for(int i = 0; i < 16; i++)
            regs[(i + 0xa) % 16] = data[2 * i] << 8 | data[2 * i + 1];
    }

    printf("result:\n");
    printf("  size: %d %s\n", resp.size, resp.size < 0 ? "(error)" : "");
    if(reg != -1 && valid_reg)
        printf("  register 0x%lx: 0x%x\n", reg, regs[reg]);
}

void si4700_write(libusb_device_handle *handle, uint8_t int_ep, int argc, char **argv)
{
    if(argc != 3)
        return usage();

    struct
    {
        struct usb_cmd_fm_i2c_t fm_i2c;
        uint8_t data[32];
    } __attribute__((packed)) fm_i2c;
    memset(&fm_i2c, 0, sizeof(fm_i2c));

    fm_i2c.fm_i2c.hdr.cmd = CMD_FM_I2C;
    fm_i2c.fm_i2c.hdr.flags = FLAGS_READ;

    char *end;
    unsigned long dummy = strtoul(argv[0], &end, 0);
    if(*end != 0 || dummy > 0xff) return usage();
    fm_i2c.fm_i2c.dev_addr = dummy;
    fm_i2c.fm_i2c.size = 32;

    unsigned long reg = strtoul(argv[1], &end, 0);
    if(*end != 0 || reg > 15) return usage();

    unsigned long value = strtoul(argv[2], &end, 0);
    if(*end != 0 || value > 0xffff) return usage();

    int ret = libusb_control_transfer(handle,
                                    LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_DEVICE,
                                    USB_CMD_WRAPPED, 0, 0, (void *)&fm_i2c.fm_i2c, sizeof(fm_i2c.fm_i2c), 1000);
    if(ret < 0)
        return_fatal("transfer error at control stage\n");

    struct usb_resp_fm_i2c_t resp;

    int recv_size;
    ret = libusb_interrupt_transfer(handle, int_ep, (void *)&resp, sizeof(resp), &recv_size, 1000);
    if(ret < 0)
        return_fatal("transfer error at first receive stage\n");

    printf("read result:\n");
    printf("  size: %d %s\n", resp.size, resp.size < 0 ? "(error)" : "");
    if(resp.size < 0 || resp.size != 32)
        return_fatal("unable to read all registers\n");

    uint16_t regs[16];
    uint8_t data[32];
    int xfered = 0;
    while(xfered < resp.size)
    {
        ret = libusb_interrupt_transfer(handle, int_ep, (void *)&data[xfered], resp.size - xfered, &recv_size, 1000);
        if(ret < 0)
            return_fatal("transfer error at receive stage\n");
        printf("xfer=%d\n", recv_size);
        xfered += recv_size;
    }
    for(int i = 0; i < 16; i++)
        regs[(i + 0xa) % 16] = data[2 * i] << 8 | data[2 * i + 1];
    printf("  register 0x%lx: was 0x%x will be 0x%lx\n", reg, regs[reg], value);
    regs[reg] = value;

    fm_i2c.fm_i2c.hdr.flags = FLAGS_WRITE;
    for(int i = 0; i < 16; i++)
    {
        fm_i2c.data[2 * i] = regs[(i + 0x2) % 16] >> 8;
        fm_i2c.data[2 * i + 1] = regs[(i + 0x2) % 16];
    }

    ret = libusb_control_transfer(handle,
                                    LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_DEVICE,
                                    USB_CMD_WRAPPED, 0, 0, (void *)&fm_i2c, sizeof(fm_i2c), 1000);
    if(ret < 0)
        return_fatal("transfer error at second control stage\n");

    ret = libusb_interrupt_transfer(handle, int_ep, (void *)&resp, sizeof(resp), &recv_size, 1000);
    if(ret < 0)
        return_fatal("transfer error at second receive stage\n");

    printf("write result:\n");
    printf("  size: %d %s\n", resp.size, resp.size < 0 ? "(error)" : "");
}

void reset(libusb_device_handle *handle, uint8_t int_ep, int argc, char **argv)
{
    (void) int_ep;
    if(argc > 1)
        return usage();

    struct usb_cmd_reset_t reset;
    memset(&reset, 0, sizeof(reset));

    reset.hdr.cmd = CMD_RESET;
    
    if(argc == 1)
    {
        if(strcmp(argv[0], "clkctrl") == 0)
            reset.hdr.flags |= FLAGS_RESET_CLKCTRL;
        else
            return usage();
    }
    else
        reset.hdr.flags |= FLAGS_RESET_CLKCTRL;

    int ret = libusb_control_transfer(handle,
                                    LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_DEVICE,
                                    USB_CMD_WRAPPED, 0, 0, (void *)&reset, sizeof(reset), 1000);
    if(ret < 0)
        return_fatal("transfer error at control stage\n");
}

void watchdog(libusb_device_handle *handle, uint8_t int_ep, int argc, char **argv)
{
    (void) handle;
    (void) int_ep;
    (void) argc;
    (void) argv;
}

void stfm1000_read(libusb_device_handle *handle, uint8_t int_ep, int argc, char **argv)
{
    if(argc != 3)
        return usage();
    struct
    {
        struct usb_cmd_i2c_generic_t i2c;
        struct usb_cmd_i2c_stage_t stage[3];
        uint8_t dev_addr;
        uint8_t reg_addr;
        uint8_t dev_addr2;
    }__attribute__((packed)) i2c;

    char *end;
    long dummy = strtol(argv[0], &end, 0);
    if(*end != 0 || dummy < 0 || dummy > 0xff)
        return_fatal("Invalid dev_addr choice\n");
    i2c.dev_addr = dummy;
    i2c.dev_addr2 = dummy | 1;

    dummy = strtol(argv[1], &end, 0);
    if(*end != 0 || dummy < 0 || dummy > 0xff)
        return_fatal("Invalid reg choice\n");
    i2c.reg_addr = dummy;

    i2c.i2c.hdr.cmd = CMD_I2C;
    i2c.i2c.hdr.flags |= FLAGS_I2C_GENERIC;
    i2c.i2c.nr_stages = 3;
    i2c.stage[0].flags = FLAGS_I2C_STAGE_START | FLAGS_I2C_STAGE_SEND;
    i2c.stage[0].length = 2;
    i2c.stage[1].flags = FLAGS_I2C_STAGE_START | FLAGS_I2C_STAGE_SEND;
    i2c.stage[1].length = 1;
    i2c.stage[2].flags = FLAGS_I2C_STAGE_STOP;
    i2c.stage[2].length = 4;

    int ret = libusb_control_transfer(handle,
                                LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_DEVICE,
                                USB_CMD_WRAPPED, 0, 0, (void *)&i2c, sizeof(i2c), 1000);
    if(ret < 0)
        return_fatal("transfer error at control stage\n");

    struct usb_resp_i2c_generic_t resp;
    
    int recv_size;
    ret = libusb_interrupt_transfer(handle, int_ep, (void *)&resp, sizeof(resp), &recv_size, 1000);
    if(ret < 0)
        return_fatal("transfer error at first receive stage\n");
    open_wrapper(argv[2]);
    write_wrapper(&resp, recv_size);
    close_wrapper();

    uint8_t v[4];
    ret = libusb_interrupt_transfer(handle, int_ep, (void *)v, sizeof(v), &recv_size, 1000);
    if(ret < 0)
        return_fatal("transfer error at second receive stage\n");
    
    printf("status: %s\n", i2c_errstr(resp.ctrl1));
    unsigned long value = v[0] |v[1] << 8 | v[2] << 16 | v[3] << 24;
    if(i2c_success(resp.ctrl1))
        printf("  register 0x%x: 0x%lx\n", i2c.reg_addr, value);
}

void stfm1000_write(libusb_device_handle *handle, uint8_t int_ep, int argc, char **argv)
{
    (void) handle;
    (void) int_ep;
    (void) argc;
    (void) argv;
}

int main(int argc, char **argv)
{
    int ret = 0;
    libusb_device_handle *handle = NULL;
    
    if(argc < 3)
    {
        usage();
        return 1;
    }

    libusb_init(&ctx);
    libusb_set_debug(ctx, 3);

    int vid, pid;

    char *p = strchr(argv[1], ':');
    if(p == NULL)
    {
        printf("Invalid VID/PID\n");
        goto Lerr;
    }

    char *end;
    vid = strtol(argv[1], &end, 16);
    if(end != p)
    {
        printf("Invalid VID/PID\n");
        goto Lerr;
    }
    pid = strtol(p + 1, &end, 16);
    if(end != (argv[1] + strlen(argv[1])))
    {
        printf("Invalid VID/PID\n");
        goto Lerr;
    }

    printf("Looking for device %#04x:%#04x...\n", vid, pid);
    
    handle = libusb_open_device_with_vid_pid(ctx, vid, pid);
    if(handle == NULL)
    {
        printf("No device found\n");
        goto Lerr;
    }

    libusb_device *mydev = libusb_get_device(handle);
    printf("device found at %d:%d\n",
        libusb_get_bus_number(mydev),
        libusb_get_device_address(mydev));

    int config_id;
    libusb_get_configuration(handle, &config_id);
    struct libusb_config_descriptor *config;
    libusb_get_active_config_descriptor(mydev, &config);
    
    printf("configuration: %d\n", config_id);
    printf("interfaces: %d\n", config->bNumInterfaces);
    
    const struct libusb_endpoint_descriptor *endp = NULL;
    int intf, intf_alt;
    for(intf = 0; intf < config->bNumInterfaces; intf++)
        for(intf_alt = 0; intf_alt < config->interface[intf].num_altsetting; intf_alt++)
            for(int ep = 0; ep < config->interface[intf].altsetting[intf_alt].bNumEndpoints; ep++)
            {
                endp = &config->interface[intf].altsetting[intf_alt].endpoint[ep];
                if((endp->bmAttributes & LIBUSB_TRANSFER_TYPE_MASK) == LIBUSB_TRANSFER_TYPE_INTERRUPT &&
                        (endp->bEndpointAddress & LIBUSB_ENDPOINT_DIR_MASK) == LIBUSB_ENDPOINT_IN)
                    goto Lfound;
            }
    printf("No suitable endpoint found\n");
    goto Lerr;

    Lfound:
    printf("Use interface %d, alt %d\n", intf, intf_alt);
    if(libusb_claim_interface(handle, intf) != 0)
    {
        printf("claim error\n");
        goto Lerr;
    }
    printf("Use endpoint %d\n", endp->bEndpointAddress);

    {
        struct usb_cmd_info_t info;
        ret = libusb_control_transfer(handle,
            LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_DEVICE | LIBUSB_ENDPOINT_IN,
            USB_CMD_INFO, 0, 0, (void *)&info, sizeof(info), 1000);
        if(ret < 0)
        {
            printf("Cannot get protocol info from device!\n");
            goto Lend;
        }
        printf("Protocol version: %d\n", info.prot_ver);
        printf("Protocol magic: ");
        for(int i = 0; i < PROTOCOL_MAGIC_SIZE; i++)
            printf("%c", isprint(info.magic[i]) ? info.magic[i] : '.');
        printf("\n");
        if(info.prot_ver != PROTOCOL_VERSION ||
                memcmp(info.magic, PROTOCOL_MAGIC, PROTOCOL_MAGIC_SIZE) != 0)
        {
            printf("Unsupported protocol version/magic!\n");
            goto Lend;
        }
    }

    if(strcmp(argv[2], "mem_read") == 0)
        mem_read(handle, endp->bEndpointAddress, argc - 3, argv + 3);
    else if(strcmp(argv[2], "otp_read") == 0)
        otp_read(handle, endp->bEndpointAddress, argc - 3, argv + 3);
    else if(strcmp(argv[2], "ssp_cmd") == 0)
        ssp_cmd(handle, endp->bEndpointAddress, argc - 3, argv + 3);
    else if(strcmp(argv[2], "mem_write32") == 0)
        mem_write32(handle, endp->bEndpointAddress, argc - 3, argv + 3);
    else if(strcmp(argv[2], "lradc_read") == 0)
        lradc_read(handle, endp->bEndpointAddress, argc - 3, argv + 3);
    else if(strcmp(argv[2], "i2c_poke") == 0)
        i2c_poke(handle, endp->bEndpointAddress, argc - 3, argv + 3);
    else if(strcmp(argv[2], "i2c_poke_generic") == 0)
        i2c_poke_generic(handle, endp->bEndpointAddress, argc - 3, argv + 3);
    else if(strcmp(argv[2], "i2c_eeprom_read") == 0)
        i2c_eeprom_read(handle, endp->bEndpointAddress, argc - 3, argv + 3);
    else if(strcmp(argv[2], "i2c_eeprom_write") == 0)
        i2c_eeprom_write(handle, endp->bEndpointAddress, argc - 3, argv + 3);
    else if(strcmp(argv[2], "pinctrl") == 0)
        pinctrl(handle, endp->bEndpointAddress, argc - 3, argv + 3);
    else if(strcmp(argv[2], "si4700_read") == 0)
        si4700_read(handle, endp->bEndpointAddress, argc - 3, argv + 3);
    else if(strcmp(argv[2], "si4700_write") == 0)
        si4700_write(handle, endp->bEndpointAddress, argc - 3, argv + 3);
    else if(strcmp(argv[2], "reset") == 0)
        reset(handle, endp->bEndpointAddress, argc - 3, argv + 3);
    else if(strcmp(argv[2], "watchdog") == 0)
        watchdog(handle, endp->bEndpointAddress, argc - 3, argv + 3);
    else if(strcmp(argv[2], "stfm1000_read") == 0)
        stfm1000_read(handle, endp->bEndpointAddress, argc - 3, argv + 3);
    else if(strcmp(argv[2], "stfm1000_write") == 0)
        stfm1000_write(handle, endp->bEndpointAddress, argc - 3, argv + 3);
    else
        usage();

    printf("Device log:\n");
    while(true)
    {
        char buffer[64];
        ret = libusb_control_transfer(handle,
            LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_DEVICE | LIBUSB_ENDPOINT_IN,
            USB_CMD_READLOG, 0, 0, (void *)buffer, sizeof(buffer) - 1, 1000);
        if(ret < 0)
            break;
        if(ret == 0)
            break;
        buffer[ret] = 0;
        printf("%s", buffer);
    }

Lend:
    if(handle)
        libusb_close(handle);
    libusb_exit(ctx);
    return ret;

Lerr:
    ret = 1;
    goto Lend;
}
