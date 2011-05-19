#include <stdio.h>
#include <stdlib.h>
#include <libusb.h>
#include <stdint.h>
#include <string.h>

libusb_context *ctx;

int main(int argc, char **argv)
{
    int ret = 0;
    libusb_device_handle *handle = NULL;
    
    if(argc != 3)
    {
        printf("usage: dfu_util <device> <file>\n");
        return 1;
    }

    libusb_init(&ctx);
    libusb_set_debug(NULL,3);

    FILE *file = fopen(argv[2], "r");
    if(file == NULL)
    {
        printf("Cannot open file for reading\n");
        goto Lerr;
    }

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
                if((endp->bmAttributes & LIBUSB_TRANSFER_TYPE_MASK) == LIBUSB_TRANSFER_TYPE_BULK &&
                        (endp->bEndpointAddress & LIBUSB_ENDPOINT_DIR_MASK) == LIBUSB_ENDPOINT_OUT)
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

    fseek(file, 0, SEEK_END);
    int filesize = ftell(file);
    fseek(file, 0, SEEK_SET);
    printf("File size: %d\n", filesize);

    #define SIZE    64
    unsigned char buffer[SIZE];

    while(filesize > 0)
    {
        int dummy;
        int xfer_size = filesize;
        if(xfer_size > SIZE)
            xfer_size = SIZE;
        filesize -= xfer_size;

        fread(buffer, xfer_size, 1, file);
        libusb_bulk_transfer(handle,
            endp->bEndpointAddress,
            buffer,
            xfer_size,
            &dummy,
            0);
    }
    libusb_bulk_transfer(handle,
        endp->bEndpointAddress,
        NULL,
        0,
        NULL,
        0);
    printf("Finished\n");

Lend:
    if(file)
        fclose(file);
    if(handle)
        libusb_close(handle);
    libusb_exit(ctx);
    return ret;

Lerr:
    ret = 1;
    goto Lend;
}
