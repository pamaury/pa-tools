#ifndef __PROTOCOL__
#define __PROTOCOL__

#define USB_CMD_INFO    0x66
#define USB_CMD_WRAPPED 0xaa
#define USB_CMD_READLOG 0xbb

#define PROTOCOL_VERSION    1

#define PROTOCOL_MAGIC  "badrock"
#define PROTOCOL_MAGIC_SIZE 7

struct usb_cmd_info_t
{
    uint8_t magic[PROTOCOL_MAGIC_SIZE];
    uint8_t prot_ver;
};

struct usb_cmd_hdr_t
{
    uint8_t cmd;
    uint8_t flags;
} __attribute__((packed));

#define CMD_MEMORY  0x00
#define CMD_OTP     0x01
#define CMD_SSP     0x02
#define CMD_LRADC   0x03
#define CMD_I2C     0x04

#define FLAGS_READ  (1 << 0)
#define FLAGS_WRITE (1 << 1)

struct usb_cmd_mem_t
{
    struct usb_cmd_hdr_t hdr;
    uint32_t addr;
    uint16_t length; /* must fit in a single usb transfer */
    uint8_t data[0];
} __attribute__((packed));

struct usb_cmd_read_otp_t
{
    struct usb_cmd_hdr_t hdr;
    uint8_t reg;
} __attribute__((packed));

#define OTP_REG_ROM_COUNT   8
#define OTP_REG_ROM(x)      (x)

#define FLAGS_SSP_NO_RESP   (1 << 2)
#define FLAGS_SSP_LONG_RESP (1 << 3)

struct usb_cmd_ssp_t
{
    struct usb_cmd_hdr_t hdr;
    uint8_t ssp;
    uint8_t cmd;
    uint32_t arg;
    uint32_t length;
    uint8_t data[0];
} __attribute__((packed));

struct usb_resp_ssp_t
{
    uint32_t status;
    uint32_t ctrl1;
    uint32_t resp[4];
    uint32_t length;
    uint8_t data[0];
} __attribute__((packed));

#define FLAGS_LRADC_DIVIDE_BY_2 (1 << 2)
#define FLAGS_LRADC_ACCUMULATE  (1 << 3)

#define LRADC_NUM_CHANNELS  16
#define LRADC_CHANNEL(x)    (x)
#define LRADC_CHANNEL_VDDIO     LRADC_CHANNEL(6)
#define LRADC_CHANNEL_BATTERY   LRADC_CHANNEL(7)
#define LRADC_CHANNEL_PMOS_THIN LRADC_CHANNEL(8)
#define LRADC_CHANNEL_NMOS_THIN LRADC_CHANNEL(9)
#define LRADC_CHANNEL_NMOS_THICK    LRADC_CHANNEL(10)
#define LRADC_CHANNEL_PMOS_THICK    LRADC_CHANNEL(11)
#define LRADC_CHANNEL_PMOS_THICK    LRADC_CHANNEL(11)
#define LRADC_CHANNEL_USB_DP    LRADC_CHANNEL(12)
#define LRADC_CHANNEL_USB_DN    LRADC_CHANNEL(13)
#define LRADC_CHANNEL_VBG       LRADC_CHANNEL(14)
#define LRADC_CHANNEL_5V        LRADC_CHANNEL(15)

struct usb_cmd_lradc_t
{
    struct usb_cmd_hdr_t hdr;
    uint8_t hw_chan;
    uint8_t num_samples;
} __attribute__((packed));

struct usb_resp_lradc_t
{
    uint32_t value;
} __attribute__((packed));

#define FLAGS_I2C_GENERIC   (1 << 2)
#define FLAGS_I2C_POKE      (1 << 3)

struct usb_cmd_i2c_poke_t
{
    struct usb_cmd_hdr_t hdr;
    uint8_t dev_addr;
} __attribute__((packed));

struct usb_resp_i2c_poke_t
{
    uint32_t ctrl1;
    uint32_t status;
} __attribute__((packed));

#define FLAGS_I2C_STAGE_START   (1 << 0)
#define FLAGS_I2C_STAGE_STOP    (1 << 1)
#define FLAGS_I2C_STAGE_SEND    (1 << 2)

struct usb_cmd_i2c_stage_t
{
    uint8_t flags;
    uint16_t length;
} __attribute__((packed));

struct usb_cmd_i2c_generic_t
{
    struct usb_cmd_hdr_t hdr;
    uint8_t nr_stages;
    struct usb_cmd_i2c_stage_t stages[0];
    uint8_t data[0];
} __attribute__((packed));

struct usb_resp_i2c_generic_t
{
    uint32_t ctrl1;
    uint32_t status;
    uint32_t length;
    uint8_t data[0];
} __attribute__((packed));

#endif /* __PROTOCOL__ */
