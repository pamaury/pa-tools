/*
 * linux/include/asm-mips/mach-jz4760b/jz4760bmdma.h
 *
 * JZ4760B MDMA register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

// 
// #ifndef __JZ4760BMDMA_H__
// #define __JZ4760BMDMA_H__

// 

// 
/* Memory Copy DMAC */
this class MDMAC goto 0xB3030000 export "Memory Copy DMAC"

// 
/*************************************************************************
 * MDMAC (MEM Copy DMA Controller)
 *************************************************************************/

// 
for n 0 1

// 
register DSAR goto<n> "(0x00 + (n) * 0x20)" export "DMA source address"
register DTAR goto<n> "(0x04 + (n) * 0x20)" export "DMA target address"
register DTCR goto<n> "(0x08 + (n) * 0x20)" export "DMA transfer count"
register DRSR goto<n> "(0x0c + (n) * 0x20)" export "DMA request source"
register DCCSR goto<n> "(0x10 + (n) * 0x20)" export "DMA control/status"
register DCMD goto<n> "(0x14 + (n) * 0x20)" export "DMA command"
register DDA goto<n> "(0x18 + (n) * 0x20)" export "DMA descriptor address"
register DSD goto<n> "(0xc0 + (n) * 0x04)" export "DMA Stride Address"

// 
register DMACR goto 0x0300 export "DMA control register"
register DMAIPR goto 0x0304 export "DMA interrupt pending"
register DMADBR goto 0x0308 export "DMA doorbell"
register DMADBSR goto 0x030C export "DMA doorbell set"
register DMACKE goto 0x0310 export ""

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
register DMACKE sizeof 32

// 
// #ifndef __MIPS_ASSEMBLER

// 
/***************************************************************************
 * Mem Copy DMAC
 ***************************************************************************/

// 
for n 0 11

// 
// #define __mdmac_enable_module \
// 	( REG_MDMAC_DMACR |= DMAC_MDMACR_DMAE | DMAC_MDMACR_PR_012345 )
// #define __mdmac_disable_module \
// 	( REG_MDMAC_DMACR &= ~DMAC_MDMACR_DMAE )

// 
/* p=0,1,2,3 */
// #define __mdmac_set_priority(p)			\
// do {							\
// 	REG_MDMAC_DMACR &= ~DMAC_DMACR_PR_MASK;	\
// 	REG_MDMAC_DMACR |= ((p) << DMAC_DMACR_PR_BIT);	\
// } while (0)

// 
// #define __mdmac_test_halt_error ( REG_MDMAC_DMACR & DMAC_MDMACR_HLT )
// #define __mdmac_test_addr_error ( REG_MDMAC_DMACR & DMAC_MDMACR_AR )

// 
// #define __mdmac_channel_enable_clk \
// 	REG_MDMAC_DMACKE |= 1 << (n);

// 
// #define __mdmac_enable_descriptor(n) \
//   ( REG_MDMAC_DCCSR((n)) &= ~DMAC_DCCSR_NDES )
// #define __mdmac_disable_descriptor(n) \
//   ( REG_MDMAC_DCCSR((n)) |= DMAC_DCCSR_NDES )

// 
// #define __mdmac_enable_channel(n)                 \
// do {                                             \
// 	REG_MDMAC_DCCSR((n)) |= DMAC_DCCSR_EN;    \
// } while (0)
// #define __mdmac_disable_channel(n)                \
// do {                                             \
// 	REG_MDMAC_DCCSR((n)) &= ~DMAC_DCCSR_EN;   \
// } while (0)
// #define __mdmac_channel_enabled(n) \
//   ( REG_MDMAC_DCCSR((n)) & DMAC_DCCSR_EN )

// 
// #define __mdmac_channel_enable_irq(n) \
//   ( REG_MDMAC_DCMD((n)) |= DMAC_DCMD_TIE )
// #define __mdmac_channel_disable_irq(n) \
//   ( REG_DMAC_DCMD((n)) &= ~DMAC_DCMD_TIE )

// 
// #define __mdmac_channel_transmit_halt_detected(n) \
//   (  REG_MDMAC_DCCSR((n)) & DMAC_DCCSR_HLT )
// #define __mdmac_channel_transmit_end_detected(n) \
//   (  REG_MDMAC_DCCSR((n)) & DMAC_DCCSR_TT )
// #define __mdmac_channel_address_error_detected(n) \
//   (  REG_DMAC_DCCSR((n)) & DMAC_DCCSR_AR )
// #define __mdmac_channel_count_terminated_detected(n) \
//   (  REG_MDMAC_DCCSR((n)) & DMAC_DCCSR_CT )
// #define __mdmac_channel_descriptor_invalid_detected(n) \
//   (  REG_MDMAC_DCCSR((n)) & DMAC_DCCSR_INV )

// 
// #define __mdmac_channel_clear_transmit_halt(n)				\
// 	do {								\
// 		/* clear both channel halt error and globle halt error */ \
// 		REG_MDMAC_DCCSR(n) &= ~DMAC_DCCSR_HLT;			\
// 		REG_MDMAC_DMACR &= ~DMAC_DMACR_HLT;	\
// 	} while (0)
// #define __mdmac_channel_clear_transmit_end(n) \
//   (  REG_MDMAC_DCCSR(n) &= ~DMAC_DCCSR_TT )
// #define __mdmac_channel_clear_address_error(n)				\
// 	do {								\
// 		REG_MDMAC_DDA(n) = 0; /* clear descriptor address register */ \
// 		REG_MDMAC_DSAR(n) = 0; /* clear source address register */ \
// 		REG_MDMAC_DTAR(n) = 0; /* clear target address register */ \
// 		/* clear both channel addr error and globle address error */ \
// 		REG_MDMAC_DCCSR(n) &= ~DMAC_DCCSR_AR;			\
// 		REG_MDMAC_DMACR &= ~DMAC_DMACR_AR;	\
// 	} while (0)
// #define __mdmac_channel_clear_count_terminated(n) \
//   (  REG_MDMAC_DCCSR((n)) &= ~DMAC_DCCSR_CT )
// #define __mdmac_channel_clear_descriptor_invalid(n) \
//   (  REG_MDMAC_DCCSR((n)) &= ~DMAC_DCCSR_INV )

// 
// #define __mdmac_channel_set_transfer_unit_32bit(n)	\
// do {							\
// 	REG_MDMAC_DCMD((n)) &= ~DMAC_DCMD_DS_MASK;	\
// 	REG_MDMAC_DCMD((n)) |= DMAC_DCMD_DS_32BIT;	\
// } while (0)

// 
// #define __mdmac_channel_set_transfer_unit_16bit(n)	\
// do {							\
// 	REG_MDMAC_DCMD((n)) &= ~DMAC_DCMD_DS_MASK;	\
// 	REG_MDMAC_DCMD((n)) |= DMAC_DCMD_DS_16BIT;	\
// } while (0)

// 
// #define __mdmac_channel_set_transfer_unit_8bit(n)	\
// do {							\
// 	REG_MDMAC_DCMD((n)) &= ~DMAC_DCMD_DS_MASK;	\
// 	REG_MDMAC_DCMD((n)) |= DMAC_DCMD_DS_8BIT;	\
// } while (0)

// 
// #define __mdmac_channel_set_transfer_unit_16byte(n)	\
// do {							\
// 	REG_MDMAC_DCMD((n)) &= ~DMAC_DCMD_DS_MASK;	\
// 	REG_MDMAC_DCMD((n)) |= DMAC_DCMD_DS_16BYTE;	\
// } while (0)

// 
// #define __mdmac_channel_set_transfer_unit_32byte(n)	\
// do {							\
// 	REG_MDMAC_DCMD((n)) &= ~DMAC_DCMD_DS_MASK;	\
// 	REG_MDMAC_DCMD((n)) |= DMAC_DCMD_DS_32BYTE;	\
// } while (0)

// 
/* w=8,16,32 */
// #define __mdmac_channel_set_dest_port_width(n,w)		\
// do {							\
// 	REG_MDMAC_DCMD((n)) &= ~DMAC_DCMD_DWDH_MASK;	\
// 	REG_MDMAC_DCMD((n)) |= DMAC_DCMD_DWDH_##w;	\
// } while (0)

// 
/* w=8,16,32 */
// #define __mdmac_channel_set_src_port_width(n,w)		\
// do {							\
// 	REG_MDMAC_DCMD((n)) &= ~DMAC_DCMD_SWDH_MASK;	\
// 	REG_MDMAC_DCMD((n)) |= DMAC_DCMD_SWDH_##w;	\
// } while (0)

// 
/* v=0-15 */
// #define __mdmac_channel_set_rdil(n,v)				\
// do {								\
// 	REG_MDMAC_DCMD((n)) &= ~DMAC_DCMD_RDIL_MASK;		\
// 	REG_MDMAC_DCMD((n) |= ((v) << DMAC_DCMD_RDIL_BIT);	\
// } while (0)

// 
// #define __mdmac_channel_dest_addr_fixed(n) \
// 	(REG_MDMAC_DCMD((n)) &= ~DMAC_DCMD_DAI)
// #define __mdmac_channel_dest_addr_increment(n) \
// 	(REG_MDMAC_DCMD((n)) |= DMAC_DCMD_DAI)

// 
// #define __mdmac_channel_src_addr_fixed(n) \
// 	(REG_MDMAC_DCMD((n)) &= ~DMAC_DCMD_SAI)
// #define __mdmac_channel_src_addr_increment(n) \
// 	(REG_MDMAC_DCMD((n)) |= DMAC_DCMD_SAI)

// 
// #define __mdmac_channel_set_doorbell(n)	\
// 	(REG_MDMAC_DMADBSR = (1 << (n)))

// 
// #define __mdmac_channel_irq_detected(n)  (REG_MDMAC_DMAIPR & (1 << (n)))
// #define __mdmac_channel_ack_irq(n)       (REG_MDMAC_DMAIPR &= ~(1 <<(n)))

// 
// static __inline__ int __mdmac_get_irq(void)
// {
// 	int i;
// 	for (i = 0; i < MAX_MDMA_NUM; i++)
// 		if (__mdmac_channel_irq_detected(i))
// 			return i;
// 	return -1;
// }

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BMDMA_H__ */

// 
