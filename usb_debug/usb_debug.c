#include <stdio.h>
#include <stdlib.h>
#include <libusb.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <features.h>
#include <time.h>

void main_loop(libusb_device_handle *handle)
{
    libusb_device *device=libusb_get_device(handle);
    printf("device found at %d:%d\n",
        libusb_get_bus_number(device),
        libusb_get_device_address(device));

    struct libusb_device_descriptor dev_desc;
    int ret = libusb_get_device_descriptor(device,&dev_desc);
    if(ret != 0)
        return;

    unsigned char buf[1025];

    while(true)
    {
        ret = libusb_control_transfer(
            handle,
            LIBUSB_ENDPOINT_IN | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE,
            0x99,
            0,
            0,
            buf,
            sizeof(buf)-1,
            100);
        if(ret < 0 && ret != LIBUSB_ERROR_TIMEOUT && ret != LIBUSB_ERROR_PIPE)
            break;

        if(ret == 0)
        {
            struct timespec tps;
            tps.tv_sec = 0;
            tps.tv_nsec = 1000000000 / 10;
            nanosleep(&tps, NULL);
        }
        else
        {
            buf[ret] = 0;
            printf("%s", buf);
            fflush(stdout);
        }
    }
}

bool is_debug(libusb_device *dev)
{
    struct libusb_device_descriptor dev_desc;
    int res=libusb_get_device_descriptor(dev,&dev_desc);
    assert(res==0);
    
    return dev_desc.idVendor==0x9999 && dev_desc.idProduct==0x9999;
}

int main(int argc,char **argv)
{
    (void)argc;
    (void)argv;
    
    assert(libusb_init(NULL)==0);
    
    libusb_set_debug(NULL,3);
    
    libusb_device **device_list;
    ssize_t list_size=libusb_get_device_list(NULL,&device_list);
    
    assert(list_size>=0);
    
    libusb_device *found = NULL;
    for(ssize_t i=0;i<list_size;i++)
    {
        if(is_debug(device_list[i]))
            found=device_list[i];
    }
    
    if(found)
    {
        libusb_device_handle *handle;
        int err = libusb_open(found,&handle);
        assert(err==0);

        main_loop(handle);

        libusb_close(handle);
    }
    
    libusb_free_device_list(device_list,1);
    
    libusb_exit(NULL);
    
    return 0;
}
