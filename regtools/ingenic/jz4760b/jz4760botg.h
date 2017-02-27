/*
 * linux/include/asm-mips/mach-jz4760b/jz4760botg.h
 *
 * JZ4760B OTG register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

#ifndef __JZ4760BOTG_H__
#define __JZ4760BOTG_H__

/*************************************************************************
 * USB Device
 *************************************************************************/
#define USB_BASE  0xB3440000

#define USB_FADDR		(USB_BASE + 0x00) /* Function Address 8-bit */
#define USB_POWER		(USB_BASE + 0x01) /* Power Managemetn 8-bit */
#define USB_INTRIN		(USB_BASE + 0x02) /* Interrupt IN 16-bit */
#define USB_INTROUT		(USB_BASE + 0x04) /* Interrupt OUT 16-bit */
#define USB_INTRINE		(USB_BASE + 0x06) /* Intr IN enable 16-bit */
#define USB_INTROUTE	(USB_BASE + 0x08) /* Intr OUT enable 16-bit */
#define USB_INTRUSB		(USB_BASE + 0x0a) /* Interrupt USB 8-bit */
#define USB_INTRUSBE	(USB_BASE + 0x0b) /* Interrupt USB Enable 8-bit */
#define USB_FRAME		(USB_BASE + 0x0c) /* Frame number 16-bit */
#define USB_INDEX		(USB_BASE + 0x0e) /* Index register 8-bit */
#define USB_TESTMODE	(USB_BASE + 0x0f) /* USB test mode 8-bit */

#define USB_CSR0		(USB_BASE + 0x12) /* EP0 CSR 8-bit */
#define USB_INMAXP		(USB_BASE + 0x10) /* EP1-2 IN Max Pkt Size 16-bit */
#define USB_INCSR		(USB_BASE + 0x12) /* EP1-2 IN CSR LSB 8/16bit */
#define USB_INCSRH		(USB_BASE + 0x13) /* EP1-2 IN CSR MSB 8-bit */
#define USB_OUTMAXP		(USB_BASE + 0x14) /* EP1 OUT Max Pkt Size 16-bit */
#define USB_OUTCSR		(USB_BASE + 0x16) /* EP1 OUT CSR LSB 8/16bit */
#define USB_OUTCSRH		(USB_BASE + 0x17) /* EP1 OUT CSR MSB 8-bit */
#define USB_OUTCOUNT	(USB_BASE + 0x18) /* bytes in EP0/1 OUT FIFO 16-bit */

#define USB_FIFO_EP0		(USB_BASE + 0x20)
#define USB_FIFO_EP1		(USB_BASE + 0x24)
#define USB_FIFO_EP2		(USB_BASE + 0x28)

#define USB_EPINFO		(USB_BASE + 0x78) /* Endpoint information */
#define USB_RAMINFO		(USB_BASE + 0x79) /* RAM information */

#define USB_INTR		(USB_BASE + 0x200) /* DMA pending interrupts */
#define USB_CNTL(1)		(USB_BASE + 0x204) /* DMA channel 1 control */
#define USB_ADDR(1)		(USB_BASE + 0x208) /* DMA channel 1 AHB memory addr */
#define USB_COUNT(1)		(USB_BASE + 0x20c) /* DMA channel 1 byte count */
#define USB_CNTL(2)		(USB_BASE + 0x214) /* DMA channel 2 control */
#define USB_ADDR(2)		(USB_BASE + 0x218) /* DMA channel 2 AHB memory addr */
#define USB_COUNT(2)		(USB_BASE + 0x21c) /* DMA channel 2 byte count */


/* Power register bit masks (POWER) */
#define USB_POWER_SUSPENDM	(1 << 0)
#define USB_POWER_RESUME	(1 << 2)
#define USB_POWER_HSMODE	(1 << 4)
#define USB_POWER_HSENAB	(1 << 5)
#define USB_POWER_SOFTCONN	(1 << 6)

/* Interrupt register bit masks (INTRUSB) */
#define USB_INTRUSB_SUSPEND	(1 << 0)
#define USB_INTRUSB_RESUME		(1 << 1)
#define USB_INTRUSB_RESET		(1 << 2)

// #define USB_INTR_EP0		(1 << 0)
// #define USB_INTR_INEP1		(1 << 1)
// #define USB_INTR_INEP2		(1 << 2)
// #define USB_INTR_OUTEP1		(1 << 1)

/* CSR0 bit masks (CSR0) */
#define USB_CSR0_OUTPKTRDY	(1 << 0)
#define USB_CSR0_INPKTRDY	(1 << 1)
#define USB_CSR0_SENTSTALL	(1 << 2)
#define USB_CSR0_DATAEND	(1 << 3)
#define USB_CSR0_SETUPEND	(1 << 4)
#define USB_CSR0_SENDSTALL	(1 << 5)
#define USB_CSR0_SVDOUTPKTRDY	(1 << 6)
#define USB_CSR0_SVDSETUPEND	(1 << 7)

/* Endpoint CSR register bits (INCSRH) */
#define USB_INCSRH_AUTOSET	(1 << 7)
#define USB_INCSRH_ISO		(1 << 6)
#define USB_INCSRH_MODE		(1 << 5)
#define USB_INCSRH_DMAREQENAB	(1 << 4)
#define USB_INCSRH_DMAREQMODE	(1 << 2)
#define USB_INCSR_CDT		(1 << 6)
#define USB_INCSR_SENTSTALL	(1 << 5)
#define USB_INCSR_SENDSTALL	(1 << 4)
#define USB_INCSR_FF		(1 << 3)
#define USB_INCSR_UNDERRUN	(1 << 2)
#define USB_INCSR_FFNOTEMPT	(1 << 1)
#define USB_INCSR_INPKTRDY	(1 << 0)
#define USB_OUTCSRH_AUTOCLR	(1 << 7)
#define USB_OUTCSRH_ISO		(1 << 6)
#define USB_OUTCSRH_DMAREQENAB	(1 << 5)
#define USB_OUTCSRH_DNYT	(1 << 4)
#define USB_OUTCSRH_DMAREQMODE	(1 << 3)
#define USB_OUTCSR_CDT		(1 << 7)
#define USB_OUTCSR_SENTSTALL	(1 << 6)
#define USB_OUTCSR_SENDSTALL	(1 << 5)
#define USB_OUTCSR_FF		(1 << 4)
#define USB_OUTCSR_DATAERR	(1 << 3)
#define USB_OUTCSR_OVERRUN	(1 << 2)
#define USB_OUTCSR_FFFULL	(1 << 1)
#define USB_OUTCSR_OUTPKTRDY	(1 << 0)

/* Testmode register bits (TESTMODE) */
#define USB_TESTMODE_SE0NAK		(1 << 0)
#define USB_TESTMODE_J		(1 << 1)
#define USB_TESTMODE_K		(1 << 2)
#define USB_TESTMODE_PACKET		(1 << 3)

/* DMA control bits (CNTL) */
#define USB_CNTL_ENA		(1 << 0)
#define USB_CNTL_DIR_IN		(1 << 1)
#define USB_CNTL_MODE_1		(1 << 2)
#define USB_CNTL_INTR_EN	(1 << 3)
#define USB_CNTL_EP(n)		((n) << 4)
#define USB_CNTL_BURST_BIT	9
#define USB_CNTL_BURST_MASK	(3 << USB_CNTL_BURST_BIT)
#define USB_CNTL_BURST_0	(0 << USB_CNTL_BURST_BIT)
#define USB_CNTL_BURST_4	(1 << USB_CNTL_BURST_BIT)
#define USB_CNTL_BURST_8	(2 << USB_CNTL_BURST_BIT)
#define USB_CNTL_BURST_16	(3 << USB_CNTL_BURST_BIT)



#ifndef __MIPS_ASSEMBLER

#endif /* __MIPS_ASSEMBLER */

#endif /* __JZ4760BOTG_H__ */

