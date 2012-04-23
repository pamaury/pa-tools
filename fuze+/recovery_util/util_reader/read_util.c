#include <stdio.h>
#include <stdlib.h>
#include <libusb.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../protocol.h"

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
    printf("Reading OTP register %u, writing to %s\n", reg, argv[2]);

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
