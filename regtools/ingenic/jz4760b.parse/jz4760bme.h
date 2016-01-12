/*
 * jz4760bme.h
 * JZ4760B ME register definition
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 *
 * Author: whxu@ingenic.cn
 */

// 
// #ifndef __JZ4760BME_H__
// #define __JZ4760BME_H__

// 

// 
/*
 * Motion estimation module(ME) address definition
 */
this class ME goto 0xb3260000

// 

// 
/*
 * ME registers offset address definition
 */
const ME_MECR_OFFSET 0x00
const ME_MERBAR_OFFSET 0x04
const ME_MECBAR_OFFSET 0x08
const ME_MEDAR_OFFSET 0x0c
const ME_MERFSR_OFFSET 0x10
const ME_MECFSR_OFFSET 0x14
const ME_MEDFSR_OFFSET 0x18
const ME_MESR_OFFSET 0x1c
const ME_MEMR_OFFSET 0x20
const ME_MEFR_OFFSET 0x24

// 

// 
/*
 * ME registers address definition
 */
register MECR goto ME_MECR_OFFSET export ""
register MERBAR goto ME_MERBAR_OFFSET export ""
register MECBAR goto ME_MECBAR_OFFSET export ""
register MEDAR goto ME_MEDAR_OFFSET export ""
register MERFSR goto ME_MERFSR_OFFSET export ""
register MECFSR goto ME_MECFSR_OFFSET export ""
register MEDFSR goto ME_MEDFSR_OFFSET export ""
register MESR goto ME_MESR_OFFSET export ""
register MEMR goto ME_MEMR_OFFSET export ""
register MEFR goto ME_MEFR_OFFSET export ""

// 

// 
/*
 * ME registers common define
 */

// 
register MECR export "ME control register"
// #define MECR_FLUSH		BIT2
// #define MECR_RESET		BIT1
// #define MECR_ENABLE		BIT0

// 
register MESR export "ME settings register"
const MESR_GATE_LSB 16
// #define MESR_GATE_MASK		BITS_H2L(31, MESR_GATE_LSB)

// 
const MESR_NUM_LSB 0
// #define MESR_NUM_MASK		BITS_H2L(5, MESR_NUM_LSB)

// 
register MEMR export "ME MVD register"
const MEMR_MVDY_LSB 16
// #define MESR_MVDY_MASK		BITS_H2L(31, MEMR_MVDY_LSB)

// 
const MEMR_MVDX_LSB 0
// #define MESR_MVDX_MASK		BITS_H2L(15, MEMR_MVDX_LSB)

// 
register MEFR export "ME flag register"
// #define MEFR_INTRA		BIT1
// #define MEFR_COMPLETED		BIT0

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 
register MECR sizeof 32
register MERBAR sizeof 32
register MECBAR sizeof 32
register MEDAR sizeof 32
register MERFSR sizeof 32
register MECFSR sizeof 32
register MEDFSR sizeof 32
register MESR sizeof 32
register MEMR sizeof 32
register MEFR sizeof 32

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BME_H__ */

// 
