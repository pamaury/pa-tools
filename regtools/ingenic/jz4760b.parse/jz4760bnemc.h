/*
 * linux/include/asm-mips/mach-jz4760b/jz4760bnemc.h
 *
 * JZ4760B NEMC register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

// 
// #ifndef __JZ4760BNEMC_H__
// #define __JZ4760BNEMC_H__

// 

// 
this class NEMC goto 0xB3410000

// 
/*************************************************************************
 * NEMC (External Memory Controller for NAND)
 *************************************************************************/

// 
register NFCSR goto 0x050 export "NAND Flash Control/Status Register"
register SMCR goto (1,0x14) export "Static Memory Control Register 1"
register SMCR goto (2,0x18) export ""
register SMCR goto (3,0x1c) export ""
register SMCR goto (4,0x20) export ""
register SMCR goto (5,0x24) export ""
register SMCR goto (6,0x28) export ""
register SACR goto (1,0x34) export ""
register SACR goto (2,0x38) export ""
register SACR goto (3,0x3c) export ""
register SACR goto (4,0x40) export ""
register SACR goto (5,0x44) export ""
register SACR goto (6,0x48) export ""

// 
register NFCSR sizeof 32
register SMCR sizeof 32
// #define REG_NEMC_SMCR1	REG32(NEMC_SMCR1)
// #define REG_NEMC_SMCR2	REG32(NEMC_SMCR2)
// #define REG_NEMC_SMCR3	REG32(NEMC_SMCR3)
// #define REG_NEMC_SMCR4	REG32(NEMC_SMCR4)
// #define REG_NEMC_SMCR5	REG32(NEMC_SMCR5)
// #define REG_NEMC_SMCR6	REG32(NEMC_SMCR6)
register SACR sizeof 32
// #define REG_NEMC_SACR1	REG32(NEMC_SACR1)
// #define REG_NEMC_SACR2	REG32(NEMC_SACR2)
// #define REG_NEMC_SACR3	REG32(NEMC_SACR3)
// #define REG_NEMC_SACR4	REG32(NEMC_SACR4)
// #define REG_NEMC_SACR5	REG32(NEMC_SACR5)
// #define REG_NEMC_SACR6	REG32(NEMC_SACR6)

// 
const NEMC_CS1 0xBA000000
const NEMC_CS2 0xB8000000
const NEMC_CS3 0xB7000000
const NEMC_CS4 0xB6000000
const NEMC_CS5 0xB5000000
const NEMC_CS6 0xB4000000

// 
// PN(bit 0):0-disable, 1-enable
// PN(bit 1):0-no reset, 1-reset
// (bit 2):Reserved
// BITCNT(bit 3):0-disable, 1-enable
// BITCNT(bit 4):0-calculate, 1's number, 1-calculate 0's number
// BITCNT(bit 5):0-no reset, 1-reset bitcnt
register PNCR goto 0x100 export ""
register PNDR goto 0x104 export ""
register BITCNT goto 0x108 export ""

// 
register PNCR sizeof 32
register PNDR sizeof 32
register BITCNT sizeof 32

// 
//#define REG_NEMC_SMCR	REG32(NEMC_SMCR)

// 
/* Static Memory Control Register */
const NEMC_SMCR_STRV_BIT 24
register SMCR int STRV goto (0x1f << NEMC_SMCR_STRV_BIT)
const NEMC_SMCR_TAW_BIT 20
register SMCR int TAW goto (0x0f << NEMC_SMCR_TAW_BIT)
const NEMC_SMCR_TBP_BIT 16
register SMCR int TBP goto (0x0f << NEMC_SMCR_TBP_BIT)
const NEMC_SMCR_TAH_BIT 12
register SMCR int TAH goto (0x0f << NEMC_SMCR_TAH_BIT)
const NEMC_SMCR_TAS_BIT 8
register SMCR int TAS goto (0x0f << NEMC_SMCR_TAS_BIT)
const NEMC_SMCR_BW_BIT 6
register SMCR int BW goto (0x03 << NEMC_SMCR_BW_BIT)
register SMCR int BW enum "8BIT" 0
register SMCR int BW enum "16BIT" 1
const NEMC_SMCR_BL_BIT 1
register SMCR int BL goto (0x03 << NEMC_SMCR_BL_BIT)
register SMCR int BL enum "4" 0
register SMCR int BL enum "8" 1
register SMCR int BL enum "16" 2
register SMCR int BL enum "32" 3
register SMCR int SMT goto 0

// 
/* Static Memory Bank Addr Config Reg */
const NEMC_SACR_BASE_BIT 8
register SACR int BASE goto (0xff << NEMC_SACR_BASE_BIT)
const NEMC_SACR_MASK_BIT 0
register SACR int MASK goto (0xff << NEMC_SACR_MASK_BIT)

// 
/* NAND Flash Control/Status Register */
register NFCSR int NFCE4 goto 7 export "NAND Flash Enable"
register NFCSR int NFE4 goto 6 export "NAND Flash FCE# Assertion Enable"
register NFCSR int NFCE3 goto 5
register NFCSR int NFE3 goto 4
register NFCSR int NFCE2 goto 3
register NFCSR int NFE2 goto 2
register NFCSR int NFCE1 goto 1
register NFCSR int NFE1 goto 0

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BNEMC_H__ */

// 