/*
 * linux/include/asm-mips/mach-jz4760b/jz4760botg.h
 *
 * JZ4760B OTG register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

// 
// #ifndef __JZ4760BOTG_H__
// #define __JZ4760BOTG_H__

// 
/*************************************************************************
 * USB Device
 *************************************************************************/
this class USB goto 0xB3440000

// 
register FADDR goto 0x00 export "Function Address 8-bit"
register POWER goto 0x01 export "Power Managemetn 8-bit"
register INTRIN goto 0x02 export "Interrupt IN 16-bit"
register INTROUT goto 0x04 export "Interrupt OUT 16-bit"
register INTRINE goto 0x06 export "Intr IN enable 16-bit"
register INTROUTE goto 0x08 export "Intr OUT enable 16-bit"
register INTRUSB goto 0x0a export "Interrupt USB 8-bit"
register INTRUSBE goto 0x0b export "Interrupt USB Enable 8-bit"
register FRAME goto 0x0c export "Frame number 16-bit"
register INDEX goto 0x0e export "Index register 8-bit"
register TESTMODE goto 0x0f export "USB test mode 8-bit"

// 
register CSR0 goto 0x12 export "EP0 CSR 8-bit"
register INMAXP goto (1 << 4) export "EP1-2 IN Max Pkt Size 16-bit"
register INCSR goto 0x12 export "EP1-2 IN CSR LSB 8/16bit"
register INCSRH goto 0x13 export "EP1-2 IN CSR MSB 8-bit"
register OUTMAXP goto 0x14 export "EP1 OUT Max Pkt Size 16-bit"
register OUTCSR goto 0x16 export "EP1 OUT CSR LSB 8/16bit"
register OUTCSRH goto 0x17 export "EP1 OUT CSR MSB 8-bit"
register OUTCOUNT goto 0x18 export "bytes in EP0/1 OUT FIFO 16-bit"

// 
register FIFO_EP0 goto 0x20 export ""
register FIFO_EP1 goto 0x24 export ""
register FIFO_EP2 goto 0x28 export ""

// 
register EPINFO goto 0x78 export "Endpoint information"
register RAMINFO goto 0x79 export "RAM information"

// 
register INTR goto 0x200 export "DMA pending interrupts"
register CNTL goto (1,0x204) export "DMA channel 1 control"
register ADDR goto (1,0x208) export "DMA channel 1 AHB memory addr"
register COUNT goto (1,0x20c) export "DMA channel 1 byte count"
register CNTL goto (2,0x214) export "DMA channel 2 control"
register ADDR goto (2,0x218) export "DMA channel 2 AHB memory addr"
register COUNT goto (2,0x21c) export "DMA channel 2 byte count"

// 

// 
register POWER export "Power register bit masks"
register POWER int SUSPENDM goto 0
register POWER int RESUME goto 2
register POWER int HSMODE goto 4
register POWER int HSENAB goto 5
register POWER int SOFTCONN goto 6

// 
register INTRUSB export "Interrupt register bit masks"
register INTRUSB int SUSPEND goto 0
register INTRUSB int RESUME goto 1
register INTRUSB int RESET goto 2

// 
// #define USB_INTR_EP0		(1 << 0)
// #define USB_INTR_INEP1		(1 << 1)
// #define USB_INTR_INEP2		(1 << 2)
// #define USB_INTR_OUTEP1		(1 << 1)

// 
register CSR0 export "CSR0 bit masks"
register CSR0 int OUTPKTRDY goto 0
register CSR0 int INPKTRDY goto 1
register CSR0 int SENTSTALL goto 2
register CSR0 int DATAEND goto 3
register CSR0 int SETUPEND goto 4
register CSR0 int SENDSTALL goto 5
register CSR0 int SVDOUTPKTRDY goto 6
register CSR0 int SVDSETUPEND goto 7

// 
register INCSRH export "Endpoint CSR register bits"
register INCSRH int AUTOSET goto 7
register INCSRH int ISO goto 6
register INCSRH int MODE goto 5
register INCSRH int DMAREQENAB goto 4
register INCSRH int DMAREQMODE goto 2
register INCSR int CDT goto 6
register INCSR int SENTSTALL goto 5
register INCSR int SENDSTALL goto 4
register INCSR int FF goto 3
register INCSR int UNDERRUN goto 2
register INCSR int FFNOTEMPT goto 1
register INCSR int INPKTRDY goto 0
register OUTCSRH int AUTOCLR goto 7
register OUTCSRH int ISO goto 6
register OUTCSRH int DMAREQENAB goto 5
register OUTCSRH int DNYT goto 4
register OUTCSRH int DMAREQMODE goto 3
register OUTCSR int CDT goto 7
register OUTCSR int SENTSTALL goto 6
register OUTCSR int SENDSTALL goto 5
register OUTCSR int FF goto 4
register OUTCSR int DATAERR goto 3
register OUTCSR int OVERRUN goto 2
register OUTCSR int FFFULL goto 1
register OUTCSR int OUTPKTRDY goto 0

// 
register TESTMODE export "Testmode register bits"
register TESTMODE int SE0NAK goto 0
register TESTMODE int J goto 1
register TESTMODE int K goto 2
register TESTMODE int PACKET goto 3

// 
register CNTL export "DMA control bits"
register CNTL int ENA goto 0
register CNTL int DIR_IN goto 1
register CNTL int MODE_1 goto 2
register CNTL int INTR_EN goto 3
// #define USB_CNTL_EP(n)		((n) << 4)
// #define USB_CNTL_BURST_0	(0 << 9)
register CNTL int BURST_4 goto 9
// #define USB_CNTL_BURST_8	(2 << 9)
// #define USB_CNTL_BURST_16	(3 << 9)

// 

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BOTG_H__ */

// 
