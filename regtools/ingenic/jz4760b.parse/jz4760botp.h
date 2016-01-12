/*
 * linux/include/asm-mips/mach-jz4760b/jz4760botp.h
 *
 * JZ4760B OTP register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

// 
// #ifndef __JZ4760BOTP_H__
// #define __JZ4760BOTP_H__

// 

// 
/* OTP (One Time Programmable Module) [not sure about the address]*/
this class OTP goto 0xB3012000 export "OTP (One Time Programmable Module) [not sure about the address]"

// 
register ID0 goto 0x00 export "ID0 Register"
register ID1 goto 0x04 export "ID1 Register"
register ID2 goto 0x08 export "ID2 Register"
register ID3 goto 0x0C export "ID3 Register"
register BR0 goto 0x10 export "BOOTROM0 Register"
register BR1 goto 0x14 export "BOOTROM1 Register"
register HW0 goto 0x18 export "Chip Hardware 0 Register"
register HW1 goto 0x1C export "Chip Hardware 1 Register"

// 
register ID0 sizeof 32
register ID1 sizeof 32
register ID2 sizeof 32
register ID3 sizeof 32
register BR0 sizeof 32
register BR1 sizeof 32
register HW0 sizeof 32
register HW1 sizeof 32

// 
/* ID0 Register */
const OTP_ID0_WID_BIT 24
register ID0 int WID export "Wafer ID"
register ID0 int WID goto (0xff << OTP_ID0_WID_BIT)
const OTP_ID0_MID_BIT 16
register ID0 int MID export "MASK ID"
register ID0 int MID goto (0xff << OTP_ID0_MID_BIT)
const OTP_ID0_FID_BIT 8
register ID0 int FID export "Foundary ID"
register ID0 int FID goto (0xff << OTP_ID0_FID_BIT)
const OTP_ID0_PID_BIT 0
register ID0 int PID export "Product ID"
register ID0 int PID goto (0xff << OTP_ID0_PID_BIT)

// 
/* ID1 Register */
const OTP_ID1_LID_BIT 8
register ID1 int LID export "Lot ID"
register ID1 int LID goto (0xffffff << OTP_ID1_LID_BIT)
const OTP_ID1_TID_BIT 0
register ID1 int TID export "Test House ID"
register ID1 int TID goto (0xff << OTP_ID1_TID_BIT)

// 
/* ID2 Register */
const OTP_ID2_XADR_BIT 24
register ID2 int XADR export "Die X-dir Address"
register ID2 int XADR goto (0xff << OTP_ID2_XADR_BIT)
const OTP_ID2_YADR_BIT 16
register ID2 int YADR export "Die Y-dir Address"
register ID2 int YADR goto (0xff << OTP_ID2_YADR_BIT)
const OTP_ID2_TDATE_BIT 0
register ID2 int TDATE export "Testing Date"
register ID2 int TDATE goto (0xffff << OTP_ID2_TDATE_BIT)

// 
/* ID3 Register */
const OTP_ID3_CID_BIT 16
register ID3 int CID export "Customer ID"
register ID3 int CID goto (0xffff << OTP_ID3_CID_BIT)
const OTP_ID3_CP_BIT 0
register ID3 int CP export "Chip Parameters"
register ID3 int CP goto (0xffff << OTP_ID3_CP_BIT)

// 
/* BOOTROM1 Register */
const OTP_BR1_UDCBOOT_BIT 0
register BR1 int UDCBOOT goto (0xff << OTP_BR1_UDCBOOT_BIT)
register BR1 int UDCBOOT enum AUTO 0xf0
register BR1 int UDCBOOT enum "24M" 0x0f export "24MHz OSC"
register BR1 int UDCBOOT enum "13M" 0x0c export "13MHz OSC"
register BR1 int UDCBOOT enum "26M" 0x03 export "26MHz OSC"
register BR1 int UDCBOOT enum "27M" 0x00 export "27MHz OSC"

// 
/* Chip Hardware 1 Register */
// #define OTP_HW1_MC_EN		(0x3 << 30) /* MC is enabled */
// #define OTP_HW1_ME_EN		(0x3 << 28)
// #define OTP_HW1_DE_EN		(0x3 << 26)
// #define OTP_HW1_IDCT_EN		(0x3 << 24)
// #define OTP_HW1_UART3_EN	(0x3 << 22)
// #define OTP_HW1_UART2_EN	(0x3 << 20)
// #define OTP_HW1_UART1_EN	(0x3 << 18)
// #define OTP_HW1_UART0_EN	(0x3 << 16)
// #define OTP_HW1_SSI1_EN		(0x3 << 14)
// #define OTP_HW1_SSI0_EN		(0x3 << 12)
// #define OTP_HW1_MSC1_EN		(0x3 << 10)
// #define OTP_HW1_MSC0_EN		(0x3 << 8)
// #define OTP_HW1_UHC_EN		(0x3 << 6)
// #define OTP_HW1_TVE_EN		(0x3 << 4)
// #define OTP_HW1_TSSI_EN		(0x3 << 2)
// #define OTP_HW1_CIM_EN		(0x3 << 0)

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BOTP_H__ */

// 
