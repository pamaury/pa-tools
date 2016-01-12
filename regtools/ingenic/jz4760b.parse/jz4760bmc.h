/*
 * jz4760bmc.h
 * JZ4760B MC register definition
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 *
 * Author: whxu@ingenic.cn
 */

// 
// #ifndef __JZ4760BMC_H__
// #define __JZ4760BMC_H__

// 

// 
/*
 * Motion compensation module(MC) address definition
 */
this class MC goto 0xb3250000

// 

// 
/*
 * MC registers offset address definition
 */
const MC_MCCR_OFFSET 0x00
const MC_MCSR_OFFSET 0x04
const MC_MCRBAR_OFFSET 0x08
const MC_MCT1LFCR_OFFSET 0x0c
const MC_MCT2LFCR_OFFSET 0x10
const MC_MCCBAR_OFFSET 0x14
const MC_MCIIR_OFFSET 0x18
const MC_MCSIR_OFFSET 0x1c
const MC_MCT1MFCR_OFFSET 0x20
const MC_MCT2MFCR_OFFSET 0x24
const MC_MCFGIR_OFFSET 0x28
const MC_MCFCIR_OFFSET 0x2c
const MC_MCRNDTR_OFFSET 0x40

// 
const MC_MC2CR_OFFSET 0x8000
const MC_MC2SR_OFFSET 0x8004
const MC_MC2RBAR_OFFSET 0x8008
const MC_MC2CBAR_OFFSET 0x800c
const MC_MC2IIR_OFFSET 0x8010
const MC_MC2TFCR_OFFSET 0x8014
const MC_MC2SIR_OFFSET 0x8018
const MC_MC2FCIR_OFFSET 0x801c
const MC_MC2RNDTR_OFFSET 0x8040

// 

// 
/*
 * MC registers address definition
 */
register MCCR goto MC_MCCR_OFFSET export ""
register MCSR goto MC_MCSR_OFFSET export ""
register MCRBAR goto MC_MCRBAR_OFFSET export ""
register MCT1LFCR goto MC_MCT1LFCR_OFFSET export ""
register MCT2LFCR goto MC_MCT2LFCR_OFFSET export ""
register MCCBAR goto MC_MCCBAR_OFFSET export ""
register MCIIR goto MC_MCIIR_OFFSET export ""
register MCSIR goto MC_MCSIR_OFFSET export ""
register MCT1MFCR goto MC_MCT1MFCR_OFFSET export ""
register MCT2MFCR goto MC_MCT2MFCR_OFFSET export ""
register MCFGIR goto MC_MCFGIR_OFFSET export ""
register MCFCIR goto MC_MCFCIR_OFFSET export ""
register MCRNDTR goto MC_MCRNDTR_OFFSET export ""

// 
register MC2CR goto MC_MC2CR_OFFSET export ""
register MC2SR goto MC_MC2SR_OFFSET export ""
register MC2RBAR goto MC_MC2RBAR_OFFSET export ""
register MC2CBAR goto MC_MC2CBAR_OFFSET export ""
register MC2IIR goto MC_MC2IIR_OFFSET export ""
register MC2TFCR goto MC_MC2TFCR_OFFSET export ""
register MC2SIR goto MC_MC2SIR_OFFSET export ""
register MC2FCIR goto MC_MC2FCIR_OFFSET export ""
register MC2RNDTR goto MC_MC2RNDTR_OFFSET export ""

// 

// 
/*
 * MC registers common define
 */

// 
register MCCR export "MC Control Register"
// #define MCCR_RETE		BIT16
// #define MCCR_DIPE		BIT7
// #define MCCR_CKGEN		BIT6
// #define MCCR_FDDEN		BIT5
// #define MCCR_DINSE		BIT3
// #define MCCR_FAE		BIT2
// #define MCCR_RST		BIT1
// #define MCCR_CHEN		BIT0

// 
const MCCR_FDDPGN_LSB 8
// #define MCCR_FDDPGN_MASK	BITS_H2L(15, MCCR_FDDPGN_LSB)

// 
register MCSR export "MC Status Register"
// #define MCSR_DLEND		BIT1
// #define MCSR_BKLEND		BIT0

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 

// 
// #define REG_MC_MCCR		REG32(REG_MC_MCCR)
// #define REG_MC_MCSR             REG32(REG_MC_MCSR)
// #define REG_MC_MCRBAR           REG32(REG_MC_MCRBAR)
// #define REG_MC_MCT1LFCR         REG32(REG_MC_MCT1LFCR)
// #define REG_MC_MCT2LFCR         REG32(REG_MC_MCT2LFCR)
// #define REG_MC_MCCBAR           REG32(REG_MC_MCCBAR)
// #define REG_MC_MCIIR            REG32(REG_MC_MCIIR)
// #define REG_MC_MCSIR            REG32(REG_MC_MCSIR)
// #define REG_MC_MCT1MFCR         REG32(REG_MC_MCT1MFCR)
// #define REG_MC_MCT2MFCR         REG32(REG_MC_MCT2MFCR)
// #define REG_MC_MCFGIR           REG32(REG_MC_MCFGIR)
// #define REG_MC_MCFCIR           REG32(REG_MC_MCFCIR)
// #define REG_MC_MCRNDTR          REG32(REG_MC_MCRNDTR)

// 
// #define REG_MC_MC2CR            REG32(REG_MC_MC2CR)
// #define REG_MC_MC2SR            REG32(REG_MC_MC2SR)
// #define REG_MC_MC2RBAR          REG32(REG_MC_MC2RBAR)
// #define REG_MC_MC2CBAR          REG32(REG_MC_MC2CBAR)
// #define REG_MC_MC2IIR           REG32(REG_MC_MC2IIR)
// #define REG_MC_MC2TFCR          REG32(REG_MC_MC2TFCR)
// #define REG_MC_MC2SIR           REG32(REG_MC_MC2SIR)
// #define REG_MC_MC2FCIR          REG32(REG_MC_MC2FCIR)
// #define REG_MC_MC2RNDTR         REG32(REG_MC_MC2RNDTR)

// 

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BMC_H__ */

// 
