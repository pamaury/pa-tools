#include "stddef.h"
#include "protocol.h"
#include "logf.h"

//#define HAVE_STMP3700

/**
 *
 * Common
 *
 */
#define MIN(a,b) ((a) < (b) ? (a) : (b))

#define __REG_SET(reg)  (*((volatile uint32_t *)(&reg + 1)))
#define __REG_CLR(reg)  (*((volatile uint32_t *)(&reg + 2)))
#define __REG_TOG(reg)  (*((volatile uint32_t *)(&reg + 3)))

#define __BLOCK_SFTRST  (1 << 31)
#define __BLOCK_CLKGATE (1 << 30)

#define __XTRACT(reg, field)    ((reg & reg##__##field##_BM) >> reg##__##field##_BP)
#define __XTRACT_EX(val, field)    (((val) & field##_BM) >> field##_BP)
#define __FIELD_SET(reg, field, val) reg = (reg & ~reg##__##field##_BM) | (val << reg##__##field##_BP)

/**
 *
 * USB subsystem
 *
 */

#define USB_BASE            0x80080000
#define USB_NUM_ENDPOINTS   2
#define MAX_PKT_SIZE        32

/* USB device mode registers (Little Endian) */
#define REG_ENDPOINTLISTADDR (*(volatile unsigned int *)(USB_BASE+0x158))
#define REG_ENDPTSETUPSTAT   (*(volatile unsigned int *)(USB_BASE+0x1ac))
#define REG_ENDPTPRIME       (*(volatile unsigned int *)(USB_BASE+0x1b0))
#define REG_ENDPTSTATUS      (*(volatile unsigned int *)(USB_BASE+0x1b8))
#define REG_ENDPTCOMPLETE    (*(volatile unsigned int *)(USB_BASE+0x1bc))
#define REG_ENDPTCTRL0       (*(volatile unsigned int *)(USB_BASE+0x1c0))
#define REG_ENDPTCTRL1       (*(volatile unsigned int *)(USB_BASE+0x1c4))
#define REG_ENDPTCTRL2       (*(volatile unsigned int *)(USB_BASE+0x1c8))
#define REG_ENDPTCTRL(_x_)   (*(volatile unsigned int *)(USB_BASE+0x1c0+4*(_x_)))

/* Endpoint Setup Status bit masks */
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
/*-------------------------------------------------------------------------*/
/* manual: 32.13.2 Endpoint Transfer Descriptor (dTD) */
struct transfer_descriptor {
    unsigned int next_td_ptr;           /* Next TD pointer(31-5), T(0) set
                                           indicate invalid */
    unsigned int size_ioc_sts;          /* Total bytes (30-16), IOC (15),
                                           MultO(11-10), STS (7-0)  */
    unsigned int buff_ptr0;             /* Buffer pointer Page 0 */
    unsigned int buff_ptr1;             /* Buffer pointer Page 1 */
    unsigned int buff_ptr2;             /* Buffer pointer Page 2 */
    unsigned int buff_ptr3;             /* Buffer pointer Page 3 */
    unsigned int buff_ptr4;             /* Buffer pointer Page 4 */
    unsigned int reserved;
} __attribute__ ((packed));

static struct transfer_descriptor td_array[USB_NUM_ENDPOINTS*2]
    __attribute__((aligned(32)));

/* manual: 32.13.1 Endpoint Queue Head (dQH) */
struct queue_head {
    unsigned int max_pkt_length;    /* Mult(31-30) , Zlt(29) , Max Pkt len
                                       and IOS(15) */
    unsigned int curr_dtd_ptr;      /* Current dTD Pointer(31-5) */
    struct transfer_descriptor dtd; /* dTD overlay */
    unsigned int setup_buffer[2];   /* Setup data 8 bytes */
    unsigned int reserved;          /* for software use, pointer to the first TD */
    unsigned int status;            /* for software use, status of chain in progress */
    unsigned int length;            /* for software use, transfered bytes of chain in progress */
    unsigned int wait;              /* for softwate use, indicates if the transfer is blocking */
} __attribute__((packed));

static struct queue_head qh_array[USB_NUM_ENDPOINTS*2] __attribute__((aligned(2048)));

static const unsigned int pipe2mask[] = {
    0x01, 0x010000,
    0x02, 0x020000,
    0x04, 0x040000,
    0x08, 0x080000,
    0x10, 0x100000,
};

extern unsigned char buffer[];

struct usb_ctrlrequest {
    unsigned char bRequestType;
    unsigned char bRequest;
    unsigned short wValue;
    unsigned short wIndex;
    unsigned short wLength;
} __attribute__ ((packed));

/* return transfered size if wait=true */
static int prime_transfer(int ep_num, void *ptr, int len, bool send, bool wait)
{
    int pipe = ep_num * 2 + (send ? 1 : 0);
    unsigned mask = pipe2mask[pipe];
    struct transfer_descriptor *td = &td_array[pipe];
    struct queue_head* qh = &qh_array[pipe];
    
    /* prepare TD */
    td->next_td_ptr = DTD_NEXT_TERMINATE;
    td->size_ioc_sts = (len<< DTD_LENGTH_BIT_POS) | DTD_STATUS_ACTIVE;
    td->buff_ptr0 = (unsigned int)ptr;
    td->buff_ptr1 = ((unsigned int)ptr & 0xfffff000) + 0x1000;
    td->buff_ptr2 = ((unsigned int)ptr & 0xfffff000) + 0x2000;
    td->buff_ptr3 = ((unsigned int)ptr & 0xfffff000) + 0x3000;
    td->buff_ptr4 = ((unsigned int)ptr & 0xfffff000) + 0x4000;
    td->reserved = 0;
    /* prime */
    qh->dtd.next_td_ptr = (unsigned int)td;
    qh->dtd.size_ioc_sts &= ~(QH_STATUS_HALT | QH_STATUS_ACTIVE);
    REG_ENDPTPRIME |= mask;
    /* wait for priming to be taken into account */
    while(!(REG_ENDPTSTATUS & mask));
    /* wait for completion */
    if(wait)
    {
        while(!(REG_ENDPTCOMPLETE & mask));
        REG_ENDPTCOMPLETE = mask;
        /* memory barrier */
        asm volatile("":::"memory");
        /* return transfered size */
        return len - (td->size_ioc_sts >> DTD_LENGTH_BIT_POS);
    }
    else
        return 0;
}

/**
 *
 * SSP susbsytem
 *
 */

#define BLOCK_SIZE      512
#define BLOCK_SIZE_LOG  9

/* ssp can value 1 or 2 */
#define __SSP_SELECT(ssp, ssp1, ssp2) ((ssp) == 1 ? (ssp1) : (ssp2))

#define INT_SRC_SSP_DMA(ssp)    __SSP_SELECT(ssp, INT_SRC_SSP1_DMA, INT_SRC_SSP2_DMA)
#define INT_SRC_SSP_ERROR(ssp)  __SSP_SELECT(ssp, INT_SRC_SSP1_ERROR, INT_SRC_SSP2_ERROR)

#define HW_SSP1_BASE        0x80010000
#define HW_SSP2_BASE        0x80034000

#define HW_SSP_BASE(ssp)    __SSP_SELECT(ssp, HW_SSP1_BASE, HW_SSP2_BASE)

#define HW_SSP_CTRL0(ssp)   (*(volatile uint32_t *)(HW_SSP_BASE(ssp) + 0x0))
#define HW_SSP_CTRL0__RUN           (1 << 29)
#define HW_SSP_CTRL0__SDIO_IRQ_CHECK    (1 << 28)
#define HW_SSP_CTRL0__LOCK_CS       (1 << 27)
#define HW_SSP_CTRL0__IGNORE_CRC    (1 << 26)
#define HW_SSP_CTRL0__READ          (1 << 25)
#define HW_SSP_CTRL0__DATA_XFER     (1 << 24)
#define HW_SSP_CTRL0__BUS_WIDTH_BM  (3 << 22)
#define HW_SSP_CTRL0__BUS_WIDTH_BP  22
#define HW_SSP_CTRL0__BUS_WIDTH__ONE_BIT    0
#define HW_SSP_CTRL0__BUS_WIDTH__FOUR_BIT   1
#define HW_SSP_CTRL0__BUS_WIDTH__EIGHT_BIT  2
#define HW_SSP_CTRL0__WAIT_FOR_IRQ  (1 << 21)
#define HW_SSP_CTRL0__WAIT_FOR_CMD  (1 << 20)
#define HW_SSP_CTRL0__LONG_RESP     (1 << 19)
#define HW_SSP_CTRL0__CHECK_RESP    (1 << 18)
#define HW_SSP_CTRL0__GET_RESP      (1 << 17)
#define HW_SSP_CTRL0__ENABLE        (1 << 16)
#define HW_SSP_CTRL0__XFER_COUNT_BM 0xffff


#define HW_SSP_CMD0(ssp)    (*(volatile uint32_t *)(HW_SSP_BASE(ssp) + 0x10))
#ifndef HAVE_STMP3700
#define HW_SSP_CMD0__SLOW_CLKING_EN     (1 << 22)
#define HW_SSP_CMD0__CONT_CLKING_EN     (1 << 21)
#endif
#define HW_SSP_CMD0__APPEND_8CYC        (1 << 20)
#define HW_SSP_CMD0__BLOCK_SIZE_BM      (0xf << 16)
#define HW_SSP_CMD0__BLOCK_SIZE_BP      16
#define HW_SSP_CMD0__BLOCK_COUNT_BM     (0xff << 8)
#define HW_SSP_CMD0__BLOCK_COUNT_BP     8
#define HW_SSP_CMD0__CMD_BM             0xff

#define HW_SSP_CMD1(ssp)    (*(volatile uint32_t *)(HW_SSP_BASE(ssp) + 0x20))

#define HW_SSP_TIMING(ssp)  (*(volatile uint32_t *)(HW_SSP_BASE(ssp) + 0x50))
#define HW_SSP_TIMING__CLOCK_TIMEOUT_BM 0xffff0000
#define HW_SSP_TIMING__CLOCK_TIMEOUT_BP 16
#define HW_SSP_TIMING__CLOCK_DIVIDE_BM  0xff00
#define HW_SSP_TIMING__CLOCK_DIVIDE_BP  8
#define HW_SSP_TIMING__CLOCK_RATE_BM    0xff

#define HW_SSP_CTRL1(ssp)   (*(volatile uint32_t *)(HW_SSP_BASE(ssp) + 0x60))
#define HW_SSP_CTRL1__SDIO_IRQ          (1 << 31)
#define HW_SSP_CTRL1__SDIO_IRQ_EN       (1 << 30)
#define HW_SSP_CTRL1__RESP_ERR_IRQ      (1 << 29)
#define HW_SSP_CTRL1__RESP_ERR_IRQ_EN   (1 << 28)
#define HW_SSP_CTRL1__RESP_TIMEOUT_IRQ  (1 << 27)
#define HW_SSP_CTRL1__RESP_TIMEOUT_IRQ_EN  (1 << 26)
#define HW_SSP_CTRL1__DATA_TIMEOUT_IRQ  (1 << 25)
#define HW_SSP_CTRL1__DATA_TIMEOUT_IRQ_EN  (1 << 24)
#define HW_SSP_CTRL1__DATA_CRC_IRQ      (1 << 23)
#define HW_SSP_CTRL1__DATA_CRC_IRQ_EN   (1 << 22)
#define HW_SSP_CTRL1__FIFO_UNDERRUN_IRQ (1 << 21)
#define HW_SSP_CTRL1__FIFO_UNDERRUN_IRQ_EN (1 << 20)
#define HW_SSP_CTRL1__RECV_TIMEOUT_IRQ  (1 << 17)
#define HW_SSP_CTRL1__RECV_TIMEOUT_IRQ_EN   (1 << 16)
#define HW_SSP_CTRL1__FIFO_OVERRUN_IRQ  (1 << 15)
#define HW_SSP_CTRL1__FIFO_OVERRUN_IRQ_EN   (1 << 14)
#define HW_SSP_CTRL1__DMA_ENABLE        (1 << 13)
#define HW_SSP_CTRL1__SLAVE_OUT_DISABLE (1 << 11)
#define HW_SSP_CTRL1__PHASE             (1 << 10)
#define HW_SSP_CTRL1__POLARITY          (1 << 9)
#define HW_SSP_CTRL1__SLAVE_MODE        (1 << 8)
#define HW_SSP_CTRL1__WORD_LENGTH_BM    (0xf << 4)
#define HW_SSP_CTRL1__WORD_LENGTH_BP    4
#define HW_SSP_CTRL1__WORD_LENGTH__EIGHT_BITS   0x7
#define HW_SSP_CTRL1__SSP_MODE_BM       0xf
#define HW_SSP_CTRL1__SSP_MODE__SD_MMC  0x3
#define HW_SSP_CTRL1__ALL_IRQ           0xaaa28000

#define HW_SSP_DATA(ssp)   (*(volatile uint32_t *)(HW_SSP_BASE(ssp) + 0x70))

#define HW_SSP_SDRESP0(ssp)   (*(volatile uint32_t *)(HW_SSP_BASE(ssp) + 0x80))
#define HW_SSP_SDRESP1(ssp)   (*(volatile uint32_t *)(HW_SSP_BASE(ssp) + 0x90))
#define HW_SSP_SDRESP2(ssp)   (*(volatile uint32_t *)(HW_SSP_BASE(ssp) + 0xA0))
#define HW_SSP_SDRESP3(ssp)   (*(volatile uint32_t *)(HW_SSP_BASE(ssp) + 0xB0))

#define HW_SSP_STATUS(ssp)   (*(volatile uint32_t *)(HW_SSP_BASE(ssp) + 0xC0))
#define HW_SSP_STATUS__BUSY                 (1 << 0)
#define HW_SSP_STATUS__FIFO_EMPTY           (1 << 5)
#define HW_SSP_STATUS__FIFO_FULL            (1 << 8)
#define HW_SSP_STATUS__RECV_TIMEOUT_STAT    (1 << 11)
#define HW_SSP_STATUS__TIMEOUT              (1 << 12)
#define HW_SSP_STATUS__DATA_CRC_ERR         (1 << 13)
#define HW_SSP_STATUS__RESP_TIMEOUT         (1 << 14)
#define HW_SSP_STATUS__RESP_ERR             (1 << 15)
#define HW_SSP_STATUS__RESP_CRC_ERR         (1 << 16)
#define HW_SSP_STATUS__CARD_DETECT          (1 << 28)
#define HW_SSP_STATUS__ALL_ERRORS           0x1f800

#define HW_SSP_DEBUG(ssp)   (*(volatile uint32_t *)(HW_SSP_BASE(ssp) + 0x100))

#define HW_SSP_VERSION(ssp) (*(volatile uint32_t *)(HW_SSP_BASE(ssp) + 0x110))

/**
 *
 * Clock control
 *
 **/
#define __CLK_CLKGATE   (1 << 31)
#define __CLK_BUSY      (1 << 29)

#define HW_CLKCTRL_BASE     0x80040000

#define HW_CLKCTRL_PLLCTRL0 (*(volatile uint32_t *)(HW_CLKCTRL_BASE + 0x0))
#define HW_CLKCTRL_PLLCTRL0__POWER          (1 << 16)
#define HW_CLKCTRL_PLLCTRL0__EN_USB_CLKS    (1 << 18)
#define HW_CLKCTRL_PLLCTRL0__DIV_SEL_BP     20
#define HW_CLKCTRL_PLLCTRL0__DIV_SEL_BM     (3 << 20)

#define HW_CLKCTRL_PLLCTRL1 (*(volatile uint32_t *)(HW_CLKCTRL_BASE + 0x10))

#define HW_CLKCTRL_CPU      (*(volatile uint32_t *)(HW_CLKCTRL_BASE + 0x20))
#define HW_CLKCTRL_CPU__DIV_CPU_BP  0
#define HW_CLKCTRL_CPU__DIV_CPU_BM  0x3f
#define HW_CLKCTRL_CPU__INTERRUPT_WAIT  (1 << 12)
#define HW_CLKCTRL_CPU__DIV_XTAL_BP 16
#define HW_CLKCTRL_CPU__DIV_XTAL_BM (0x3ff << 16)
#define HW_CLKCTRL_CPU__DIV_XTAL_FRAC_EN    (1 << 26)
#define HW_CLKCTRL_CPU__BUSY_REF_CPU    (1 << 28)

#define HW_CLKCTRL_HBUS     (*(volatile uint32_t *)(HW_CLKCTRL_BASE + 0x30))
#define HW_CLKCTRL_HBUS__DIV_BP         0
#define HW_CLKCTRL_HBUS__DIV_BM         0x1f
#define HW_CLKCTRL_HBUS__DIV_FRAC_EN    (1 << 5)
#define HW_CLKCTRL_HBUS__SLOW_DIV_BP    16
#define HW_CLKCTRL_HBUS__SLOW_DIV_BM    (0x7 << 16)
#define HW_CLKCTRL_HBUS__AUTO_SLOW_MODE (1 << 20)

#define HW_CLKCTRL_XBUS     (*(volatile uint32_t *)(HW_CLKCTRL_BASE + 0x40))
#define HW_CLKCTRL_XBUS__DIV_BP     0
#define HW_CLKCTRL_XBUS__DIV_BM     0x3ff
#define HW_CLKCTRL_XBUS__BUSY       (1 << 31)

#define HW_CLKCTRL_XTAL     (*(volatile uint32_t *)(HW_CLKCTRL_BASE + 0x50))
#define HW_CLKCTRL_XTAL__TIMROT_CLK32K_GATE (1 << 26)
#define HW_CLKCTRL_XTAL__DRI_CLK24M_GATE    (1 << 28)
#define HW_CLKCTRL_XTAL__FILT_CLK24M_GATE   (1 << 30)

#define HW_CLKCTRL_PIX      (*(volatile uint32_t *)(HW_CLKCTRL_BASE + 0x60))
#define HW_CLKCTRL_PIX__DIV_BP  0
#define HW_CLKCTRL_PIX__DIV_BM  0xfff

#define HW_CLKCTRL_SSP      (*(volatile uint32_t *)(HW_CLKCTRL_BASE + 0x70))
#define HW_CLKCTRL_SSP__DIV_BP  0
#define HW_CLKCTRL_SSP__DIV_BM  0x1ff

#define HW_CLKCTRL_EMI      (*(volatile uint32_t *)(HW_CLKCTRL_BASE + 0xa0))
#define HW_CLKCTRL_EMI__DIV_EMI_BP  0
#define HW_CLKCTRL_EMI__DIV_EMI_BM  0x3f
#define HW_CLKCTRL_EMI__DIV_XTAL_BP 8
#define HW_CLKCTRL_EMI__DIV_XTAL_BM (0xf << 8)
#define HW_CLKCTRL_EMI__BUSY_REF_EMI    (1 << 28)
#define HW_CLKCTRL_EMI__SYNC_MODE_EN    (1 << 30)
#define HW_CLKCTRL_EMI__CLKGATE     (1 << 31)

#ifdef HAVE_STMP3770
#define HW_CLKCTRL_CLKSEQ   (*(volatile uint32_t *)(HW_CLKCTRL_BASE + 0xe0))
#else
#define HW_CLKCTRL_CLKSEQ   (*(volatile uint32_t *)(HW_CLKCTRL_BASE + 0x110))
#endif
#define HW_CLKCTRL_CLKSEQ__BYPASS_PIX   (1 << 1)
#define HW_CLKCTRL_CLKSEQ__BYPASS_SSP   (1 << 5)
#define HW_CLKCTRL_CLKSEQ__BYPASS_EMI   (1 << 6)
#define HW_CLKCTRL_CLKSEQ__BYPASS_CPU   (1 << 7)

#ifdef HAVE_STMP3770
#define HW_CLKCTRL_FRAC     (*(volatile uint32_t *)(HW_CLKCTRL_BASE + 0xd0))
#else
#define HW_CLKCTRL_FRAC     (*(volatile uint32_t *)(HW_CLKCTRL_BASE + 0xf0))
#endif
#define HW_CLKCTRL_FRAC_CPU (*(volatile uint8_t *)(HW_CLKCTRL_BASE + 0xf0))
#define HW_CLKCTRL_FRAC_EMI (*(volatile uint8_t *)(HW_CLKCTRL_BASE + 0xf1))
#define HW_CLKCTRL_FRAC_PIX (*(volatile uint8_t *)(HW_CLKCTRL_BASE + 0xf2))
#define HW_CLKCTRL_FRAC_IO  (*(volatile uint8_t *)(HW_CLKCTRL_BASE + 0xf3))
#define HW_CLKCTRL_FRAC_XX__XXDIV_BM    0x3f
#define HW_CLKCTRL_FRAC_XX__XX_STABLE   (1 << 6)
#define HW_CLKCTRL_FRAC_XX__CLKGATEXX   (1 << 7)

#define HW_CLKCTRL_RESET    (*(volatile uint32_t *)(HW_CLKCTRL_BASE + 0x120))
#define HW_CLKCTRL_RESET_CHIP   0x2
#define HW_CLKCTRL_RESET_DIG    0x1

/**
 *
 * Pin control
 *
 */

#define HW_PINCTRL_BASE         0x80018000

#define HW_PINCTRL_CTRL         (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0x0))
#define HW_PINCTRL_MUXSEL(i)    (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0x100 + (i) * 0x10))
#define HW_PINCTRL_DRIVE(i)     (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0x200 + (i) * 0x10))
#ifdef HAVE_STMP3700
#define HW_PINCTRL_PULL(i)      (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0x300 + (i) * 0x10))
#define HW_PINCTRL_DOUT(i)      (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0x400 + (i) * 0x10))
#define HW_PINCTRL_DIN(i)       (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0x500 + (i) * 0x10))
#define HW_PINCTRL_DOE(i)       (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0x600 + (i) * 0x10))
#define HW_PINCTRL_PIN2IRQ(i)   (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0x700 + (i) * 0x10))
#define HW_PINCTRL_IRQEN(i)     (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0x800 + (i) * 0x10))
#define HW_PINCTRL_IRQLEVEL(i)  (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0x900 + (i) * 0x10))
#define HW_PINCTRL_IRQPOL(i)    (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0xa00 + (i) * 0x10))
#define HW_PINCTRL_IRQSTAT(i)   (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0xb00 + (i) * 0x10))
#else
#define HW_PINCTRL_PULL(i)      (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0x400 + (i) * 0x10))
#define HW_PINCTRL_DOUT(i)      (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0x500 + (i) * 0x10))
#define HW_PINCTRL_DIN(i)       (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0x600 + (i) * 0x10))
#define HW_PINCTRL_DOE(i)       (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0x700 + (i) * 0x10))
#define HW_PINCTRL_PIN2IRQ(i)   (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0x800 + (i) * 0x10))
#define HW_PINCTRL_IRQEN(i)     (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0x900 + (i) * 0x10))
#define HW_PINCTRL_IRQLEVEL(i)  (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0xa00 + (i) * 0x10))
#define HW_PINCTRL_IRQPOL(i)    (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0xb00 + (i) * 0x10))
#define HW_PINCTRL_IRQSTAT(i)   (*(volatile uint32_t *)(HW_PINCTRL_BASE + 0xc00 + (i) * 0x10))
#endif

#define PINCTRL_FUNCTION_MAIN   0
#define PINCTRL_FUNCTION_ALT1   1
#define PINCTRL_FUNCTION_ALT2   2
#define PINCTRL_FUNCTION_GPIO   3

#define PINCTRL_DRIVE_4mA       0
#define PINCTRL_DRIVE_8mA       1
#define PINCTRL_DRIVE_12mA      2
#define PINCTRL_DRIVE_16mA      3 /* not available on all pins */

typedef void (*pin_irq_cb_t)(int bank, int pin);

static inline void imx233_pinctrl_init(void)
{
    __REG_CLR(HW_PINCTRL_CTRL) = __BLOCK_CLKGATE | __BLOCK_SFTRST;
}

static inline void imx233_set_pin_drive_strength(unsigned bank, unsigned pin, unsigned strength)
{
    __REG_CLR(HW_PINCTRL_DRIVE(4 * bank + pin / 8)) = 3 << (4 * (pin % 8));
    __REG_SET(HW_PINCTRL_DRIVE(4 * bank + pin / 8)) = strength << (4 * (pin % 8));
}

static inline void imx233_enable_gpio_output(unsigned bank, unsigned pin, bool enable)
{
    if(enable)
        __REG_SET(HW_PINCTRL_DOE(bank)) = 1 << pin;
    else
        __REG_CLR(HW_PINCTRL_DOE(bank)) = 1 << pin;
}

static inline void imx233_enable_gpio_output_mask(unsigned bank, uint32_t pin_mask, bool enable)
{
    if(enable)
        __REG_SET(HW_PINCTRL_DOE(bank)) = pin_mask;
    else
        __REG_CLR(HW_PINCTRL_DOE(bank)) = pin_mask;
}

static inline void imx233_set_gpio_output(unsigned bank, unsigned pin, bool value)
{
    if(value)
        __REG_SET(HW_PINCTRL_DOUT(bank)) = 1 << pin;
    else
        __REG_CLR(HW_PINCTRL_DOUT(bank)) = 1 << pin;
}

static inline void imx233_set_gpio_output_mask(unsigned bank, uint32_t pin_mask, bool value)
{
    if(value)
        __REG_SET(HW_PINCTRL_DOUT(bank)) = pin_mask;
    else
        __REG_CLR(HW_PINCTRL_DOUT(bank)) = pin_mask;
}

static inline uint32_t imx233_get_gpio_input_mask(unsigned bank, uint32_t pin_mask)
{
    return HW_PINCTRL_DIN(bank) & pin_mask;
}

static inline void imx233_set_pin_function(unsigned bank, unsigned pin, unsigned function)
{
    __REG_CLR(HW_PINCTRL_MUXSEL(2 * bank + pin / 16)) = 3 << (2 * (pin % 16));
    __REG_SET(HW_PINCTRL_MUXSEL(2 * bank + pin / 16)) = function << (2 * (pin % 16));
}

static inline void imx233_enable_pin_pullup(unsigned bank, unsigned pin, bool enable)
{
    if(enable)
        __REG_SET(HW_PINCTRL_PULL(bank)) = 1 << pin;
    else
        __REG_CLR(HW_PINCTRL_PULL(bank)) = 1 << pin;
}

static inline void imx233_enable_pin_pullup_mask(unsigned bank, uint32_t pin_msk, bool enable)
{
    if(enable)
        __REG_SET(HW_PINCTRL_PULL(bank)) = pin_msk;
    else
        __REG_CLR(HW_PINCTRL_PULL(bank)) = pin_msk;
}

void imx233_ssp_setup_ssp1_sd_mmc_pins(bool enable_pullups, unsigned bus_width,
                                       unsigned drive_strength, bool use_alt)
{
    /* SSP_{CMD,SCK} */
    imx233_set_pin_drive_strength(2, 0, drive_strength);
    imx233_set_pin_drive_strength(2, 6, drive_strength);
    imx233_set_pin_function(2, 0, PINCTRL_FUNCTION_MAIN);
    imx233_set_pin_function(2, 6, PINCTRL_FUNCTION_MAIN);
    imx233_enable_pin_pullup(2, 0, enable_pullups);
    /* SSP_DATA{0-3} */
    for(unsigned i = 0; i < MIN(bus_width, 4); i++)
    {
        imx233_set_pin_drive_strength(2, 2 + i, drive_strength);
        imx233_set_pin_function(2, 2 + i, PINCTRL_FUNCTION_MAIN);
        imx233_enable_pin_pullup(2, 2 + i, enable_pullups);
    }
    
    /* SSP_DATA{4-7} */
    for(unsigned i = 4; i < bus_width; i++)
    {
        if(use_alt)
        {
            imx233_set_pin_drive_strength(0, 22 + i, drive_strength);
            imx233_set_pin_function(0, 22 + i, PINCTRL_FUNCTION_ALT2);
            imx233_enable_pin_pullup(0, 22 + i, enable_pullups);
        }
        else
        {
            imx233_set_pin_drive_strength(0, 4 + i, drive_strength);
            imx233_set_pin_function(0, 4 + i, PINCTRL_FUNCTION_ALT2);
            imx233_enable_pin_pullup(0, 4 + i, enable_pullups);
        }
    }
}

void imx233_ssp_setup_ssp2_sd_mmc_pins(bool enable_pullups, unsigned bus_width,
                                       unsigned drive_strength)
{
    /* SSP_{CMD,SCK} */
    imx233_set_pin_drive_strength(0, 20, drive_strength);
    imx233_set_pin_drive_strength(0, 24, drive_strength);
    imx233_set_pin_function(0, 20, PINCTRL_FUNCTION_ALT2);
    imx233_set_pin_function(0, 24, PINCTRL_FUNCTION_ALT2);
    imx233_enable_pin_pullup(0, 20, enable_pullups);
    /* SSP_DATA{0-7}*/
    for(unsigned i = 0; i < bus_width; i++)
    {
        imx233_set_pin_drive_strength(0, i, drive_strength);
        imx233_set_pin_function(0, i, PINCTRL_FUNCTION_ALT2);
        imx233_enable_pin_pullup(0, i, enable_pullups);
    }
    
    imx233_enable_gpio_output_mask(0, 0x11000ff, false);
    imx233_set_gpio_output_mask(0, 0x11000ff, false);
}

/**
 * LRADC
 */
#define HW_LRADC_BASE       0x80050000

#define HW_LRADC_CTRL0      (*(volatile uint32_t *)(HW_LRADC_BASE + 0x0))
#define HW_LRADC_CTRL0__ONCHIP_GROUNDREF    (1 << 21)
#define HW_LRADC_CTRL0__SCHEDULE(x)         (1 << (x))

#define HW_LRADC_CTRL1      (*(volatile uint32_t *)(HW_LRADC_BASE + 0x10))
#define HW_LRADC_CTRL1__LRADCx_IRQ(x)   (1 << (x))
#define HW_LRADC_CTRL1__LRADCx_IRQ_EN(x)   (1 << ((x) + 16))

#define HW_LRADC_CTRL2      (*(volatile uint32_t *)(HW_LRADC_BASE + 0x20))
#define HW_LRADC_CTRL2__TEMP_ISRC1_BP           4
#define HW_LRADC_CTRL2__TEMP_ISRC1_BM           0xf0
#define HW_LRADC_CTRL2__TEMP_ISRC0_BP           0
#define HW_LRADC_CTRL2__TEMP_ISRC0_BM           0xf
#define HW_LRADC_CTRL2__TEMP_SENSOR_IENABLE0    (1 << 8)
#define HW_LRADC_CTRL2__TEMP_SENSOR_IENABLE1    (1 << 9)
#define HW_LRADC_CTRL2__TEMPSENSE_PWD           (1 << 15)
#define HW_LRADC_CTRL2__DIVIDE_BY_TWO(x)        (1 << ((x) + 24))

#define HW_LRADC_CTRL3      (*(volatile uint32_t *)(HW_LRADC_BASE + 0x30))
#define HW_LRADC_CTRL3__CYCLE_TIME_BM       0x300
#define HW_LRADC_CTRL3__CYCLE_TIME_BP       8
#define HW_LRADC_CTRL3__CYCLE_TIME__6MHz    (0 << 8)
#define HW_LRADC_CTRL3__CYCLE_TIME__4MHz    (1 << 8)
#define HW_LRADC_CTRL3__CYCLE_TIME__3MHz    (2 << 8)
#define HW_LRADC_CTRL3__CYCLE_TIME__2MHz    (3 << 8)

#define HW_LRADC_STATUS     (*(volatile uint32_t *)(HW_LRADC_BASE + 0x40))

#define HW_LRADC_CHx(x)     (*(volatile uint32_t *)(HW_LRADC_BASE + 0x50 + (x) * 0x10))
#define HW_LRADC_CHx__NUM_SAMPLES_BM    (0xf << 24)
#define HW_LRADC_CHx__NUM_SAMPLES_BP    24
#define HW_LRADC_CHx__ACCUMULATE        29
#define HW_LRADC_CHx__VALUE_BM          0x3ffff
#define HW_LRADC_CHx__VALUE_BP          0

#define HW_LRADC_DELAYx(x)  (*(volatile uint32_t *)(HW_LRADC_BASE + 0xD0 + (x) * 0x10))
#define HW_LRADC_DELAYx__DELAY_BP           0
#define HW_LRADC_DELAYx__DELAY_BM           0x7ff
#define HW_LRADC_DELAYx__LOOP_COUNT_BP      11
#define HW_LRADC_DELAYx__LOOP_COUNT_BM      (0x1f << 11)
#define HW_LRADC_DELAYx__TRIGGER_DELAYS_BP  16
#define HW_LRADC_DELAYx__TRIGGER_DELAYS_BM  (0xf << 16)
#define HW_LRADC_DELAYx__KICK               (1 << 20)
#define HW_LRADC_DELAYx__TRIGGER_LRADCS_BP  24
#define HW_LRADC_DELAYx__TRIGGER_LRADCS_BM  (0xff << 24)

#define HW_LRADC_CONVERSION (*(volatile uint32_t *)(HW_LRADC_BASE + 0x130))
#define HW_LRADC_CONVERSION__SCALED_BATT_VOLTAGE_BP 0
#define HW_LRADC_CONVERSION__SCALED_BATT_VOLTAGE_BM 0x3ff
#define HW_LRADC_CONVERSION__SCALE_FACTOR_BM        (3 << 16)
#define HW_LRADC_CONVERSION__SCALE_FACTOR_BP        16
#define HW_LRADC_CONVERSION__SCALE_FACTOR__LI_ION   (2 << 16)
#define HW_LRADC_CONVERSION__AUTOMATIC              (1 << 20)

#define HW_LRADC_CTRL4      (*(volatile uint32_t *)(HW_LRADC_BASE + 0x140))
#define HW_LRADC_CTRL4__LRADCxSELECT_BM(x)  (0xf << ((x) * 4))
#define HW_LRADC_CTRL4__LRADCxSELECT_BP(x)  ((x) * 4)

#define HW_LRADC_VERSION    (*(volatile uint32_t *)(HW_LRADC_BASE + 0x150))

#define HW_LRADC_NUM_CHANNELS   8
#define HW_LRADC_NUM_DELAYS     4

/**
 *
 * Log
 *
 */


/**
 *
 * Main
 *
 */

extern uint32_t call_lr;

void memcpy(uint8_t *dst, const uint8_t *src, uint32_t length)
{
    for(uint32_t i = 0; i < length; i++)
        dst[i] = src[i];
}

void memset(uint8_t *dst, uint8_t fill, uint32_t length)
{
    for(uint32_t i = 0; i < length; i++)
        dst[i] = fill;
}

void main(uint32_t arg)
{
    logf("recovery_util\n");
    logf("protocol version %d\n", PROTOCOL_VERSION);
    logf("protocol magic: %s\n", PROTOCOL_MAGIC);
    logf("argument: 0x%08x\n", arg);
    /** Sansa Fuze+ has an internal eMMC 8-bit wide flash, power gate is pin PWM3
     * and power up time is 20ms */
    imx233_set_pin_function(1, 29, PINCTRL_FUNCTION_GPIO);
    imx233_enable_gpio_output(1, 29, true);
    imx233_set_gpio_output(1, 29, false);
    imx233_ssp_setup_ssp2_sd_mmc_pins(true, 8, PINCTRL_DRIVE_8mA);
    
    qh_array[0].max_pkt_length = 1 << 29 | MAX_PKT_SIZE << 16;
    qh_array[1].max_pkt_length = 1 << 29 | MAX_PKT_SIZE << 16;
    qh_array[3].max_pkt_length = 1 << 29 | MAX_PKT_SIZE << 16;
    /* setup qh */
    REG_ENDPOINTLISTADDR = (unsigned int)qh_array;
    /* clear setup status */
    REG_ENDPTSETUPSTAT = EPSETUP_STATUS_EP0;
    /* infinite loop */
    while(1)
    {
        uint32_t addr;
        /* wait for setup */
        while(!(REG_ENDPTSETUPSTAT & EPSETUP_STATUS_EP0))
            ;
        /* clear setup status */
        REG_ENDPTSETUPSTAT = EPSETUP_STATUS_EP0;
        /* check request */
        asm volatile("":::"memory");
        struct usb_ctrlrequest *req = (void *)&qh_array[0].setup_buffer[0];
        struct usb_cmd_hdr_t *hdr = (struct usb_cmd_hdr_t *)buffer;

        if(req->bRequest == USB_CMD_INFO)
        {
            struct usb_cmd_info_t *info = (struct usb_cmd_info_t *)buffer;
            info->prot_ver = PROTOCOL_VERSION;
            memcpy(info->magic, PROTOCOL_MAGIC, PROTOCOL_MAGIC_SIZE);
            prime_transfer(0, buffer, MIN(sizeof(struct usb_cmd_info_t), req->wLength), true, true);
            prime_transfer(0, NULL, 0, false, true);
            continue;
        }
        else if(req->bRequest == USB_CMD_READLOG)
        {
            size_t sz = logf_readback(buffer, MAX_PKT_SIZE);
            prime_transfer(0, buffer, MIN(sz, req->wLength), true, true);
            prime_transfer(0, NULL, 0, false, true);
            continue;
        }
        else if(req->bRequest != USB_CMD_WRAPPED)
            goto Lstall;
        /* receive more data */
        prime_transfer(0, buffer, req->wLength, false, true);
        /* send ack */
        prime_transfer(0, 0, 0, true, true);

        logf("wrapped command: cmd=0x%x, flags=0x%x\n", hdr->cmd, hdr->flags);
        
        if(hdr->cmd == CMD_MEMORY)
        {
            struct usb_cmd_mem_t mem = *(struct usb_cmd_mem_t *)buffer;
            logf("  memory command: addr=0x%x, len=0x%x\n", mem.addr, mem.length);
            if(mem.hdr.flags & FLAGS_READ)
            {
                for(uint32_t i = 0; i < mem.length; i++)
                    buffer[i] = *(volatile uint8_t *)(mem.addr + i);
                /* send data back */
                prime_transfer(1, buffer, mem.length, true, true);
            }
            else if(mem.hdr.flags & FLAGS_WRITE)
            {
                uint8_t *p = buffer + sizeof(struct usb_cmd_mem_t);
                for(uint32_t i = 0; i < mem.length;)
                {
                    if((i + 4) <= mem.length)
                    {
                        *(volatile uint32_t *)(mem.addr + i) = *(uint32_t *)&p[i];
                        i += 4;
                    }
                    else if((i + 2) <= mem.length)
                    {
                        *(volatile uint16_t *)(mem.addr + i) = *(uint16_t *)&p[i];
                        i += 2;
                    }
                    else
                    {
                        *(volatile uint8_t *)(mem.addr + i) = *(uint8_t *)&p[i];
                        i += 1;
                    }
                }
            }
            else
                goto Lstall;
        }
        else if(hdr->cmd == CMD_SSP)
        {
            struct usb_cmd_ssp_t ssp = *(struct usb_cmd_ssp_t *)buffer;
            logf("  ssp command: ssp=%d, cmd=0x%x, arg=0x%x, len=0x%x\n",
                ssp.ssp, ssp.cmd, ssp.arg, ssp.length);
            /* Clkgate */
            __REG_SET(HW_SSP_CTRL0(ssp.ssp)) = __BLOCK_SFTRST;
            __REG_CLR(HW_SSP_CTRL0(ssp.ssp)) = __BLOCK_CLKGATE | __BLOCK_SFTRST;
            /** 2.3.1: the clk_ssp maximum frequency is 102.858 MHz */
            /* ref_xtal = 24MHz
             * intdiv = 1 => clk_ssp = ref_xtal / 1 = 24Mhz */
            HW_CLKCTRL_SSP = 1;
            while(HW_CLKCTRL_SSP & __CLK_BUSY);
            __REG_SET(HW_CLKCTRL_CLKSEQ) = HW_CLKCTRL_CLKSEQ__BYPASS_SSP;
            /* SSPCLK @ 24MHz
             * gives bitrate of 24000 / 60 / 1 = 400kHz */
            HW_SSP_TIMING(ssp.ssp) = 60 << HW_SSP_TIMING__CLOCK_DIVIDE_BP |
                0xf << HW_SSP_TIMING__CLOCK_TIMEOUT_BP;
            /* ssp setup */
            __REG_SET(HW_SSP_CTRL0(ssp.ssp)) = HW_SSP_CTRL0__ENABLE | HW_SSP_CTRL0__IGNORE_CRC;
            __REG_CLR(HW_SSP_CTRL0(ssp.ssp)) = HW_SSP_CTRL0__XFER_COUNT_BM | HW_SSP_CTRL0__DATA_XFER |
                HW_SSP_CTRL0__GET_RESP | HW_SSP_CTRL0__LONG_RESP;
            if(ssp.hdr.flags & (FLAGS_READ | FLAGS_WRITE))
            {
                __REG_CLR(HW_SSP_CTRL0(ssp.ssp)) = HW_SSP_CTRL0__IGNORE_CRC;
                __REG_SET(HW_SSP_CTRL0(ssp.ssp)) = ssp.length | HW_SSP_CTRL0__DATA_XFER;
                if(ssp.hdr.flags & FLAGS_READ)
                    __REG_SET(HW_SSP_CTRL0(ssp.ssp)) = HW_SSP_CTRL0__READ;
            }
            HW_SSP_CTRL1(ssp.ssp) = HW_SSP_CTRL1__SSP_MODE__SD_MMC |
                HW_SSP_CTRL1__WORD_LENGTH__EIGHT_BITS << HW_SSP_CTRL1__WORD_LENGTH_BP |
                HW_SSP_CTRL1__POLARITY;
            if(!(ssp.hdr.flags & FLAGS_SSP_NO_RESP))
                __REG_SET(HW_SSP_CTRL0(ssp.ssp)) = HW_SSP_CTRL0__GET_RESP;
            if(ssp.hdr.flags & FLAGS_SSP_LONG_RESP)
                __REG_SET(HW_SSP_CTRL0(ssp.ssp)) = HW_SSP_CTRL0__LONG_RESP;
            unsigned block_cnt = ssp.length / BLOCK_SIZE;
            if(block_cnt > 0)
                block_cnt--;
            HW_SSP_CMD0(ssp.ssp) = ssp.cmd | HW_SSP_CMD0__APPEND_8CYC |
                block_cnt << HW_SSP_CMD0__BLOCK_COUNT_BP |
                BLOCK_SIZE_LOG << HW_SSP_CMD0__BLOCK_SIZE_BP;
            HW_SSP_CMD1(ssp.ssp) = ssp.arg;
            __REG_CLR(HW_SSP_CTRL1(ssp.ssp)) = HW_SSP_CTRL1__ALL_IRQ;
            __REG_SET(HW_SSP_CTRL0(ssp.ssp)) = HW_SSP_CTRL0__RUN;

            logf("  timing=0x%x\n", HW_SSP_TIMING(ssp.ssp));
            logf("  ctrl0=0x%x\n  cmd0=0x%x\n  cmd1=0x%x\n  ctrl1=0x%x\n  status=0x%x\n",
                 HW_SSP_CTRL0(ssp.ssp), HW_SSP_CMD0(ssp.ssp), HW_SSP_CMD1(ssp.ssp),
                 HW_SSP_CTRL1(ssp.ssp), HW_SSP_STATUS(ssp.ssp));

            uint32_t xfered = 0;
            struct usb_resp_ssp_t *sd_resp = (struct usb_resp_ssp_t *)buffer;
            uint32_t *data_buf = (uint32_t *)(sd_resp + 1);
            while(HW_SSP_STATUS(ssp.ssp) & HW_SSP_STATUS__BUSY)
            {
                if(ssp.hdr.flags & FLAGS_READ && !(HW_SSP_STATUS(ssp.ssp) & HW_SSP_STATUS__FIFO_EMPTY))
                {
                    if(xfered < ssp.length)
                    {
                        *data_buf++ = HW_SSP_DATA(ssp.ssp);
                        xfered += 4;
                    }
                }
            }
            logf("  END\n");
            logf("  ctrl0=0x%x\n  cmd0=0x%x\n  cmd1=0x%x\n  ctrl1=0x%x\n  status=0x%x\n",
                 HW_SSP_CTRL0(ssp.ssp), HW_SSP_CMD0(ssp.ssp), HW_SSP_CMD1(ssp.ssp),
                 HW_SSP_CTRL1(ssp.ssp), HW_SSP_STATUS(ssp.ssp));
            sd_resp->status = HW_SSP_STATUS(ssp.ssp);
            sd_resp->ctrl1 = HW_SSP_CTRL1(ssp.ssp);
            sd_resp->resp[0] = HW_SSP_SDRESP0(ssp.ssp);
            sd_resp->resp[1] = HW_SSP_SDRESP1(ssp.ssp);
            sd_resp->resp[2] = HW_SSP_SDRESP2(ssp.ssp);
            sd_resp->resp[3] = HW_SSP_SDRESP3(ssp.ssp);
            sd_resp->length = xfered;
            if(!(ssp.hdr.flags & FLAGS_SSP_NO_RESP))
                logf("  resp0=0x%x\n", HW_SSP_SDRESP0(ssp.ssp));
            if(ssp.hdr.flags & FLAGS_SSP_LONG_RESP)
            {
                logf("  resp1=0x%x\n", HW_SSP_SDRESP1(ssp.ssp));
                logf("  resp2=0x%x\n", HW_SSP_SDRESP2(ssp.ssp));
                logf("  resp3=0x%x\n", HW_SSP_SDRESP3(ssp.ssp));
            }
            __REG_SET(HW_SSP_CTRL0(ssp.ssp)) = __BLOCK_CLKGATE;
            /* send data back */
            prime_transfer(1, sd_resp, sizeof(struct usb_resp_ssp_t), true, true);
            uint8_t *ptr = (uint8_t *)(sd_resp + 1);
            while(xfered > 0)
            {
                unsigned send = MIN(xfered, MAX_PKT_SIZE);
                prime_transfer(1, ptr, send, true, true);
                xfered -= send;
                ptr += send;
            }
        }
        else if(hdr->cmd == CMD_LRADC)
        {
            struct usb_cmd_lradc_t lradc = *(struct usb_cmd_lradc_t *)buffer;
            logf("  lradc command: hw_chan=%d, div2=%d, acc=%d, samples=0x%x\n",
                lradc.hw_chan, !!(hdr->flags & FLAGS_LRADC_DIVIDE_BY_2),
                 !!(hdr->flags & FLAGS_LRADC_ACCUMULATE), lradc.num_samples);
            /* clkgate */
            __REG_SET(HW_LRADC_CTRL0) = __BLOCK_SFTRST;
            __REG_CLR(HW_LRADC_CTRL0) = __BLOCK_CLKGATE | __BLOCK_SFTRST;
            /* divide by 2 */
            if(hdr->flags & FLAGS_LRADC_DIVIDE_BY_2)
                __REG_SET(HW_LRADC_CTRL2) = HW_LRADC_CTRL2__DIVIDE_BY_TWO(0);
            else
                __REG_CLR(HW_LRADC_CTRL2) = HW_LRADC_CTRL2__DIVIDE_BY_TWO(1);
            /* channel */
            __REG_CLR(HW_LRADC_CTRL4) = HW_LRADC_CTRL4__LRADCxSELECT_BM(0);
            __REG_SET(HW_LRADC_CTRL4) = lradc.hw_chan << HW_LRADC_CTRL4__LRADCxSELECT_BP(0);
            /* accumulate & samples */
            HW_LRADC_CHx(0) = (!!(hdr->flags & FLAGS_LRADC_ACCUMULATE)) << HW_LRADC_CHx__ACCUMULATE |
                lradc.num_samples << HW_LRADC_CHx__NUM_SAMPLES_BP;
            /* schedule */
            __REG_CLR(HW_LRADC_CTRL1) = HW_LRADC_CTRL1__LRADCx_IRQ(0);
            __REG_SET(HW_LRADC_CTRL0) = HW_LRADC_CTRL0__SCHEDULE(0);
            /* wait */
            while(!(HW_LRADC_CTRL1 & HW_LRADC_CTRL1__LRADCx_IRQ(0)));
            /* build response */
            struct usb_resp_lradc_t *lradc_resp = (struct usb_resp_lradc_t *)buffer;
            lradc_resp->value = (HW_LRADC_CHx(0) & HW_LRADC_CHx__VALUE_BM) >> HW_LRADC_CHx__VALUE_BP;
            /* send back */
            prime_transfer(1, lradc_resp, sizeof(struct usb_resp_lradc_t), true, true);
        }
        else
            goto Lstall;
        continue;

        Lstall:
        /* stall and start over again */
        REG_ENDPTCTRL0 |= EPCTRL_TX_EP_STALL;
        continue;
    }
}
