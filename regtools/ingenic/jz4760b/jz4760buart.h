/*
 * linux/include/asm-mips/mach-jz4760b/jz4760buart.h
 *
 * JZ4760B UART register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

#ifndef __JZ4760BUART_H__
#define __JZ4760BUART_H__


#define	UART_BASE(0)	0xB0030000
#define	UART_BASE(1)	0xB0031000
#define	UART_BASE(2)	0xB0032000
#define	UART_BASE(3)	0xB0033000

/*************************************************************************
 * UART
 *************************************************************************/

// #define IRDA_BASE	UART_BASE
// #define UART_BASE	UART_BASE
#define UART_OFF	0x1000

/* Register Offset */
#define OFF_RDR		(0x00)	/* R  8b H'xx */
#define OFF_TDR		(0x00)	/* W  8b H'xx */
#define OFF_DLLR	(0x00)	/* RW 8b H'00 */
#define OFF_DLHR	(0x04)	/* RW 8b H'00 */
#define OFF_IER		(0x04)	/* RW 8b H'00 */
#define OFF_ISR		(0x08)	/* R  8b H'01 */
#define OFF_FCR		(0x08)	/* W  8b H'00 */
#define OFF_LCR		(0x0C)	/* RW 8b H'00 */
#define OFF_MCR		(0x10)	/* RW 8b H'00 */
#define OFF_LSR		(0x14)	/* R  8b H'00 */
#define OFF_MSR		(0x18)	/* R  8b H'00 */
#define OFF_SPR		(0x1C)	/* RW 8b H'00 */
#define OFF_SIRCR	(0x20)	/* RW 8b H'00, UART0 */
#define OFF_UMR		(0x24)	/* RW 8b H'00, UART M Register */
#define OFF_UACR	(0x28)	/* RW 8b H'00, UART Add Cycle Register */

/* Register Address */
#define UART_RDR	(UART_BASE + OFF_RDR)
#define UART_TDR	(UART_BASE + OFF_TDR)
#define UART_DLLR	(UART_BASE + OFF_DLLR)
#define UART_DLHR	(UART_BASE + OFF_DLHR)
#define UART_IER	(UART_BASE + OFF_IER)
#define UART_ISR	(UART_BASE + OFF_ISR)
#define UART_FCR	(UART_BASE + OFF_FCR)
#define UART_LCR	(UART_BASE + OFF_LCR)
#define UART_MCR	(UART_BASE + OFF_MCR)
#define UART_LSR	(UART_BASE + OFF_LSR)
#define UART_MSR	(UART_BASE + OFF_MSR)
#define UART_SPR	(UART_BASE + OFF_SPR)
#define UART_SIRCR	(UART_BASE + OFF_SIRCR)
#define UART_UMR	(UART_BASE + OFF_UMR)
#define UART_UACR	(UART_BASE + OFF_UACR)

// #define UART1_RDR	(UART1_BASE + OFF_RDR)
// #define UART1_TDR	(UART1_BASE + OFF_TDR)
// #define UART1_DLLR	(UART1_BASE + OFF_DLLR)
// #define UART1_DLHR	(UART1_BASE + OFF_DLHR)
// #define UART1_IER	(UART1_BASE + OFF_IER)
// #define UART1_ISR	(UART1_BASE + OFF_ISR)
// #define UART1_FCR	(UART1_BASE + OFF_FCR)
// #define UART1_LCR	(UART1_BASE + OFF_LCR)
// #define UART1_MCR	(UART1_BASE + OFF_MCR)
// #define UART1_LSR	(UART1_BASE + OFF_LSR)
// #define UART1_MSR	(UART1_BASE + OFF_MSR)
// #define UART1_SPR	(UART1_BASE + OFF_SPR)
// #define UART1_UART_SIRCR	(UART1_BASE + OFF_UART_SIRCR)
// 
// #define UART2_RDR	(UART2_BASE + OFF_RDR)
// #define UART2_TDR	(UART2_BASE + OFF_TDR)
// #define UART2_DLLR	(UART2_BASE + OFF_DLLR)
// #define UART2_DLHR	(UART2_BASE + OFF_DLHR)
// #define UART2_IER	(UART2_BASE + OFF_IER)
// #define UART2_ISR	(UART2_BASE + OFF_ISR)
// #define UART2_FCR	(UART2_BASE + OFF_FCR)
// #define UART2_LCR	(UART2_BASE + OFF_LCR)
// #define UART2_MCR	(UART2_BASE + OFF_MCR)
// #define UART2_LSR	(UART2_BASE + OFF_LSR)
// #define UART2_MSR	(UART2_BASE + OFF_MSR)
// #define UART2_SPR	(UART2_BASE + OFF_SPR)
// #define UART2_UART_SIRCR	(UART2_BASE + OFF_UART_SIRCR)
// 
// #define UART3_RDR	(UART3_BASE + OFF_RDR)
// #define UART3_TDR	(UART3_BASE + OFF_TDR)
// #define UART3_DLLR	(UART3_BASE + OFF_DLLR)
// #define UART3_DLHR	(UART3_BASE + OFF_DLHR)
// #define UART3_IER	(UART3_BASE + OFF_IER)
// #define UART3_ISR	(UART3_BASE + OFF_ISR)
// #define UART3_FCR	(UART3_BASE + OFF_FCR)
// #define UART3_LCR	(UART3_BASE + OFF_LCR)
// #define UART3_MCR	(UART3_BASE + OFF_MCR)
// #define UART3_LSR	(UART3_BASE + OFF_LSR)
// #define UART3_MSR	(UART3_BASE + OFF_MSR)
// #define UART3_SPR	(UART3_BASE + OFF_SPR)
// #define UART3_UART_SIRCR	(UART3_BASE + OFF_UART_SIRCR)


/*
 * Define macros for UART_IER
 * UART Interrupt Enable Register
 */
#define UART_IER_RIE	(1 << 0)	/* 0: receive fifo full interrupt disable */
#define UART_IER_TIE	(1 << 1)	/* 0: transmit fifo empty interrupt disable */
#define UART_IER_RLIE	(1 << 2)	/* 0: receive line status interrupt disable */
#define UART_IER_MIE	(1 << 3)	/* 0: modem status interrupt disable */
#define UART_IER_RTIE	(1 << 4)	/* 0: receive timeout interrupt disable */

/*
 * Define macros for UART_ISR
 * UART Interrupt Status Register
 */
#define UART_ISR_IP	(1 << 0)	/* 0: interrupt is pending  1: no interrupt */
#define UART_ISR_IID	(7 << 1)	/* Source of Interrupt */
#define UART_ISR_IID_MSI		(0 << 1)  /* Modem status interrupt */
#define UART_ISR_IID_THRI	(1 << 1)  /* Transmitter holding register empty */
#define UART_ISR_IID_RDI		(2 << 1)  /* Receiver data interrupt */
#define UART_ISR_IID_RLSI	(3 << 1)  /* Receiver line status interrupt */
#define UART_ISR_IID_RTO		(6 << 1)  /* Receive timeout */
#define UART_ISR_FFMS		(3 << 6)  /* FIFO mode select, set when UART_FCR.FE is set to 1 */
#define UART_ISR_FFMS_NO_FIFO	(0 << 6)
#define UART_ISR_FFMS_FIFO_MODE	(3 << 6)

/*
 * Define macros for UART_FCR
 * UART FIFO Control Register
 */
#define UART_FCR_FE	(1 << 0)	/* 0: non-FIFO mode  1: FIFO mode */
#define UART_FCR_RFLS	(1 << 1)	/* write 1 to flush receive FIFO */
#define UART_FCR_TFLS	(1 << 2)	/* write 1 to flush transmit FIFO */
#define UART_FCR_DMS	(1 << 3)	/* 0: disable DMA mode */
#define UART_FCR_UUE	(1 << 4)	/* 0: disable UART */
#define UART_FCR_RTRG	(3 << 6)	/* Receive FIFO Data Trigger */
#define UART_FCR_RTRG_1	(0 << 6)
#define UART_FCR_RTRG_4	(1 << 6)
#define UART_FCR_RTRG_8	(2 << 6)
#define UART_FCR_RTRG_15	(3 << 6)

/*
 * Define macros for UART_LCR
 * UART Line Control Register
 */
#define UART_LCR_WLEN	(3 << 0)	/* word length */
#define UART_LCR_WLEN_5	(0 << 0)
#define UART_LCR_WLEN_6	(1 << 0)
#define UART_LCR_WLEN_7	(2 << 0)
#define UART_LCR_WLEN_8	(3 << 0)
#define UART_LCR_STOP	(1 << 2)	/* 0: 1 stop bit when word length is 5,6,7,8
					   1: 1.5 stop bits when 5; 2 stop bits when 6,7,8 */
#define UART_LCR_STOP1	(0 << 2)
#define UART_LCR_STOP2	(1 << 2)
#define UART_LCR_PE	(1 << 3)	/* 0: parity disable */
#define UART_LCR_PROE	(1 << 4)	/* 0: even parity  1: odd parity */
#define UART_LCR_SPAR	(1 << 5)	/* 0: sticky parity disable */
#define UART_LCR_SBRK	(1 << 6)	/* write 0 normal, write 1 send break */
#define UART_LCR_DLAB	(1 << 7)	/* 0: access UARTRDR/TDR/IER  1: access UARTDLLR/DLHR */

/*
 * Define macros for UART_LSR
 * UART Line Status Register
 */
#define UART_LSR_DR	(1 << 0)	/* 0: receive FIFO is empty  1: receive data is ready */
#define UART_LSR_ORER	(1 << 1)	/* 0: no overrun error */
#define UART_LSR_PER	(1 << 2)	/* 0: no parity error */
#define UART_LSR_FER	(1 << 3)	/* 0; no framing error */
#define UART_LSR_BRK	(1 << 4)	/* 0: no break detected  1: receive a break signal */
#define UART_LSR_TDRQ	(1 << 5)	/* 1: transmit FIFO half 'empty' */
#define UART_LSR_TEMT	(1 << 6)	/* 1: transmit FIFO and shift registers empty */
#define UART_LSR_RFER	(1 << 7)	/* 0: no receive error  1: receive error in FIFO mode */

/*
 * Define macros for UART_MCR
 * UART Modem Control Register
 */
#define UART_MCR_RTS	(1 << 1)	/* 0: RTS_ output high, 1: RTS_ output low */
#define UART_MCR_LOOP	(1 << 4)	/* 0: normal  1: loopback mode */
#define UART_MCR_FCM	(1 << 6)	/* 0: software  1: hardware */
#define UART_MCR_MCE	(1 << 7)	/* 0: modem function is disable */

/*
 * Define macros for UARTMSR
 * UART Modem Status Register
 */
#define UARTMSR_CCTS	(1 << 0)        /* 1: a change on CTS_ pin */
#define UARTMSR_CTS	(1 << 4)	/* 0: CTS_ pin is high */

/*
 * Define macros for UART_SIRCR
 * Slow IrDA Control Register
 */
#define UART_SIRCR_TSIRE	(1 << 0)  /* 0: transmitter is in UART mode  1: SIR mode */
#define UART_SIRCR_RSIRE	(1 << 1)  /* 0: receiver is in UART mode  1: SIR mode */
#define UART_SIRCR_TPWS	(1 << 2)  /* 0: transmit 0 pulse width is 3/16 of bit length, 1: 0 pulse width is 1.6us for 115.2Kbps */
#define UART_SIRCR_TDPL	(1 << 3)  /* 0: encoder generates a positive pulse for 0 */
#define UART_SIRCR_RDPL	(1 << 4)  /* 0: decoder interprets positive pulse as 0 */


#ifndef __MIPS_ASSEMBLER

/***************************************************************************
 * UART
 ***************************************************************************/
#define __jtag_as_uart3()			\
do {	                    			\
	REG_GPIO_PXSELC(0) = 0x40000000;	\
	REG_GPIO_PXSELS(0) = 0x80000000;	\
} while(0)

#define __uart_enable(n) \
  ( REG8(UART_BASE + UART_OFF*(n) + OFF_FCR) |= UART_FCR_UUE | UART_FCR_FE )
#define __uart_disable(n) \
  ( REG8(UART_BASE + UART_OFF*(n) + OFF_FCR) = ~UART_FCR_UUE )

#define __uart_enable_transmit_irq(n) \
  ( REG8(UART_BASE + UART_OFF*(n) + OFF_IER) |= UART_IER_TIE )
#define __uart_disable_transmit_irq(n) \
  ( REG8(UART_BASE + UART_OFF*(n) + OFF_IER) &= ~UART_IER_TIE )

#define __uart_enable_receive_irq(n) \
  ( REG8(UART_BASE + UART_OFF*(n) + OFF_IER) |= UART_IER_RIE | UART_IER_RLIE | UART_IER_RTIE )
#define __uart_disable_receive_irq(n) \
  ( REG8(UART_BASE + UART_OFF*(n) + OFF_IER) &= ~(UART_IER_RIE | UART_IER_RLIE | UART_IER_RTIE) )

#define __uart_enable_loopback(n) \
  ( REG8(UART_BASE + UART_OFF*(n) + OFF_MCR) |= UART_MCR_LOOP )
#define __uart_disable_loopback(n) \
  ( REG8(UART_BASE + UART_OFF*(n) + OFF_MCR) &= ~UART_MCR_LOOP )

#define __uart_set_8n1(n) \
  ( REG8(UART_BASE + UART_OFF*(n) + OFF_LCR) = UART_LCR_WLEN_8 )

#define __uart_set_baud(n, devclk, baud)						\
  do {											\
	REG8(UART_BASE + UART_OFF*(n) + OFF_LCR) |= UART_LCR_DLAB;			\
	REG8(UART_BASE + UART_OFF*(n) + OFF_DLLR) = (devclk / 16 / baud) & 0xff;	\
	REG8(UART_BASE + UART_OFF*(n) + OFF_DLHR) = ((devclk / 16 / baud) >> 8) & 0xff;	\
	REG8(UART_BASE + UART_OFF*(n) + OFF_LCR) &= ~UART_LCR_DLAB;			\
  } while (0)

#define __uart_parity_error(n) \
  ( (REG8(UART_BASE + UART_OFF*(n) + OFF_LSR) & UART_LSR_PER) != 0 )

#define __uart_clear_errors(n) \
  ( REG8(UART_BASE + UART_OFF*(n) + OFF_LSR) &= ~(UART_LSR_ORER | UART_LSR_BRK | UART_LSR_FER | UART_LSR_PER | UART_LSR_RFER) )

#define __uart_transmit_fifo_empty(n) \
  ( (REG8(UART_BASE + UART_OFF*(n) + OFF_LSR) & UART_LSR_TDRQ) != 0 )

#define __uart_transmit_end(n) \
  ( (REG8(UART_BASE + UART_OFF*(n) + OFF_LSR) & UART_LSR_TEMT) != 0 )

#define __uart_transmit_char(n, ch) \
  REG8(UART_BASE + UART_OFF*(n) + OFF_TDR) = (ch)

#define __uart_receive_fifo_full(n) \
  ( (REG8(UART_BASE + UART_OFF*(n) + OFF_LSR) & UART_LSR_DR) != 0 )

#define __uart_receive_ready(n) \
  ( (REG8(UART_BASE + UART_OFF*(n) + OFF_LSR) & UART_LSR_DR) != 0 )

#define __uart_receive_char(n) \
  REG8(UART_BASE + UART_OFF*(n) + OFF_RDR)

#define __uart_disable_irda() \
  ( REG8(IRDA_BASE + OFF_UART_SIRCR) &= ~(UART_SIRCR_TSIRE | UART_SIRCR_RSIRE) )
#define __uart_enable_irda() \
  /* Tx high pulse as 0, Rx low pulse as 0 */ \
  ( REG8(IRDA_BASE + OFF_UART_SIRCR) = UART_SIRCR_TSIRE | UART_SIRCR_RSIRE | UART_SIRCR_RXPL | UART_SIRCR_TPWS )



#endif /* __MIPS_ASSEMBLER */

#endif /* __JZ4760BUART_H__ */

