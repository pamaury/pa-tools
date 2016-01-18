/*
 * linux/include/asm-mips/mach-jz4760b/jz4760bbdma.h
 *
 * JZ4760B BDMA register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

#ifndef __JZ4760BBDMA_H__
#define __JZ4760BBDMA_H__

/* BDMAC (BCH & NAND DMA Controller) */
#define BDMAC_BASE  0xB3450000


/* n is the DMA channel index (0 - 2) */
#define BDMAC_DSA(n)		(BDMAC_BASE + (0x00 + (n) * 0x20)) /* DMA source address */
#define BDMAC_DTA(n)  		(BDMAC_BASE + (0x04 + (n) * 0x20)) /* DMA target address */
#define BDMAC_DTC(n)  		(BDMAC_BASE + (0x08 + (n) * 0x20)) /* DMA transfer count */
#define BDMAC_DRT(n)  		(BDMAC_BASE + (0x0c + (n) * 0x20)) /* DMA request source */
#define BDMAC_DCS(n) 		(BDMAC_BASE + (0x10 + (n) * 0x20)) /* DMA control/status */
#define BDMAC_DCM(n)  		(BDMAC_BASE + (0x14 + (n) * 0x20)) /* DMA command */
#define BDMAC_DDA(n)   		(BDMAC_BASE + (0x18 + (n) * 0x20)) /* DMA descrpiDtor address */
#define BDMAC_DSD(n)   		(BDMAC_BASE + (0x1c + (n) * 0x20)) /* DMA Stride Address */
#define BDMAC_DNT(n)  		(BDMAC_BASE + (0xc0 + (n) * 0x04)) /* NAND Detect Timer */

#define BDMAC_DMAC			(BDMAC_BASE + 0x0300) 	/* DMA control register */
#define BDMAC_DIRQP		(BDMAC_BASE + 0x0304) 	/* DMA interrupt pending */
#define BDMAC_DDR		(BDMAC_BASE + 0x0308) 	/* DMA doorbell */
#define BDMAC_DDRS		(BDMAC_BASE + 0x030C) 	/* DMA doorbell set */
#define BDMAC_DCKE  		(BDMAC_BASE + 0x0310)   /* DMA clock enable */
#define BDMAC_DCKES  		(BDMAC_BASE + 0x0314)
#define BDMAC_DCKEC  		(BDMAC_BASE + 0x0318)

#define REG_BDMAC_DSA(n)	REG32(BDMAC_DSA((n)))
#define REG_BDMAC_DTA(n)	REG32(BDMAC_DTA((n)))
#define REG_BDMAC_DTC(n)	REG32(BDMAC_DTC((n)))
#define REG_BDMAC_DRT(n)	REG32(BDMAC_DRT((n)))
#define REG_BDMAC_DCS(n)	REG32(BDMAC_DCS((n)))
#define REG_BDMAC_DCM(n)	REG32(BDMAC_DCM((n)))
#define REG_BDMAC_DDA(n)	REG32(BDMAC_DDA((n)))
#define REG_BDMAC_DSD(n)    REG32(BDMAC_DSD(n))
#define REG_BDMAC_DNT(n)	REG32(BDMAC_DNT(n))

#define REG_BDMAC_DMAC		REG32(BDMAC_DMAC)
#define REG_BDMAC_DIRQP	REG32(BDMAC_DIRQP)
#define REG_BDMAC_DDR	REG32(BDMAC_DDR)
#define REG_BDMAC_DDRS	REG32(BDMAC_DDRS)
#define REG_BDMAC_DCKE    REG32(BDMAC_DCKE)
#define REG_BDMAC_DCKES    REG32(BDMAC_DCKES)
#define REG_BDMAC_DCKEC    REG32(BDMAC_DCKEC)

// BDMA request source register (DRT)
#define BDMAC_DRT_RS_BIT	0
#define BDMAC_DRT_RS_MASK	(0x3f << BDMAC_DRT_RS_BIT)
#define BDMAC_DRT_RS_BCH_ENC	(2 << BDMAC_DRT_RS_BIT)
#define BDMAC_DRT_RS_BCH_DEC	(3 << BDMAC_DRT_RS_BIT)
#define BDMAC_DRT_RS_NAND0	(6 << BDMAC_DRT_RS_BIT)
#define BDMAC_DRT_RS_NAND1	(7 << BDMAC_DRT_RS_BIT)
#define BDMAC_DRT_RS_AUTO	(8 << BDMAC_DRT_RS_BIT)
#define BDMAC_DRT_RS_EXT	(12 << BDMAC_DRT_RS_BIT)

// BDMA channel control/status register (DCS)
#define BDMAC_DCS_NDES	(1 << 31) /* descriptor (0) or not (1) ? */
#define BDMAC_DCS_DES8    	(1 << 30) /* Descriptor 8 Word */
#define BDMAC_DCS_DES4    	(0 << 30) /* Descriptor 4 Word */
#define BDMAC_DCS_LASTMD0    	(0 << 28) /* BCH Decoding last mode 0, there's one descriptor for decoding blcok*/
#define BDMAC_DCS_LASTMD1    	(1 << 28) /* BCH Decoding last mode 1, there's two descriptor for decoding blcok*/
#define BDMAC_DCS_LASTMD2    	(2 << 28) /* BCH Decoding last mode 2, there's three descriptor for decoding blcok*/
#define BDMAC_DCS_FRBS(n)	((n) << 24)
#define BDMAC_DCS_CDOA_BIT	16        /* copy of DMA offset address */
  #define BDMAC_DCS_CDOA_MASK	(0xff << BDMAC_DCS_CDOA_BIT)
#define BDMAC_DCS_BERR_BIT	7  /* BCH error within this transfer, Only for channel 0 */
#define BDMAC_DCS_BERR_MASK	(0x1f << BDMAC_DCS_BERR_BIT)
#define BDMAC_DCS_BUERR       (1 << 6)  /* BCH uncorrectable error, only for channel 0 */
#define BDMAC_DCS_NSERR       (1 << 5)  /* status error, only for channel 1 */
#define BDMAC_DCS_AR		(1 << 4)  /* address error */
#define BDMAC_DCS_TT		(1 << 3)  /* transfer terminated */
#define BDMAC_DCS_HLT		(1 << 2)  /* DMA halted */
#define BDMAC_DCS_BAC		(1 << 1)  /* BCH auto correction */
#define BDMAC_DCS_EN		(1 << 0)  /* channel enable bit */

// BDMA channel command register (DCM)
#define BDMAC_DCM_EACKS_LOW  	(1 << 31) /* External DACK Output Level Select, active low */
#define BDMAC_DCM_EACKS_HIGH  	(0 << 31) /* External DACK Output Level Select, active high */
#define BDMAC_DCM_EACKM_WRITE 	(1 << 30) /* External DACK Output Mode Select, output in write cycle */
#define BDMAC_DCM_EACKM_READ 	(0 << 30) /* External DACK Output Mode Select, output in read cycle */
#define BDMAC_DCM_ERDM_BIT	28        /* External DREQ Detection Mode Select */
  #define BDMAC_DCM_ERDM_MASK	(0x03 << BDMAC_DCM_ERDM_BIT)
  #define BDMAC_DCM_ERDM_LOW	(0 << BDMAC_DCM_ERDM_BIT)
  #define BDMAC_DCM_ERDM_FALL	(1 << BDMAC_DCM_ERDM_BIT)
  #define BDMAC_DCM_ERDM_HIGH	(2 << BDMAC_DCM_ERDM_BIT)
  #define BDMAC_DCM_ERDM_RISE	(3 << BDMAC_DCM_ERDM_BIT)
#define BDMAC_DCM_BLAST	(1 << 25) /* BCH last */
#define BDMAC_DCM_SAI		(1 << 23) /* source address increment */
#define BDMAC_DCM_DAI		(1 << 22) /* dest address increment */
#define BDMAC_DCM_SWDH_BIT	14  /* source port width */
  #define BDMAC_DCM_SWDH_MASK	(0x03 << BDMAC_DCM_SWDH_BIT)
  #define BDMAC_DCM_SWDH_32	(0 << BDMAC_DCM_SWDH_BIT)
  #define BDMAC_DCM_SWDH_8	(1 << BDMAC_DCM_SWDH_BIT)
  #define BDMAC_DCM_SWDH_16	(2 << BDMAC_DCM_SWDH_BIT)
#define BDMAC_DCM_DWDH_BIT	12  /* dest port width */
  #define BDMAC_DCM_DWDH_MASK	(0x03 << BDMAC_DCM_DWDH_BIT)
  #define BDMAC_DCM_DWDH_32	(0 << BDMAC_DCM_DWDH_BIT)
  #define BDMAC_DCM_DWDH_8	(1 << BDMAC_DCM_DWDH_BIT)
  #define BDMAC_DCM_DWDH_16	(2 << BDMAC_DCM_DWDH_BIT)
#define BDMAC_DCM_DS_BIT	8  /* transfer data size of a data unit */
  #define BDMAC_DCM_DS_MASK	(0x07 << BDMAC_DCM_DS_BIT)
  #define BDMAC_DCM_DS_32BIT	(0 << BDMAC_DCM_DS_BIT)
  #define BDMAC_DCM_DS_8BIT	(1 << BDMAC_DCM_DS_BIT)
  #define BDMAC_DCM_DS_16BIT	(2 << BDMAC_DCM_DS_BIT)
  #define BDMAC_DCM_DS_16BYTE	(3 << BDMAC_DCM_DS_BIT)
  #define BDMAC_DCM_DS_32BYTE	(4 << BDMAC_DCM_DS_BIT)
  #define BDMAC_DCM_DS_64BYTE	(5 << BDMAC_DCM_DS_BIT)
#define BDMAC_DCM_NRD   	(1 << 7)  /* NAND direct read */
#define BDMAC_DCM_NWR   	(1 << 6)  /* NAND direct write */
#define BDMAC_DCM_NAC   	(1 << 5)  /* NAND AL/CL enable */
#define BDMAC_DCM_STDE   	(1 << 2)  /* Stride Disable/Enable */
#define BDMAC_DCM_TIE		(1 << 1)  /* DMA transfer interrupt enable */
#define BDMAC_DCM_LINK		(1 << 0)  /* descriptor link enable */

// BDMA descriptor address register (DDA)
#define BDMAC_DDA_BASE_BIT	12  /* descriptor base address */
  #define BDMAC_DDA_BASE_MASK	(0x0fffff << BDMAC_DDA_BASE_BIT)
#define BDMAC_DDA_OFFSET_BIT	4   /* descriptor offset address */
  #define BDMAC_DDA_OFFSET_MASK	(0x0ff << BDMAC_DDA_OFFSET_BIT)

// BDMA stride address register (DSD)
#define BDMAC_DSD_TSD_BIT	16	/* target stride address */
  #define BDMAC_DSD_TSD_MASK	(0xffff << BDMAC_DSD_TSD_BIT)
#define BDMAC_DSD_SSD_BIT	0	/* source stride address */
  #define BDMAC_DSD_SSD_MASK	(0xffff << BDMAC_DSD_SSD_BIT)

// BDMA NAND Detect timer register (DNT)
#define BDMAC_DNT_DNTE	(1 << 15)  /* enable detect timer */
#define BDMAC_DNT_DTCT_BIT	16 /* tail counter */
#define BDMAC_DNT_DTCT_MASK     (0x7f << BDMAC_DNT_DTCT_BIT)
#define BDMAC_DNT_DNT_BIT	0 /* detect counter */
#define BDMAC_DNT_DNT_MASK     (0x3f << BDMAC_DNT_DNT_BIT)

// BDMA control register (DMAC)
#define BDMAC_DMAC_PR_BIT	8	/* channel priority mode */
  #define BDMAC_DMAC_PR_MASK	(0x03 << BDMAC_DMAC_PR_BIT)
  #define BDMAC_DMAC_PR_01_2	(0 << BDMAC_DMAC_PR_BIT)
  #define BDMAC_DMAC_PR_12_0	(1 << BDMAC_DMAC_PR_BIT)
  #define BDMAC_DMAC_PR_20_1	(2 << BDMAC_DMAC_PR_BIT)
  #define BDMAC_DMAC_PR_012	(3 << BDMAC_DMAC_PR_BIT)
#define BDMAC_DMAC_HLT		(1 << 3)  /* DMA halt flag */
#define BDMAC_DMAC_AR		(1 << 2)  /* address error flag */
#define BDMAC_DMAC_DMAE	(1 << 0)  /* DMA enable bit */

// BDMA interrupt pending register (DIRQP)
#define BDMAC_DIRQP_CIRQ2	(1 << 2)  /* irq pending status for channel 2 */
#define BDMAC_DIRQP_CIRQ1	(1 << 1)  /* irq pending status for channel 1 */
#define BDMAC_DIRQP_CIRQ0	(1 << 0)  /* irq pending status for channel 0 */

// BDMA doorbell register (DDR)
#define BDMAC_DDR_DB2	(1 << 2)  /* doorbell for channel 2 */
#define BDMAC_DDR_DB1	(1 << 1)  /* doorbell for channel 1 */
#define BDMAC_DDR_DB0	(1 << 0)  /* doorbell for channel 0 */

// BDMA doorbell set register (DDRS)
#define BDMAC_DDRS_DBS2	(1 << 2)  /* enable doorbell for channel 2 */
#define BDMAC_DDRS_DBS1	(1 << 1)  /* enable doorbell for channel 1 */
#define BDMAC_DDRS_DBS0	(1 << 0)  /* enable doorbell for channel 0 */


#ifndef __MIPS_ASSEMBLER


/***************************************************************************
 * BCH & NAND DMAC
 ***************************************************************************/

/* n is the DMA channel index (0 - 2) */

#define __bdmac_test_halt_error ( REG_BDMAC_DMAC & BDMAC_DMAC_HLT )
#define __bdmac_test_addr_error ( REG_BDMAC_DMAC & BDMAC_DMAC_AR )

#define __bdmac_channel_enable_clk(n)           \
	REG_BDMAC_DCKES |= 1 << (n);

#define __bdmac_enable_descriptor(n) \
  ( REG_BDMAC_DCS((n)) &= ~BDMAC_DCS_NDES )
#define __bdmac_disable_descriptor(n) \
  ( REG_BDMAC_DCS((n)) |= BDMAC_DCS_NDES )

#define __bdmac_enable_channel(n)                 \
do {                                             \
	REG_BDMAC_DCS((n)) |= BDMAC_DCS_EN;    \
} while (0)
#define __bdmac_disable_channel(n)                \
do {                                             \
	REG_BDMAC_DCS((n)) &= ~BDMAC_DCS_EN;   \
} while (0)

#define __bdmac_channel_enable_irq(n) \
  ( REG_BDMAC_DCM((n)) |= BDMAC_DCM_TIE )
#define __bdmac_channel_disable_irq(n) \
  ( REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_TIE )

#define __bdmac_channel_transmit_halt_detected(n) \
  (  REG_BDMAC_DCS((n)) & BDMAC_DCS_HLT )
#define __bdmac_channel_transmit_end_detected(n) \
  (  REG_BDMAC_DCS((n)) & BDMAC_DCS_TT )
/* Nand ops status error, only for channel 1 */
#define __bdmac_channel_status_error_detected() \
  (  REG_BDMAC_DCS(1) & BDMAC_DCS_NSERR )
#define __bdmac_channel_address_error_detected(n) \
  (  REG_BDMAC_DCS((n)) & BDMAC_DCS_AR )
#define __bdmac_channel_count_terminated_detected(n) \
  (  REG_BDMAC_DCS((n)) & BDMAC_DCS_CT )
#define __bdmac_channel_descriptor_invalid_detected(n) \
  (  REG_BDMAC_DCS((n)) & BDMAC_DCS_INV )
#define __bdmac_BCH_error_detected(n) \
  (  REG_BDMAC_DCS((n)) & BDMAC_DCS_BERR )

#define __bdmac_channel_clear_transmit_halt(n)				\
	do {								\
		/* clear both channel halt error and globle halt error */ \
		REG_BDMAC_DCS(n) &= ~BDMAC_DCS_HLT;			\
		REG_BDMAC_DMAC &= ~BDMAC_DMAC_HLT;	\
	} while (0)
#define __bdmac_channel_clear_transmit_end(n) \
  (  REG_BDMAC_DCS(n) &= ~BDMAC_DCS_TT )
#define __bdmac_channel_clear_status_error() \
  ( REG_BDMAC_DCS(1) &= ~BDMAC_DCS_NSERR )
#define __bdmac_channel_clear_address_error(n)				\
	do {								\
		REG_BDMAC_DDA(n) = 0; /* clear descriptor address register */ \
		REG_BDMAC_DSA(n) = 0; /* clear source address register */ \
		REG_BDMAC_DTA(n) = 0; /* clear target address register */ \
		/* clear both channel addr error and globle address error */ \
		REG_BDMAC_DCS(n) &= ~BDMAC_DCS_AR;			\
		REG_BDMAC_DMAC &= ~BDMAC_DMAC_AR;	\
	} while (0)
#define __bdmac_channel_clear_count_terminated(n) \
  (  REG_BDMAC_DCS((n)) &= ~BDMAC_DCS_CT )
#define __bdmac_channel_clear_descriptor_invalid(n) \
  (  REG_BDMAC_DCS((n)) &= ~BDMAC_DCS_INV )

#define __bdmac_channel_set_transfer_unit_32bit(n)	\
do {							\
	REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_DS_MASK;	\
	REG_BDMAC_DCM((n)) |= BDMAC_DCM_DS_32BIT;	\
} while (0)

#define __bdmac_channel_set_transfer_unit_16bit(n)	\
do {							\
	REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_DS_MASK;	\
	REG_BDMAC_DCM((n)) |= BDMAC_DCM_DS_16BIT;	\
} while (0)

#define __bdmac_channel_set_transfer_unit_8bit(n)	\
do {							\
	REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_DS_MASK;	\
	REG_BDMAC_DCM((n)) |= BDMAC_DCM_DS_8BIT;	\
} while (0)

#define __bdmac_channel_set_transfer_unit_16byte(n)	\
do {							\
	REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_DS_MASK;	\
	REG_BDMAC_DCM((n)) |= BDMAC_DCM_DS_16BYTE;	\
} while (0)

#define __bdmac_channel_set_transfer_unit_32byte(n)	\
do {							\
	REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_DS_MASK;	\
	REG_BDMAC_DCM((n)) |= BDMAC_DCM_DS_32BYTE;	\
} while (0)

/* w=8,16,32 */
#define __bdmac_channel_set_dest_port_width(n,w)		\
do {							\
	REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_DWDH_MASK;	\
	REG_BDMAC_DCM((n)) |= BDMAC_DCM_DWDH_##w;	\
} while (0)

/* w=8,16,32 */
#define __bdmac_channel_set_src_port_width(n,w)		\
do {							\
	REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_SWDH_MASK;	\
	REG_BDMAC_DCM((n)) |= BDMAC_DCM_SWDH_##w;	\
} while (0)

#define __bdmac_channel_dest_addr_fixed(n) \
	(REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_DAI)
#define __bdmac_channel_dest_addr_increment(n) \
	(REG_BDMAC_DCM((n)) |= BDMAC_DCM_DAI)

#define __bdmac_channel_src_addr_fixed(n) \
	(REG_BDMAC_DCM((n)) &= ~BDMAC_DCM_SAI)
#define __bdmac_channel_src_addr_increment(n) \
	(REG_BDMAC_DCM((n)) |= BDMAC_DCM_SAI)

#define __bdmac_channel_set_doorbell(n)	\
	(REG_BDMAC_DDRS = (1 << (n)))

#define __bdmac_channel_irq_detected(n)  (REG_BDMAC_DIRQP & (1 << (n)))
#define __bdmac_channel_ack_irq(n)       (REG_BDMAC_DIRQP &= ~(1 <<(n)))

static __inline__ int __bdmac_get_irq(void)
{
	int i;
	for (i = 0; i < MAX_BDMA_NUM; i++)
		if (__bdmac_channel_irq_detected(i))
			return i;
	return -1;
}

#endif /* __MIPS_ASSEMBLER */

#endif /* __JZ4760BBDMA_H__ */

