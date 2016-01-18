/*
 * linux/include/asm-mips/mach-jz4760b/jz4760bssi.h
 *
 * JZ4760B SSI register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

// 
// #ifndef __JZ4760BSSI_H__
// #define __JZ4760BSSI_H__

// 
/* SSI (Synchronous Serial Interface) */
this class SSI goto (0, 0xB0043000) export "SSI (Synchronous Serial Interface)"
this class SSI goto (1, 0xB0044000)
this class SSI goto (2, 0xB0045000)

// 

// 

// 

// 
for n 0 2
register DR goto<n> "0x000 + (n)*0x1000" export ""
register CR0 goto<n> "0x004 + (n)*0x1000" export ""
register CR1 goto<n> "0x008 + (n)*0x1000" export ""
register SR goto<n> "0x00C + (n)*0x1000" export ""
register ITR goto<n> "0x010 + (n)*0x1000" export ""
register ICR goto<n> "0x014 + (n)*0x1000" export ""
register GR goto<n> "0x018 + (n)*0x1000" export ""

// 
register DR sizeof 32
register CR0 sizeof 16
register CR1 sizeof 32
register SR sizeof 32
register ITR sizeof 16
register ICR sizeof 8
register GR sizeof 16

// 
register DR export "SSI Data Register"

// 
const SSI_DR_GPC_BIT 0
register DR int GPC goto (0x1ff << SSI_DR_GPC_BIT)

// 
const SSI_MAX_FIFO_ENTRIES 128

// 
register CR0 export "SSI Control Register 0"

// 
register CR0 int SSIE goto 15
register CR0 int TIE goto 14
register CR0 int RIE goto 13
register CR0 int TEIE goto 12
register CR0 int REIE goto 11
register CR0 int LOOP goto 10
register CR0 int RFINE goto 9
register CR0 int RFINC goto 8
register CR0 int EACLRUN goto 7 export "hardware auto clear underrun when TxFifo no empty"
register CR0 int FSEL goto 6
register CR0 int TFLUSH goto 2
register CR0 int RFLUSH goto 1
register CR0 int DISREV goto 0

// 
register CR1 export "SSI Control Register 1"

// 
const SSI_CR1_FRMHL_BIT 30
register CR1 int FRMHL goto (0x3 << SSI_CR1_FRMHL_BIT)
register CR1 int FRMHL enum CELOW_CE2LOW 0 export "SSI_CE_ is low valid and SSI_CE2_ is low valid"
register CR1 int FRMHL enum CEHIGH_CE2LOW 1 export "SSI_CE_ is high valid and SSI_CE2_ is low valid"
register CR1 int FRMHL enum CELOW_CE2HIGH 2 export "SSI_CE_ is low valid  and SSI_CE2_ is high valid"
register CR1 int FRMHL enum CEHIGH_CE2HIGH 3 export "SSI_CE_ is high valid and SSI_CE2_ is high valid"
const SSI_CR1_TFVCK_BIT 28
register CR1 int TFVCK goto (0x3 << SSI_CR1_TFVCK_BIT)
register CR1 int TFVCK enum "0" 0
register CR1 int TFVCK enum "1" 1
register CR1 int TFVCK enum "2" 2
register CR1 int TFVCK enum "3" 3
const SSI_CR1_TCKFI_BIT 26
register CR1 int TCKFI goto (0x3 << SSI_CR1_TCKFI_BIT)
register CR1 int TCKFI enum "0" 0
register CR1 int TCKFI enum "1" 1
register CR1 int TCKFI enum "2" 2
register CR1 int TCKFI enum "3" 3
register CR1 int LFST goto 25
register CR1 int ITFRM goto 24
register CR1 int UNFIN goto 23
register CR1 int MULTS goto 22
const SSI_CR1_FMAT_BIT 20
register CR1 int FMAT goto (0x3 << SSI_CR1_FMAT_BIT)
register CR1 int FMAT enum SPI 0 export "Motorola¡¯s SPI format"
register CR1 int FMAT enum SSP 1 export "TI's SSP format"
register CR1 int FMAT enum MW1 2 export "National Microwire 1 format"
register CR1 int FMAT enum MW2 3 export "National Microwire 2 format"
const SSI_CR1_TTRG_BIT 16
register CR1 int TTRG export "SSI1 TX trigger"
register CR1 int TTRG goto (0xf << SSI_CR1_TTRG_BIT)
const SSI_CR1_MCOM_BIT 12
register CR1 int MCOM goto (0xf << SSI_CR1_MCOM_BIT)
register CR1 int MCOM enum "1BIT" 0x0 export "1-bit command selected"
register CR1 int MCOM enum "2BIT" 0x1 export "2-bit command selected"
register CR1 int MCOM enum "3BIT" 0x2 export "3-bit command selected"
register CR1 int MCOM enum "4BIT" 0x3 export "4-bit command selected"
register CR1 int MCOM enum "5BIT" 0x4 export "5-bit command selected"
register CR1 int MCOM enum "6BIT" 0x5 export "6-bit command selected"
register CR1 int MCOM enum "7BIT" 0x6 export "7-bit command selected"
register CR1 int MCOM enum "8BIT" 0x7 export "8-bit command selected"
register CR1 int MCOM enum "9BIT" 0x8 export "9-bit command selected"
register CR1 int MCOM enum "10BIT" 0x9 export "10-bit command selected"
register CR1 int MCOM enum "11BIT" 0xA export "11-bit command selected"
register CR1 int MCOM enum "12BIT" 0xB export "12-bit command selected"
register CR1 int MCOM enum "13BIT" 0xC export "13-bit command selected"
register CR1 int MCOM enum "14BIT" 0xD export "14-bit command selected"
register CR1 int MCOM enum "15BIT" 0xE export "15-bit command selected"
register CR1 int MCOM enum "16BIT" 0xF export "16-bit command selected"
const SSI_CR1_RTRG_BIT 8
register CR1 int RTRG export "SSI RX trigger"
register CR1 int RTRG goto (0xf << SSI_CR1_RTRG_BIT)
const SSI_CR1_FLEN_BIT 4
register CR1 int FLEN goto (0xf << SSI_CR1_FLEN_BIT)
register CR1 int FLEN enum "2BIT" 0x0
register CR1 int FLEN enum "3BIT" 0x1
register CR1 int FLEN enum "4BIT" 0x2
register CR1 int FLEN enum "5BIT" 0x3
register CR1 int FLEN enum "6BIT" 0x4
register CR1 int FLEN enum "7BIT" 0x5
register CR1 int FLEN enum "8BIT" 0x6
register CR1 int FLEN enum "9BIT" 0x7
register CR1 int FLEN enum "10BIT" 0x8
register CR1 int FLEN enum "11BIT" 0x9
register CR1 int FLEN enum "12BIT" 0xA
register CR1 int FLEN enum "13BIT" 0xB
register CR1 int FLEN enum "14BIT" 0xC
register CR1 int FLEN enum "15BIT" 0xD
register CR1 int FLEN enum "16BIT" 0xE
register CR1 int FLEN enum "17BIT" 0xF
register CR1 int PHA goto 1
register CR1 int POL goto 0

// 
register SR export "SSI Status Register"

// 
const SSI_SR_TFIFONUM_BIT 16
register SR int TFIFONUM goto (0xff << SSI_SR_TFIFONUM_BIT)
const SSI_SR_RFIFONUM_BIT 8
register SR int RFIFONUM goto (0xff << SSI_SR_RFIFONUM_BIT)
register SR int END goto 7
register SR int BUSY goto 6
register SR int TFF goto 5
register SR int RFE goto 4
register SR int TFHE goto 3
register SR int RFHF goto 2
register SR int UNDR goto 1
register SR int OVER goto 0

// 
register ITR export "SSI Interval Time Control Register"

// 
register ITR int CNTCLK goto 15
const SSI_ITR_IVLTM_BIT 0
register ITR int IVLTM goto (0x7fff << SSI_ITR_IVLTM_BIT)

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 
/***************************************************************************
 * SSI (Synchronous Serial Interface)
 ***************************************************************************/
/* n = 0, 1 (SSI0, SSI1) */
// #define __ssi_enable(n) 	( REG_SSI_CR0(n) |= SSI_CR0_SSIE )
// #define __ssi_disable(n) 	( REG_SSI_CR0(n) &= ~SSI_CR0_SSIE )
// #define __ssi_select_ce(n) 	( REG_SSI_CR0(n) &= ~SSI_CR0_FSEL )

// 
// #define __ssi_normal_mode(n) ( REG_SSI_ITR(n) &= ~SSI_ITR_IVLTM_MASK )

// 
// #define __ssi_select_ce2(n) 		\
// do { 					\
// 	REG_SSI_CR0(n) |= SSI_CR0_FSEL; 	\
// 	REG_SSI_CR1(n) &= ~SSI_CR1_MULTS;	\
// } while (0)

// 
// #define __ssi_select_gpc(n) 			\
// do { 						\
// 	REG_SSI_CR0(n) &= ~SSI_CR0_FSEL;	\
// 	REG_SSI_CR1(n) |= SSI_CR1_MULTS;	\
// } while (0)

// 
// #define __ssi_underrun_auto_clear(n) 		\
// do { 						\
// 	REG_SSI_CR0(n) |= SSI_CR0_EACLRUN; 	\
// } while (0)

// 
// #define __ssi_underrun_clear_manually(n) 	\
// do { 						\
// 	REG_SSI_CR0(n) &= ~SSI_CR0_EACLRUN; 	\
// } while (0)

// 
// #define __ssi_enable_tx_intr(n)					\
// 	( REG_SSI_CR0(n) |= SSI_CR0_TIE | SSI_CR0_TEIE )

// 
// #define __ssi_disable_tx_intr(n)				\
// 	( REG_SSI_CR0(n) &= ~(SSI_CR0_TIE | SSI_CR0_TEIE) )

// 
// #define __ssi_enable_rx_intr(n)					\
// 	( REG_SSI_CR0(n) |= SSI_CR0_RIE | SSI_CR0_REIE )

// 
// #define __ssi_disable_rx_intr(n)				\
// 	( REG_SSI_CR0(n) &= ~(SSI_CR0_RIE | SSI_CR0_REIE) )

// 
// #define __ssi_enable_txfifo_half_empty_intr(n)  \
// 	( REG_SSI_CR0(n) |= SSI_CR0_TIE )
// #define __ssi_disable_txfifo_half_empty_intr(n)	\
// 	( REG_SSI_CR0(n) &= ~SSI_CR0_TIE )
// #define __ssi_enable_tx_error_intr(n)		\
// 	( REG_SSI_CR0(n) |= SSI_CR0_TEIE )
// #define __ssi_disable_tx_error_intr(n)		\
// 	( REG_SSI_CR0(n) &= ~SSI_CR0_TEIE )
// #define __ssi_enable_rxfifo_half_full_intr(n)	\
// 	( REG_SSI_CR0(n) |= SSI_CR0_RIE )
// #define __ssi_disable_rxfifo_half_full_intr(n)  \
// 	( REG_SSI_CR0(n) &= ~SSI_CR0_RIE )
// #define __ssi_enable_rx_error_intr(n)		\
// 	( REG_SSI_CR0(n) |= SSI_CR0_REIE )
// #define __ssi_disable_rx_error_intr(n)		\
// 	( REG_SSI_CR0(n) &= ~SSI_CR0_REIE )

// 
// #define __ssi_enable_loopback(n)  ( REG_SSI_CR0(n) |= SSI_CR0_LOOP )
// #define __ssi_disable_loopback(n) ( REG_SSI_CR0(n) &= ~SSI_CR0_LOOP )

// 
// #define __ssi_enable_receive(n)   ( REG_SSI_CR0(n) &= ~SSI_CR0_DISREV )
// #define __ssi_disable_receive(n)  ( REG_SSI_CR0(n) |= SSI_CR0_DISREV )

// 
// #define __ssi_finish_receive(n)					\
// 	( REG_SSI_CR0(n) |= (SSI_CR0_RFINE | SSI_CR0_RFINC) )

// 
// #define __ssi_disable_recvfinish(n)				\
// 	( REG_SSI_CR0(n) &= ~(SSI_CR0_RFINE | SSI_CR0_RFINC) )

// 
// #define __ssi_flush_txfifo(n)   	( REG_SSI_CR0(n) |= SSI_CR0_TFLUSH )
// #define __ssi_flush_rxfifo(n)   	( REG_SSI_CR0(n) |= SSI_CR0_RFLUSH )

// 
// #define __ssi_flush_fifo(n)					\
// 	( REG_SSI_CR0(n) |= SSI_CR0_TFLUSH | SSI_CR0_RFLUSH )

// 
// #define __ssi_finish_transmit(n) 	( REG_SSI_CR1(n) &= ~SSI_CR1_UNFIN )
// #define __ssi_wait_transmit(n) 		( REG_SSI_CR1(n) |= SSI_CR1_UNFIN )
// #define __ssi_use_busy_wait_mode(n) 	__ssi_wait_transmit(n)
// #define __ssi_unset_busy_wait_mode(n) 	__ssi_finish_transmit(n)

// 
// #define __ssi_spi_format(n)						\
// 	do {								\
// 		REG_SSI_CR1(n) &= ~SSI_CR1_FMAT_MASK; 			\
// 		REG_SSI_CR1(n) |= SSI_CR1_FMAT_SPI;			\
// 		REG_SSI_CR1(n) &= ~(SSI_CR1_TFVCK_MASK|SSI_CR1_TCKFI_MASK); \
// 		REG_SSI_CR1(n) |= (SSI_CR1_TFVCK_1 | SSI_CR1_TCKFI_1);	\
// 	} while (0)

// 
/* TI's SSP format, must clear SSI_CR1.UNFIN */
// #define __ssi_ssp_format(n)						\
// 	do { 								\
// 		REG_SSI_CR1(n) &= ~(SSI_CR1_FMAT_MASK | SSI_CR1_UNFIN);	\
// 		REG_SSI_CR1(n) |= SSI_CR1_FMAT_SSP;			\
// 	} while (0)

// 
/* National's Microwire format, must clear SSI_CR0.RFINE, and set max delay */
// #define __ssi_microwire_format(n)					\
// 	do {								\
// 		REG_SSI_CR1(n) &= ~SSI_CR1_FMAT_MASK; 			\
// 		REG_SSI_CR1(n) |= SSI_CR1_FMAT_MW1;			\
// 		REG_SSI_CR1(n) &= ~(SSI_CR1_TFVCK_MASK|SSI_CR1_TCKFI_MASK); \
// 		REG_SSI_CR1(n) |= (SSI_CR1_TFVCK_3 | SSI_CR1_TCKFI_3);	\
// 		REG_SSI_CR0(n) &= ~SSI_CR0_RFINE;			\
// 	} while (0)

// 
/* CE# level (FRMHL), CE# in interval time (ITFRM),
   clock phase and polarity (PHA POL),
   interval time (SSIITR), interval characters/frame (SSIICR) */

// 
/* frmhl,endian,mcom,flen,pha,pol MASK */
// #define SSICR1_MISC_MASK 					\
// 	( SSI_CR1_FRMHL_MASK | SSI_CR1_LFST | SSI_CR1_MCOM_MASK	\
// 	  | SSI_CR1_FLEN_MASK | SSI_CR1_PHA | SSI_CR1_POL )

// 
// #define __ssi_spi_set_misc(n,frmhl,endian,flen,mcom,pha,pol)		\
// 	do {								\
// 		REG_SSI_CR1(n) &= ~SSICR1_MISC_MASK;			\
// 		REG_SSI_CR1(n) |= ((frmhl) << 30) | ((endian) << 25) | 	\
// 			(((mcom) - 1) << 12) | (((flen) - 2) << 4) | 	\
// 			((pha) << 1) | (pol); 				\
// 	} while(0)

// 
/* Transfer with MSB or LSB first */
// #define __ssi_set_msb(n) ( REG_SSI_CR1(n) &= ~SSI_CR1_LFST )
// #define __ssi_set_lsb(n) ( REG_SSI_CR1(n) |= SSI_CR1_LFST )

// 
// #define __ssi_set_frame_length(n, m)					\
// 	REG_SSI_CR1(n) = (REG_SSI_CR1(n) & ~SSI_CR1_FLEN_MASK) | (((m) - 2) << 4)

// 
/* m = 1 - 16 */
// #define __ssi_set_microwire_command_length(n,m)				\
// 	( REG_SSI_CR1(n) = ((REG_SSI_CR1(n) & ~SSI_CR1_MCOM_MASK) | SSI_CR1_MCOM_##m##BIT) )

// 
/* Set the clock phase for SPI */
// #define __ssi_set_spi_clock_phase(n, m)					\
// 	( REG_SSI_CR1(n) = ((REG_SSI_CR1(n) & ~SSI_CR1_PHA) | (((m)&0x1)<< 1)))

// 
/* Set the clock polarity for SPI */
// #define __ssi_set_spi_clock_polarity(n, p)				\
// 	( REG_SSI_CR1(n) = ((REG_SSI_CR1(n) & ~SSI_CR1_POL) | ((p)&0x1)) )

// 
/* SSI tx trigger, m = i x 8 */
// #define __ssi_set_tx_trigger(n, m)				\
// 	do {							\
// 		REG_SSI_CR1(n) &= ~SSI_CR1_TTRG_MASK;		\
// 		REG_SSI_CR1(n) |= ((m)/8)<<SSI_CR1_TTRG_BIT;	\
// 	} while (0)

// 
/* SSI rx trigger, m = i x 8 */
// #define __ssi_set_rx_trigger(n, m)				\
// 	do {							\
// 		REG_SSI_CR1(n) &= ~SSI_CR1_RTRG_MASK;		\
// 		REG_SSI_CR1(n) |= ((m)/8)<<SSI_CR1_RTRG_BIT;	\
// 	} while (0)

// 
// #define __ssi_get_txfifo_count(n)					\
// 	( (REG_SSI_SR(n) & SSI_SR_TFIFONUM_MASK) >> SSI_SR_TFIFONUM_BIT )

// 
// #define __ssi_get_rxfifo_count(n)					\
// 	( (REG_SSI_SR(n) & SSI_SR_RFIFONUM_MASK) >> SSI_SR_RFIFONUM_BIT )

// 
// #define __ssi_transfer_end(n)		( REG_SSI_SR(n) & SSI_SR_END )
// #define __ssi_is_busy(n)		( REG_SSI_SR(n) & SSI_SR_BUSY )

// 
// #define __ssi_txfifo_full(n)		( REG_SSI_SR(n) & SSI_SR_TFF )
// #define __ssi_rxfifo_empty(n)		( REG_SSI_SR(n) & SSI_SR_RFE )
// #define __ssi_rxfifo_half_full(n)	( REG_SSI_SR(n) & SSI_SR_RFHF )
// #define __ssi_txfifo_half_empty(n)	( REG_SSI_SR(n) & SSI_SR_TFHE )
// #define __ssi_underrun(n)		( REG_SSI_SR(n) & SSI_SR_UNDR )
// #define __ssi_overrun(n)		( REG_SSI_SR(n) & SSI_SR_OVER )
// #define __ssi_clear_underrun(n)		( REG_SSI_SR(n) = ~SSI_SR_UNDR )
// #define __ssi_clear_overrun(n)		( REG_SSI_SR(n) = ~SSI_SR_OVER )
// #define __ssi_clear_errors(n)		( REG_SSI_SR(n) &= ~(SSI_SR_UNDR | SSI_SR_OVER) )

// 
// #define __ssi_set_clk(n, dev_clk, ssi_clk)			\
// 	( REG_SSI_GR(n) = (dev_clk) / (2*(ssi_clk)) - 1 )

// 
// #define __ssi_receive_data(n) 		REG_SSI_DR(n)
// #define __ssi_transmit_data(n, v) 	(REG_SSI_DR(n) = (v))

// 

// 
// #define __ssi_set_grdiv(n,v)			(REG_SSI_GR(n) = v)
// #define __ssi_get_grdiv(n)				(REG_SSI_GR(n))

// 
// #define __ssi_txfifo_half_empty_intr(n)  \
// 	( REG_SSI_CR0(n) & SSI_CR0_TIE )
// #define __ssi_rxfifo_half_full_intr(n)	\
// 	( REG_SSI_CR0(n) & SSI_CR0_RIE )

// 	
// #define __ssi_tx_error_intr(n)		\
// 	( REG_SSI_CR0(n) & SSI_CR0_TEIE )
// #define __ssi_rx_error_intr(n)		\
// 	( REG_SSI_CR0(n) & SSI_CR0_REIE )	

// 

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BSSI_H__ */

// 