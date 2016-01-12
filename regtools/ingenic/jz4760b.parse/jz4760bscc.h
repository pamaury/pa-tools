/*
 * linux/include/asm-mips/mach-jz4760b/jz4760bscc.h
 *
 * JZ4760B SCC register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

// 
// #ifndef __JZ4760BSCC_H__
// #define __JZ4760BSCC_H__

// 

// 
this class SCC goto 0xB0040000

// 
/*************************************************************************
 * SCC
 *************************************************************************/
register DR goto 0x000 export ""
register FDR goto 0x004 export ""
register CR goto 0x008 export ""
register SR goto 0x00C export ""
register TFR goto 0x010 export ""
register EGTR goto 0x014 export ""
register ECR goto 0x018 export ""
register RTOR goto 0x01C export ""

// 
register DR sizeof 8
register FDR sizeof 8
register CR sizeof 32
register SR sizeof 16
register TFR sizeof 16
register EGTR sizeof 8
register ECR sizeof 32
register RTOR sizeof 8

// 
register FDR export "SCC FIFO Data Count Register"

// 
const SCC_FDR_EMPTY 0x00
const SCC_FDR_FULL 0x10

// 
register CR export "SCC Control Register"

// 
register CR int SCCE goto 31
register CR int TRS goto 30
register CR int T2R goto 29
const SCC_CR_FDIV_BIT 24
register CR int FDIV goto (0x3 << SCC_CR_FDIV_BIT)
register CR int FDIV enum "1" 0 export "SCC_CLK frequency is the same as device clock"
register CR int FDIV enum "2" 1 export "SCC_CLK frequency is half of device clock"
register CR int FLUSH goto 23
const SCC_CR_TRIG_BIT 16
register CR int TRIG goto (0x3 << SCC_CR_TRIG_BIT)
register CR int TRIG enum "1" 0 export "Receive/Transmit-FIFO Trigger is 1"
register CR int TRIG enum "4" 1 export "Receive/Transmit-FIFO Trigger is 4"
register CR int TRIG enum "8" 2 export "Receive/Transmit-FIFO Trigger is 8"
register CR int TRIG enum "14" 3 export "Receive/Transmit-FIFO Trigger is 14"
register CR int TP goto 15
register CR int CONV goto 14
register CR int TXIE goto 13
register CR int RXIE goto 12
register CR int TENDIE goto 11
register CR int RTOIE goto 10
register CR int ECIE goto 9
register CR int EPIE goto 8
register CR int RETIE goto 7
register CR int EOIE goto 6
register CR int TSEND goto 3
const SCC_CR_PX_BIT 1
register CR int PX goto (0x3 << SCC_CR_PX_BIT)
register CR int PX enum NOT_SUPPORT 0 export "SCC does not support clock stop"
register CR int PX enum STOP_LOW 1 export "SCC_CLK stops at state low"
register CR int PX enum STOP_HIGH 2 export "SCC_CLK stops at state high"
register CR int CLKSTP goto 0

// 
register SR export "SCC Status Register"

// 
register SR int TRANS goto 15
register SR int ORER goto 12
register SR int RTO goto 11
register SR int PER goto 10
register SR int TFTG goto 9
register SR int RFTG goto 8
register SR int TEND goto 7
register SR int RETR_3 goto 4
register SR int ECNTO goto 0

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 
/***************************************************************************
 * SCC
 ***************************************************************************/

// 
// #define __scc_enable()			( REG_SCC_CR |= SCC_CR_SCCE )
// #define __scc_disable()			( REG_SCC_CR &= ~SCC_CR_SCCE )

// 
// #define __scc_set_tx_mode()		( REG_SCC_CR |= SCC_CR_TRS )
// #define __scc_set_rx_mode()		( REG_SCC_CR &= ~SCC_CR_TRS )

// 
// #define __scc_enable_t2r()		( REG_SCC_CR |= SCC_CR_T2R )
// #define __scc_disable_t2r()		( REG_SCC_CR &= ~SCC_CR_T2R )

// 
// #define __scc_clk_as_devclk()			\
// do {						\
//   REG_SCC_CR &= ~SCC_CR_FDIV_MASK;		\
//   REG_SCC_CR |= SCC_CR_FDIV_1;			\
// } while (0)

// 
// #define __scc_clk_as_half_devclk()		\
// do {						\
//   REG_SCC_CR &= ~SCC_CR_FDIV_MASK;		\
//   REG_SCC_CR |= SCC_CR_FDIV_2;			\
// } while (0)

// 
/* n=1,4,8,14 */
// #define __scc_set_fifo_trigger(n)		\
// do {						\
//   REG_SCC_CR &= ~SCC_CR_TRIG_MASK;		\
//   REG_SCC_CR |= SCC_CR_TRIG_##n;		\
// } while (0)

// 
// #define __scc_set_protocol(p)			\
// do {						\
// 	if (p)					\
// 	  	REG_SCC_CR |= SCC_CR_TP;	\
// 	else					\
// 	 	REG_SCC_CR &= ~SCC_CR_TP;	\
// } while (0)

// 
// #define __scc_flush_fifo()		( REG_SCC_CR |= SCC_CR_FLUSH )

// 
// #define __scc_set_invert_mode()		( REG_SCC_CR |= SCC_CR_CONV )
// #define __scc_set_direct_mode()		( REG_SCC_CR &= ~SCC_CR_CONV )

// 
// #define SCC_ERR_INTRS \
//     ( SCC_CR_ECIE | SCC_CR_EPIE | SCC_CR_RETIE | SCC_CR_EOIE )
// #define SCC_ALL_INTRS \
//     ( SCC_CR_TXIE | SCC_CR_RXIE | SCC_CR_TENDIE | SCC_CR_RTOIE | \
//       SCC_CR_ECIE | SCC_CR_EPIE | SCC_CR_RETIE | SCC_CR_EOIE )

// 
// #define __scc_enable_err_intrs()	( REG_SCC_CR |= SCC_ERR_INTRS )
// #define __scc_disable_err_intrs()	( REG_SCC_CR &= ~SCC_ERR_INTRS )

// 
// #define SCC_ALL_ERRORS \
//     ( SCC_SR_ORER | SCC_SR_RTO | SCC_SR_PER | SCC_SR_RETR_3 | SCC_SR_ECNTO)

// 
// #define __scc_clear_errors()		( REG_SCC_SR &= ~SCC_ALL_ERRORS )

// 
// #define __scc_enable_all_intrs()	( REG_SCC_CR |= SCC_ALL_INTRS )
// #define __scc_disable_all_intrs()	( REG_SCC_CR &= ~SCC_ALL_INTRS )

// 
// #define __scc_enable_tx_intr()		( REG_SCC_CR |= SCC_CR_TXIE | SCC_CR_TENDIE )
// #define __scc_disable_tx_intr()		( REG_SCC_CR &= ~(SCC_CR_TXIE | SCC_CR_TENDIE) )

// 
// #define __scc_enable_rx_intr()		( REG_SCC_CR |= SCC_CR_RXIE)
// #define __scc_disable_rx_intr()		( REG_SCC_CR &= ~SCC_CR_RXIE)

// 
// #define __scc_set_tsend()		( REG_SCC_CR |= SCC_CR_TSEND )
// #define __scc_clear_tsend()		( REG_SCC_CR &= ~SCC_CR_TSEND )

// 
// #define __scc_set_clockstop()		( REG_SCC_CR |= SCC_CR_CLKSTP )
// #define __scc_clear_clockstop()		( REG_SCC_CR &= ~SCC_CR_CLKSTP )

// 
// #define __scc_clockstop_low()			\
// do {						\
//   REG_SCC_CR &= ~SCC_CR_PX_MASK;		\
//   REG_SCC_CR |= SCC_CR_PX_STOP_LOW;		\
// } while (0)

// 
// #define __scc_clockstop_high()			\
// do {						\
//   REG_SCC_CR &= ~SCC_CR_PX_MASK;		\
//   REG_SCC_CR |= SCC_CR_PX_STOP_HIGH;		\
// } while (0)

// 
/* SCC status checking */
// #define __scc_check_transfer_status()		( REG_SCC_SR & SCC_SR_TRANS )
// #define __scc_check_rx_overrun_error()		( REG_SCC_SR & SCC_SR_ORER )
// #define __scc_check_rx_timeout()		( REG_SCC_SR & SCC_SR_RTO )
// #define __scc_check_parity_error()		( REG_SCC_SR & SCC_SR_PER )
// #define __scc_check_txfifo_trigger()		( REG_SCC_SR & SCC_SR_TFTG )
// #define __scc_check_rxfifo_trigger()		( REG_SCC_SR & SCC_SR_RFTG )
// #define __scc_check_tx_end()			( REG_SCC_SR & SCC_SR_TEND )
// #define __scc_check_retx_3()			( REG_SCC_SR & SCC_SR_RETR_3 )
// #define __scc_check_ecnt_overflow()		( REG_SCC_SR & SCC_SR_ECNTO )

// 

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BSCC_H__ */

// 
