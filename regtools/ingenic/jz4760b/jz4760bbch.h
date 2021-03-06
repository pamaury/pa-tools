/*
 * linux/include/asm-mips/mach-jz4760b/jz4760bbch.h
 *
 * JZ4760B bch register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

#ifndef __JZ4760BBCH_H__
#define __JZ4760BBCH_H__


#define BCH_BASE	0xB34D0000

/*************************************************************************
 * BCH
 *************************************************************************/
#define	BCH_CR         	(BCH_BASE + 0x00) /* BCH Control register */
#define	BCH_CRS       	(BCH_BASE + 0x04) /* BCH Control Set register */
#define	BCH_CRC       	(BCH_BASE + 0x08) /* BCH Control Clear register */
#define	BCH_CNT    	(BCH_BASE + 0x0C) /* BCH ENC/DEC Count register */
#define	BCH_DR     	(BCH_BASE + 0x10) /* BCH data register */
/* n (0-11) */
#define	BCH_PAR(n)    	(BCH_BASE + 0x14 + 4 *(n)) /* BCH Parity register */
// #define	BCH_PAR0    	(BCH_BASE + 0x14) /* BCH Parity 0 register */
// #define	BCH_PAR1    	(BCH_BASE + 0x18) /* BCH Parity 1 register */
// #define	BCH_PAR2    	(BCH_BASE + 0x1C) /* BCH Parity 2 register */
// #define	BCH_PAR3    	(BCH_BASE + 0x20) /* BCH Parity 3 register */
// #define	BCH_PAR4    	(BCH_BASE + 0x24) /* BCH Parity 4 register */
// #define	BCH_PAR5    	(BCH_BASE + 0x28) /* BCH Parity 5 register */
// #define	BCH_PAR6    	(BCH_BASE + 0x2C) /* BCH Parity 6 register */
// #define	BCH_PAR7    	(BCH_BASE + 0x30) /* BCH Parity 7 register */
// #define	BCH_PAR8    	(BCH_BASE + 0x34) /* BCH Parity 8 register */
// #define	BCH_PAR9    	(BCH_BASE + 0x38) /* BCH Parity 9 register */
/* n (0-11) */
#define	BCH_ERR(n)        (BCH_BASE + 0x3C + 4*(n)) /* BCH Error Report register */
// #define	BCH_ERR0        (BCH_BASE + 0x3C) /* BCH Error Report 0 register */
// #define	BCH_ERR1        (BCH_BASE + 0x40) /* BCH Error Report 1 register */
// #define	BCH_ERR2        (BCH_BASE + 0x44) /* BCH Error Report 2 register */
// #define	BCH_ERR3        (BCH_BASE + 0x48) /* BCH Error Report 3 register */
// #define	BCH_ERR4        (BCH_BASE + 0x4C) /* BCH Error Report 4 register */
// #define	BCH_ERR5        (BCH_BASE + 0x50) /* BCH Error Report 5 register */
// #define	BCH_ERR6        (BCH_BASE + 0x54) /* BCH Error Report 6 register */
// #define	BCH_ERR7        (BCH_BASE + 0x58) /* BCH Error Report 7 register */
// #define	BCH_ERR8        (BCH_BASE + 0x5C) /* BCH Error Report 8 register */
// #define	BCH_ERR9        (BCH_BASE + 0x60) /* BCH Error Report 9 register */
// #define	BCH_ERR10       (BCH_BASE + 0x64) /* BCH Error Report 10 register */
// #define	BCH_ERR11       (BCH_BASE + 0x68) /* BCH Error Report 11 register */
#define	BCH_INTS    	(BCH_BASE + 0x6C) /* BCH Interrupt Status register */
#define	BCH_INTE	(BCH_BASE + 0x70) /* BCH Interrupt Enable register */
#define	BCH_INTES       (BCH_BASE + 0x74) /* BCH Interrupt Set register */
#define	BCH_INTEC	(BCH_BASE + 0x78) /* BCH Interrupt Clear register */

#define	REG_BCH_CR      REG32(BCH_CR)
#define	REG_BCH_CRS     REG32(BCH_CRS)
#define	REG_BCH_CRC     REG32(BCH_CRC)
#define	REG_BCH_CNT     REG32(BCH_CNT)
#define	REG_BCH_DR      REG8(BCH_DR)
#define	REG_BCH_PAR(n)   REG32(BCH_PAR(n))
// #define	REG_BCH_PAR0    REG32(BCH_PAR0)
// #define	REG_BCH_PAR1    REG32(BCH_PAR1)
// #define	REG_BCH_PAR2    REG32(BCH_PAR2)
// #define	REG_BCH_PAR3    REG32(BCH_PAR3)
// #define	REG_BCH_PAR4    REG32(BCH_PAR4)
// #define	REG_BCH_PAR5    REG32(BCH_PAR5)
// #define	REG_BCH_PAR6    REG32(BCH_PAR6)
// #define	REG_BCH_PAR7    REG32(BCH_PAR7)
// #define	REG_BCH_PAR8    REG32(BCH_PAR8)
// #define	REG_BCH_PAR9    REG32(BCH_PAR9)
#define	REG_BCH_ERR(n)    REG32(BCH_ERR(n))
// #define	REG_BCH_ERR0    REG32(BCH_ERR0)
// #define	REG_BCH_ERR1    REG32(BCH_ERR1)
// #define	REG_BCH_ERR2    REG32(BCH_ERR2)
// #define	REG_BCH_ERR3    REG32(BCH_ERR3)
// #define	REG_BCH_ERR4    REG32(BCH_ERR4)
// #define	REG_BCH_ERR5    REG32(BCH_ERR5)
// #define	REG_BCH_ERR6    REG32(BCH_ERR6)
// #define	REG_BCH_ERR7    REG32(BCH_ERR7)
// #define	REG_BCH_ERR8    REG32(BCH_ERR8)
// #define	REG_BCH_ERR9    REG32(BCH_ERR9)
// #define	REG_BCH_ERR10   REG32(BCH_ERR10)
// #define	REG_BCH_ERR11   REG32(BCH_ERR11)
#define	REG_BCH_INTS    REG32(BCH_INTS)
#define	REG_BCH_INTE    REG32(BCH_INTE)
#define	REG_BCH_INTEC   REG32(BCH_INTEC)
#define	REG_BCH_INTES   REG32(BCH_INTES)

/* BCH Interrupt Enable Set Register (INTES) */
#define BCH_INTES_ALL_FES	(1 << 4)
#define BCH_INTES_DECFES	(1 << 3)
#define BCH_INTES_ENCFES	(1 << 2)
#define BCH_INTES_UNCORES	(1 << 1)
#define BCH_INTES_ERRES		(1 << 0)

/* BCH Interrupt Enable Clear Register (INTEC) */
#define BCH_INTEC_ALL_FEC	(1 << 4)
#define BCH_INTEC_DECFEC	(1 << 3)
#define BCH_INTEC_ENCFEC	(1 << 2)
#define BCH_INTEC_UNCOREC	(1 << 1)
#define BCH_INTEC_ERREC		(1 << 0)

/* BCH Control Register*/
/* BCH Control Register*/
#define	BCH_CR_DMAE              (1 << 7)  /* BCH DMA Enable */
#define	BCH_CR_BSEL_BIT          3
#define	BCH_CR_BSEL_MASK         (0x7 << BCH_CR_BSEL_BIT)
  #define BCH_CR_BSEL_4          (0x0 << BCH_CR_BSEL_BIT)  /* 4 Bit BCH Select */
  #define BCH_CR_BSEL_8          (0x1 << BCH_CR_BSEL_BIT)  /* 8 Bit BCH Select */
  #define BCH_CR_BSEL_12         (0x2 << BCH_CR_BSEL_BIT)  /* 12 Bit BCH Select */
  #define BCH_CR_BSEL_16         (0x3 << BCH_CR_BSEL_BIT)  /* 16 Bit BCH Select */
  #define BCH_CR_BSEL_20         (0x4 << BCH_CR_BSEL_BIT)  /* 20 Bit BCH Select */
  #define BCH_CR_BSEL_24         (0x5 << BCH_CR_BSEL_BIT)  /* 24 Bit BCH Select */
#define	BCH_CR_ENCE              (1 << 2)  /* BCH Encoding Select */
#define	BCH_CR_DECE              (0 << 2)  /* BCH Decoding Select */
#define	BCH_CR_BRST              (1 << 1)  /* BCH Reset */
#define	BCH_CR_BCHE              (1 << 0)  /* BCH Enable */

/* BCH Interrupt Status Register (INTS) */
#define	BCH_INTS_ERRC_BIT        27
#define	BCH_INTS_ERRC_MASK       (0x1f << BCH_INTS_ERRC_BIT)
#define	BCH_INTS_ALL0            (1 << 5)
#define	BCH_INTS_ALLf            (1 << 4)
#define	BCH_INTS_DECF            (1 << 3)
#define	BCH_INTS_ENCF            (1 << 2)
#define	BCH_INTS_UNCOR           (1 << 1)
#define	BCH_INTS_ERR             (1 << 0)

/* BCH ENC/DEC Count Register (CNT) */
#define BCH_CNT_DEC_BIT          16
#define BCH_CNT_DEC_MASK         (0x7ff << BCH_CNT_DEC_BIT)
#define BCH_CNT_ENC_BIT          0
#define BCH_CNT_ENC_MASK         (0x7ff << BCH_CNT_ENC_BIT)

/* BCH Error Report Register (ERR) */
#define BCH_ERR_INDEX_ODD_BIT    16
#define BCH_ERR_INDEX_ODD_MASK   (0x1fff << BCH_ERR_INDEX_ODD_BIT)
#define BCH_ERR_INDEX_EVEN_BIT   0
#define BCH_ERR_INDEX_EVEN_MASK  (0x1fff << BCH_ERR_INDEX_EVEN_BIT)
#define BCH_ERR_INDEX_MASK	 0x1fff

#ifndef __MIPS_ASSEMBLER

/*************************************************************************
 * BCH
 *************************************************************************/
#define __ecc_encoding_4bit()						\
do {									\
	REG_BCH_CRS = BCH_CR_BSEL_4 | BCH_CR_ENCE | BCH_CR_BCHE;	\
	REG_BCH_CRC = ~(BCH_CR_BSEL_4 | BCH_CR_ENCE | BCH_CR_BCHE);	\
	REG_BCH_CRS = BCH_CR_BRST;					\
} while(0)
#define __ecc_decoding_4bit()						\
do {									\
	REG_BCH_CRS = BCH_CR_BSEL_4 | BCH_CR_DECE | BCH_CR_BCHE;	\
	REG_BCH_CRC = ~(BCH_CR_BSEL_4 | BCH_CR_DECE | BCH_CR_BCHE);	\
	REG_BCH_CRS = BCH_CR_BRST;					\
} while(0)
#define __ecc_encoding_8bit()                                           \
do {				   		                        \
	REG_BCH_CRS = BCH_CR_BSEL_8 | BCH_CR_ENCE | BCH_CR_BCHE;	\
	REG_BCH_CRC = ~(BCH_CR_BSEL_8 | BCH_CR_ENCE | BCH_CR_BCHE);	\
	REG_BCH_CRS = BCH_CR_BRST;					\
} while(0)
#define __ecc_decoding_8bit()						\
do {									\
	REG_BCH_CRS = BCH_CR_BSEL_8 | BCH_CR_DECE | BCH_CR_BCHE;	\
	REG_BCH_CRC = ~(BCH_CR_BSEL_8 | BCH_CR_DECE | BCH_CR_BCHE);	\
	REG_BCH_CRS = BCH_CR_BRST;					\
} while(0)
#define __ecc_encoding_12bit()						\
do {									\
	REG_BCH_CRS = BCH_CR_BSEL_12 | BCH_CR_ENCE | BCH_CR_BCHE;	\
	REG_BCH_CRC = ~(BCH_CR_BSEL_12 | BCH_CR_ENCE | BCH_CR_BCHE);	\
	REG_BCH_CRS = BCH_CR_BRST;					\
} while(0)
#define __ecc_decoding_12bit()						\
do {									\
	REG_BCH_CRS = BCH_CR_BSEL_12 | BCH_CR_DECE | BCH_CR_BCHE;	\
	REG_BCH_CRC = ~(BCH_CR_BSEL_12 | BCH_CR_DECE | BCH_CR_BCHE);	\
	REG_BCH_CRS = BCH_CR_BRST;					\
} while(0)
#define __ecc_encoding_16bit()						\
do {									\
	REG_BCH_CRS = BCH_CR_BSEL_16 | BCH_CR_ENCE | BCH_CR_BCHE;	\
	REG_BCH_CRC = ~(BCH_CR_BSEL_16 | BCH_CR_ENCE | BCH_CR_BCHE);	\
	REG_BCH_CRS = BCH_CR_BRST;					\
} while(0)
#define __ecc_decoding_16bit()						\
do {									\
	REG_BCH_CRS = BCH_CR_BSEL_16 | BCH_CR_DECE | BCH_CR_BCHE;	\
	REG_BCH_CRC = ~(BCH_CR_BSEL_16 | BCH_CR_DECE | BCH_CR_BCHE);	\
	REG_BCH_CRS = BCH_CR_BRST;					\
} while(0)
#define __ecc_encoding_20bit()						\
do {									\
	REG_BCH_CRS = BCH_CR_BSEL_20 | BCH_CR_ENCE | BCH_CR_BCHE;	\
	REG_BCH_CRC = ~(BCH_CR_BSEL_20 | BCH_CR_ENCE | BCH_CR_BCHE);	\
	REG_BCH_CRS = BCH_CR_BRST;					\
} while(0)
#define __ecc_decoding_20bit()						\
do {									\
	REG_BCH_CRS = BCH_CR_BSEL_20 | BCH_CR_DECE | BCH_CR_BCHE;	\
	REG_BCH_CRC = ~(BCH_CR_BSEL_20 | BCH_CR_DECE | BCH_CR_BCHE);	\
	REG_BCH_CRS = BCH_CR_BRST;					\
} while(0)
#define __ecc_encoding_24bit()						\
do {									\
	REG_BCH_CRS = BCH_CR_BSEL_24 | BCH_CR_ENCE | BCH_CR_BCHE;	\
	REG_BCH_CRC = ~(BCH_CR_BSEL_24 | BCH_CR_ENCE | BCH_CR_BCHE);	\
	REG_BCH_CRS = BCH_CR_BRST;					\
} while(0)
#define __ecc_decoding_24bit()						\
do {									\
	REG_BCH_CRS = BCH_CR_BSEL_24 | BCH_CR_DECE | BCH_CR_BCHE;	\
	REG_BCH_CRC = ~(BCH_CR_BSEL_24 | BCH_CR_DECE | BCH_CR_BCHE);	\
	REG_BCH_CRS = BCH_CR_BRST;					\
} while(0)
#define __ecc_dma_enable()        ( REG_BCH_CRS = BCH_CR_DMAE )
#define __ecc_dma_disable()       ( REG_BCH_CRC = BCH_CR_DMAE )
#define __ecc_disable()           ( REG_BCH_CRC = BCH_CR_BCHE )
#define __ecc_encode_sync()       while (!(REG_BCH_INTS & BCH_INTS_ENCF))
#define __ecc_decode_sync()       while (!(REG_BCH_INTS & BCH_INTS_DECF))

#define __bch_enc_finish()	(REG_BCH_INTS & BCH_INTS_ENCF)
#define __bch_dec_finish()	(REG_BCH_INTS & BCH_INTS_DECF)

#define __bch_clear_enc_finish()	(REG_BCH_INTS &= ~BCH_INTS_ENCF)
#define __bch_clear_dec_finish()	(REG_BCH_INTS &= ~BCH_INTS_DECF)

#define __ecc_cnt_dec(n)                                             \
do {						               	     \
        REG_BCH_CNT = (n) << BCH_CNT_DEC_BIT;                        \
} while(0)

#define __ecc_cnt_enc(n)                                             \
do {                                                                 \
        REG_BCH_CNT = (n) << BCH_CNT_ENC_BIT;                        \
} while(0)

#endif /* __MIPS_ASSEMBLER */

#endif /* __JZ4760BBCH_H__ */

