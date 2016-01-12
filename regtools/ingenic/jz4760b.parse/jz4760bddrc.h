/*
 * linux/include/asm-mips/mach-jz4760b/jz4760bddrc.h
 *
 * JZ4760B DDRC register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

// 
// #ifndef __JZ4760BDDRC_H__
// #define __JZ4760BDDRC_H__

// 

// 
this class DDRC goto 0xB3020000

// 
/*************************************************************************
 * DDRC (DDR Controller)
 *************************************************************************/
register ST goto 0x0 export "DDR Status Register"
register CFG goto 0x4 export "DDR Configure Register"
register CTRL goto 0x8 export "DDR Control Register"
register LMR goto 0xc export "DDR Load-Mode-Register"
register TIMING1 goto 0x10 export "DDR Timing Config Register 1"
register TIMING2 goto 0x14 export "DDR Timing Config Register 2"
register REFCNT goto 0x18 export "DDR  Auto-Refresh Counter"
register DQS goto 0x1c export "DDR DQS Delay Control Register"
register DQSADJ goto 0x20 export "DDR DQS Delay Adjust Register"
for n 0 1
register MMAP goto<n> "0x24 + 4*(n)" export "DDR Memory Map Config Register"
// #define DDRC_MMAP0	(DDRC_BASE + 0x24) /* DDR Memory Map Config Register */
// #define DDRC_MMAP1	(DDRC_BASE + 0x28) /* DDR Memory Map Config Register */

// 
/* DDRC Register */
register ST sizeof 32
register CFG sizeof 32
register CTRL sizeof 32
register LMR sizeof 32
register TIMING1 sizeof 32
register TIMING2 sizeof 32
register REFCNT sizeof 32
register DQS sizeof 32
register DQSADJ sizeof 32
register MMAP sizeof 32
// #define REG_DDRC_MMAP0		REG32(DDRC_MMAP0)
// #define REG_DDRC_MMAP1		REG32(DDRC_MMAP1)

// 
/* DDRC Status Register */
register ST int ENDIAN goto 7 export "0 Little data endian, 1 Big data endian"
register ST int DPDN goto 5 export "0 DDR memory is NOT in deep-power-down state, 1 DDR memory is in deep-power-down state"
register ST int PDN goto 4 export "0 DDR memory is NOT in power-down state, 1 DDR memory is in power-down state"
register ST int AREF goto 3 export "0 DDR memory is NOT in auto-refresh state, 1 DDR memory is in auto-refresh state"
register ST int SREF goto 2 export "0 DDR memory is NOT in self-refresh state, 1 DDR memory is in self-refresh state"
register ST int CKE1 goto 1 export "0 CKE1 Pin is low, 1 CKE1 Pin is high"
register ST int CKE0 goto 0 export "0 CKE0 Pin is low, 1 CKE0 Pin is high"

// 
/* DDRC Configure Register */
const DDRC_CFG_MSEL_BIT 16
register CFG int MSEL export "Mask delay select"
register CFG int MSEL goto (0x3 << DDRC_CFG_MSEL_BIT)
register CFG int MSEL enum "0" 0 export "00 No delay"
register CFG int MSEL enum "1" 1 export "01 delay 1 tCK"
register CFG int MSEL enum "2" 2 export "10 delay 2 tCK"
register CFG int MSEL enum "3" 3 export "11 delay 3 tCK"

// 
register CFG int HL goto 15 export "0: no extra delay 1: one extra half tCK delay"

// 
const DDRC_CFG_ROW1_BIT 27
register CFG int ROW1 export "Row Address width."
register CFG int ROW1 goto (3 << DDRC_CFG_ROW1_BIT)
const DDRC_CFG_COL1_BIT 25
register CFG int COL1 export "Row Address width."
register CFG int COL1 goto (3 << DDRC_CFG_COL1_BIT)
register CFG int BA1_BIT goto 24
register CFG int IMBA_BIT goto 23
register CFG int BTRUN goto 21

// 
const DDRC_CFG_TYPE_BIT 12
register CFG int TYPE goto (0x7 << DDRC_CFG_TYPE_BIT)
register CFG int TYPE enum DDR1 2
register CFG int TYPE enum MDDR 3
register CFG int TYPE enum DDR2 4

// 
const DDRC_CFG_ROW_BIT 10
register CFG int ROW export "Row Address width."
register CFG int ROW goto (0x3 << DDRC_CFG_ROW_BIT)
register CFG int ROW enum "13" 0 export "13-bit row address is used"
register CFG int ROW enum "14" 1 export "14-bit row address is used"

// 
const DDRC_CFG_COL_BIT 8
register CFG int COL export "Column Address width. Specify the Column address width of external DDR."
register CFG int COL goto (0x3 << DDRC_CFG_COL_BIT)
register CFG int COL enum "9" 0 export "9-bit Column address is used"
register CFG int COL enum "10" 1 export "10-bit Column address is used"

// 
register CFG int CS1EN goto 7 export "0 DDR Pin CS1 un-used, 1 There're DDR memory connected to CS1"
register CFG int CS0EN goto 6 export "0 DDR Pin CS0 un-used, 1 There're DDR memory connected to CS0"

// 
const DDRC_CFG_TSEL_BIT 18
register CFG int TSEL export "Read delay select"
register CFG int TSEL goto (0x3 << DDRC_CFG_TSEL_BIT)
register CFG int TSEL enum "0" 0 export "No delay"
register CFG int TSEL enum "1" 1 export "delay 1 tCK"
register CFG int TSEL enum "2" 2 export "delay 2 tCK"
register CFG int TSEL enum "3" 3 export "delay 3 tCK"

// 
const DDRC_CFG_CL_BIT 2
register CFG int CL export "CAS Latency"
register CFG int CL goto (0xf << DDRC_CFG_CL_BIT)
register CFG int CL enum "3" 0 export "CL = 3 tCK"
register CFG int CL enum "4" 1 export "CL = 4 tCK"
register CFG int CL enum "5" 2 export "CL = 5 tCK"
register CFG int CL enum "6" 3 export "CL = 6 tCK"

// 
register CFG int BA goto 1 export "0 4 bank device, Pin ba[1:0] valid, ba[2] un-used, 1 8 bank device, Pin ba[2:0] valid"
register CFG int DW goto 0 export "0 External memory data width is 16-bit, 1 External memory data width is 32-bit"

// 
/* DDRC Control Register */
register CTRL int ACTPD goto 15 export "0 Precharge all banks before entering power-down, 1 Do not precharge banks before entering power-down"
const DDRC_CTRL_PDT_BIT 12
register CTRL int PDT export "Power-Down Timer"
register CTRL int PDT goto (0x7 << DDRC_CTRL_PDT_BIT)
register CTRL int PDT enum DIS 0 export "power-down disabled"
register CTRL int PDT enum "8" 1 export "Enter power-down after 8 tCK idle"
register CTRL int PDT enum "16" 2 export "Enter power-down after 16 tCK idle"
register CTRL int PDT enum "32" 3 export "Enter power-down after 32 tCK idle"
register CTRL int PDT enum "64" 4 export "Enter power-down after 64 tCK idle"
register CTRL int PDT enum "128" 5 export "Enter power-down after 128 tCK idle"

// 
const DDRC_CTRL_PRET_BIT 8
register CTRL int PRET export "Precharge Timer"
register CTRL int PRET goto (0x7 << DDRC_CTRL_PRET_BIT) export ""
register CTRL int PRET enum DIS 0 export "PRET function Disabled"
register CTRL int PRET enum "8" 1 export "Precharge active bank after 8 tCK idle"
register CTRL int PRET enum "16" 2 export "Precharge active bank after 16 tCK idle"
register CTRL int PRET enum "32" 3 export "Precharge active bank after 32 tCK idle"
register CTRL int PRET enum "64" 4 export "Precharge active bank after 64 tCK idle"
register CTRL int PRET enum "128" 5 export "Precharge active bank after 128 tCK idle"

// 
register CTRL int SR goto 5 export "1 Drive external DDR device entering self-refresh mode, 0 Drive external DDR device exiting self-refresh mode"
register CTRL int UNALIGN goto 4 export "0 Disable unaligned transfer on AXI BUS, 1 Enable unaligned transfer on AXI BUS"
register CTRL int ALH goto 3 export "Advanced Latency Hiding: 0 Disable ALH, 1 Enable ALH"
register CTRL int RDC goto 2 export "0 dclk clock frequency is lower than 60MHz, 1 dclk clock frequency is higher than 60MHz"
register CTRL int CKE goto 1 export "0 Not set CKE Pin High, 1 Set CKE Pin HIGH"
register CTRL int RESET goto 0 export "0 End resetting ddrc_controller, 1 Resetting ddrc_controller"

// 
/* DDRC Load-Mode-Register */
const DDRC_LMR_DDR_ADDR_BIT 16
register LMR int DDR_ADDR goto (0xff << DDRC_LMR_DDR_ADDR_BIT)

// 
const DDRC_LMR_BA_BIT 8
register LMR int BA export "When performing a DDR command, BA[2:0] corresponding to external DDR address Pin BA[2:0]."
register LMR int BA goto (0x7 << DDRC_LMR_BA_BIT)
//   /* For DDR2 */
register LMR int BA enum MRS 0 export "(For DDR2) Mode Register set"
register LMR int BA enum EMRS1 1 export "(For DDR2) Extended Mode Register1 set"
register LMR int BA enum EMRS2 2 export "(For DDR2) Extended Mode Register2 set"
register LMR int BA enum EMRS3 3 export "(For DDR2) Extended Mode Register3 set"
//   /* For mobile DDR */
register LMR int BA enum M_MRS 0 export "(For mobile DDR) Mode Register set"
register LMR int BA enum M_EMRS 2 export "(For mobile DDR) Extended Mode Register set"
register LMR int BA enum M_SR 1 export "(For mobile DDR) Status Register set"

// 
const DDRC_LMR_CMD_BIT 4
register LMR int CMD goto (0x3 << DDRC_LMR_CMD_BIT)
register LMR int CMD enum PREC 0 export "Precharge one bank/All banks"
register LMR int CMD enum AUREF 1 export "Auto-Refresh"
register LMR int CMD enum LMR 2 export "Load Mode Register"

// 
register LMR int START goto 0 export "0 No command is performed, 1 On the posedge of START, perform a command defined by CMD field"

// 
/* DDRC Mode Register Set */
const DDR_MRS_PD_BIT 10
register MRS int PD export "Active power down exit time"
register MRS int PD goto (1 << DDR_MRS_PD_BIT)
register MRS int PD enum FAST_EXIT 0
register MRS int PD enum SLOW_EXIT 1
const DDR_MRS_WR_BIT 9
register MRS int WR export "Write Recovery for autoprecharge"
register MRS int WR goto (7 << DDR_MRS_WR_BIT)
register MRS int DLL_RST goto 8 export "DLL Reset"
const DDR_MRS_TM_BIT 7
register MRS int TM export "Operating Mode"
register MRS int TM goto (1 << DDR_MRS_TM_BIT)
register MRS int TM enum NORMAL 0
register MRS int TM enum TEST 1
const DDR_MRS_CAS_BIT 4
register MRS int CAS export "CAS Latency"
register MRS int CAS goto (7 << DDR_MRS_CAS_BIT)
const DDR_MRS_BT_BIT 3
register MRS int BT export "Burst Type"
register MRS int BT goto (1 << DDR_MRS_BT_BIT)
register MRS int BT enum SEQ 0 export "Sequential"
register MRS int BT enum INT 1 export "Interleave"
const DDR_MRS_BL_BIT 0
register MRS int BL export "Burst Length"
register MRS int BL goto (7 << DDR_MRS_BL_BIT)
register MRS int BL enum "4" 2
register MRS int BL enum "8" 3

// 
/* DDRC Extended Mode Register1 Set */
register EMRS1 int QOFF goto 12 export "0 Output buffer enabled, 1 Output buffer disabled"
register EMRS1 int RDQS_EN goto 11 export "0 Disable, 1 Enable"
register EMRS1 int DQS_DIS goto 10 export "0 Enable, 1 Disable"
const DDR_EMRS1_OCD_BIT 7
register EMRS1 int OCD export "Additive Latency 0 -> 6"
register EMRS1 int OCD goto (0x7 << DDR_EMRS1_OCD_BIT)
register EMRS1 int OCD enum EXIT 0
register EMRS1 int OCD enum D0 1
register EMRS1 int OCD enum D1 2
register EMRS1 int OCD enum ADJ 4
register EMRS1 int OCD enum DFLT 7
const DDR_EMRS1_AL_BIT 3
register EMRS1 int AL export "Additive Latency 0 -> 6"
register EMRS1 int AL goto (7 << DDR_EMRS1_AL_BIT)
const DDR_EMRS1_RTT_BIT 2
register EMRS1 int RTT export ""
register EMRS1 int RTT goto (0x11 << DDR_EMRS1_RTT_BIT) export "Bit 6, Bit 2"
const DDR_EMRS1_DIC_BIT 1
register EMRS1 int DIC export "Output Driver Impedence Control"
register EMRS1 int DIC goto (1 << DDR_EMRS1_DIC_BIT) export "100%"
register EMRS1 int DIC enum NORMAL 0 export "60%"
register EMRS1 int DIC enum HALF 1
const DDR_EMRS1_DLL_BIT 0
register EMRS1 int DLL export "DLL Enable"
register EMRS1 int DLL goto (1 << DDR_EMRS1_DLL_BIT)
register EMRS1 int DLL enum EN 0
register EMRS1 int DLL enum DIS 1

// 
/* Mobile SDRAM Extended Mode Register */
const DDR_EMRS_DS_BIT 5
register EMRS int DS export "Driver strength"
register EMRS int DS goto (7 << DDR_EMRS_DS_BIT)
register EMRS int DS enum FULL 0 export "Full"
register EMRS int DS enum HALF 1 export "1/2 Strength"
register EMRS int DS enum QUTR 2 export "1/4 Strength"
register EMRS int DS enum OCTANT 3 export "1/8 Strength"
register EMRS int DS enum QUTR3 4 export "3/4 Strength"

// 
const DDR_EMRS_PRSR_BIT 0
register EMRS int PRSR export "Partial Array Self Refresh"
register EMRS int PRSR goto (7 << DDR_EMRS_PRSR_BIT)
register EMRS int PRSR enum ALL 0 export "All Banks"
register EMRS int PRSR enum HALF_TL 1 export "Half of Total Bank"
register EMRS int PRSR enum QUTR_TL 2 export "Quarter of Total Bank"
register EMRS int PRSR enum HALF_B0 5 export "Half of Bank0"
register EMRS int PRSR enum QUTR_B0 6 export "Quarter of Bank0"

// 

// 
/* DDRC Timing Config Register 1 */
const DDRC_TIMING1_TRAS_BIT 28
register TIMING1 int TRAS export "ACTIVE to PRECHARGE command period (2 * tRAS + 1)"
register TIMING1 int TRAS goto (0xf << DDRC_TIMING1_TRAS_BIT)

// 

// 
const DDRC_TIMING1_TRTP_BIT 24
register TIMING1 int TRTP export "READ to PRECHARGE command period."
register TIMING1 int TRTP goto (0x3 << DDRC_TIMING1_TRTP_BIT)

// 
const DDRC_TIMING1_TRP_BIT 20
register TIMING1 int TRP export "PRECHARGE command period."
register TIMING1 int TRP goto (0x7 << DDRC_TIMING1_TRP_BIT)

// 
const DDRC_TIMING1_TRCD_BIT 16
register TIMING1 int TRCD export "ACTIVE to READ or WRITE command period."
register TIMING1 int TRCD goto (0x7 << DDRC_TIMING1_TRCD_BIT)

// 
const DDRC_TIMING1_TRC_BIT 12
register TIMING1 int TRC export "ACTIVE to ACTIVE command period."
register TIMING1 int TRC goto (0xf << DDRC_TIMING1_TRC_BIT)

// 
const DDRC_TIMING1_TRRD_BIT 8
register TIMING1 int TRRD export "ACTIVE bank A to ACTIVE bank B command period."
register TIMING1 int TRRD goto (0x3 << DDRC_TIMING1_TRRD_BIT)
register TIMING1 int TRRD enum DISABLE 0
register TIMING1 int TRRD enum "2" 1
register TIMING1 int TRRD enum "3" 2
register TIMING1 int TRRD enum "4" 3

// 
const DDRC_TIMING1_TWR_BIT 4
register TIMING1 int TWR export "WRITE Recovery Time defined by register MR of DDR2 memory"
register TIMING1 int TWR goto (0x7 << DDRC_TIMING1_TWR_BIT)
register TIMING1 int TWR enum "1" 0
register TIMING1 int TWR enum "2" 1
register TIMING1 int TWR enum "3" 2
register TIMING1 int TWR enum "4" 3
register TIMING1 int TWR enum "5" 4
register TIMING1 int TWR enum "6" 5

// 
const DDRC_TIMING1_TWTR_BIT 0
register TIMING1 int TWTR export "WRITE to READ command delay."
register TIMING1 int TWTR goto (0x3 << DDRC_TIMING1_TWTR_BIT)
register TIMING1 int TWTR enum "1" 0
register TIMING1 int TWTR enum "2" 1
register TIMING1 int TWTR enum "3" 2
register TIMING1 int TWTR enum "4" 3

// 
/* DDRC Timing Config Register 2 */
const DDRC_TIMING2_TRFC_BIT 12
register TIMING2 int TRFC export "AUTO-REFRESH command period."
register TIMING2 int TRFC goto (0xf << DDRC_TIMING2_TRFC_BIT)
const DDRC_TIMING2_TMINSR_BIT 8
register TIMING2 int TMINSR export "Minimum Self-Refresh / Deep-Power-Down time"
register TIMING2 int TMINSR goto (0xf << DDRC_TIMING2_TMINSR_BIT)
const DDRC_TIMING2_TXP_BIT 4
register TIMING2 int TXP export "EXIT-POWER-DOWN to next valid command period."
register TIMING2 int TXP goto (0x7 << DDRC_TIMING2_TXP_BIT)
const DDRC_TIMING2_TMRD_BIT 0
register TIMING2 int TMRD export "Load-Mode-Register to next valid command period."
register TIMING2 int TMRD goto (0x3 << DDRC_TIMING2_TMRD_BIT)

// 
/* DDRC  Auto-Refresh Counter */
const DDRC_REFCNT_CON_BIT 16
register REFCNT int CON export "Constant value used to compare with CNT value."
register REFCNT int CON goto (0xff << DDRC_REFCNT_CON_BIT)
const DDRC_REFCNT_CNT_BIT 8
register REFCNT int CNT export "8-bit counter"
register REFCNT int CNT goto (0xff << DDRC_REFCNT_CNT_BIT)
const DDRC_REFCNT_CLKDIV_BIT 1
register REFCNT int CLKDIV export "Clock Divider for auto-refresh counter."
register REFCNT int CLKDIV goto (0x7 << DDRC_REFCNT_CLKDIV_BIT)
register REFCNT int REF_EN goto 0 export "Enable Refresh Counter"

// 
/* DDRC DQS Delay Control Register */
register DQS int ERROR goto 29 export "ahb_clk Delay Detect ERROR, read-only."
register DQS int READY goto 28 export "ahb_clk Delay Detect READY, read-only."
register DQS int AUTO goto 23 export "Hardware auto-detect & set delay line"
register DQS int DET goto 24 export "Start delay detecting."
const DDRC_DQS_CLKD_BIT 16
register DQS int CLKD export "CLKD is reference value for setting WDQS and RDQS."
register DQS int CLKD goto (0x7f << DDRC_DQS_CLKD_BIT)
const DDRC_DQS_WDQS_BIT 8
register DQS int WDQS export "Set delay element number to write DQS delay-line."
register DQS int WDQS goto (0x3f << DDRC_DQS_WDQS_BIT)
const DDRC_DQS_RDQS_BIT 0
register DQS int RDQS export "Set delay element number to read DQS delay-line."
register DQS int RDQS goto (0x3f << DDRC_DQS_RDQS_BIT)

// 
/* DDRC DQS Delay Adjust Register */
const DDRC_DQSADJWDQS_BIT 8
// #define DDRC_DQSADJWDQS_MASK         (0x1f << DDRC_DQSADJWDQS_BIT)
const DDRC_DQSADJRDQS_BIT 0
// #define DDRC_DQSADJRDQS_MASK         (0x1f << DDRC_DQSADJRDQS_BIT)

// 
/* DDRC Memory Map Config Register */
const DDRC_MMAP_BASE_BIT 8
register MMAP int BASE export "base address"
register MMAP int BASE goto (0xff << DDRC_MMAP_BASE_BIT)
const DDRC_MMAP_MASK_BIT 0
register MMAP int MASK export "address mask"
register MMAP int MASK goto (0xff << DDRC_MMAP_MASK_BIT)

// 
// #define DDRC_MMAP_BASE		     (0x20 << DDRC_MMAP_BASE_BIT)
register MMAP int BASE enum "64M" 0x24 export "when bank0 is 128M"
register MMAP int BASE enum "128M" 0x28 export "when bank0 is 128M"
register MMAP int BASE enum "256M" 0x30 export "when bank0 is 128M"

// 
register MMAP int MASK enum "64_64" 0xfc export "mask for two 128M SDRAM"
register MMAP int MASK enum "128_128" 0xf8 export "mask for two 128M SDRAM"
register MMAP int MASK enum "256_256" 0xf0 export "mask for two 128M SDRAM"

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BDDRC_H__ */

// 
