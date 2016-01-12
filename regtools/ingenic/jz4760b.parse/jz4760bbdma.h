/*
 * linux/include/asm-mips/mach-jz4760b/jz4760bbdma.h
 *
 * JZ4760B BDMA register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

// 
// #ifndef __JZ4760BBDMA_H__
// #define __JZ4760BBDMA_H__

// 
/* BDMAC (BCH & NAND DMA Controller) */
this class BDMAC goto 0xB3450000 export "BDMAC (BCH & NAND DMA Controller)"

// 

// 
for n 0 2
register DSA goto<n> "(0x00 + (n) * 0x20)" export "DMA source address"
register DTA goto<n> "(0x04 + (n) * 0x20)" export "DMA target address"
register DTC goto<n> "(0x08 + (n) * 0x20)" export "DMA transfer count"
register DRT goto<n> "(0x0c + (n) * 0x20)" export "DMA request source"
register DCS goto<n> "(0x10 + (n) * 0x20)" export "DMA control/status"
register DCM goto<n> "(0x14 + (n) * 0x20)" export "DMA command"
register DDA goto<n> "(0x18 + (n) * 0x20)" export "DMA descrpiDtor address"
register DSD goto<n> "(0x1c + (n) * 0x20)" export "DMA Stride Address"
register DNT goto<n> "(0xc0 + (n) * 0x04)" export "NAND Detect Timer"

// 
register DMAC goto 0x0300 export "DMA control register"
register DIRQP goto 0x0304 export "DMA interrupt pending"
register DDR goto 0x0308 export "DMA doorbell"
register DDRS goto 0x030C export "DMA doorbell set"
register DCKE goto 0x0310 export "DMA clock enable"
register DCKES goto 0x0314 export ""
register DCKEC goto 0x0318 export ""

// 
register DSA sizeof 32
register DTA sizeof 32
register DTC sizeof 32
register DRT sizeof 32
register DCS sizeof 32
register DCM sizeof 32
register DDA sizeof 32
register DSD sizeof 32
register DNT sizeof 32

// 
register DMAC sizeof 32
register DIRQP sizeof 32
register DDR sizeof 32
register DDRS sizeof 32
register DCKE sizeof 32
register DCKES sizeof 32
register DCKEC sizeof 32

// 
register DRT export "BDMA request source register"
const BDMAC_DRT_RS_BIT 0
register DRT int RS goto (0x3f << BDMAC_DRT_RS_BIT)
register DRT int RS enum BCH_ENC 2
register DRT int RS enum BCH_DEC 3
register DRT int RS enum NAND0 6
register DRT int RS enum NAND1 7
register DRT int RS enum AUTO 8
register DRT int RS enum EXT 12

// 
register DCS export "BDMA channel control/status register"
register DCS int NDES goto 31 export "descriptor (0) or not (1) ?"
register DCS int DES8 goto 30 export "Descriptor 8 Word"
// #define BDMAC_DCS_DES4    	(0 << 30) /* Descriptor 4 Word */
// #define BDMAC_DCS_LASTMD0    	(0 << 28) /* BCH Decoding last mode 0, there's one descriptor for decoding blcok*/
register DCS int LASTMD1 goto 28 export "BCH Decoding last mode 1, there's two descriptor for decoding blcok"
// #define BDMAC_DCS_LASTMD2    	(2 << 28) /* BCH Decoding last mode 2, there's three descriptor for decoding blcok*/
// #define BDMAC_DCS_FRBS(n)	((n) << 24)
const BDMAC_DCS_CDOA_BIT 16
register DCS int CDOA export "copy of DMA offset address"
register DCS int CDOA goto (0xff << BDMAC_DCS_CDOA_BIT)
// #define BDMAC_DCS_BERR	(0x1f << 7)  /* BCH error within this transfer, Only for channel 0 */
register DCS int BUERR goto 6 export "BCH uncorrectable error, only for channel 0"
register DCS int NSERR goto 5 export "status error, only for channel 1"
register DCS int AR goto 4 export "address error"
register DCS int TT goto 3 export "transfer terminated"
register DCS int HLT goto 2 export "DMA halted"
register DCS int BAC goto 1 export "BCH auto correction"
register DCS int EN goto 0 export "channel enable bit"

// 
register DCM export "BDMA channel command register"
register DCM int EACKS_LOW goto 31 export "External DACK Output Level Select, active low"
// #define BDMAC_DCM_EACKS_HIGH  	(0 << 31) /* External DACK Output Level Select, active high */
register DCM int EACKM_WRITE goto 30 export "External DACK Output Mode Select, output in write cycle"
// #define BDMAC_DCM_EACKM_READ 	(0 << 30) /* External DACK Output Mode Select, output in read cycle */
const BDMAC_DCM_ERDM_BIT 28
register DCM int ERDM export "External DREQ Detection Mode Select"
register DCM int ERDM goto (0x03 << BDMAC_DCM_ERDM_BIT)
register DCM int ERDM enum LOW 0
register DCM int ERDM enum FALL 1
register DCM int ERDM enum HIGH 2
register DCM int ERDM enum RISE 3
register DCM int BLAST goto 25 export "BCH last"
register DCM int SAI goto 23 export "source address increment"
register DCM int DAI goto 22 export "dest address increment"
const BDMAC_DCM_SWDH_BIT 14
register DCM int SWDH export "source port width"
register DCM int SWDH goto (0x03 << BDMAC_DCM_SWDH_BIT)
register DCM int SWDH enum "32" 0
register DCM int SWDH enum "8" 1
register DCM int SWDH enum "16" 2
const BDMAC_DCM_DWDH_BIT 12
register DCM int DWDH export "dest port width"
register DCM int DWDH goto (0x03 << BDMAC_DCM_DWDH_BIT)
register DCM int DWDH enum "32" 0
register DCM int DWDH enum "8" 1
register DCM int DWDH enum "16" 2
const BDMAC_DCM_DS_BIT 8
register DCM int DS export "transfer data size of a data unit"
register DCM int DS goto (0x07 << BDMAC_DCM_DS_BIT)
register DCM int DS enum "32BIT" 0
register DCM int DS enum "8BIT" 1
register DCM int DS enum "16BIT" 2
register DCM int DS enum "16BYTE" 3
register DCM int DS enum "32BYTE" 4
register DCM int DS enum "64BYTE" 5
register DCM int NRD goto 7 export "NAND direct read"
register DCM int NWR goto 6 export "NAND direct write"
register DCM int NAC goto 5 export "NAND AL/CL enable"
register DCM int STDE goto 2 export "Stride Disable/Enable"
register DCM int TIE goto 1 export "DMA transfer interrupt enable"
register DCM int LINK goto 0 export "descriptor link enable"

// 
register DDA export "BDMA descriptor address register"
const BDMAC_DDA_BASE_BIT 12
register DDA int BASE export "descriptor base address"
register DDA int BASE goto (0x0fffff << BDMAC_DDA_BASE_BIT)
const BDMAC_DDA_OFFSET_BIT 4
register DDA int OFFSET export "descriptor offset address"
register DDA int OFFSET goto (0x0ff << BDMAC_DDA_OFFSET_BIT)

// 
register DSD export "BDMA stride address register"
const BDMAC_DSD_TSD_BIT 16
register DSD int TSD export "target stride address"
register DSD int TSD goto (0xffff << BDMAC_DSD_TSD_BIT)
const BDMAC_DSD_SSD_BIT 0
register DSD int SSD export "source stride address"
register DSD int SSD goto (0xffff << BDMAC_DSD_SSD_BIT)

// 
register DNT export "BDMA NAND Detect timer register"
register DNT int DNTE goto 15 export "enable detect timer"
const BDMAC_DNT_DTCT_BIT 16
register DNT int DTCT export "tail counter"
register DNT int DTCT goto (0x7f << BDMAC_DNT_DTCT_BIT)
const BDMAC_DNT_DNT_BIT 0
register DNT int DNT export "detect counter"
register DNT int DNT goto (0x3f << BDMAC_DNT_DNT_BIT)

// 
register DMAC export "BDMA control register"
const BDMAC_DMAC_PR_BIT 8
register DMAC int PR export "channel priority mode"
register DMAC int PR goto (0x03 << BDMAC_DMAC_PR_BIT)
register DMAC int PR enum "01_2" 0
register DMAC int PR enum "12_0" 1
register DMAC int PR enum "20_1" 2
register DMAC int PR enum "012" 3
register DMAC int HLT goto 3 export "DMA halt flag"
register DMAC int AR goto 2 export "address error flag"
register DMAC int DMAE goto 0 export "DMA enable bit"

// 
register DIRQP export "BDMA interrupt pending register"
register DIRQP int CIRQ2 goto 2 export "irq pending status for channel 2"
register DIRQP int CIRQ1 goto 1 export "irq pending status for channel 1"
register DIRQP int CIRQ0 goto 0 export "irq pending status for channel 0"

// 
register DDR export "BDMA doorbell register"
register DDR int DB2 goto 2 export "doorbell for channel 2"
register DDR int DB1 goto 1 export "doorbell for channel 1"
register DDR int DB0 goto 0 export "doorbell for channel 0"

// 
register DDRS export "BDMA doorbell set register"
register DDRS int DBS2 goto 2 export "enable doorbell for channel 2"
register DDRS int DBS1 goto 1 export "enable doorbell for channel 1"
register DDRS int DBS0 goto 0 export "enable doorbell for channel 0"

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 

// 
/***************************************************************************
 * BCH & NAND DMAC
 ***************************************************************************/

// 
for n 0 2

// 
// #define __bdmac_test_halt_error ( REG_BDMAC_DMAC & BDMAC_DMAC_HLT )
// #define __bdmac_test_addr_error ( REG_BDMAC_DMAC & BDMAC_DMAC_AR )

// 
// #define __bdmac_channel_enable_clk(n)           \
// 	REG_BDMAC_DCKES |= 1 << (n);

// 
// #define __bdmac_enable_descriptor(n) \
//   ( REG_BDMAC_DCS((n)) &= ~BDMAC_DCS_NDES )
// #define __bdmac_disable_descriptor(n) \
//   ( REG_BDMAC_DCS((n)) |= BDMAC_DCS_NDES )

// 
// #define __bdmac_enable_channel(n)                 \
// do {                                             \
// 	REG_BDMAC_DCS((n)) |= BDMAC_DCS_EN;    \
// } while (0)
// #define __bdmac_disable_channel(n)                \
// do {                                             \
// 	REG_BDMAC_DCS((n)) &= ~BDMAC_DCS_EN;   \
// } while (0)

// 
// #define __bdmac_channel_enable_irq(n) \
//   ( REG_BDMAC_DCM((n)) |= BDMAC_DCM_TIE )
// #define __bdmac_channel_disable_irq(n) \
//   ( REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_TIE )

// 
// #define __bdmac_channel_transmit_halt_detected(n) \
//   (  REG_BDMAC_DCS((n)) & BDMAC_DCS_HLT )
// #define __bdmac_channel_transmit_end_detected(n) \
//   (  REG_BDMAC_DCS((n)) & BDMAC_DCS_TT )
/* Nand ops status error, only for channel 1 */
// #define __bdmac_channel_status_error_detected() \
//   (  REG_BDMAC_DCS(1) & BDMAC_DCS_NSERR )
// #define __bdmac_channel_address_error_detected(n) \
//   (  REG_BDMAC_DCS((n)) & BDMAC_DCS_AR )
// #define __bdmac_channel_count_terminated_detected(n) \
//   (  REG_BDMAC_DCS((n)) & BDMAC_DCS_CT )
// #define __bdmac_channel_descriptor_invalid_detected(n) \
//   (  REG_BDMAC_DCS((n)) & BDMAC_DCS_INV )
// #define __bdmac_BCH_error_detected(n) \
//   (  REG_BDMAC_DCS((n)) & BDMAC_DCS_BERR )

// 
// #define __bdmac_channel_clear_transmit_halt(n)				\
// 	do {								\
// 		/* clear both channel halt error and globle halt error */ \
// 		REG_BDMAC_DCS(n) &= ~BDMAC_DCS_HLT;			\
// 		REG_BDMAC_DMAC &= ~BDMAC_DMAC_HLT;	\
// 	} while (0)
// #define __bdmac_channel_clear_transmit_end(n) \
//   (  REG_BDMAC_DCS(n) &= ~BDMAC_DCS_TT )
// #define __bdmac_channel_clear_status_error() \
//   ( REG_BDMAC_DCS(1) &= ~BDMAC_DCS_NSERR )
// #define __bdmac_channel_clear_address_error(n)				\
// 	do {								\
// 		REG_BDMAC_DDA(n) = 0; /* clear descriptor address register */ \
// 		REG_BDMAC_DSA(n) = 0; /* clear source address register */ \
// 		REG_BDMAC_DTA(n) = 0; /* clear target address register */ \
// 		/* clear both channel addr error and globle address error */ \
// 		REG_BDMAC_DCS(n) &= ~BDMAC_DCS_AR;			\
// 		REG_BDMAC_DMAC &= ~BDMAC_DMAC_AR;	\
// 	} while (0)
// #define __bdmac_channel_clear_count_terminated(n) \
//   (  REG_BDMAC_DCS((n)) &= ~BDMAC_DCS_CT )
// #define __bdmac_channel_clear_descriptor_invalid(n) \
//   (  REG_BDMAC_DCS((n)) &= ~BDMAC_DCS_INV )

// 
// #define __bdmac_channel_set_transfer_unit_32bit(n)	\
// do {							\
// 	REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_DS_MASK;	\
// 	REG_BDMAC_DCM((n)) |= BDMAC_DCM_DS_32BIT;	\
// } while (0)

// 
// #define __bdmac_channel_set_transfer_unit_16bit(n)	\
// do {							\
// 	REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_DS_MASK;	\
// 	REG_BDMAC_DCM((n)) |= BDMAC_DCM_DS_16BIT;	\
// } while (0)

// 
// #define __bdmac_channel_set_transfer_unit_8bit(n)	\
// do {							\
// 	REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_DS_MASK;	\
// 	REG_BDMAC_DCM((n)) |= BDMAC_DCM_DS_8BIT;	\
// } while (0)

// 
// #define __bdmac_channel_set_transfer_unit_16byte(n)	\
// do {							\
// 	REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_DS_MASK;	\
// 	REG_BDMAC_DCM((n)) |= BDMAC_DCM_DS_16BYTE;	\
// } while (0)

// 
// #define __bdmac_channel_set_transfer_unit_32byte(n)	\
// do {							\
// 	REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_DS_MASK;	\
// 	REG_BDMAC_DCM((n)) |= BDMAC_DCM_DS_32BYTE;	\
// } while (0)

// 
/* w=8,16,32 */
// #define __bdmac_channel_set_dest_port_width(n,w)		\
// do {							\
// 	REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_DWDH_MASK;	\
// 	REG_BDMAC_DCM((n)) |= BDMAC_DCM_DWDH_##w;	\
// } while (0)

// 
/* w=8,16,32 */
// #define __bdmac_channel_set_src_port_width(n,w)		\
// do {							\
// 	REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_SWDH_MASK;	\
// 	REG_BDMAC_DCM((n)) |= BDMAC_DCM_SWDH_##w;	\
// } while (0)

// 
// #define __bdmac_channel_dest_addr_fixed(n) \
// 	(REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_DAI)
// #define __bdmac_channel_dest_addr_increment(n) \
// 	(REG_BDMAC_DCM((n)) |= BDMAC_DCM_DAI)

// 
// #define __bdmac_channel_src_addr_fixed(n) \
// 	(REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_SAI)
// #define __bdmac_channel_src_addr_increment(n) \
// 	(REG_BDMAC_DCM((n)) |= BDMAC_DCM_SAI)

// 
// #define __bdmac_channel_set_doorbell(n)	\
// 	(REG_BDMAC_DDRS = (1 << (n)))

// 
// #define __bdmac_channel_irq_detected(n)  (REG_BDMAC_DIRQP & (1 << (n)))
// #define __bdmac_channel_ack_irq(n)       (REG_BDMAC_DIRQP &= ~(1 <<(n)))

// 
// static __inline__ int __bdmac_get_irq(void)
// {
// 	int i;
// 	for (i = 0; i < MAX_BDMA_NUM; i++)
// 		if (__bdmac_channel_irq_detected(i))
// 			return i;
// 	return -1;
// }

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BBDMA_H__ */

// 
