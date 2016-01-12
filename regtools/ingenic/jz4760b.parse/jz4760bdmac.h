/*
 * linux/include/asm-mips/mach-jz4760b/jz4760bdmac.h
 *
 * JZ4760B DMAC register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

// 
// #ifndef __JZ4760BDMAC_H__
// #define __JZ4760BDMAC_H__

// 
/* DMAC (DMA Controller) */
this class DMAC goto 0xB3420000 export "DMAC (DMA Controller)"

// 

// 
const MAX_DMA_NUM 12
const MAX_MDMA_NUM 3
const MAX_BDMA_NUM 3
const HALF_DMA_NUM 6

// 
for m 0 1
for n 0 11
register DSAR goto<n> "((n)/HALF_DMA_NUM*0x100 + 0x00 + ((n)-(n)/HALF_DMA_NUM*HALF_DMA_NUM) * 0x20)" export "DMA source address"
register DTAR goto<n> "((n)/HALF_DMA_NUM*0x100 + 0x04 + ((n)-(n)/HALF_DMA_NUM*HALF_DMA_NUM) * 0x20)" export "DMA target address"
register DTCR goto<n> "((n)/HALF_DMA_NUM*0x100 + 0x08 + ((n)-(n)/HALF_DMA_NUM*HALF_DMA_NUM) * 0x20)" export "DMA transfer count"
register DRSR goto<n> "((n)/HALF_DMA_NUM*0x100 + 0x0c + ((n)-(n)/HALF_DMA_NUM*HALF_DMA_NUM) * 0x20)" export "DMA request source"
register DCCSR goto<n> "((n)/HALF_DMA_NUM*0x100 + 0x10 + ((n)-(n)/HALF_DMA_NUM*HALF_DMA_NUM) * 0x20)" export "DMA control/status"
register DCMD goto<n> "((n)/HALF_DMA_NUM*0x100 + 0x14 + ((n)-(n)/HALF_DMA_NUM*HALF_DMA_NUM) * 0x20)" export "DMA command"
register DDA goto<n> "((n)/HALF_DMA_NUM*0x100 + 0x18 + ((n)-(n)/HALF_DMA_NUM*HALF_DMA_NUM) * 0x20)" export "DMA descriptor address"
register DSD goto<n> "((n)/HALF_DMA_NUM*0x100 + 0x1c + ((n)-(n)/HALF_DMA_NUM*HALF_DMA_NUM) * 0x04)" export "DMA Stride Address"

// 
register DMACR goto<m> "0x0300 + 0x100 * (m)" export "DMA control register"
register DMAIPR goto<m> "0x0304 + 0x100 * (m)" export "DMA interrupt pending"
register DMADBR goto<m> "0x0308 + 0x100 * (m)" export "DMA doorbell"
register DMADBSR goto<m> "0x030C + 0x100 * (m)" export "DMA doorbell set"
register DMACK goto<m> "0x0310 + 0x100 * (m)" export ""
register DMACKS goto<m> "0x0314 + 0x100 * (m)" export ""
register DMACKC goto<m> "0x0318 + 0x100 * (m)" export ""

// 
register DSAR sizeof 32
register DTAR sizeof 32
register DTCR sizeof 32
register DRSR sizeof 32
register DCCSR sizeof 32
register DCMD sizeof 32
register DDA sizeof 32
register DSD sizeof 32
register DMACR sizeof 32
register DMAIPR sizeof 32
register DMADBR sizeof 32
register DMADBSR sizeof 32
register DMACK sizeof 32
register DMACKS sizeof 32
register DMACKC sizeof 32

// 
// DMA request source register
const DMAC_DRSR_RS_BIT 0
register DRSR int RS goto (0x3f << DMAC_DRSR_RS_BIT)
/* 0~7 is reserved */
register DRSR int RS enum AUTO 8
register DRSR int RS enum TSSIIN 9
/* 10 ~ 11 is reserved */
register DRSR int RS enum EXTERN 12
/* 13 is reserved */
register DRSR int RS enum UART3OUT 14
register DRSR int RS enum UART3IN 15
register DRSR int RS enum UART2OUT 16
register DRSR int RS enum UART2IN 17
register DRSR int RS enum UART1OUT 18
register DRSR int RS enum UART1IN 19
register DRSR int RS enum UART0OUT 20
register DRSR int RS enum UART0IN 21
register DRSR int RS enum SSI0OUT 22
register DRSR int RS enum SSI0IN 23
register DRSR int RS enum AICOUT 24
register DRSR int RS enum AICIN 25
register DRSR int RS enum MSC0OUT 26
register DRSR int RS enum MSC0IN 27
register DRSR int RS enum TCU 28
register DRSR int RS enum SADC 29
register DRSR int RS enum MSC1OUT 30
register DRSR int RS enum MSC1IN 31
register DRSR int RS enum SSI1OUT 32
register DRSR int RS enum SSI1IN 33
register DRSR int RS enum PMOUT 34
register DRSR int RS enum PMIN 35
register DRSR int RS enum MSC2OUT 36
register DRSR int RS enum MSC2IN 37
/* others are reserved */

// 
// DMA channel control/status register
register DCCSR int NDES goto 31 export "descriptor (0) or not (1) ?"
register DCCSR int DES8 goto 30 export "Descriptor 8 Word"
// #define DMAC_DCCSR_DES4    	(0 << 30) /* Descriptor 4 Word */
/* [29:24] reserved */
const DMAC_DCCSR_CDOA_BIT 16
register DCCSR int CDOA export "copy of DMA offset address"
register DCCSR int CDOA goto (0xff << DMAC_DCCSR_CDOA_BIT)
/* [15:5] reserved */
register DCCSR int AR goto 4 export "address error"
register DCCSR int TT goto 3 export "transfer terminated"
register DCCSR int HLT goto 2 export "DMA halted"
register DCCSR int CT goto 1 export "count terminated"
register DCCSR int EN goto 0 export "channel enable bit"

// 
// DMA channel command register
register DCMD int EACKS_LOW goto 31 export "External DACK Output Level Select, active low"
// #define DMAC_DCMD_EACKS_HIGH  	(0 << 31) /* External DACK Output Level Select, active high */
register DCMD int EACKM_WRITE goto 30 export "External DACK Output Mode Select, output in write cycle"
// #define DMAC_DCMD_EACKM_READ 	(0 << 30) /* External DACK Output Mode Select, output in read cycle */
const DMAC_DCMD_ERDM_BIT 28
register DCMD int ERDM export "External DREQ Detection Mode Select"
register DCMD int ERDM goto (0x03 << DMAC_DCMD_ERDM_BIT)
register DCMD int ERDM enum LOW 0
register DCMD int ERDM enum FALL 1
register DCMD int ERDM enum HIGH 2
register DCMD int ERDM enum RISE 3
/* [27:24] reserved */
register DCMD int SAI goto 23 export "source address increment"
register DCMD int DAI goto 22 export "dest address increment"
const DMAC_DCMD_RDIL_BIT 16
register DCMD int RDIL export "request detection interval length"
register DCMD int RDIL goto (0x0f << DMAC_DCMD_RDIL_BIT)
register DCMD int RDIL enum IGN 0
register DCMD int RDIL enum "2" 1
register DCMD int RDIL enum "4" 2
register DCMD int RDIL enum "8" 3
register DCMD int RDIL enum "12" 4
register DCMD int RDIL enum "16" 5
register DCMD int RDIL enum "20" 6
register DCMD int RDIL enum "24" 7
register DCMD int RDIL enum "28" 8
register DCMD int RDIL enum "32" 9
register DCMD int RDIL enum "48" 10
register DCMD int RDIL enum "60" 11
register DCMD int RDIL enum "64" 12
register DCMD int RDIL enum "124" 13
register DCMD int RDIL enum "128" 14
register DCMD int RDIL enum "200" 15
const DMAC_DCMD_SWDH_BIT 14
register DCMD int SWDH export "source port width"
register DCMD int SWDH goto (0x03 << DMAC_DCMD_SWDH_BIT)
register DCMD int SWDH enum "32" 0
register DCMD int SWDH enum "8" 1
register DCMD int SWDH enum "16" 2
const DMAC_DCMD_DWDH_BIT 12
register DCMD int DWDH export "dest port width"
register DCMD int DWDH goto (0x03 << DMAC_DCMD_DWDH_BIT)
register DCMD int DWDH enum "32" 0
register DCMD int DWDH enum "8" 1
register DCMD int DWDH enum "16" 2
/* bit11 reserved */
const DMAC_DCMD_DS_BIT 8
register DCMD int DS export "transfer data size of a data unit"
register DCMD int DS goto (0x07 << DMAC_DCMD_DS_BIT)
register DCMD int DS enum "32BIT" 0
register DCMD int DS enum "8BIT" 1
register DCMD int DS enum "16BIT" 2
register DCMD int DS enum "16BYTE" 3
register DCMD int DS enum "32BYTE" 4
register DCMD int DS enum "64BYTE" 5
/* [7:3] reserved */
register DCMD int STDE goto 2 export "Stride Disable/Enable"
register DCMD int TIE goto 1 export "DMA transfer interrupt enable"
register DCMD int LINK goto 0 export "descriptor link enable"

// 
// DMA descriptor address register
const DMAC_DDA_BASE_BIT 12
register DDA int BASE export "descriptor base address"
register DDA int BASE goto (0x0fffff << DMAC_DDA_BASE_BIT)
const DMAC_DDA_OFFSET_BIT 4
register DDA int OFFSET export "descriptor offset address"
register DDA int OFFSET goto (0x0ff << DMAC_DDA_OFFSET_BIT)
/* [3:0] reserved */

// 
// DMA stride address register
const DMAC_DSD_TSD_BIT 16
register DSD int TSD export "target stride address"
register DSD int TSD goto (0xffff << DMAC_DSD_TSD_BIT)
const DMAC_DSD_SSD_BIT 0
register DSD int SSD export "source stride address"
register DSD int SSD goto (0xffff << DMAC_DSD_SSD_BIT)

// 
// DMA control register
register DMACR int FMSC goto 31 export "MSC Fast DMA mode"
register DMACR int FSSI goto 30 export "SSI Fast DMA mode"
register DMACR int FTSSI goto 29 export "TSSI Fast DMA mode"
register DMACR int FUART goto 28 export "UART Fast DMA mode"
register DMACR int FAIC goto 27 export "AIC Fast DMA mode"
/* [26:10] reserved */
const DMAC_DMACR_PR_BIT 8
register DMACR int PR export "channel priority mode"
register DMACR int PR goto (0x03 << DMAC_DMACR_PR_BIT)
register DMACR int PR enum "012345" 0
register DMACR int PR enum "120345" 1
register DMACR int PR enum "230145" 2
register DMACR int PR enum "340125" 3
/* [7:4] resered */
register DMACR int HLT goto 3 export "DMA halt flag"
register DMACR int AR goto 2 export "address error flag"
/* bit1 reserved */
register DMACR int DMAE goto 0 export "DMA enable bit"

// 
// DMA doorbell register
register DMADBR int DB5 goto 5 export "doorbell for channel 5"
register DMADBR int DB4 goto 4 export "doorbell for channel 4"
register DMADBR int DB3 goto 3 export "doorbell for channel 3"
register DMADBR int DB2 goto 2 export "doorbell for channel 2"
register DMADBR int DB1 goto 1 export "doorbell for channel 1"
register DMADBR int DB0 goto 0 export "doorbell for channel 0"

// 
// DMA doorbell set register
register DMADBSR int DBS5 goto 5 export "enable doorbell for channel 5"
register DMADBSR int DBS4 goto 4 export "enable doorbell for channel 4"
register DMADBSR int DBS3 goto 3 export "enable doorbell for channel 3"
register DMADBSR int DBS2 goto 2 export "enable doorbell for channel 2"
register DMADBSR int DBS1 goto 1 export "enable doorbell for channel 1"
register DMADBSR int DBS0 goto 0 export "enable doorbell for channel 0"

// 
// DMA interrupt pending register
register DMAIPR int CIRQ5 goto 5 export "irq pending status for channel 5"
register DMAIPR int CIRQ4 goto 4 export "irq pending status for channel 4"
register DMAIPR int CIRQ3 goto 3 export "irq pending status for channel 3"
register DMAIPR int CIRQ2 goto 2 export "irq pending status for channel 2"
register DMAIPR int CIRQ1 goto 1 export "irq pending status for channel 1"
register DMAIPR int CIRQ0 goto 0 export "irq pending status for channel 0"

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 

// 
/***************************************************************************
 * DMAC
 ***************************************************************************/

// 
for m 0 11

// 
// #define __dmac_enable_module(m)						\
// 	( REG_DMAC_DMACR(m) |= DMAC_DMACR_DMAE | DMAC_DMACR_PR_012345 )
// #define __dmac_disable_module(m)			\
// 	( REG_DMAC_DMACR(m) &= ~DMAC_DMACR_DMAE )

// 
/* p=0,1,2,3 */
// #define __dmac_set_priority(m,p)					\
// 	do {								\
// 		REG_DMAC_DMACR(m) &= ~DMAC_DMACR_PR_MASK;		\
// 		REG_DMAC_DMACR(m) |= ((p) << DMAC_DMACR_PR_BIT);	\
// 	} while (0)

// 
// #define __dmac_test_halt_error(m) ( REG_DMAC_DMACR(m) & DMAC_DMACR_HLT )
// #define __dmac_test_addr_error(m) ( REG_DMAC_DMACR(m) & DMAC_DMACR_AR )

// 
// #define __dmac_channel_enable_clk(n)					\
// 	REG_DMAC_DMACKS((n)/HALF_DMA_NUM) |= 1 << ((n)-(n)/HALF_DMA_NUM*HALF_DMA_NUM);

// 
// #define __dmac_channel_clear_clk(n)					\
// 	REG_DMAC_DMACKC((n)/HALF_DMA_NUM) |= 1 << ((n)-(n)/HALF_DMA_NUM*HALF_DMA_NUM);

// 
// #define __dmac_enable_descriptor(n)			\
// 	( REG_DMAC_DCCSR((n)) &= ~DMAC_DCCSR_NDES )
// #define __dmac_disable_descriptor(n)			\
// 	( REG_DMAC_DCCSR((n)) |= DMAC_DCCSR_NDES )

// 
// #define __dmac_enable_channel(n)			\
// 	do {						\
// 		REG_DMAC_DCCSR((n)) |= DMAC_DCCSR_EN;	\
// 	} while (0)
// #define __dmac_disable_channel(n)			\
// 	do {						\
// 		REG_DMAC_DCCSR((n)) &= ~DMAC_DCCSR_EN;	\
// 	} while (0)
// #define __dmac_channel_enabled(n)		\
// 	( REG_DMAC_DCCSR((n)) & DMAC_DCCSR_EN )

// 
// #define __dmac_channel_enable_irq(n)		\
// 	( REG_DMAC_DCMD((n)) |= DMAC_DCMD_TIE )
// #define __dmac_channel_disable_irq(n)			\
// 	( REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_TIE )

// 
// #define __dmac_channel_transmit_halt_detected(n)	\
// 	(  REG_DMAC_DCCSR((n)) & DMAC_DCCSR_HLT )
// #define __dmac_channel_transmit_end_detected(n)		\
// 	(  REG_DMAC_DCCSR((n)) & DMAC_DCCSR_TT )
// #define __dmac_channel_address_error_detected(n)	\
// 	(  REG_DMAC_DCCSR((n)) & DMAC_DCCSR_AR )
// #define __dmac_channel_count_terminated_detected(n)	\
// 	(  REG_DMAC_DCCSR((n)) & DMAC_DCCSR_CT )
// #define __dmac_channel_descriptor_invalid_detected(n)	\
// 	(  REG_DMAC_DCCSR((n)) & DMAC_DCCSR_INV )

// 
// #define __dmac_channel_clear_transmit_halt(n)				\
// 	do {								\
// 		/* clear both channel halt error and globle halt error */ \
// 		REG_DMAC_DCCSR(n) &= ~DMAC_DCCSR_HLT;			\
// 		REG_DMAC_DMACR(n/HALF_DMA_NUM) &= ~DMAC_DMACR_HLT;	\
// 	} while (0)
// #define __dmac_channel_clear_transmit_end(n)		\
// 	(  REG_DMAC_DCCSR(n) &= ~DMAC_DCCSR_TT )
// #define __dmac_channel_clear_address_error(n)				\
// 	do {								\
// 		REG_DMAC_DDA(n) = 0; /* clear descriptor address register */ \
// 		REG_DMAC_DSAR(n) = 0; /* clear source address register */ \
// 		REG_DMAC_DTAR(n) = 0; /* clear target address register */ \
// 		/* clear both channel addr error and globle address error */ \
// 		REG_DMAC_DCCSR(n) &= ~DMAC_DCCSR_AR;			\
// 		REG_DMAC_DMACR(n/HALF_DMA_NUM) &= ~DMAC_DMACR_AR;	\
// 	} while (0)
// #define __dmac_channel_clear_count_terminated(n)	\
// 	(  REG_DMAC_DCCSR((n)) &= ~DMAC_DCCSR_CT )
// #define __dmac_channel_clear_descriptor_invalid(n)	\
// 	(  REG_DMAC_DCCSR((n)) &= ~DMAC_DCCSR_INV )

// 
// #define __dmac_channel_set_transfer_unit_32bit(n)		\
// 	do {							\
// 		REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_DS_MASK;	\
// 		REG_DMAC_DCMD((n)) |= DMAC_DCMD_DS_32BIT;	\
// 	} while (0)

// 
// #define __dmac_channel_set_transfer_unit_16bit(n)		\
// 	do {							\
// 		REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_DS_MASK;	\
// 		REG_DMAC_DCMD((n)) |= DMAC_DCMD_DS_16BIT;	\
// 	} while (0)

// 
// #define __dmac_channel_set_transfer_unit_8bit(n)		\
// 	do {							\
// 		REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_DS_MASK;	\
// 		REG_DMAC_DCMD((n)) |= DMAC_DCMD_DS_8BIT;	\
// 	} while (0)

// 
// #define __dmac_channel_set_transfer_unit_16byte(n)		\
// 	do {							\
// 		REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_DS_MASK;	\
// 		REG_DMAC_DCMD((n)) |= DMAC_DCMD_DS_16BYTE;	\
// 	} while (0)

// 
// #define __dmac_channel_set_transfer_unit_32byte(n)		\
// 	do {							\
// 		REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_DS_MASK;	\
// 		REG_DMAC_DCMD((n)) |= DMAC_DCMD_DS_32BYTE;	\
// 	} while (0)

// 
/* w=8,16,32 */
// #define __dmac_channel_set_dest_port_width(n,w)			\
// 	do {							\
// 		REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_DWDH_MASK;	\
// 		REG_DMAC_DCMD((n)) |= DMAC_DCMD_DWDH_##w;	\
// 	} while (0)

// 
/* w=8,16,32 */
// #define __dmac_channel_set_src_port_width(n,w)			\
// 	do {							\
// 		REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_SWDH_MASK;	\
// 		REG_DMAC_DCMD((n)) |= DMAC_DCMD_SWDH_##w;	\
// 	} while (0)

// 
/* v=0-15 */
// #define __dmac_channel_set_rdil(n,v)				\
// 	do {							\
// 	REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_RDIL_MASK;		\
// 	REG_DMAC_DCMD((n) |= ((v) << DMAC_DCMD_RDIL_BIT);	\
// 		      } while (0)

// 
// #define __dmac_channel_dest_addr_fixed(n)		\
// 	(  REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_DAI )
// #define __dmac_channel_dest_addr_increment(n)		\
// 	(  REG_DMAC_DCMD((n)) |= DMAC_DCMD_DAI )

// 
// #define __dmac_channel_src_addr_fixed(n)		\
// 	(  REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_SAI )
// #define __dmac_channel_src_addr_increment(n)		\
// 	(  REG_DMAC_DCMD((n)) |= DMAC_DCMD_SAI )

// 
// #define __dmac_channel_set_doorbell(n)					\
// 	(  REG_DMAC_DMADBSR((n)/HALF_DMA_NUM) = (1 << ((n)-(n)/HALF_DMA_NUM*HALF_DMA_NUM)) )

// 
// #define __dmac_channel_irq_detected(n)  ( REG_DMAC_DMAIPR((n)/HALF_DMA_NUM) & (1 << ((n)-(n)/HALF_DMA_NUM*HALF_DMA_NUM)) )
// #define __dmac_channel_ack_irq(n)       ( REG_DMAC_DMAIPR((n)/HALF_DMA_NUM) &= ~(1 <<((n)-(n)/HALF_DMA_NUM*HALF_DMA_NUM)) )

// 
// static __inline__ int __dmac_get_irq(void)
// {
// 	int i;
// 	for (i = 0; i < MAX_DMA_NUM; i++)
// 		if (__dmac_channel_irq_detected(i))
// 			return i;
// 	return -1;
// }

// 

// 

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BDMAC_H__ */

// 
