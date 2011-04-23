#include "usb.h"
#include "string.h"
#include "logf.h"
#include "string.h"

#define USB_BASE            0x80080000
#define REG_ID               (*(volatile unsigned int *)(USB_BASE+0x000))
#define REG_HWGENERAL        (*(volatile unsigned int *)(USB_BASE+0x004))
#define REG_HWHOST           (*(volatile unsigned int *)(USB_BASE+0x008))
#define REG_HWDEVICE         (*(volatile unsigned int *)(USB_BASE+0x00c))
#define REG_TXBUF            (*(volatile unsigned int *)(USB_BASE+0x010))
#define REG_RXBUF            (*(volatile unsigned int *)(USB_BASE+0x014))
#define REG_CAPLENGTH        (*(volatile unsigned char*)(USB_BASE+0x100))
#define REG_DCIVERSION       (*(volatile unsigned int *)(USB_BASE+0x120))
#define REG_DCCPARAMS        (*(volatile unsigned int *)(USB_BASE+0x124))
#define REG_USBCMD           (*(volatile unsigned int *)(USB_BASE+0x140))
#define REG_USBSTS           (*(volatile unsigned int *)(USB_BASE+0x144))
#define REG_USBINTR          (*(volatile unsigned int *)(USB_BASE+0x148))
#define REG_FRINDEX          (*(volatile unsigned int *)(USB_BASE+0x14c))
#define REG_DEVICEADDR       (*(volatile unsigned int *)(USB_BASE+0x154))
#define REG_ENDPOINTLISTADDR (*(volatile unsigned int *)(USB_BASE+0x158))
#define REG_BURSTSIZE        (*(volatile unsigned int *)(USB_BASE+0x160))
#define REG_ULPI             (*(volatile unsigned int *)(USB_BASE+0x170))
#define REG_CONFIGFLAG       (*(volatile unsigned int *)(USB_BASE+0x180))
#define REG_PORTSC1          (*(volatile unsigned int *)(USB_BASE+0x184))
#define REG_OTGSC            (*(volatile unsigned int *)(USB_BASE+0x1a4))
#define REG_USBMODE          (*(volatile unsigned int *)(USB_BASE+0x1a8))
#define REG_ENDPTSETUPSTAT   (*(volatile unsigned int *)(USB_BASE+0x1ac))
#define REG_ENDPTPRIME       (*(volatile unsigned int *)(USB_BASE+0x1b0))
#define REG_ENDPTFLUSH       (*(volatile unsigned int *)(USB_BASE+0x1b4))
#define REG_ENDPTSTATUS      (*(volatile unsigned int *)(USB_BASE+0x1b8))
#define REG_ENDPTCOMPLETE    (*(volatile unsigned int *)(USB_BASE+0x1bc))
#define REG_ENDPTCTRL0       (*(volatile unsigned int *)(USB_BASE+0x1c0))
#define REG_ENDPTCTRL1       (*(volatile unsigned int *)(USB_BASE+0x1c4))
#define REG_ENDPTCTRL2       (*(volatile unsigned int *)(USB_BASE+0x1c8))
#define REG_ENDPTCTRL(_x_)   (*(volatile unsigned int *)(USB_BASE+0x1c0+4*(_x_)))

/* USB CMD  Register Bit Masks */
#define USBCMD_RUN                            (0x00000001)
#define USBCMD_CTRL_RESET                     (0x00000002)
#define USBCMD_PERIODIC_SCHEDULE_EN           (0x00000010)
#define USBCMD_ASYNC_SCHEDULE_EN              (0x00000020)
#define USBCMD_INT_AA_DOORBELL                (0x00000040)
#define USBCMD_ASP                            (0x00000300)
#define USBCMD_ASYNC_SCH_PARK_EN              (0x00000800)
#define USBCMD_SUTW                           (0x00002000)
#define USBCMD_ATDTW                          (0x00004000)
#define USBCMD_ITC                            (0x00FF0000)

/* USB STS Register Bit Masks */
#define USBSTS_INT                            (0x00000001)
#define USBSTS_ERR                            (0x00000002)
#define USBSTS_PORT_CHANGE                    (0x00000004)
#define USBSTS_FRM_LST_ROLL                   (0x00000008)
#define USBSTS_SYS_ERR                        (0x00000010) /* not used */
#define USBSTS_IAA                            (0x00000020)
#define USBSTS_RESET                          (0x00000040)
#define USBSTS_SOF                            (0x00000080)
#define USBSTS_SUSPEND                        (0x00000100)
#define USBSTS_HC_HALTED                      (0x00001000)
#define USBSTS_RCL                            (0x00002000)
#define USBSTS_PERIODIC_SCHEDULE              (0x00004000)
#define USBSTS_ASYNC_SCHEDULE                 (0x00008000)

/* USB INTR Register Bit Masks */
#define USBINTR_INT_EN                        (0x00000001)
#define USBINTR_ERR_INT_EN                    (0x00000002)
#define USBINTR_PTC_DETECT_EN                 (0x00000004)
#define USBINTR_FRM_LST_ROLL_EN               (0x00000008)
#define USBINTR_SYS_ERR_EN                    (0x00000010)
#define USBINTR_ASYN_ADV_EN                   (0x00000020)
#define USBINTR_RESET_EN                      (0x00000040)
#define USBINTR_SOF_EN                        (0x00000080)
#define USBINTR_DEVICE_SUSPEND                (0x00000100)

/* Device Address bit masks */
#define USBDEVICEADDRESS_MASK                 (0xFE000000)
#define USBDEVICEADDRESS_BIT_POS              (25)

/* endpoint list address bit masks */
#define USB_EP_LIST_ADDRESS_MASK               (0xfffff800)

/* PORTSCX  Register Bit Masks */
#define PORTSCX_CURRENT_CONNECT_STATUS         (0x00000001)
#define PORTSCX_CONNECT_STATUS_CHANGE          (0x00000002)
#define PORTSCX_PORT_ENABLE                    (0x00000004)
#define PORTSCX_PORT_EN_DIS_CHANGE             (0x00000008)
#define PORTSCX_OVER_CURRENT_ACT               (0x00000010)
#define PORTSCX_OVER_CURRENT_CHG               (0x00000020)
#define PORTSCX_PORT_FORCE_RESUME              (0x00000040)
#define PORTSCX_PORT_SUSPEND                   (0x00000080)
#define PORTSCX_PORT_RESET                     (0x00000100)
#define PORTSCX_LINE_STATUS_BITS               (0x00000C00)
#define PORTSCX_PORT_POWER                     (0x00001000)
#define PORTSCX_PORT_INDICTOR_CTRL             (0x0000C000)
#define PORTSCX_PORT_TEST_CTRL                 (0x000F0000)
#define PORTSCX_WAKE_ON_CONNECT_EN             (0x00100000)
#define PORTSCX_WAKE_ON_CONNECT_DIS            (0x00200000)
#define PORTSCX_WAKE_ON_OVER_CURRENT           (0x00400000)
#define PORTSCX_PHY_LOW_POWER_SPD              (0x00800000)
#define PORTSCX_PORT_FORCE_FULL_SPEED          (0x01000000)
#define PORTSCX_PORT_SPEED_MASK                (0x0C000000)
#define PORTSCX_PORT_WIDTH                     (0x10000000)
#define PORTSCX_PHY_TYPE_SEL                   (0xC0000000)

/* bit 11-10 are line status */
#define PORTSCX_LINE_STATUS_SE0                (0x00000000)
#define PORTSCX_LINE_STATUS_JSTATE             (0x00000400)
#define PORTSCX_LINE_STATUS_KSTATE             (0x00000800)
#define PORTSCX_LINE_STATUS_UNDEF              (0x00000C00)
#define PORTSCX_LINE_STATUS_BIT_POS            (10)

/* bit 15-14 are port indicator control */
#define PORTSCX_PIC_OFF                        (0x00000000)
#define PORTSCX_PIC_AMBER                      (0x00004000)
#define PORTSCX_PIC_GREEN                      (0x00008000)
#define PORTSCX_PIC_UNDEF                      (0x0000C000)
#define PORTSCX_PIC_BIT_POS                    (14)

/* bit 19-16 are port test control */
#define PORTSCX_PTC_DISABLE                    (0x00000000)
#define PORTSCX_PTC_JSTATE                     (0x00010000)
#define PORTSCX_PTC_KSTATE                     (0x00020000)
#define PORTSCX_PTC_SE0NAK                     (0x00030000)
#define PORTSCX_PTC_PACKET                     (0x00040000)
#define PORTSCX_PTC_FORCE_EN                   (0x00050000)
#define PORTSCX_PTC_BIT_POS                    (16)

/* bit 27-26 are port speed */
#define PORTSCX_PORT_SPEED_FULL                (0x00000000)
#define PORTSCX_PORT_SPEED_LOW                 (0x04000000)
#define PORTSCX_PORT_SPEED_HIGH                (0x08000000)
#define PORTSCX_PORT_SPEED_UNDEF               (0x0C000000)
#define PORTSCX_SPEED_BIT_POS                  (26)

/* bit 28 is parallel transceiver width for UTMI interface */
#define PORTSCX_PTW                            (0x10000000)
#define PORTSCX_PTW_8BIT                       (0x00000000)
#define PORTSCX_PTW_16BIT                      (0x10000000)

/* bit 31-30 are port transceiver select */
#define PORTSCX_PTS_UTMI                       (0x00000000)
#define PORTSCX_PTS_CLASSIC                    (0x40000000)
#define PORTSCX_PTS_ULPI                       (0x80000000)
#define PORTSCX_PTS_FSLS                       (0xC0000000)
#define PORTSCX_PTS_BIT_POS                    (30)

/* USB MODE Register Bit Masks */
#define USBMODE_CTRL_MODE_IDLE                (0x00000000)
#define USBMODE_CTRL_MODE_DEVICE              (0x00000002)
#define USBMODE_CTRL_MODE_HOST                (0x00000003)
#define USBMODE_CTRL_MODE_RSV                 (0x00000001)
#define USBMODE_SETUP_LOCK_OFF                (0x00000008)
#define USBMODE_STREAM_DISABLE                (0x00000010)

/* Endpoint Flush Register */
#define EPFLUSH_TX_OFFSET                      (0x00010000)
#define EPFLUSH_RX_OFFSET                      (0x00000000)

/* Endpoint Setup Status bit masks */
#define EPSETUP_STATUS_MASK                   (0x0000003F)
#define EPSETUP_STATUS_EP0                    (0x00000001)

/* ENDPOINTCTRLx  Register Bit Masks */
#define EPCTRL_TX_ENABLE                       (0x00800000)
#define EPCTRL_TX_DATA_TOGGLE_RST              (0x00400000)    /* Not EP0 */
#define EPCTRL_TX_DATA_TOGGLE_INH              (0x00200000)    /* Not EP0 */
#define EPCTRL_TX_TYPE                         (0x000C0000)
#define EPCTRL_TX_DATA_SOURCE                  (0x00020000)    /* Not EP0 */
#define EPCTRL_TX_EP_STALL                     (0x00010000)
#define EPCTRL_RX_ENABLE                       (0x00000080)
#define EPCTRL_RX_DATA_TOGGLE_RST              (0x00000040)    /* Not EP0 */
#define EPCTRL_RX_DATA_TOGGLE_INH              (0x00000020)    /* Not EP0 */
#define EPCTRL_RX_TYPE                         (0x0000000C)
#define EPCTRL_RX_DATA_SINK                    (0x00000002)    /* Not EP0 */
#define EPCTRL_RX_EP_STALL                     (0x00000001)

/* bit 19-18 and 3-2 are endpoint type */
#define EPCTRL_TX_EP_TYPE_SHIFT                (18)
#define EPCTRL_RX_EP_TYPE_SHIFT                (2)

/* pri_ctrl Register Bit Masks */
#define PRI_CTRL_PRI_LVL1                      (0x0000000C)
#define PRI_CTRL_PRI_LVL0                      (0x00000003)

/* si_ctrl Register Bit Masks */
#define SI_CTRL_ERR_DISABLE                    (0x00000010)
#define SI_CTRL_IDRC_DISABLE                   (0x00000008)
#define SI_CTRL_RD_SAFE_EN                     (0x00000004)
#define SI_CTRL_RD_PREFETCH_DISABLE            (0x00000002)
#define SI_CTRL_RD_PREFEFETCH_VAL              (0x00000001)

/* control Register Bit Masks */
#define USB_CTRL_IOENB                         (0x00000004)
#define USB_CTRL_ULPI_INT0EN                   (0x00000001)

/* OTGSC Register Bit Masks */
#define OTGSC_B_SESSION_VALID                  (0x00000800)
#define OTGSC_A_VBUS_VALID                     (0x00000200)

#define QH_MULT_POS                            (30)
#define QH_ZLT_SEL                             (0x20000000)
#define QH_MAX_PKT_LEN_POS                     (16)
#define QH_IOS                                 (0x00008000)
#define QH_NEXT_TERMINATE                      (0x00000001)
#define QH_IOC                                 (0x00008000)
#define QH_MULTO                               (0x00000C00)
#define QH_STATUS_HALT                         (0x00000040)
#define QH_STATUS_ACTIVE                       (0x00000080)
#define EP_QUEUE_CURRENT_OFFSET_MASK         (0x00000FFF)
#define EP_QUEUE_HEAD_NEXT_POINTER_MASK      (0xFFFFFFE0)
#define EP_QUEUE_FRINDEX_MASK                (0x000007FF)
#define EP_MAX_LENGTH_TRANSFER               (0x4000)

#define DTD_NEXT_TERMINATE                   (0x00000001)
#define DTD_IOC                              (0x00008000)
#define DTD_STATUS_ACTIVE                    (0x00000080)
#define DTD_STATUS_HALTED                    (0x00000040)
#define DTD_STATUS_DATA_BUFF_ERR             (0x00000020)
#define DTD_STATUS_TRANSACTION_ERR           (0x00000008)
#define DTD_RESERVED_FIELDS                  (0x80007300)
#define DTD_ADDR_MASK                        (0xFFFFFFE0)
#define DTD_PACKET_SIZE                      (0x7FFF0000)
#define DTD_LENGTH_BIT_POS                   (16)
#define DTD_ERROR_MASK                       (DTD_STATUS_HALTED | \
                                               DTD_STATUS_DATA_BUFF_ERR | \
                                               DTD_STATUS_TRANSACTION_ERR)

#define DTD_RESERVED_LENGTH_MASK             0x0001ffff
#define DTD_RESERVED_IN_USE                  0x80000000
#define DTD_RESERVED_PIPE_MASK               0x0ff00000
#define DTD_RESERVED_PIPE_OFFSET             20

struct usb_td_t
{
    unsigned int next_td_ptr; /* Next TD pointer(31-5), T(0) set indicate invalid */
    unsigned int size_ioc_sts; /* Total bytes (30-16), IOC (15), MultO(11-10), STS (7-0)  */
    unsigned int buff_ptr0; /* Buffer pointer Page 0 */
    unsigned int buff_ptr1; /* Buffer pointer Page 1 */
    unsigned int buff_ptr2; /* Buffer pointer Page 2 */
    unsigned int buff_ptr3; /* Buffer pointer Page 3 */
    unsigned int buff_ptr4; /* Buffer pointer Page 4 */
    unsigned int reserved;
} __attribute__ ((packed));

struct usb_qh_t {
    unsigned int max_pkt_length;/* Mult(31-30) , Zlt(29) , Max Pkt len and IOS(15) */
    unsigned int curr_dtd_ptr; /* Current dTD Pointer(31-5) */
    struct usb_td_t dtd; /* dTD overlay */
    unsigned int setup_buffer[2]; /* Setup data 8 bytes */
    unsigned int reserved[4];
} __attribute__((packed));

/*
 * USB directions
 *
 * This bit flag is used in endpoint descriptors' bEndpointAddress field.
 * It's also one of three fields in control requests bRequestType.
 */
#define USB_DIR_OUT                     0               /* to device */
#define USB_DIR_IN                      0x80            /* to host */

/*
 * USB types, the second of three bRequestType fields
 */
#define USB_TYPE_MASK                   (0x03 << 5)
#define USB_TYPE_STANDARD               (0x00 << 5)
#define USB_TYPE_CLASS                  (0x01 << 5)
#define USB_TYPE_VENDOR                 (0x02 << 5)
#define USB_TYPE_RESERVED               (0x03 << 5)

/*
 * USB recipients, the third of three bRequestType fields
 */
#define USB_RECIP_MASK                  0x1f
#define USB_RECIP_DEVICE                0x00
#define USB_RECIP_INTERFACE             0x01
#define USB_RECIP_ENDPOINT              0x02
#define USB_RECIP_OTHER                 0x03

/*
 * Standard requests, for the bRequest field of a SETUP packet.
 *
 * These are qualified by the bRequestType field, so that for example
 * TYPE_CLASS or TYPE_VENDOR specific feature flags could be retrieved
 * by a GET_STATUS request.
 */
#define USB_REQ_GET_STATUS              0x00
#define USB_REQ_CLEAR_FEATURE           0x01
#define USB_REQ_SET_FEATURE             0x03
#define USB_REQ_SET_ADDRESS             0x05
#define USB_REQ_GET_DESCRIPTOR          0x06
#define USB_REQ_SET_DESCRIPTOR          0x07
#define USB_REQ_GET_CONFIGURATION       0x08
#define USB_REQ_SET_CONFIGURATION       0x09
#define USB_REQ_GET_INTERFACE           0x0A
#define USB_REQ_SET_INTERFACE           0x0B
#define USB_REQ_SYNCH_FRAME             0x0C
/*
 * USB feature flags are written using USB_REQ_{CLEAR,SET}_FEATURE, and
 * are read as a bit array returned by USB_REQ_GET_STATUS.  (So there
 * are at most sixteen features of each type.)  Hubs may also support a
 * new USB_REQ_TEST_AND_SET_FEATURE to put ports into L1 suspend.
 */
#define USB_DEVICE_SELF_POWERED         0   /* (read only) */
#define USB_DEVICE_REMOTE_WAKEUP        1   /* dev may initiate wakeup */
#define USB_DEVICE_TEST_MODE            2   /* (wired high speed only) */
#define USB_DEVICE_BATTERY              2   /* (wireless) */
#define USB_DEVICE_B_HNP_ENABLE         3   /* (otg) dev may initiate HNP */
#define USB_DEVICE_WUSB_DEVICE          3   /* (wireless)*/
#define USB_DEVICE_A_HNP_SUPPORT        4   /* (otg) RH port supports HNP */
#define USB_DEVICE_A_ALT_HNP_SUPPORT    5   /* (otg) other RH port does */
#define USB_DEVICE_DEBUG_MODE           6   /* (special devices only) */

#define USB_ENDPOINT_HALT       0   /* IN/OUT will STALL */

struct usb_ctrlrequest {
        uint8_t bRequestType;
        uint8_t bRequest;
        uint16_t wValue;
        uint16_t wIndex;
        uint16_t wLength;
} __attribute__ ((packed));

/*
 * Descriptor types ... USB 2.0 spec table 9.5
 */
#define USB_DT_DEVICE                   0x01
#define USB_DT_CONFIG                   0x02
#define USB_DT_STRING                   0x03
#define USB_DT_INTERFACE                0x04
#define USB_DT_ENDPOINT                 0x05
#define USB_DT_DEVICE_QUALIFIER         0x06
#define USB_DT_OTHER_SPEED_CONFIG       0x07
#define USB_DT_INTERFACE_POWER          0x08
/* these are from a minor usb 2.0 revision (ECN) */
#define USB_DT_OTG                      0x09
#define USB_DT_DEBUG                    0x0a
#define USB_DT_INTERFACE_ASSOCIATION    0x0b
/* these are from the Wireless USB spec */
#define USB_DT_SECURITY                 0x0c
#define USB_DT_KEY                      0x0d
#define USB_DT_ENCRYPTION_TYPE          0x0e
#define USB_DT_BOS                      0x0f
#define USB_DT_DEVICE_CAPABILITY        0x10
#define USB_DT_WIRELESS_ENDPOINT_COMP   0x11
#define USB_DT_WIRE_ADAPTER             0x21
#define USB_DT_RPIPE                    0x22
#define USB_DT_CS_RADIO_CONTROL         0x23

/* USB_DT_DEVICE: Device descriptor */
struct usb_device_descriptor {
        uint8_t  bLength;
        uint8_t  bDescriptorType;

        uint16_t bcdUSB;
        uint8_t  bDeviceClass;
        uint8_t  bDeviceSubClass;
        uint8_t  bDeviceProtocol;
        uint8_t  bMaxPacketSize0;
        uint16_t idVendor;
        uint16_t idProduct;
        uint16_t bcdDevice;
        uint8_t  iManufacturer;
        uint8_t  iProduct;
        uint8_t  iSerialNumber;
        uint8_t  bNumConfigurations;
} __attribute__ ((packed));

#define USB_DT_DEVICE_SIZE              18

/*
 * Device and/or Interface Class codes
 * as found in bDeviceClass or bInterfaceClass
 * and defined by www.usb.org documents
 */
#define USB_CLASS_PER_INTERFACE         0       /* for DeviceClass */
#define USB_CLASS_AUDIO                 1
#define USB_CLASS_COMM                  2
#define USB_CLASS_HID                   3
#define USB_CLASS_PHYSICAL              5
#define USB_CLASS_STILL_IMAGE           6
#define USB_CLASS_PRINTER               7
#define USB_CLASS_MASS_STORAGE          8
#define USB_CLASS_HUB                   9
#define USB_CLASS_CDC_DATA              0x0a
#define USB_CLASS_CSCID                 0x0b    /* chip+ smart card */
#define USB_CLASS_CONTENT_SEC           0x0d    /* content security */
#define USB_CLASS_VIDEO                 0x0e
#define USB_CLASS_WIRELESS_CONTROLLER   0xe0
#define USB_CLASS_MISC                  0xef
#define USB_CLASS_APP_SPEC              0xfe
#define USB_CLASS_VENDOR_SPEC           0xff

/* USB_DT_CONFIG: Configuration descriptor information.
 *
 * USB_DT_OTHER_SPEED_CONFIG is the same descriptor, except that the
 * descriptor type is different.  Highspeed-capable devices can look
 * different depending on what speed they're currently running.  Only
 * devices with a USB_DT_DEVICE_QUALIFIER have any OTHER_SPEED_CONFIG
 * descriptors.
 */
struct usb_config_descriptor {
       uint8_t  bLength;
       uint8_t  bDescriptorType;

       uint16_t wTotalLength;
       uint8_t  bNumInterfaces;
       uint8_t  bConfigurationValue;
       uint8_t  iConfiguration;
       uint8_t  bmAttributes;
       uint8_t  bMaxPower;
} __attribute__ ((packed));

#define USB_DT_CONFIG_SIZE              9

/* from config descriptor bmAttributes */
#define USB_CONFIG_ATT_ONE              (1 << 7)        /* must be set */
#define USB_CONFIG_ATT_SELFPOWER        (1 << 6)        /* self powered */
#define USB_CONFIG_ATT_WAKEUP           (1 << 5)        /* can wakeup */
#define USB_CONFIG_ATT_BATTERY          (1 << 4)        /* battery powered */

static struct usb_qh_t qh_array[2]
    __attribute__((section(".octext"))) __attribute__((aligned(2048)));
static struct usb_td_t td_array[2]
    __attribute__((section(".octext"))) __attribute__((aligned(64)));
static unsigned char response_data[256]
    __attribute__((section(".octext")));

#define USB_MAX_CURRENT     500

static struct usb_device_descriptor __attribute__((aligned(2))) __attribute__((section(".octext")))
                                          device_descriptor=
{
    .bLength            = sizeof(struct usb_device_descriptor),
    .bDescriptorType    = USB_DT_DEVICE,
    .bcdUSB             = 0x0200,
    .bDeviceClass       = USB_CLASS_PER_INTERFACE,
    .bDeviceSubClass    = 0,
    .bDeviceProtocol    = 0,
    .bMaxPacketSize0    = 64,
    .idVendor           = 0x9999,
    .idProduct          = 0x9999,
    .bcdDevice          = 0x0100,
    .iManufacturer      = 0,
    .iProduct           = 0,
    .iSerialNumber      = 0,
    .bNumConfigurations = 1
};

static struct usb_config_descriptor __attribute__((aligned(2)))
                                    config_descriptor =
{
    .bLength             = sizeof(struct usb_config_descriptor),
    .bDescriptorType     = USB_DT_CONFIG,
    .wTotalLength        = 0, /* will be filled in later */
    .bNumInterfaces      = 0,
    .bConfigurationValue = 1,
    .iConfiguration      = 0,
    .bmAttributes        = USB_CONFIG_ATT_ONE | USB_CONFIG_ATT_SELFPOWER,
    .bMaxPower           = (USB_MAX_CURRENT + 1) / 2, /* In 2mA units */
};

static void usb_xfer(void *ptr, unsigned len, bool send)
{
    unsigned pipe = send ? 1 : 0;
    unsigned mask = send ? 0x10000 : 0x1;
    struct usb_td_t *td = &td_array[pipe];
    struct usb_qh_t *qh = &qh_array[pipe];
    
    memset(td, 0, sizeof(struct usb_td_t));
    td->next_td_ptr = DTD_NEXT_TERMINATE;
    td->size_ioc_sts = (len<< DTD_LENGTH_BIT_POS) | DTD_STATUS_ACTIVE | DTD_IOC;
    td->buff_ptr0 = (unsigned int)ptr;
    td->buff_ptr1 = ((unsigned int)ptr & 0xfffff000) + 0x1000;
    td->buff_ptr2 = ((unsigned int)ptr & 0xfffff000) + 0x2000;
    td->buff_ptr3 = ((unsigned int)ptr & 0xfffff000) + 0x3000;
    td->buff_ptr4 = ((unsigned int)ptr & 0xfffff000) + 0x4000;
    td->reserved |= DTD_RESERVED_LENGTH_MASK & len;
    td->reserved |= DTD_RESERVED_IN_USE;
    td->reserved |= (pipe << DTD_RESERVED_PIPE_OFFSET);
    qh->dtd.next_td_ptr = (unsigned int)td;
    qh->dtd.size_ioc_sts &= ~(QH_STATUS_HALT | QH_STATUS_ACTIVE);

    REG_ENDPTPRIME |= mask;
}

static void usb_send(void *buffer, unsigned len)
{
    usb_xfer(buffer, len, true);
}

static void usb_recv(void *buffer, unsigned len)
{
    usb_xfer(buffer, len, false);
}

static void usb_stall()
{
    REG_ENDPTCTRL(0) |= EPCTRL_TX_EP_STALL | EPCTRL_RX_EP_STALL;
}

static void handle_get_desc(struct usb_ctrlrequest *req)
{
    void *ptr;
    unsigned size;
    unsigned length = req->wLength;

    switch(req->wValue >> 8)
    {
        case USB_DT_DEVICE:
            ptr = &device_descriptor;
            size = sizeof(struct usb_device_descriptor);
            break;
        case USB_DT_CONFIG:
            ptr = &config_descriptor;
            size = sizeof(struct usb_config_descriptor);
            break;
        default:
            usb_stall();
            return;
    }

    length = MIN(size, length);

    if(ptr != response_data)
        memcpy(response_data, ptr, length);

    usb_recv(NULL, 0);
    usb_send(response_data, length);
}

static void handle_std_setup(struct usb_ctrlrequest *req)
{
    switch(req->bRequest)
    {
        case USB_REQ_SET_ADDRESS:
            usb_send(NULL, 0);
            REG_DEVICEADDR = req->wValue << USBDEVICEADDRESS_BIT_POS;
            break;
        case USB_REQ_GET_DESCRIPTOR:
            handle_get_desc(req);
            break;
        case USB_REQ_SET_CONFIGURATION:
            usb_send(NULL, 0);
            break;
        default:
            usb_stall();
            break;
    }
}

static void handle_vendor_setup(struct usb_ctrlrequest *req)
{
    if(req->bRequestType & USB_DIR_IN &&
            (req->bRequestType & USB_RECIP_MASK) == USB_RECIP_DEVICE)
    {
        if(req->bRequest == 0x99)
        {
            size_t len = logf_readback((char *)response_data, sizeof(response_data));
            usb_recv(NULL, 0);
            usb_send(response_data, len);
        }
        else
            usb_stall();
    }
    else
        usb_stall();
}

static void handle_setup(struct usb_ctrlrequest *req)
{
    switch(req->bRequestType & USB_TYPE_MASK)
    {
        case USB_TYPE_STANDARD:
            return handle_std_setup(req);
        case USB_TYPE_VENDOR:
            return handle_vendor_setup(req);
        default:
            usb_stall();
    }
}

static void control_received()
{
    static unsigned int tmp[2];
    tmp[0] = qh_array[0].setup_buffer[0];
    tmp[1] = qh_array[0].setup_buffer[1];

    /* acknowledge packet recieved */
    REG_ENDPTSETUPSTAT = EPSETUP_STATUS_EP0;

    handle_setup((struct usb_ctrlrequest *)tmp);
}

static void transfer_completed()
{
    unsigned int mask = REG_ENDPTCOMPLETE;
    REG_ENDPTCOMPLETE = mask;
}

void INT_USB_CTRL(void)
{
    unsigned int usbintr = REG_USBINTR;
    unsigned int status = REG_USBSTS & usbintr;

    /* usb transaction interrupt */
    if(status & USBSTS_INT)
    {
        REG_USBSTS = USBSTS_INT;

        if(REG_ENDPTSETUPSTAT & EPSETUP_STATUS_EP0)
            control_received();

        if(REG_ENDPTCOMPLETE)
            transfer_completed();
    }

    /* error interrupt */
    if(status & USBSTS_ERR)
        REG_USBSTS = USBSTS_ERR;

    /* reset interrupt */
    if(status & USBSTS_RESET)
    {
        REG_USBSTS = USBSTS_RESET;

        REG_DEVICEADDR = 0;
        REG_ENDPTSETUPSTAT = REG_ENDPTSETUPSTAT;
        REG_ENDPTCOMPLETE  = REG_ENDPTCOMPLETE;
        REG_ENDPTFLUSH = ~0;
        while(REG_ENDPTFLUSH);
        memset(td_array, 0, sizeof(td_array));
    }

    /* port change */
    if(status & USBSTS_PORT_CHANGE)
        REG_USBSTS = USBSTS_PORT_CHANGE;
}

void usb_init(void)
{
    REG_USBCMD &= ~USBCMD_RUN;
    udelay(HZ / 20);
    REG_USBCMD |= USBCMD_CTRL_RESET;
    while (REG_USBCMD & USBCMD_CTRL_RESET);
    REG_USBMODE = USBMODE_CTRL_MODE_DEVICE;
    
    memset(qh_array, 0, sizeof qh_array);
    qh_array[0].max_pkt_length = 64 << QH_MAX_PKT_LEN_POS | QH_IOS;
    qh_array[0].dtd.next_td_ptr = QH_NEXT_TERMINATE;
    qh_array[1].max_pkt_length = 64 << QH_MAX_PKT_LEN_POS;
    qh_array[1].dtd.next_td_ptr = QH_NEXT_TERMINATE;
    REG_ENDPOINTLISTADDR = (unsigned int)qh_array;
    REG_DEVICEADDR = 0;
    REG_USBINTR = USBINTR_INT_EN | USBINTR_ERR_INT_EN |
        USBINTR_PTC_DETECT_EN | USBINTR_RESET_EN;
    imx233_enable_interrupt(INT_SRC_USB_CTRL, true);
    REG_USBCMD |= USBCMD_RUN;
}

void usb_task(void)
{
}
