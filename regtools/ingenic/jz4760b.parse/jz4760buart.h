/*
 * linux/include/asm-mips/mach-jz4760b/jz4760buart.h
 *
 * JZ4760B UART register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

// 
// #ifndef __JZ4760BUART_H__
// #define __JZ4760BUART_H__

// 

// 
this class UART goto (0, 0xB0030000)
this class UART goto (1, 0xB0031000)
this class UART goto (2, 0xB0032000)
this class UART goto (3, 0xB0033000)

// 
/*************************************************************************
 * UART
 *************************************************************************/

// 
// #define IRDA_BASE	UART_BASE
// #define UART_BASE	UART_BASE
const UART_OFF 0x1000

// 
/* Register Offset */
const OFF_RDR 0x00
const OFF_TDR 0x00
const OFF_DLLR 0x00
const OFF_DLHR 0x04
const OFF_IER 0x04
const OFF_ISR 0x08
const OFF_FCR 0x08
const OFF_LCR 0x0C
const OFF_MCR 0x10
const OFF_LSR 0x14
const OFF_MSR 0x18
const OFF_SPR 0x1C
const OFF_SIRCR 0x20
const OFF_UMR 0x24
const OFF_UACR 0x28

// 
/* Register Address */
register RDR goto OFF_RDR export ""
register TDR goto OFF_TDR export ""
register DLLR goto OFF_DLLR export ""
register DLHR goto OFF_DLHR export ""
register IER goto OFF_IER export ""
register ISR goto OFF_ISR export ""
register FCR goto OFF_FCR export ""
register LCR goto OFF_LCR export ""
register MCR goto OFF_MCR export ""
register LSR goto OFF_LSR export ""
register MSR goto OFF_MSR export ""
register SPR goto OFF_SPR export ""
register SIRCR goto OFF_SIRCR export ""
register UMR goto OFF_UMR export ""
register UACR goto OFF_UACR export ""

// 
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

// 

// 
/*
 * Define macros for UART_IER
 * UART Interrupt Enable Register
 */
register IER int RIE goto 0 export "0: receive fifo full interrupt disable"
register IER int TIE goto 1 export "0: transmit fifo empty interrupt disable"
register IER int RLIE goto 2 export "0: receive line status interrupt disable"
register IER int MIE goto 3 export "0: modem status interrupt disable"
register IER int RTIE goto 4 export "0: receive timeout interrupt disable"

// 
/*
 * Define macros for UART_ISR
 * UART Interrupt Status Register
 */
register ISR int IP goto 0 export "0: interrupt is pending  1: no interrupt"
// #define UART_ISR_IID	(7 << 1)	/* Source of Interrupt */
// #define UART_ISR_IID_MSI		(0 << 1)  /* Modem status interrupt */
register ISR int IID_THRI goto 1 export "Transmitter holding register empty"
// #define UART_ISR_IID_RDI		(2 << 1)  /* Receiver data interrupt */
// #define UART_ISR_IID_RLSI	(3 << 1)  /* Receiver line status interrupt */
// #define UART_ISR_IID_RTO		(6 << 1)  /* Receive timeout */
// #define UART_ISR_FFMS		(3 << 6)  /* FIFO mode select, set when UART_FCR.FE is set to 1 */
// #define UART_ISR_FFMS_NO_FIFO	(0 << 6)
// #define UART_ISR_FFMS_FIFO_MODE	(3 << 6)

// 
/*
 * Define macros for UART_FCR
 * UART FIFO Control Register
 */
register FCR int FE goto 0 export "0: non-FIFO mode  1: FIFO mode"
register FCR int RFLS goto 1 export "write 1 to flush receive FIFO"
register FCR int TFLS goto 2 export "write 1 to flush transmit FIFO"
register FCR int DMS goto 3 export "0: disable DMA mode"
register FCR int UUE goto 4 export "0: disable UART"
// #define UART_FCR_RTRG	(3 << 6)	/* Receive FIFO Data Trigger */
// #define UART_FCR_RTRG_1	(0 << 6)
register FCR int RTRG_4 goto 6
// #define UART_FCR_RTRG_8	(2 << 6)
// #define UART_FCR_RTRG_15	(3 << 6)

// 
/*
 * Define macros for UART_LCR
 * UART Line Control Register
 */
// #define UART_LCR_WLEN	(3 << 0)	/* word length */
// #define UART_LCR_WLEN_5	(0 << 0)
register LCR int WLEN_6 goto 0
// #define UART_LCR_WLEN_7	(2 << 0)
// #define UART_LCR_WLEN_8	(3 << 0)
// #define UART_LCR_STOP	(1 << 2)	/* 0: 1 stop bit when word length is 5,6,7,8
// 					   1: 1.5 stop bits when 5; 2 stop bits when 6,7,8 */
// #define UART_LCR_STOP1	(0 << 2)
register LCR int STOP2 goto 2
register LCR int PE goto 3 export "0: parity disable"
register LCR int PROE goto 4 export "0: even parity  1: odd parity"
register LCR int SPAR goto 5 export "0: sticky parity disable"
register LCR int SBRK goto 6 export "write 0 normal, write 1 send break"
register LCR int DLAB goto 7 export "0: access UARTRDR/TDR/IER  1: access UARTDLLR/DLHR"

// 
/*
 * Define macros for UART_LSR
 * UART Line Status Register
 */
register LSR int DR goto 0 export "0: receive FIFO is empty  1: receive data is ready"
register LSR int ORER goto 1 export "0: no overrun error"
register LSR int PER goto 2 export "0: no parity error"
register LSR int FER goto 3 export "0; no framing error"
register LSR int BRK goto 4 export "0: no break detected  1: receive a break signal"
register LSR int TDRQ goto 5 export "1: transmit FIFO half 'empty'"
register LSR int TEMT goto 6 export "1: transmit FIFO and shift registers empty"
register LSR int RFER goto 7 export "0: no receive error  1: receive error in FIFO mode"

// 
/*
 * Define macros for UART_MCR
 * UART Modem Control Register
 */
register MCR int RTS goto 1 export "0: RTS_ output high, 1: RTS_ output low"
register MCR int LOOP goto 4 export "0: normal  1: loopback mode"
register MCR int FCM goto 6 export "0: software  1: hardware"
register MCR int MCE goto 7 export "0: modem function is disable"

// 
/*
 * Define macros for UARTMSR
 * UART Modem Status Register
 */
// #define UARTMSR_CCTS	(1 << 0)        /* 1: a change on CTS_ pin */
// #define UARTMSR_CTS	(1 << 4)	/* 0: CTS_ pin is high */

// 
/*
 * Define macros for UART_SIRCR
 * Slow IrDA Control Register
 */
register SIRCR int TSIRE goto 0 export "0: transmitter is in UART mode  1: SIR mode"
register SIRCR int RSIRE goto 1 export "0: receiver is in UART mode  1: SIR mode"
register SIRCR int TPWS goto 2 export "0: transmit 0 pulse width is 3/16 of bit length, 1: 0 pulse width is 1.6us for 115.2Kbps"
register SIRCR int TDPL goto 3 export "0: encoder generates a positive pulse for 0"
register SIRCR int RDPL goto 4 export "0: decoder interprets positive pulse as 0"

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 
/***************************************************************************
 * UART
 ***************************************************************************/
// #define __jtag_as_uart3()			\
// do {	                    			\
// 	REG_GPIO_PXSELC(0) = 0x40000000;	\
// 	REG_GPIO_PXSELS(0) = 0x80000000;	\
// } while(0)

// 
// #define __uart_enable(n) \
//   ( REG8(UART_BASE + UART_OFF*(n) + OFF_FCR) |= UART_FCR_UUE | UART_FCR_FE )
// #define __uart_disable(n) \
//   ( REG8(UART_BASE + UART_OFF*(n) + OFF_FCR) = ~UART_FCR_UUE )

// 
// #define __uart_enable_transmit_irq(n) \
//   ( REG8(UART_BASE + UART_OFF*(n) + OFF_IER) |= UART_IER_TIE )
// #define __uart_disable_transmit_irq(n) \
//   ( REG8(UART_BASE + UART_OFF*(n) + OFF_IER) &= ~UART_IER_TIE )

// 
// #define __uart_enable_receive_irq(n) \
//   ( REG8(UART_BASE + UART_OFF*(n) + OFF_IER) |= UART_IER_RIE | UART_IER_RLIE | UART_IER_RTIE )
// #define __uart_disable_receive_irq(n) \
//   ( REG8(UART_BASE + UART_OFF*(n) + OFF_IER) &= ~(UART_IER_RIE | UART_IER_RLIE | UART_IER_RTIE) )

// 
// #define __uart_enable_loopback(n) \
//   ( REG8(UART_BASE + UART_OFF*(n) + OFF_MCR) |= UART_MCR_LOOP )
// #define __uart_disable_loopback(n) \
//   ( REG8(UART_BASE + UART_OFF*(n) + OFF_MCR) &= ~UART_MCR_LOOP )

// 
// #define __uart_set_8n1(n) \
//   ( REG8(UART_BASE + UART_OFF*(n) + OFF_LCR) = UART_LCR_WLEN_8 )

// 
// #define __uart_set_baud(n, devclk, baud)						\
//   do {											\
// 	REG8(UART_BASE + UART_OFF*(n) + OFF_LCR) |= UART_LCR_DLAB;			\
// 	REG8(UART_BASE + UART_OFF*(n) + OFF_DLLR) = (devclk / 16 / baud) & 0xff;	\
// 	REG8(UART_BASE + UART_OFF*(n) + OFF_DLHR) = ((devclk / 16 / baud) >> 8) & 0xff;	\
// 	REG8(UART_BASE + UART_OFF*(n) + OFF_LCR) &= ~UART_LCR_DLAB;			\
//   } while (0)

// 
// #define __uart_parity_error(n) \
//   ( (REG8(UART_BASE + UART_OFF*(n) + OFF_LSR) & UART_LSR_PER) != 0 )

// 
// #define __uart_clear_errors(n) \
//   ( REG8(UART_BASE + UART_OFF*(n) + OFF_LSR) &= ~(UART_LSR_ORER | UART_LSR_BRK | UART_LSR_FER | UART_LSR_PER | UART_LSR_RFER) )

// 
// #define __uart_transmit_fifo_empty(n) \
//   ( (REG8(UART_BASE + UART_OFF*(n) + OFF_LSR) & UART_LSR_TDRQ) != 0 )

// 
// #define __uart_transmit_end(n) \
//   ( (REG8(UART_BASE + UART_OFF*(n) + OFF_LSR) & UART_LSR_TEMT) != 0 )

// 
// #define __uart_transmit_char(n, ch) \
//   REG8(UART_BASE + UART_OFF*(n) + OFF_TDR) = (ch)

// 
// #define __uart_receive_fifo_full(n) \
//   ( (REG8(UART_BASE + UART_OFF*(n) + OFF_LSR) & UART_LSR_DR) != 0 )

// 
// #define __uart_receive_ready(n) \
//   ( (REG8(UART_BASE + UART_OFF*(n) + OFF_LSR) & UART_LSR_DR) != 0 )

// 
// #define __uart_receive_char(n) \
//   REG8(UART_BASE + UART_OFF*(n) + OFF_RDR)

// 
// #define __uart_disable_irda() \
//   ( REG8(IRDA_BASE + OFF_UART_SIRCR) &= ~(UART_SIRCR_TSIRE | UART_SIRCR_RSIRE) )
// #define __uart_enable_irda() \
//   /* Tx high pulse as 0, Rx low pulse as 0 */ \
//   ( REG8(IRDA_BASE + OFF_UART_SIRCR) = UART_SIRCR_TSIRE | UART_SIRCR_RSIRE | UART_SIRCR_RXPL | UART_SIRCR_TPWS )

// 

// 

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BUART_H__ */

// 
