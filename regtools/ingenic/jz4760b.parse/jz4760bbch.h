/*
 * linux/include/asm-mips/mach-jz4760b/jz4760bbch.h
 *
 * JZ4760B bch register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

// 
// #ifndef __JZ4760BBCH_H__
// #define __JZ4760BBCH_H__

// 

// 
this class BCH goto 0xB34D0000

// 
/*************************************************************************
 * BCH
 *************************************************************************/
register CR goto 0x00 export "BCH Control register"
register CRS goto 0x04 export "BCH Control Set register"
register CRC goto 0x08 export "BCH Control Clear register"
register CNT goto 0x0C export "BCH ENC/DEC Count register"
register DR goto 0x10 export "BCH data register"
for n 0 11
register PAR goto<n> "0x14 + 4 *(n)" export "BCH Parity register"
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
for n 0 11
register ERR goto<n> "0x3C + 4*(n)" export "BCH Error Report register"
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
register INTS goto 0x6C export "BCH Interrupt Status register"
register INTE goto 0x70 export "BCH Interrupt Enable register"
register INTES goto 0x74 export "BCH Interrupt Set register"
register INTEC goto 0x78 export "BCH Interrupt Clear register"

// 
register CR sizeof 32
register CRS sizeof 32
register CRC sizeof 32
register CNT sizeof 32
register DR sizeof 8
register PAR sizeof 32
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
register ERR sizeof 32
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
register INTS sizeof 32
register INTE sizeof 32
register INTEC sizeof 32
register INTES sizeof 32

// 
register INTES export "BCH Interrupt Enable Set Register"
register INTES int ALL_FES goto 4
register INTES int DECFES goto 3
register INTES int ENCFES goto 2
register INTES int UNCORES goto 1
register INTES int ERRES goto 0

// 
register INTEC export "BCH Interrupt Enable Clear Register"
register INTEC int ALL_FEC goto 4
register INTEC int DECFEC goto 3
register INTEC int ENCFEC goto 2
register INTEC int UNCOREC goto 1
register INTEC int ERREC goto 0

// 
/* BCH Control Register*/
/* BCH Control Register*/
register CR int DMAE goto 7 export "BCH DMA Enable"
const BCH_CR_BSEL_BIT 3
register CR int BSEL goto (0x7 << BCH_CR_BSEL_BIT)
register CR int BSEL enum "4" 0x0 export "4 Bit BCH Select"
register CR int BSEL enum "8" 0x1 export "8 Bit BCH Select"
register CR int BSEL enum "12" 0x2 export "12 Bit BCH Select"
register CR int BSEL enum "16" 0x3 export "16 Bit BCH Select"
register CR int BSEL enum "20" 0x4 export "20 Bit BCH Select"
register CR int BSEL enum "24" 0x5 export "24 Bit BCH Select"
register CR int ENCE goto 2 export "BCH Encoding Select"
// #define	BCH_CR_DECE              (0 << 2)  /* BCH Decoding Select */
register CR int BRST goto 1 export "BCH Reset"
register CR int BCHE goto 0 export "BCH Enable"

// 
register INTS export "BCH Interrupt Status Register"
const BCH_INTS_ERRC_BIT 27
register INTS int ERRC goto (0x1f << BCH_INTS_ERRC_BIT)
register INTS int ALL0 goto 5
register INTS int ALLf goto 4
register INTS int DECF goto 3
register INTS int ENCF goto 2
register INTS int UNCOR goto 1
register INTS int ERR goto 0

// 
register CNT export "BCH ENC/DEC Count Register"
const BCH_CNT_DEC_BIT 16
register CNT int DEC goto (0x7ff << BCH_CNT_DEC_BIT)
const BCH_CNT_ENC_BIT 0
register CNT int ENC goto (0x7ff << BCH_CNT_ENC_BIT)

// 
register ERR export "BCH Error Report Register"
const BCH_ERR_INDEX_ODD_BIT 16
register ERR int INDEX_ODD goto (0x1fff << BCH_ERR_INDEX_ODD_BIT)
const BCH_ERR_INDEX_EVEN_BIT 0
register ERR int INDEX_EVEN goto (0x1fff << BCH_ERR_INDEX_EVEN_BIT)
const BCH_ERR_INDEX_MASK 0x1fff

// 
// #ifndef __MIPS_ASSEMBLER

// 
/*************************************************************************
 * BCH
 *************************************************************************/
// #define __ecc_encoding_4bit()						\
// do {									\
// 	REG_BCH_CRS = BCH_CR_BSEL_4 | BCH_CR_ENCE | BCH_CR_BCHE;	\
// 	REG_BCH_CRC = ~(BCH_CR_BSEL_4 | BCH_CR_ENCE | BCH_CR_BCHE);	\
// 	REG_BCH_CRS = BCH_CR_BRST;					\
// } while(0)
// #define __ecc_decoding_4bit()						\
// do {									\
// 	REG_BCH_CRS = BCH_CR_BSEL_4 | BCH_CR_DECE | BCH_CR_BCHE;	\
// 	REG_BCH_CRC = ~(BCH_CR_BSEL_4 | BCH_CR_DECE | BCH_CR_BCHE);	\
// 	REG_BCH_CRS = BCH_CR_BRST;					\
// } while(0)
// #define __ecc_encoding_8bit()                                           \
// do {				   		                        \
// 	REG_BCH_CRS = BCH_CR_BSEL_8 | BCH_CR_ENCE | BCH_CR_BCHE;	\
// 	REG_BCH_CRC = ~(BCH_CR_BSEL_8 | BCH_CR_ENCE | BCH_CR_BCHE);	\
// 	REG_BCH_CRS = BCH_CR_BRST;					\
// } while(0)
// #define __ecc_decoding_8bit()						\
// do {									\
// 	REG_BCH_CRS = BCH_CR_BSEL_8 | BCH_CR_DECE | BCH_CR_BCHE;	\
// 	REG_BCH_CRC = ~(BCH_CR_BSEL_8 | BCH_CR_DECE | BCH_CR_BCHE);	\
// 	REG_BCH_CRS = BCH_CR_BRST;					\
// } while(0)
// #define __ecc_encoding_12bit()						\
// do {									\
// 	REG_BCH_CRS = BCH_CR_BSEL_12 | BCH_CR_ENCE | BCH_CR_BCHE;	\
// 	REG_BCH_CRC = ~(BCH_CR_BSEL_12 | BCH_CR_ENCE | BCH_CR_BCHE);	\
// 	REG_BCH_CRS = BCH_CR_BRST;					\
// } while(0)
// #define __ecc_decoding_12bit()						\
// do {									\
// 	REG_BCH_CRS = BCH_CR_BSEL_12 | BCH_CR_DECE | BCH_CR_BCHE;	\
// 	REG_BCH_CRC = ~(BCH_CR_BSEL_12 | BCH_CR_DECE | BCH_CR_BCHE);	\
// 	REG_BCH_CRS = BCH_CR_BRST;					\
// } while(0)
// #define __ecc_encoding_16bit()						\
// do {									\
// 	REG_BCH_CRS = BCH_CR_BSEL_16 | BCH_CR_ENCE | BCH_CR_BCHE;	\
// 	REG_BCH_CRC = ~(BCH_CR_BSEL_16 | BCH_CR_ENCE | BCH_CR_BCHE);	\
// 	REG_BCH_CRS = BCH_CR_BRST;					\
// } while(0)
// #define __ecc_decoding_16bit()						\
// do {									\
// 	REG_BCH_CRS = BCH_CR_BSEL_16 | BCH_CR_DECE | BCH_CR_BCHE;	\
// 	REG_BCH_CRC = ~(BCH_CR_BSEL_16 | BCH_CR_DECE | BCH_CR_BCHE);	\
// 	REG_BCH_CRS = BCH_CR_BRST;					\
// } while(0)
// #define __ecc_encoding_20bit()						\
// do {									\
// 	REG_BCH_CRS = BCH_CR_BSEL_20 | BCH_CR_ENCE | BCH_CR_BCHE;	\
// 	REG_BCH_CRC = ~(BCH_CR_BSEL_20 | BCH_CR_ENCE | BCH_CR_BCHE);	\
// 	REG_BCH_CRS = BCH_CR_BRST;					\
// } while(0)
// #define __ecc_decoding_20bit()						\
// do {									\
// 	REG_BCH_CRS = BCH_CR_BSEL_20 | BCH_CR_DECE | BCH_CR_BCHE;	\
// 	REG_BCH_CRC = ~(BCH_CR_BSEL_20 | BCH_CR_DECE | BCH_CR_BCHE);	\
// 	REG_BCH_CRS = BCH_CR_BRST;					\
// } while(0)
// #define __ecc_encoding_24bit()						\
// do {									\
// 	REG_BCH_CRS = BCH_CR_BSEL_24 | BCH_CR_ENCE | BCH_CR_BCHE;	\
// 	REG_BCH_CRC = ~(BCH_CR_BSEL_24 | BCH_CR_ENCE | BCH_CR_BCHE);	\
// 	REG_BCH_CRS = BCH_CR_BRST;					\
// } while(0)
// #define __ecc_decoding_24bit()						\
// do {									\
// 	REG_BCH_CRS = BCH_CR_BSEL_24 | BCH_CR_DECE | BCH_CR_BCHE;	\
// 	REG_BCH_CRC = ~(BCH_CR_BSEL_24 | BCH_CR_DECE | BCH_CR_BCHE);	\
// 	REG_BCH_CRS = BCH_CR_BRST;					\
// } while(0)
// #define __ecc_dma_enable()        ( REG_BCH_CRS = BCH_CR_DMAE )
// #define __ecc_dma_disable()       ( REG_BCH_CRC = BCH_CR_DMAE )
// #define __ecc_disable()           ( REG_BCH_CRC = BCH_CR_BCHE )
// #define __ecc_encode_sync()       while (!(REG_BCH_INTS & BCH_INTS_ENCF))
// #define __ecc_decode_sync()       while (!(REG_BCH_INTS & BCH_INTS_DECF))

// 
// #define __bch_enc_finish()	(REG_BCH_INTS & BCH_INTS_ENCF)
// #define __bch_dec_finish()	(REG_BCH_INTS & BCH_INTS_DECF)

// 
// #define __bch_clear_enc_finish()	(REG_BCH_INTS &= ~BCH_INTS_ENCF)
// #define __bch_clear_dec_finish()	(REG_BCH_INTS &= ~BCH_INTS_DECF)

// 
// #define __ecc_cnt_dec(n)                                             \
// do {						               	     \
//         REG_BCH_CNT = (n) << BCH_CNT_DEC_BIT;                        \
// } while(0)

// 
// #define __ecc_cnt_enc(n)                                             \
// do {                                                                 \
//         REG_BCH_CNT = (n) << BCH_CNT_ENC_BIT;                        \
// } while(0)

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BBCH_H__ */

// 