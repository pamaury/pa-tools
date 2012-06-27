#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <pcap.h>
#include <pcap/usb.h>
#include "mtp_internal.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

char errbuf[PCAP_ERRBUF_SIZE];
int g_dev_seen[256];

int g_datalink = 0;
int g_mtp_dev_addr = 0;
unsigned g_in_command = 0; /* for out ep */
unsigned g_cur_cmd_len = 0;
unsigned g_cur_cmd_rem_len = 0;
unsigned g_in_resp= 0; /* for in ep */
unsigned g_cur_resp_len = 0;
unsigned g_cur_resp_rem_len = 0;
void *g_cur_cmd_data;
void *g_cur_cmd_data_ptr;
void *g_cur_resp_data;
void *g_cur_resp_data_ptr;

struct mtp_command g_cur_cmd;
struct mtp_response g_cur_resp;

void *g_cur_unpack_ptr;
unsigned g_cur_unpack_len;

struct usb_xfer_t
{
    u_int8_t event_type;
    u_int8_t transfer_type;
    u_int8_t endpoint_number;
    u_int8_t device_address;
    u_int16_t bus_id;
    char setup_flag;/*if !=0 the urb setup header is not present*/
    char data_flag; /*if !=0 no urb data is present*/
    int32_t status;
    u_int32_t urb_len;
    u_int32_t data_len; /* amount of urb data really present in this event*/
    pcap_usb_setup setup;
    void *data;
};

void start_unpack_data_block(void *data, uint32_t data_len)
{
    g_cur_unpack_ptr = data;
    g_cur_unpack_len = data_len;
}

bool unpack_data_block_ptr(void *ptr, size_t length)
{
    if(g_cur_unpack_len < length) return false;
    if(ptr) memcpy(ptr, g_cur_unpack_ptr, length);
    g_cur_unpack_ptr += length;
    g_cur_unpack_len -= length;
    return true;
}

#define define_unpack(type) \
    bool unpack_data_block_##type(type *val) \
    { \
        return unpack_data_block_ptr(val, sizeof(type)); \
    }

define_unpack(uint8_t)
define_unpack(uint16_t)
define_unpack(uint32_t)
define_unpack(uint64_t)

bool unpack_data_block_string_fixed(struct mtp_string *str, uint32_t max_len)
{
    if(!unpack_data_block_uint8_t(&str->length))
        return false;

    if(str->length > max_len)
        return false;

    return unpack_data_block_ptr(str->data, sizeof(uint16_t) * str->length);
}

bool unpack_data_block_string_var(struct mtp_string_var *str)
{
    if(!unpack_data_block_uint8_t(&str->length))
        return false;
    str->data = malloc(sizeof(uint16_t) * str->length);

    return unpack_data_block_ptr(str->data, sizeof(uint16_t) * str->length);
}

#define define_unpack_array_var(type) \
    bool unpack_data_block_array_##type##_var(struct mtp_array_##type##_var *val) \
    { \
        if(!unpack_data_block_uint32_t(&val->length)) \
            return false; \
        val->data = malloc(sizeof(type) * val->length); \
        return unpack_data_block_ptr(val->data, sizeof(type) * val->length); \
    }

#define define_print_array_var(type) \
    void print_array_##type##_var(struct mtp_array_##type##_var *val) \
    { \
        for(unsigned i = 0; i < val->length; i++) \
            printf("0x%x ", val->data[i]); \
    }

define_unpack_array_var(uint16_t)
define_print_array_var(uint16_t)
define_unpack_array_var(uint32_t)
define_print_array_var(uint32_t)

void free_string_var(struct mtp_string_var *str)
{
    free(str->data);
    str->data = NULL;
    str->length = 0;
}

bool unpack_data_block_string_charz(unsigned char *dest, uint32_t dest_len)
{
    uint8_t len;

    if(!unpack_data_block_uint8_t(&len)) return false;

    if(dest && (uint32_t)(len + 1) > dest_len)
        return false;

    while(len-- != 0)
    {
        uint16_t chr;
        if (!unpack_data_block_uint16_t(&chr)) return false;
        if (dest) *dest++ = chr;
    }
    if (dest) *dest = 0;
    return true;
}

bool unpack_data_block_any_var(struct mtp_any_var *var, uint16_t type)
{
    var->type = type;
#define do_case_basic(type, name) \
    case type: \
        var->data = malloc(sizeof(type)); \
        return unpack_data_block_##name(var->data);
#define do_case_adv(type, name) \
    case type: \
        var->data = malloc(sizeof(struct mtp_##name##_var)); \
        return unpack_data_block_##name##_var(var->data);

    switch(type)
    {
        do_case_basic(TYPE_UINT8, uint8_t)
        do_case_basic(TYPE_UINT16, uint16_t)
        do_case_basic(TYPE_UINT32, uint32_t)
        do_case_basic(TYPE_UINT64, uint64_t)
        do_case_adv(TYPE_AUINT16, array_uint16_t)
        do_case_adv(TYPE_AUINT32, array_uint32_t)
        default:
            printf("Unsupported data type 0x%x for unpack op\n", type);
            return false;
    }
#undef do_case_basic
#undef do_case_adv
}

void print_any_var(struct mtp_any_var *var)
{
#define do_case_basic_unsigned(type, name) \
    case type: \
        printf("0x%llx (%llu)", (unsigned long long)*(name *)var->data, (unsigned long long)*(name *)var->data); break;
    switch(var->type)
    {
        do_case_basic_unsigned(TYPE_UINT8, uint8_t)
        do_case_basic_unsigned(TYPE_UINT16, uint16_t)
        do_case_basic_unsigned(TYPE_UINT32, uint32_t)
        default:
            printf("Unsupported data type 0x%x for print op\n", var->type);
    }
#undef do_case_basic_unsigned
}

bool finish_unpack_data_block(void)
{
    return g_cur_unpack_len == 0;
}

wchar_t *str_var_to_wchar(struct mtp_string_var *var)
{
    wchar_t *str = malloc(sizeof(wchar_t) * (var->length + 1));
    for(int i = 0; i < var->length; i++)
        str[i] = var->data[i];
    str[var->length] = 0;
    return str;
}

void do_resp(uint16_t code, unsigned nr_param, uint32_t *param)
{
    g_cur_resp.code = code;
    g_cur_resp.nb_parameters = nr_param;
    printf("RESPONSE: code=0x%x params=", code);
    for(unsigned i = 0; i < nr_param; i++)
    {
        g_cur_resp.param[i] = param[i];
        printf("%d ", param[i]);
    }
    printf("\n");
}

void do_cmd(uint16_t code, unsigned nr_param, uint32_t *param)
{
    g_cur_cmd.code = code;
    g_cur_cmd.nb_parameters = nr_param;
    printf("COMMAND: code=0x%x params=", code);
    for(unsigned i = 0; i < nr_param; i++)
    {
        g_cur_cmd.param[i] = param[i];
        printf("%d ", param[i]);
    }
    printf("\n");
}

void do_dev_info_data(void *data, unsigned len)
{
    uint16_t std_ver;
    uint32_t mtp_vendor_ext_id;
    uint16_t mtp_ver;
    struct mtp_string_var mtp_ext, manufacturer, model, dev_ver, serial_num;
    uint16_t func_mode;
    struct mtp_array_uint16_t_var op_list, evt_list, dev_prop_list;
    struct mtp_array_uint16_t_var capture_fmt_list, playback_fmt_list;

    start_unpack_data_block(data, len);
    bool ok = unpack_data_block_uint16_t(&std_ver) &&
        unpack_data_block_uint32_t(&mtp_vendor_ext_id) &&
        unpack_data_block_uint16_t(&mtp_ver) &&
        unpack_data_block_string_var(&mtp_ext) &&
        unpack_data_block_uint16_t(&func_mode) &&
        unpack_data_block_array_uint16_t_var(&op_list) &&
        unpack_data_block_array_uint16_t_var(&evt_list) &&
        unpack_data_block_array_uint16_t_var(&dev_prop_list) &&
        unpack_data_block_array_uint16_t_var(&capture_fmt_list) &&
        unpack_data_block_array_uint16_t_var(&playback_fmt_list) &&
        unpack_data_block_string_var(&manufacturer) &&
        unpack_data_block_string_var(&model) &&
        unpack_data_block_string_var(&dev_ver) &&
        unpack_data_block_string_var(&serial_num);
    if(ok)
    {
        printf("DeviceInfo:\n");
        printf("  Standard Version: %x\n", std_ver);
        printf("  MTP Vendor Ext ID: %x\n", mtp_vendor_ext_id);
        printf("  MTP Version: %x\n", mtp_ver);
        printf("  MTP Ext: %S\n", str_var_to_wchar(&mtp_ext));
        printf("  Func Mode: %x\n", func_mode);
        printf("  Operations: ");
        print_array_uint16_t_var(&op_list);
        printf("\n");
        printf("  Events: ");
        print_array_uint16_t_var(&evt_list);
        printf("\n");
        printf("  Device Prop: ");
        print_array_uint16_t_var(&dev_prop_list);
        printf("\n");
        printf("  Capture Fmt: ");
        print_array_uint16_t_var(&capture_fmt_list);
        printf("\n");
        printf("  Playback Fmt: ");
        print_array_uint16_t_var(&playback_fmt_list);
        printf("\n");
        printf("  Manufacturer: %S\n", str_var_to_wchar(&manufacturer));
        printf("  Model: %S\n", str_var_to_wchar(&model));
        printf("  Device Ver: %S\n", str_var_to_wchar(&dev_ver));
        printf("  Serial Num: %S\n", str_var_to_wchar(&serial_num));
    }
    else
        printf("failed to unpack DeviceInfo dataset\n");
}

void do_stor_ids_data(void *data, unsigned len)
{
    struct mtp_array_uint32_t_var stor_list;

    start_unpack_data_block(data, len);
    bool ok = unpack_data_block_array_uint32_t_var(&stor_list);
    if(ok)
    {
        printf("Storage IDs:\n  ");
        print_array_uint32_t_var(&stor_list);
        printf("\n");
    }
    else
        printf("failed to unpack StorageIDs dataset\n");
}

void do_stor_info_data(void *data, unsigned len)
{
    uint16_t stor_type, fs_type, access_cap;
    uint32_t free_space_obj;
    uint64_t max_cap, free_space_byte;
    struct mtp_string_var stor_desc, volume_id;

    start_unpack_data_block(data, len);
    bool ok = unpack_data_block_uint16_t(&stor_type) &&
        unpack_data_block_uint16_t(&fs_type) &&
        unpack_data_block_uint16_t(&access_cap) &&
        unpack_data_block_uint64_t(&max_cap) &&
        unpack_data_block_uint64_t(&free_space_byte) &&
        unpack_data_block_uint32_t(&free_space_obj) &&
        unpack_data_block_string_var(&stor_desc) &&
        unpack_data_block_string_var(&volume_id);
    if(ok)
    {
        printf("Storage Info (StorID=0x%x):\n", g_cur_cmd.param[0]);
        printf("  Storage Type: %x\n", stor_type);
        printf("  FS Type: %x\n", fs_type);
        printf("  Access Cap: %x\n", access_cap);
        printf("  Max Cap: %llu bytes\n", (unsigned long long)max_cap);
        printf("  Free Space: %llu bytes\n", (unsigned long long) free_space_byte);
        printf("  Free Space: %lu objects\n", (unsigned long)free_space_obj);
        printf("  Description: %S\n", str_var_to_wchar(&stor_desc));
        printf("  Volume ID: %S\n", str_var_to_wchar(&volume_id));
    }
    else
        printf("failed to unpack StorageIDs dataset\n");
}

void do_get_obj_handles_data(void *data, unsigned len)
{
    struct mtp_array_uint32_t_var handle_list;

    start_unpack_data_block(data, len);
    bool ok = unpack_data_block_array_uint32_t_var(&handle_list);
    if(ok)
    {
        printf("Handle List (StorID=0x%x", g_cur_cmd.param[0]);
        if(g_cur_cmd.nb_parameters >= 2)
            printf(",FmtCode=0x%x", g_cur_cmd.param[1]);
        if(g_cur_cmd.nb_parameters >= 3)
            printf(",Handle=0x%x", g_cur_cmd.param[2]);
        printf("):\n  ");
        print_array_uint32_t_var(&handle_list);
        printf("\n");
    }
    else
        printf("failed to unpack HandleList dataset\n");
}

void do_get_dev_prop_desc(void *data, unsigned len)
{
    uint16_t code, datatype;
    uint8_t get_set;
    struct mtp_any_var factory_fault, cur_value;

    start_unpack_data_block(data, len);
    bool ok = unpack_data_block_uint16_t(&code) &&
        unpack_data_block_uint16_t(&datatype) &&
        unpack_data_block_uint8_t(&get_set) &&
        unpack_data_block_any_var(&factory_fault, datatype) &&
        unpack_data_block_any_var(&cur_value, datatype);
    if(ok)
    {
        printf("Device Property Desc:\n");
    }
    else
        printf("failed to unpack HandleList dataset\n");
}

struct mtp_dev_prop_info
{
    uint16_t code;
    uint16_t type;
    const char *name;
} g_dev_prop_info_list[] =
{
    {DEV_PROP_BATTERY_LEVEL, TYPE_UINT8, "Battery Level" },
};

struct mtp_obj_fmt_info
{
    uint16_t fmt;
    const char *name;
} g_obj_fmt_info_list[] =
{
    {OBJ_FMT_FIRMWARE, "Firmware" },
};

const char *get_fmt_name(uint16_t type)
{
    unsigned len = sizeof(g_obj_fmt_info_list) / sizeof(struct mtp_obj_fmt_info);
    for(unsigned i = 0; i < len; i++)
        if(g_obj_fmt_info_list[i].fmt == type)
            return g_obj_fmt_info_list[i].name;
    return NULL;
}

void do_get_dev_prop_value(void *data, unsigned len)
{
    unsigned list_len = sizeof(g_dev_prop_info_list) / sizeof(struct mtp_dev_prop_info);
    struct mtp_any_var any;
    
    for(unsigned i = 0; i < list_len; i++)
    {
        if(g_dev_prop_info_list[i].code != g_cur_cmd.param[0])
            continue;
        printf("Device Property:\n");
            printf("  %s: ", g_dev_prop_info_list[i].name);
        start_unpack_data_block(data, len);
        if(unpack_data_block_any_var(&any, g_dev_prop_info_list[i].type))
        {
            print_any_var(&any);
            printf("\n");
        }
        else
            printf("N/A (unpack failure)\n");
        return;
    }
    printf("Unsupported device property 0x%x\n", g_cur_cmd.param[0]);
}

void do_obj_info(void *data, unsigned len)
{
    uint16_t protection, obj_fmt, thumb_fmt, assoc_type;
    uint32_t stor_id, compressed_size;
    uint32_t thumb_compressed_size, thumb_pix_width, thumb_pix_height;
    uint32_t img_pix_width, img_pix_height, imx_pix_depth, parent;
    uint32_t assoc_desc, seq_nr;
    struct mtp_string_var filename, date_created, date_modified, keywords;

    start_unpack_data_block(data, len);
    bool ok = unpack_data_block_uint32_t(&stor_id) &&
        unpack_data_block_uint16_t(&obj_fmt) &&
        unpack_data_block_uint16_t(&protection) &&
        unpack_data_block_uint32_t(&compressed_size) &&
        unpack_data_block_uint16_t(&thumb_fmt) &&
        unpack_data_block_uint32_t(&thumb_compressed_size) &&
        unpack_data_block_uint32_t(&thumb_pix_width) &&
        unpack_data_block_uint32_t(&thumb_pix_height) &&
        unpack_data_block_uint32_t(&img_pix_width) &&
        unpack_data_block_uint32_t(&img_pix_height) &&
        unpack_data_block_uint32_t(&imx_pix_depth) &&
        unpack_data_block_uint32_t(&parent) &&
        unpack_data_block_uint16_t(&assoc_type) &&
        unpack_data_block_uint32_t(&assoc_desc) &&
        unpack_data_block_uint32_t(&seq_nr) &&
        unpack_data_block_string_var(&filename) &&
        unpack_data_block_string_var(&date_created) &&
        unpack_data_block_string_var(&date_modified) &&
        unpack_data_block_string_var(&keywords);
    if(ok)
    {
        const char *fmt_str = get_fmt_name(obj_fmt);
        if(fmt_str == NULL)
            fmt_str = "N/A";
        printf("Object Info(Handle=0x%x):\n", g_cur_cmd.param[0]);
        printf("  Storage ID: 0x%x\n", stor_id);
        printf("  Object Fmt: 0x%x (%s)\n", obj_fmt, fmt_str);
        printf("  Protection: 0x%x\n", protection);
        printf("  Compr Size: %d\n", compressed_size);
        printf("  Parent: 0x%x\n", parent);
        printf("  Assoc Type: 0x%x\n", assoc_type);
        printf("  Assoc Desc: 0x%x\n", assoc_desc);
        printf("  Filename: %S\n", str_var_to_wchar(&filename));
        printf("  Date Created: %S\n", str_var_to_wchar(&date_created));
        printf("  Date Mod: %S\n", str_var_to_wchar(&date_modified));
        printf("  Keywords: %S\n", str_var_to_wchar(&keywords));
    }
    else
        printf("failed to unpack ObjectInfo dataset\n");
}

void do_send_obj(void *data, unsigned len)
{
    uint8_t *buf = data;
    printf("Object:\n");
    printf("  0x%02x 0x%02x ... 0x%02x 0x%02x\n", buf[0], buf[1],
        buf[len - 2], buf[len - 1]);
}

void do_data(uint16_t code, void *data, unsigned len, int dir_in)
{
    printf("DATA: code=0x%x length=%d dir_in=%d\n", code, len, dir_in);

    if(code == MTP_OP_GET_DEV_INFO && dir_in)
        do_dev_info_data(data, len);
    else if(code == MTP_OP_GET_STORAGE_IDS && dir_in)
        do_stor_ids_data(data, len);
    else if(code == MTP_OP_GET_STORAGE_INFO && dir_in)
        do_stor_info_data(data, len);
    else if(code == MTP_OP_GET_OBJECT_HANDLES && dir_in)
        do_get_obj_handles_data(data, len);
    else if(code == MTP_OP_GET_DEV_PROP_DESC && dir_in)
        do_get_dev_prop_desc(data, len);
    else if(code == MTP_OP_GET_DEV_PROP_VALUE && dir_in)
        do_get_dev_prop_value(data, len);
    else if(code == MTP_OP_SEND_OBJECT_INFO && !dir_in)
        do_obj_info(data, len);
    else if(code == MTP_OP_SEND_OBJECT && !dir_in)
        do_send_obj(data, len);
}

const char *cont_type_str(int type)
{
    switch(type)
    {
        case CONTAINER_COMMAND_BLOCK: return "cmd";
        case CONTAINER_DATA_BLOCK: return "data";
        case CONTAINER_RESPONSE_BLOCK: return "resp";
        case CONTAINER_EVENT_BLOCK: return "evt";
        default: return "unk";
    }
}

void do_container(void *data, unsigned len, int dir_in)
{
    struct generic_container *cont = data;
    if(cont->length != len)
        printf("DIE (%d <> %d)\n", cont->length, len);
    /*
    printf("container: len=%d type=%d (%s) code=0x%x id=%d dir_in=%d\n", cont->length,
        cont->type, cont_type_str(cont->type), cont->code, cont->transaction_id, dir_in);
    //*/
    unsigned nr_param = (cont->length - sizeof(struct generic_container)) / sizeof(uint32_t);
    if(nr_param > 5)
        nr_param = 5;
    uint32_t param[5];
    for(unsigned i = 0; i < nr_param; i++)
        param[i] = *(i + (uint32_t *)(cont + 1));

    if(cont->type == CONTAINER_COMMAND_BLOCK)
        do_cmd(cont->code, nr_param, param);
    else if(cont->type == CONTAINER_RESPONSE_BLOCK)
        do_resp(cont->code, nr_param, param);
    else if(cont->type == CONTAINER_DATA_BLOCK)
        do_data(cont->code, cont + 1, cont->length - sizeof(struct generic_container), dir_in);
}

void do_bulk_in(struct usb_xfer_t *xfer)
{
    void *buf = xfer->data;
    unsigned len = xfer->data_len;

    /*
    printf("ep=%x dir=%x len=%d status=%d type=%c\n", xfer->endpoint_number & 0x7f,
        xfer->endpoint_number & 0x80, xfer->data_len,
        xfer->status, xfer->event_type);
    //*/
    while(len > 0)
    {
        struct generic_container *cont = buf;

        if(!g_in_resp)
        {
            g_in_resp = 1;
            /*
            printf("container: len=%d type=%d code=%d id=%d\n", cont->length, cont->type,
                cont->code, cont->transaction_id);
            //*/
            g_cur_resp_len = cont->length;
            g_cur_resp_rem_len = cont->length;
            
            g_cur_resp_data = malloc(cont->length);
            g_cur_resp_data_ptr = g_cur_resp_data;
        }
        
        unsigned this_len = MIN(g_cur_resp_rem_len, len);

        memcpy(g_cur_resp_data_ptr, buf, this_len);
        g_cur_resp_data_ptr += this_len;
        g_cur_resp_rem_len -= this_len;
        buf += this_len;
        len -= this_len;

        if(g_cur_resp_rem_len <= 0)
        {
            do_container(g_cur_resp_data, g_cur_resp_len, 1);
            free(g_cur_resp_data);
            g_cur_resp_data = g_cur_resp_data_ptr = NULL;
            g_in_resp = 0;
        }
    }
}

void do_bulk_out(struct usb_xfer_t *xfer)
{
    void *buf = xfer->data;
    unsigned len = xfer->data_len;

    /*
    printf("ep=%x dir=%x len=%X status=%d type=%c\n", xfer->endpoint_number & 0x7f,
        xfer->endpoint_number & 0x80, xfer->data_len,
        xfer->status, xfer->event_type);
    //*/
    while(len > 0)
    {
        struct generic_container *cont = buf;

        if(!g_in_command)
        {
            g_in_command = 1;
            /*
            printf("container: len=%d type=%d code=%d id=%d\n", cont->length, cont->type,
                cont->code, cont->transaction_id);
            //*/
            g_cur_cmd_len = cont->length;
            g_cur_cmd_rem_len = cont->length;

            g_cur_cmd_data = malloc(cont->length);
            g_cur_cmd_data_ptr = g_cur_cmd_data;
        }
        
        unsigned this_len = MIN(g_cur_cmd_rem_len, len);

        memcpy(g_cur_cmd_data_ptr, buf, this_len);
        g_cur_cmd_data_ptr += this_len;
        g_cur_cmd_rem_len -= this_len;
        buf += this_len;
        len -= this_len;

        if(g_cur_cmd_rem_len <= 0)
        {
            do_container(g_cur_cmd_data, g_cur_cmd_len, 0);
            free(g_cur_cmd_data);
            g_cur_cmd_data = g_cur_cmd_data_ptr = NULL;
            g_in_command = 0;
        }
    }
}

void xfer_cb(struct usb_xfer_t *xfer)
{
    if(!xfer->event_type == URB_COMPLETE)
        return;
    if(g_mtp_dev_addr == 0)
    {
        if(!g_dev_seen[xfer->device_address])
        {
            g_dev_seen[xfer->device_address] = 1;
            printf("device: %d\n", xfer->device_address);
        }
        return;
    }
    if(xfer->device_address != g_mtp_dev_addr)
        return;

    if(xfer->transfer_type == URB_CONTROL)
    {
    }
    else if(xfer->transfer_type == URB_BULK)
    {
        /* no data ? */
        if(xfer->data_flag != 0)
            return;
        if(xfer->endpoint_number & 0x80)
            do_bulk_in(xfer);
        else
            do_bulk_out(xfer);
    }
}

void capture_cb(u_char *user, const struct pcap_pkthdr *pkt, const u_char *data)
{
    (void) user;
    (void) pkt;
    (void) data;

    struct usb_xfer_t xfer;
    memset(&xfer, 0, sizeof(xfer));

#define copy(field) xfer.field = usb_hdr->field
    
#ifdef DLT_USB_LINUX
    if(g_datalink == DLT_USB_LINUX)
    {
        pcap_usb_header *usb_hdr = (pcap_usb_header *)data;
        copy(event_type);
        copy(transfer_type);
        copy(endpoint_number);
        copy(device_address);
        copy(bus_id);
        copy(setup_flag);
        copy(data_flag);
        copy(status);
        copy(urb_len);
        copy(data_len);
        copy(setup);
        xfer.data = (void *)(usb_hdr + 1);
    }
#endif
#ifdef DLT_USB_LINUX_MMAPPED
    if(g_datalink == DLT_USB_LINUX_MMAPPED)
    {
        pcap_usb_header_mmapped *usb_hdr = (pcap_usb_header_mmapped *)data;
        copy(event_type);
        copy(transfer_type);
        copy(endpoint_number);
        copy(device_address);
        copy(bus_id);
        copy(setup_flag);
        copy(data_flag);
        copy(status);
        copy(urb_len);
        copy(data_len);
        xfer.setup = usb_hdr->s.setup;
        xfer.data = (void *)(usb_hdr + 1);
    }
#endif

    xfer_cb(&xfer);
}

void list_all_dev(void)
{
    pcap_if_t *list_head;
    int rc = pcap_findalldevs(&list_head, errbuf);
    if(rc < 0)
        goto Lpcap_err;

    {
        pcap_if_t *list = list_head;

        printf("capture device list:\n");
        while(list != NULL)
        {
            printf("  %s\t%s\n", list->name, list->description);
            list = list->next;
        }
    }

    pcap_freealldevs(list_head);
    return;

    Lpcap_err:
    printf("pcap error: %s\n", errbuf);
}

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    if(argc < 3)
    {
        printf("usage: mtp_analyzer live|offline <dev/file> <dev addr>\n");
        list_all_dev();
        return 0;
    }

    if(argc == 4)
        g_mtp_dev_addr = atoi(argv[3]);
    printf("dev addr: %d\n", g_mtp_dev_addr);

    pcap_t *device = NULL;
    if(strcmp(argv[1], "live") == 0)
    {
        printf("opening '%s' for capture...\n", argv[1]);
        device = pcap_open_live(argv[2], 65535, 1, 100, errbuf);
        if(device == NULL)
            goto Lpcap_err;
    }
    else if(strcmp(argv[1], "offline") == 0)
    {
        printf("opening '%s' for replay...\n", argv[1]);
        device = pcap_open_offline(argv[2], errbuf);
        if(device == NULL)
            goto Lpcap_err;
    }
    else
    {
        printf("Unknown open method '%s'\n", argv[1]);
        return 1;
    }

    g_datalink = pcap_datalink(device);
    printf("data link: %s\n", pcap_datalink_val_to_name(g_datalink));

    printf("start capture...\n");
    pcap_loop(device, -1, &capture_cb, NULL);

    printf("closing capture device...\n");
    pcap_close(device);

    printf("bye\n");

    return 0;

    Lpcap_err:
    printf("pcap error: %s\n", errbuf);
    return 0;
}
 
