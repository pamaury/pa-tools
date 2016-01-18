/*
 * linux/include/asm-mips/mach-jz4760b/jz4760bintc.h
 *
 * JZ4760B INTC register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

// 
// #ifndef __JZ4760BINTC_H__
// #define __JZ4760BINTC_H__

// 
/* INTC (Interrupt Controller) */
this class INTC goto 0xB0001000 export "INTC (Interrupt Controller)"

// 

// 
/*************************************************************************
 * INTC (Interrupt Controller)
 *************************************************************************/
for n 0 1
register ISR goto<n> "0x00 + (n) * 0x20" export ""
register IMR goto<n> "0x04 + (n) * 0x20" export ""
// #define INTC_ICMR(n)    INTC_IMR(n)
register IMSR goto<n> "0x08 + (n) * 0x20" export ""
// #define INTC_ICMSR(n)   INTC_IMSR(n)
register IMCR goto<n> "0x0c + (n) * 0x20" export ""
// #define INTC_ICMCR(n)	INTC_IMCR(n)
register IPR goto<n> "0x10 + (n) * 0x20" export ""
//#define INTC_ISSR	(INTC_BASE + 0x18)  /* Interrupt Controller Source Set Register */
//#define INTC_ISCR	(INTC_BASE + 0x1c)  /* Interrupt Controller Source Clear Register */

// 
register ISR sizeof 32
register IMR sizeof 32
register IMSR sizeof 32
register IMCR sizeof 32
register IPR sizeof 32
//#define REG_INTC_ISSR   REG32(INTC_ISSR)
//#define REG_INTC_ISCR   REG32(INTC_ISCR)

// 
// 1st-level interrupts
const IRQ_I2C1 0
const IRQ_I2C0 1
const IRQ_UART3 2
const IRQ_UART2 3
const IRQ_UART1 4
const IRQ_UART0 5
const IRQ_SSI2 6
const IRQ_SSI1 7
const IRQ_SSI0 8
const IRQ_TSSI 9
const IRQ_BDMA 10
const IRQ_KBC 11
const IRQ_GPIO5 12
const IRQ_GPIO4 13
const IRQ_GPIO3 14
const IRQ_GPIO2 15
const IRQ_GPIO1 16
const IRQ_GPIO0 17
const IRQ_SADC 18
const IRQ_ETH 19
const IRQ_UHC 20
const IRQ_OTG 21
const IRQ_MDMA 22
const IRQ_DMAC1 23
const IRQ_DMAC0 24
const IRQ_TCU2 25
const IRQ_TCU1 26
const IRQ_TCU0 27
const IRQ_GPS 28
const IRQ_IPU 29
const IRQ_CIM 30
const IRQ_LCD 31

// 
const IRQ_RTC 32
const IRQ_OWI 33
const IRQ_AIC 34
const IRQ_MSC2 35
const IRQ_MSC1 36
const IRQ_MSC0 37
const IRQ_SCC 38
const IRQ_BCH 39
const IRQ_PCM 40

// 

// 
// 2nd-level interrupts

// 
const IRQ_DMA_0 46
//#define IRQ_DMA_0	32  /* 64 ~ 75 for DMAC0 channel 0 ~ 5 & DMAC1 channel 0 ~ 5 */
// #define IRQ_DMA_1	(IRQ_DMA_0 + HALF_DMA_NUM)  /* 64 ~ 75 for DMAC0 channel 0 ~ 5 & DMAC1 channel 0 ~ 5 */
// #define IRQ_MDMA_0	(IRQ_DMA_0 + MAX_DMA_NUM)   /* 64 ~ 66 for MDMAC channel 0 ~ 2 */
// #define IRQ_BDMA_0  (IRQ_DMA_0 + MAX_DMA_NUM + MAX_MDMA_NUM) /* 61 ~ 63 for BDMA channel 0 ~ 2 */

// 
//#define IRQ_GPIO_0	96  /* 96 to 287 for GPIO pin 0 to 127 */
const IRQ_GPIO_0 64

// 
const NUM_INTC 41
// #define NUM_DMA         MAX_DMA_NUM	/* 12 */
// #define NUM_MDMA        MAX_MDMA_NUM	/* 3 */
// #define NUM_GPIO        MAX_GPIO_NUM	/* GPIO NUM: 192, Jz4760b real num GPIO 178 */

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 

// 
/***************************************************************************
 * INTC
 ***************************************************************************/
// #define __intc_unmask_irq(n)	(REG_INTC_IMCR((n)/32) = (1 << ((n)%32)))
// #define __intc_mask_irq(n)	(REG_INTC_IMSR((n)/32) = (1 << ((n)%32)))
// #define __intc_ack_irq(n)	(REG_INTC_IPR((n)/32) = (1 << ((n)%32))) /* A dummy ack, as the Pending Register is Read Only. Should we remove __intc_ack_irq() */

// 

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BINTC_H__ */

// 