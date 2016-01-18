/*
 * linux/include/asm-mips/mach-jz4760b/jz4760bemc.h
 *
 * JZ4760B EMC register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

// 
// #ifndef __JZ4760BEMC_H__
// #define __JZ4760BEMC_H__

// 
/* EMC (External Memory Controller) */
this class EMC goto 0xB3010000 export "EMC (External Memory Controller)"

// 

// 
/*************************************************************************
 * EMC (External Memory Controller)
 *************************************************************************/
register BCR goto 0x00 export "Bus Control Register"
register PMEMBS1 goto 0x6004 export ""
register PMEMBS0 goto 0x6008 export ""
for n 0 6
register SMCR goto<n> "0x10 + (n)*4" export "Static Memory Control Register"
// #define EMC_SMCR0	(EMC_BASE + 0x10)  /* Static Memory Control Register 0 ??? */
// #define EMC_SMCR1	(EMC_BASE + 0x14)  /* Static Memory Control Register 1 */
// #define EMC_SMCR2	(EMC_BASE + 0x18)  /* Static Memory Control Register 2 */
// #define EMC_SMCR3	(EMC_BASE + 0x1c)  /* Static Memory Control Register 3 */
// #define EMC_SMCR4	(EMC_BASE + 0x20)  /* Static Memory Control Register 4 */
// #define EMC_SMCR5	(EMC_BASE + 0x24)  /* Static Memory Control Register 5 */
// #define EMC_SMCR6	(EMC_BASE + 0x28)  /* Static Memory Control Register 6 */
for n 0 4
register SACR goto<n> "0x30 + (n)*4" export "Static Memory Bank Addr Config Reg"
// #define EMC_SACR0	(EMC_BASE + 0x30)  /* Static Memory Bank 0 Addr Config Reg */
// #define EMC_SACR1	(EMC_BASE + 0x34)  /* Static Memory Bank 1 Addr Config Reg */
// #define EMC_SACR2	(EMC_BASE + 0x38)  /* Static Memory Bank 2 Addr Config Reg */
// #define EMC_SACR3	(EMC_BASE + 0x3c)  /* Static Memory Bank 3 Addr Config Reg */
// #define EMC_SACR4	(EMC_BASE + 0x40)  /* Static Memory Bank 4 Addr Config Reg */

// 
register NFCSR goto 0x050 export "NAND Flash Control/Status Register"

// 
register DMCR goto 0x80 export "DRAM Control Register"
register RTCSR goto 0x84 export "Refresh Time Control/Status Register"
register RTCNT goto 0x88 export "Refresh Timer Counter"
register RTCOR goto 0x8c export "Refresh Time Constant Register"
for n 0 1
register DMAR goto<n> "0x90 + (n)*4" export "SDRAM Bank Addr Config Register"
// #define EMC_DMAR0	(EMC_BASE + 0x90)  /* SDRAM Bank 0 Addr Config Register */
// #define EMC_DMAR1	(EMC_BASE + 0x94)  /* SDRAM Bank 1 Addr Config Register */
register SDMR goto 0xa000 export "Mode Register of SDRAM bank"

// 
register BCR sizeof 32
register PMEMBS1 sizeof 32
register PMEMBS0 sizeof 32
register SMCR sizeof 32
// #define REG_EMC_SMCR0	REG32(EMC_SMCR0) // ???
// #define REG_EMC_SMCR1	REG32(EMC_SMCR1)
// #define REG_EMC_SMCR2	REG32(EMC_SMCR2)
// #define REG_EMC_SMCR3	REG32(EMC_SMCR3)
// #define REG_EMC_SMCR4	REG32(EMC_SMCR4)
// #define REG_EMC_SMCR5	REG32(EMC_SMCR5)
// #define REG_EMC_SMCR6	REG32(EMC_SMCR6)
register SACR sizeof 32
// #define REG_EMC_SACR0	REG32(EMC_SACR0)
// #define REG_EMC_SACR1	REG32(EMC_SACR1)
// #define REG_EMC_SACR2	REG32(EMC_SACR2)
// #define REG_EMC_SACR3	REG32(EMC_SACR3)
// #define REG_EMC_SACR4	REG32(EMC_SACR4)

// 
register NFCSR sizeof 32

// 
register DMCR sizeof 32
register RTCSR sizeof 16
register RTCNT sizeof 16
register RTCOR sizeof 16
register DMAR sizeof 32
// #define REG_EMC_DMAR0	REG32(EMC_DMAR0)
// #define REG_EMC_DMAR1	REG32(EMC_DMAR1)

// 
register BCR export "Bus Control Register"
const EMC_BCR_BT_SEL_BIT 30
register BCR int BT_SEL goto (0x3 << EMC_BCR_BT_SEL_BIT)
register BCR int PK_SEL goto 24
const EMC_BCR_BSR_BIT 2
register BCR int BSR goto (1 << EMC_BCR_BSR_BIT) export "Nand and SDRAM Bus Share Select: 0, share; 1, unshare"
register BCR int BSR enum SHARE 0
register BCR int BSR enum UNSHARE 1
register BCR int BRE goto 1
register BCR int ENDIAN goto 0

// 
register SMCR export "Static Memory Control Register"
const EMC_SMCR_STRV_BIT 24
register SMCR int STRV goto (0x0f << EMC_SMCR_STRV_BIT)
const EMC_SMCR_TAW_BIT 20
register SMCR int TAW goto (0x0f << EMC_SMCR_TAW_BIT)
const EMC_SMCR_TBP_BIT 16
register SMCR int TBP goto (0x0f << EMC_SMCR_TBP_BIT)
const EMC_SMCR_TAH_BIT 12
register SMCR int TAH goto (0x07 << EMC_SMCR_TAH_BIT)
const EMC_SMCR_TAS_BIT 8
register SMCR int TAS goto (0x07 << EMC_SMCR_TAS_BIT)
const EMC_SMCR_BW_BIT 6
register SMCR int BW goto (0x03 << EMC_SMCR_BW_BIT)
register SMCR int BW enum "8BIT" 0
register SMCR int BW enum "16BIT" 1
register SMCR int BW enum "32BIT" 2
register SMCR int BCM goto 3
const EMC_SMCR_BL_BIT 1
register SMCR int BL goto (0x03 << EMC_SMCR_BL_BIT)
register SMCR int BL enum "4" 0
register SMCR int BL enum "8" 1
register SMCR int BL enum "16" 2
register SMCR int BL enum "32" 3
register SMCR int SMT goto 0

// 
register SACR export "Static Memory Bank Addr Config Reg"
const EMC_SACR_BASE_BIT 8
register SACR int BASE goto (0xff << EMC_SACR_BASE_BIT)
const EMC_SACR_MASK_BIT 0
register SACR int MASK goto (0xff << EMC_SACR_MASK_BIT)

// 
register NFCSR export "NAND Flash Control/Status Register"
register NFCSR int NFCE4 goto 7 export "NAND Flash Enable"
register NFCSR int NFE4 goto 6 export "NAND Flash FCE# Assertion Enable"
register NFCSR int NFCE3 goto 5
register NFCSR int NFE3 goto 4
register NFCSR int NFCE2 goto 3
register NFCSR int NFE2 goto 2
register NFCSR int NFCE1 goto 1
register NFCSR int NFE1 goto 0

// 
register DMCR export "DRAM Control Register"
const EMC_DMCR_BW_BIT 31
register DMCR int BW goto (1 << EMC_DMCR_BW_BIT)
const EMC_DMCR_CA_BIT 26
register DMCR int CA goto (0x07 << EMC_DMCR_CA_BIT)
register DMCR int CA enum "8" 0
register DMCR int CA enum "9" 1
register DMCR int CA enum "10" 2
register DMCR int CA enum "11" 3
register DMCR int CA enum "12" 4
register DMCR int RMODE goto 25
register DMCR int RFSH goto 24
register DMCR int MRSET goto 23
const EMC_DMCR_RA_BIT 20
register DMCR int RA goto (0x03 << EMC_DMCR_RA_BIT)
register DMCR int RA enum "11" 0
register DMCR int RA enum "12" 1
register DMCR int RA enum "13" 2
const EMC_DMCR_BA_BIT 19
register DMCR int BA goto (1 << EMC_DMCR_BA_BIT)
register DMCR int PDM goto 18
register DMCR int EPIN goto 17
register DMCR int MBSEL goto 16
const EMC_DMCR_TRAS_BIT 13
register DMCR int TRAS goto (0x07 << EMC_DMCR_TRAS_BIT)
const EMC_DMCR_RCD_BIT 11
register DMCR int RCD goto (0x03 << EMC_DMCR_RCD_BIT)
const EMC_DMCR_TPC_BIT 8
register DMCR int TPC goto (0x07 << EMC_DMCR_TPC_BIT)
const EMC_DMCR_TRWL_BIT 5
register DMCR int TRWL goto (0x03 << EMC_DMCR_TRWL_BIT)
const EMC_DMCR_TRC_BIT 2
register DMCR int TRC goto (0x07 << EMC_DMCR_TRC_BIT)
const EMC_DMCR_TCL_BIT 0
register DMCR int TCL goto (0x03 << EMC_DMCR_TCL_BIT)

// 
register RTCSR export "Refresh Time Control/Status Register"
register RTCSR int SFR goto 8 export "self refresh flag"
register RTCSR int CMF goto 7
const EMC_RTCSR_CKS_BIT 0
register RTCSR int CKS goto (0x07 << EMC_RTCSR_CKS_BIT)
register RTCSR int CKS enum DISABLE 0
register RTCSR int CKS enum "4" 1
register RTCSR int CKS enum "16" 2
register RTCSR int CKS enum "64" 3
register RTCSR int CKS enum "256" 4
register RTCSR int CKS enum "1024" 5
register RTCSR int CKS enum "2048" 6
register RTCSR int CKS enum "4096" 7

// 
register DMAR export "SDRAM Bank Address Configuration Register"
const EMC_DMAR_BASE_BIT 8
register DMAR int BASE goto (0xff << EMC_DMAR_BASE_BIT)
const EMC_DMAR_MASK_BIT 0
register DMAR int MASK goto (0xff << EMC_DMAR_MASK_BIT)

// 
register SDMR export "Mode Register of SDRAM bank"
register SDMR int BM goto 9 export "Write Burst Mode"
const EMC_SDMR_OM_BIT 7
register SDMR int OM export "Operating Mode"
register SDMR int OM goto (3 << EMC_SDMR_OM_BIT)
register SDMR int OM enum NORMAL 0
const EMC_SDMR_CAS_BIT 4
register SDMR int CAS export "CAS Latency"
register SDMR int CAS goto (7 << EMC_SDMR_CAS_BIT)
register SDMR int CAS enum "1" 1
register SDMR int CAS enum "2" 2
register SDMR int CAS enum "3" 3
const EMC_SDMR_BT_BIT 3
register SDMR int BT export "Burst Type"
register SDMR int BT goto (1 << EMC_SDMR_BT_BIT)
register SDMR int BT enum SEQ 0 export "Sequential"
register SDMR int BT enum INT 1 export "Interleave"
const EMC_SDMR_BL_BIT 0
register SDMR int BL export "Burst Length"
register SDMR int BL goto (7 << EMC_SDMR_BL_BIT)
register SDMR int BL enum "1" 0
register SDMR int BL enum "2" 1
register SDMR int BL enum "4" 2
register SDMR int BL enum "8" 3

// 
// #define EMC_SDMR_CAS2_16BIT \
//   (EMC_SDMR_CAS_2 | EMC_SDMR_BT_SEQ | EMC_SDMR_BL_2)
// #define EMC_SDMR_CAS2_32BIT \
//   (EMC_SDMR_CAS_2 | EMC_SDMR_BT_SEQ | EMC_SDMR_BL_4)
// #define EMC_SDMR_CAS3_16BIT \
//   (EMC_SDMR_CAS_3 | EMC_SDMR_BT_SEQ | EMC_SDMR_BL_2)
// #define EMC_SDMR_CAS3_32BIT \
//   (EMC_SDMR_CAS_3 | EMC_SDMR_BT_SEQ | EMC_SDMR_BL_4)

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BEMC_H__ */

// 
