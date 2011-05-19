#include <stdio.h>
#include <stdlib.h>
#include <libusb.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

void main_loop(libusb_device_handle *handle)
{
    libusb_device *device=libusb_get_device(handle);
    printf("device found at %d:%d\n",
        libusb_get_bus_number(device),
        libusb_get_device_address(device));
    
    struct libusb_device_descriptor dev_desc;
    int res=libusb_get_device_descriptor(device,&dev_desc);
    assert(res==0);
    
    const int STRING_SIZE=64;
    unsigned char string[STRING_SIZE];
    
    /*
    res=libusb_get_string_descriptor_ascii(handle,dev_desc.iProduct,string,STRING_SIZE);
    assert(res>=0);
    printf("device: %s\n",string);
    */
    
    int config_id;
    res=libusb_get_configuration(handle,&config_id);
    assert(res==0);
    struct libusb_config_descriptor *config;
    res=libusb_get_active_config_descriptor(device,&config);
    assert(res==0);
    
    printf("configuration: %d\n",config_id);
    printf("interfaces: %d\n",config->bNumInterfaces);
    
    int serial_interface=-1;
    
    for(int i=0;i<config->bNumInterfaces;i++)
    {
        printf("interface %d: alternative settings: %d\n",i,config->interface[i].num_altsetting);
        for(int j=0;j<config->interface[i].num_altsetting;j++)
        {
            /*
            res=libusb_get_string_descriptor_ascii(handle,config->interface[i].altsetting[j].iInterface,string,STRING_SIZE);
            assert(res>=0);
            */
            
            printf("interface %d,%d: class=%#x\n",i,j,config->interface[i].altsetting[j].bInterfaceClass);
            printf("interface %d,%d: subclass=%#x\n",i,j,config->interface[i].altsetting[j].bInterfaceSubClass);
            
            if(config->interface[i].altsetting[j].bInterfaceClass==LIBUSB_CLASS_DATA)
                serial_interface=i;
        }
    }
    
    printf("serial interface: %d\n",serial_interface);
    struct libusb_interface_descriptor *interface=&config->interface[serial_interface].altsetting[0];
    
    res=libusb_claim_interface(handle,serial_interface);
    if(res!=0)
    {
        printf("claim error: %d\n",res);
        assert(false);
    }
    
    printf("endpoints: %d\n",interface->bNumEndpoints);
    
    int read_endpoint=-1;
    int write_endpoint=-1;
    
    for(int i=0;i<interface->bNumEndpoints;i++)
    {
        printf("endpoint %d: addr=%d dir=%d type=%d\n",i,
                interface->endpoint[i].bEndpointAddress&0x7,interface->endpoint[i].bEndpointAddress>>7,
                interface->endpoint[i].bmAttributes&0x3);
        
        if(interface->endpoint[i].bEndpointAddress&LIBUSB_ENDPOINT_IN)
            read_endpoint=interface->endpoint[i].bEndpointAddress;
        else
            write_endpoint=interface->endpoint[i].bEndpointAddress;
    }
    
    const int READ_BUF_SIZE=32;
    char buffer[READ_BUF_SIZE];
    int xfered;
    
    printf("read endpoint: %#x\n",read_endpoint);
    printf("write endpoint: %#x\n",write_endpoint);
    
    sprintf(buffer,"HELLO FROM SERIAL_READER\n");
    
    res=libusb_bulk_transfer(handle,write_endpoint,buffer,strlen(buffer),&xfered,0);
    if(res<0)
        printf("write xfer error: %d\n",res);
    else
        printf("write xfer success\n");
    
    while(1)
    {
        res=libusb_bulk_transfer(handle,read_endpoint,buffer,/*READ_BUF_SIZE*/32,&xfered,0);
        if(res<0)
        {
            printf("xfer error: %d\n",res);
            //assert(false);
            break;
        }
        /*
        else
            printf("xfered: %d\n",xfered);
        */
        buffer[xfered]=0;
        printf("%s",buffer);
        fflush(stdout);
    }
    
    libusb_release_interface(handle,serial_interface);
}

bool is_sansa(libusb_device *dev)
{
    struct libusb_device_descriptor dev_desc;
    int res=libusb_get_device_descriptor(dev,&dev_desc);
    assert(res==0);
    
    return dev_desc.idVendor==0x0781 && (dev_desc.idProduct==0x7421 || dev_desc.idProduct==0x74d1);
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
        if(is_sansa(device_list[i]))
            found=device_list[i];
    }
    
    if(found)
    {
        libusb_device_handle *handle;
        int err=libusb_open(found,&handle);
        assert(err==0);

        main_loop(handle);

        libusb_close(handle);
    }
    
    libusb_free_device_list(device_list,1);
    
    libusb_exit(NULL);
    
    return 0;
}
