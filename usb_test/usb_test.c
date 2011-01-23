#include <stdio.h>
#include <stdlib.h>
#include <libusb.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "usb_test_def.h"

unsigned char iso_buffer[128];
unsigned char *big_buffer;
int xfer_completed;

libusb_context *ctx;

#define MIN(a,b) ((a)<(b)?(a):(b));

void iso_cb(struct libusb_transfer *transfer)
{
    xfer_completed++;

    /*
    printf("iso xfer completed !\n");
    printf("  status: %d length=%d\n", transfer->status, transfer->length);
    fflush(stdout);
    */

    /*
    if(transfer->status==LIBUSB_TRANSFER_COMPLETED)
    {
        int i;
        printf("data:\n");
        for(i=0;i<transfer->length;i++)
        {
            if(i!=0 && (i%16)==0)
                printf("\n");
            printf("%02x ", iso_buffer[i]);
        }
        printf("\n");
    }
    */
}

unsigned crc_32(const void *src, unsigned len, unsigned crc32)
{
    const unsigned char *buf = (const unsigned char *)src;
    
    /* CCITT standard polynomial 0x04C11DB7 */
    static const unsigned crc32_lookup[16] =
    {   /* lookup table for 4 bits at a time is affordable */
        0x00000000, 0x04C11DB7, 0x09823B6E, 0x0D4326D9,
        0x130476DC, 0x17C56B6B, 0x1A864DB2, 0x1E475005,
        0x2608EDB8, 0x22C9F00F, 0x2F8AD6D6, 0x2B4BCB61,
        0x350C9B64, 0x31CD86D3, 0x3C8EA00A, 0x384FBDBD
    };

    unsigned char byte;
    unsigned t;

    while (len--)
    {
        byte = *buf++; /* get one byte of data */

        /* upper nibble of our data */
        t = crc32 >> 28; /* extract the 4 most significant bits */
        t ^= byte >> 4; /* XOR in 4 bits of data into the extracted bits */
        crc32 <<= 4; /* shift the CRC register left 4 bits */
        crc32 ^= crc32_lookup[t]; /* do the table lookup and XOR the result */

        /* lower nibble of our data */
        t = crc32 >> 28; /* extract the 4 most significant bits */
        t ^= byte & 0x0F; /* XOR in 4 bits of data into the extracted bits */
        crc32 <<= 4; /* shift the CRC register left 4 bits */
        crc32 ^= crc32_lookup[t]; /* do the table lookup and XOR the result */
    }

    return crc32;
}

void prepare_crc32_block(unsigned char *block,int length)
{
    *(uint32_t *)block = crc_32(block+4,length-4, 0xffffffff);
}

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
    
    int config_id;
    res=libusb_get_configuration(handle,&config_id);
    assert(res==0);
    struct libusb_config_descriptor *config;
    res=libusb_get_active_config_descriptor(device,&config);
    assert(res==0);
    
    printf("configuration: %d\n",config_id);
    printf("interfaces: %d\n",config->bNumInterfaces);
    
    int test_interface=-1;
    
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
            
            if(config->interface[i].altsetting[j].bInterfaceClass==USB_TEST_CLASS &&
                    config->interface[i].altsetting[j].bInterfaceSubClass==USB_TEST_SUBCLASS &&
                    config->interface[i].altsetting[j].bInterfaceProtocol==USB_TEST_PROTOCOL)
                test_interface=i;
        }
    }
    
    printf("test interface: %d\n",test_interface);
    const struct libusb_interface_descriptor *interface=&config->interface[test_interface].altsetting[0];
    
    res=libusb_claim_interface(handle,test_interface);
    if(res!=0)
    {
        printf("claim error: %d\n",res);
        assert(false);
    }
    
    printf("endpoints: %d\n",interface->bNumEndpoints);
    
    int bulk_in_ep=-1;
    int bulk_out_ep=-1;
    int iso_in_ep=-1;
    int iso_out_ep=-1;
    
    for(int i=0;i<interface->bNumEndpoints;i++)
    {
        printf("endpoint %d: addr=%d dir=%d type=%d\n",i,
                interface->endpoint[i].bEndpointAddress&0x7,interface->endpoint[i].bEndpointAddress>>7,
                interface->endpoint[i].bmAttributes&0x3);
        
        if((interface->endpoint[i].bEndpointAddress&LIBUSB_ENDPOINT_DIR_MASK)==LIBUSB_ENDPOINT_IN &&
                (interface->endpoint[i].bmAttributes&LIBUSB_TRANSFER_TYPE_MASK)==LIBUSB_TRANSFER_TYPE_BULK)
            bulk_in_ep=interface->endpoint[i].bEndpointAddress;
        else if((interface->endpoint[i].bEndpointAddress&LIBUSB_ENDPOINT_DIR_MASK)==LIBUSB_ENDPOINT_OUT &&
                (interface->endpoint[i].bmAttributes&LIBUSB_TRANSFER_TYPE_MASK)==LIBUSB_TRANSFER_TYPE_BULK)
            bulk_out_ep=interface->endpoint[i].bEndpointAddress;
        else if((interface->endpoint[i].bEndpointAddress&LIBUSB_ENDPOINT_DIR_MASK)==LIBUSB_ENDPOINT_IN &&
                (interface->endpoint[i].bmAttributes&LIBUSB_TRANSFER_TYPE_MASK)==LIBUSB_TRANSFER_TYPE_ISOCHRONOUS)
            iso_in_ep=interface->endpoint[i].bEndpointAddress;
        else if((interface->endpoint[i].bEndpointAddress&LIBUSB_ENDPOINT_DIR_MASK)==LIBUSB_ENDPOINT_OUT &&
                (interface->endpoint[i].bmAttributes&LIBUSB_TRANSFER_TYPE_MASK)==LIBUSB_TRANSFER_TYPE_ISOCHRONOUS)
            iso_out_ep=interface->endpoint[i].bEndpointAddress;
    }
    
    printf("bulk IN: %#02x\n", bulk_in_ep);
    printf("bulk OUT: %#02x\n", bulk_out_ep);
    printf("iso IN: %#02x\n", iso_in_ep);
    printf("iso OUT: %#02x\n", iso_out_ep);

    const int interface_alt=0;
    printf("use interface %d\n",interface_alt);
    res=libusb_set_interface_alt_setting(handle,test_interface,interface_alt);
    if(res<0)
    {
        printf("cannot use that interface !\n");
        return;
    }

    struct usb_test_data_request data_req;
    struct usb_test_iso_request iso_req;
    struct usb_test_stat_request stat_req;
    
    stat_req.dwMagic=USB_TEST_MAGIC;
    stat_req.bReq=USB_TEST_STAT_CLEAR;
    res=libusb_control_transfer(
        handle,
        LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE,
        USB_TEST_REQ_STAT,
        0,
        test_interface,
        (unsigned char *)&stat_req,
        sizeof(stat_req),
        0);

    int big_buffer_size=32*1024*10;
    int packet_per_submit=1;
    int packet_size=32;
    big_buffer=malloc(packet_per_submit*packet_size);
    

    data_req.dwMagic=USB_TEST_MAGIC;
    data_req.bReq=USB_TEST_DATA_IN_GENERATE | USB_TEST_DATA_OUT_CRC32;
    res=libusb_control_transfer(
        handle,
        LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE,
        USB_TEST_REQ_DATA,
        0,
        test_interface,
        (unsigned char *)&data_req,
        sizeof(data_req),
        0);
    if(res<0)
    {
        printf("control transfer error: %d\n", res);
        goto Lend;
    }
    
    int nb_transfers=big_buffer_size/packet_size/packet_per_submit;
    iso_req.dwMagic=USB_TEST_MAGIC;
    iso_req.bReq=USB_TEST_ISO_OUT;
    iso_req.dwLength=big_buffer_size;
    res=libusb_control_transfer(
        handle,
        LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE,
        USB_TEST_REQ_TEST_ISO,
        0,
        test_interface,
        (unsigned char *)&iso_req,
        sizeof(iso_req),
        0);
    if(res<0)
    {
        printf("control transfer error: %d\n", res);
        goto Lend;
    }

    struct timeval start_time, end_time;

    gettimeofday(&start_time, NULL);

    FILE *f = fopen("iso.bin", "w");
    if(f == NULL)
    {
        printf("Cannot open 'iso.bin':");
        perror("");
        goto Lend;
    }

    for(int i=0;i<nb_transfers;i++)
    {
        struct libusb_transfer *xfer2 = libusb_alloc_transfer(packet_per_submit);
        libusb_fill_iso_transfer(xfer2,
            handle,
            iso_out_ep,
            big_buffer,
            packet_per_submit*packet_size,
            packet_per_submit,
            &iso_cb,
            NULL,
            0);
        libusb_set_iso_packet_lengths(xfer2, packet_size);
        for(int j=0;j<packet_per_submit;j++)
        {
            for(int k=0;k<packet_size;k++)
                big_buffer[j*packet_size+k] = (i*packet_size*packet_per_submit+j*packet_size+k)%0x100;
            prepare_crc32_block(big_buffer+j*packet_size,packet_size);
            //*
            if((rand()%1000) == -1)
            {
                printf("introduce error\n");
                big_buffer[j*packet_size]=rand();
            }
            //*/
            fwrite(big_buffer+j*packet_size, packet_size, 1, f);
        }
        res=libusb_submit_transfer(xfer2);
        if(res<0)
        {
            printf("(%d)iso transfer error: %d\n", i, res);
            goto Lend;
        }

        while((i-xfer_completed)>20)
            libusb_handle_events(ctx);
    }
    
    fclose(f);

    clock_t end_wait = clock() + CLOCKS_PER_SEC;
    while(xfer_completed != nb_transfers && (clock() < end_wait))
        libusb_handle_events(ctx);
    usleep(1000);

    gettimeofday(&end_time, NULL);
    int ms=(end_time.tv_sec-start_time.tv_sec)*1000+(end_time.tv_usec-start_time.tv_usec)/1000;
    printf("transfer took %d ms\n", ms);

    Lend:
    res=libusb_control_transfer(
        handle,
        LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE,
        USB_TEST_REQ_CANCEL,
        0,
        test_interface,
        NULL,
        0,
        0);
    
    stat_req.dwMagic=USB_TEST_MAGIC;
    stat_req.bReq=USB_TEST_STAT_LOG;
    res=libusb_control_transfer(
        handle,
        LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE,
        USB_TEST_REQ_STAT,
        0,
        test_interface,
        (unsigned char *)&stat_req,
        sizeof(stat_req),
        0);

    libusb_release_interface(handle,test_interface);
}

bool is_sansa(libusb_device *dev)
{
    struct libusb_device_descriptor dev_desc;
    int res=libusb_get_device_descriptor(dev,&dev_desc);
    assert(res==0);
    
    return dev_desc.idVendor==0x0781 && dev_desc.idProduct==0x7421;
}

int main(int argc,char **argv)
{
    (void)argc;
    (void)argv;

    srand(time(NULL));
    
    assert(libusb_init(&ctx)==0);
    
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
