/*
 * linux/include/asm-mips/mach-jz4760b/jz4760blcdc.h
 *
 * JZ4760B LCDC register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

// 
// #ifndef __JZ4760BLCDC_H__
// #define __JZ4760BLCDC_H__

// 
/* SLCD (Smart LCD Controller) */
this class SLCD goto 0xB3050000 export "SLCD (Smart LCD Controller)"

// 

// 
/*************************************************************************
 * SLCD (Smart LCD Controller)
 *************************************************************************/

// 
register CFG goto 0xA0 export "SLCD Configure Register"
register CTRL goto 0xA4 export "SLCD Control Register"
register STATE goto 0xA8 export "SLCD Status Register"
register DATA goto 0xAC export "SLCD Data Register"

// 
register CFG sizeof 32
register CTRL sizeof 8
register STATE sizeof 8
register DATA sizeof 32

// 
/* SLCD Configure Register */
const SLCD_CFG_DWIDTH_BIT 10
register CFG int DWIDTH goto (0x7 << SLCD_CFG_DWIDTH_BIT)
register CFG int DWIDTH enum "18BIT" 0
register CFG int DWIDTH enum "16BIT" 1
register CFG int DWIDTH enum "8BIT_x3" 2
register CFG int DWIDTH enum "8BIT_x2" 3
register CFG int DWIDTH enum "8BIT_x1" 4
register CFG int DWIDTH enum "24BIT" 5
register CFG int DWIDTH enum "9BIT_x2" 7
const SLCD_CFG_CWIDTH_BIT 8
register CFG int CWIDTH goto (0x3 << SLCD_CFG_CWIDTH_BIT)
register CFG int CWIDTH enum "16BIT" 0
register CFG int CWIDTH enum "8BIT" 1
register CFG int CWIDTH enum "18BIT" 2
register CFG int CWIDTH enum "24BIT" 3
// #define SLCD_CFG_CS_ACTIVE_LOW	(0 << 4)
register CFG int CS_ACTIVE_HIGH goto 4
// #define SLCD_CFG_RS_CMD_LOW	(0 << 3)
register CFG int RS_CMD_HIGH goto 3
// #define SLCD_CFG_CLK_ACTIVE_FALLING	(0 << 1)
register CFG int CLK_ACTIVE_RISING goto 1
// #define SLCD_CFG_TYPE_PARALLEL	(0 << 0)
register CFG int TYPE_SERIAL goto 0

// 
/* SLCD Control Register */
register CTRL int DMA_MODE goto 2
register CTRL int DMA_START goto 1
register CTRL int DMA_EN goto 0

// 
/* SLCD Status Register */
register STATE int BUSY goto 0

// 
/* SLCD Data Register */
// #define SLCD_DATA_RS_DATA	(0 << 31)
register DATA int RS_COMMAND goto 31

// 
/* LCD (LCD Controller) */
this class LCD goto 0xB3050000 export "LCD (LCD Controller)"

// 
register CFG goto 0x00 export "LCD Configure Register"
register CTRL goto 0x30 export "LCD Control Register"
register STATE goto 0x34 export "LCD Status Register"

// 
register OSDC goto 0x100 export "LCD OSD Configure Register"
register OSDCTRL goto 0x104 export "LCD OSD Control Register"
register OSDS goto 0x108 export "LCD OSD Status Register"
register BGC goto 0x10C export "LCD Background Color Register"
register KEY goto (0,0x110) export "LCD Foreground Color Key Register 0"
register KEY goto (1,0x114) export "LCD Foreground Color Key Register 1"
register ALPHA goto 0x118 export "LCD ALPHA Register"
register IPUR goto 0x11C export "LCD IPU Restart Register"

// 
register VAT goto 0x0c export "Virtual Area Setting Register"
register DAH goto 0x10 export "Display Area Horizontal Start/End Point"
register DAV goto 0x14 export "Display Area Vertical Start/End Point"
register XYP goto (0,0x120) export "Foreground 0 XY Position Register"
register XYP goto (1,0x124) export "Foreground 1 XY Position Register"
register XYP0_PART2 goto 0x1F0 export "Foreground 0 PART2 XY Position Register"
register SIZE goto (0,0x128) export "Foreground 0 Size Register"
register SIZE goto (1,0x12C) export "Foreground 1 Size Register"
register SIZE0_PART2 goto 0x1F4 export "Foreground 0 PART2 Size Register"
register RGBC goto 0x90 export "RGB Controll Register"

// 
register VSYNC goto 0x04 export "Vertical Synchronize Register"
register HSYNC goto 0x08 export "Horizontal Synchronize Register"
register PS goto 0x18 export "PS Signal Setting"
register CLS goto 0x1c export "CLS Signal Setting"
register SPL goto 0x20 export "SPL Signal Setting"
register REV goto 0x24 export "REV Signal Setting"
register IID goto 0x38 export "Interrupt ID Register"
register DA goto (0,0x40) export "Descriptor Address Register 0"
register SA goto (0,0x44) export "Source Address Register 0"
register FID goto (0,0x48) export "Frame ID Register 0"
register CMD goto (0,0x4c) export "DMA Command Register 0"
register OFFS goto (0,0x60) export "DMA Offsize Register 0"
register PW goto (0,0x64) export "DMA Page Width Register 0"
register CNUM goto (0,0x68) export "DMA Command Counter Register 0"
register DESSIZE goto (0,0x6C) export "Foreground Size in Descriptor 0 Register"

// 
register DA0_PART2 goto 0x1C0 export "Descriptor Address Register PART2"
register SA0_PART2 goto 0x1C4 export "Source Address Register PART2"
register FID0_PART2 goto 0x1C8 export "Frame ID Register PART2"
register CMD0_PART2 goto 0x1CC export "DMA Command Register PART2"
register OFFS0_PART2 goto 0x1E0 export "DMA Offsize Register PART2"
register PW0_PART2 goto 0x1E4 export "DMA Command Counter Register PART2"
register CNUM0_PART2 goto 0x1E8 export "Foreground Size in Descriptor PART2 Register"
register DESSIZE0_PART2 goto 0x1EC export ""
register PCFG goto 0x2C0 export ""

// 
register DA goto (1,0x50) export "Descriptor Address Register 1"
register SA goto (1,0x54) export "Source Address Register 1"
register FID goto (1,0x58) export "Frame ID Register 1"
register CMD goto (1,0x5c) export "DMA Command Register 1"
register OFFS goto (1,0x70) export "DMA Offsize Register 1"
register PW goto (1,0x74) export "DMA Page Width Register 1"
register CNUM goto (1,0x78) export "DMA Command Counter Register 1"
register DESSIZE goto (1,0x7C) export "Foreground Size in Descriptor 1 Register"

// 
register CFG sizeof 32
register CTRL sizeof 32
register STATE sizeof 32

// 
register OSDC sizeof 16
register OSDCTRL sizeof 16
register OSDS sizeof 16
register BGC sizeof 32
register KEY sizeof 32
// #define REG_LCD_KEY0	REG32(LCD_KEY0)
// #define REG_LCD_KEY1	REG32(LCD_KEY1)
register ALPHA sizeof 8
register IPUR sizeof 32

// 
register VAT sizeof 32
register DAH sizeof 32
register DAV sizeof 32

// 
register XYP sizeof 32
// #define REG_LCD_XYP0		REG32(LCD_XYP0)
// #define REG_LCD_XYP0_PART2	REG32(LCD_XYP0_PART2)
// #define REG_LCD_XYP1		REG32(LCD_XYP1)
register SIZE sizeof 32
// #define REG_LCD_SIZE0		REG32(LCD_SIZE0)
// #define REG_LCD_SIZE0_PART2	REG32(LCD_SIZE0_PART2)
// #define REG_LCD_SIZE1	REG32(LCD_SIZE1)

// 
register RGBC sizeof 16

// 
register VSYNC sizeof 32
register HSYNC sizeof 32
register PS sizeof 32
register CLS sizeof 32
register SPL sizeof 32
register REV sizeof 32
register IID sizeof 32
register DA sizeof 32
register SA sizeof 32
register FID sizeof 32
register CMD sizeof 32
// #define REG_LCD_DA0	REG32(LCD_DA0)
// #define REG_LCD_SA0	REG32(LCD_SA0)
// #define REG_LCD_FID0	REG32(LCD_FID0)
// #define REG_LCD_CMD0	REG32(LCD_CMD0)

// 
register OFFS sizeof 32
register PW sizeof 32
register CNUM sizeof 32
register DESSIZE sizeof 32
// #define REG_LCD_OFFS0	REG32(LCD_OFFS0)
// #define REG_LCD_PW0	REG32(LCD_PW0)
// #define REG_LCD_CNUM0	REG32(LCD_CNUM0)
// #define REG_LCD_DESSIZE0	REG32(LCD_DESSIZE0)

// 
// #define REG_LCD_DA0_PART2	REG32(LCD_DA0_PART2)
// #define REG_LCD_SA0_PART2	REG32(LCD_SA0_PART2)
// #define REG_LCD_FID0_PART2	REG32(LCD_FID0_PART2)
// #define REG_LCD_CMD0_PART2	REG32(LCD_CMD0_PART2)
// #define REG_LCD_OFFS0_PART2	REG32(LCD_OFFS0_PART2)
// #define REG_LCD_PW0_PART2	REG32(LCD_PW0_PART2)
// #define REG_LCD_CNUM0_PART2	REG32(LCD_CNUM0_PART2)
// #define REG_LCD_DESSIZE0_PART2	REG32(LCD_DESSIZE0_PART2)
register PCFG sizeof 32

// 
// #define REG_LCD_DA1	REG32(LCD_DA1)
// #define REG_LCD_SA1	REG32(LCD_SA1)
// #define REG_LCD_FID1	REG32(LCD_FID1)
// #define REG_LCD_CMD1	REG32(LCD_CMD1)
// #define REG_LCD_OFFS1	REG32(LCD_OFFS1)
// #define REG_LCD_PW1	REG32(LCD_PW1)
// #define REG_LCD_CNUM1	REG32(LCD_CNUM1)
// #define REG_LCD_DESSIZE1	REG32(LCD_DESSIZE1)

// 
/* LCD Configure Register */
const LCD_CFG_LCDPIN_BIT 31
register CFG int LCDPIN export "LCD pins selection"
register CFG int LCDPIN goto (0x1 << LCD_CFG_LCDPIN_BIT)
register CFG int LCDPIN enum LCD 0x0
register CFG int LCDPIN enum SLCD 0x1
register CFG int TVEPEH goto 30 export "TVE PAL enable extra halfline signal"
register CFG int FUHOLD goto 29 export "hold pixel clock when outFIFO underrun"
register CFG int NEWDES goto 28 export "use new descripter. old: 4words, new:8words"
register CFG int PALBP goto 27 export "bypass data format and alpha blending"
register CFG int TVEN goto 26 export "indicate the terminal is lcd or tv"
register CFG int RECOVER goto 25 export "Auto recover when output fifo underrun"
register CFG int DITHER goto 24 export "Dither function"
register CFG int PSM goto 23 export "PS signal mode"
register CFG int CLSM goto 22 export "CLS signal mode"
register CFG int SPLM goto 21 export "SPL signal mode"
register CFG int REVM goto 20 export "REV signal mode"
register CFG int HSYNM goto 19 export "HSYNC signal mode"
register CFG int PCLKM goto 18 export "PCLK signal mode"
register CFG int INVDAT goto 17 export "Inverse output data"
register CFG int SYNDIR_IN goto 16 export "VSYNC&HSYNC direction"
register CFG int PSP goto 15 export "PS pin reset state"
register CFG int CLSP goto 14 export "CLS pin reset state"
register CFG int SPLP goto 13 export "SPL pin reset state"
register CFG int REVP goto 12 export "REV pin reset state"
register CFG int HSP goto 11 export "HSYNC polarity:0-active high,1-active low"
register CFG int PCP goto 10 export "PCLK polarity:0-rising,1-falling"
register CFG int DEP goto 9 export "DE polarity:0-active high,1-active low"
register CFG int VSP goto 8 export "VSYNC polarity:0-rising,1-falling"
register CFG int MODE_TFT_18BIT goto 7 export "18bit TFT"
// #define LCD_CFG_MODE_TFT_16BIT 	(0 << 7)  /* 16bit TFT */
register CFG int MODE_TFT_24BIT goto 6 export "24bit TFT"
const LCD_CFG_PDW_BIT 4
register CFG int PDW export "STN pins utilization"
register CFG int PDW goto (0x3 << LCD_CFG_PDW_BIT)
register CFG int PDW enum "1" 0 export "LCD_D[0]"
register CFG int PDW enum "2" 1 export "LCD_D[0:1]"
register CFG int PDW enum "4" 2 export "LCD_D[0:3]/LCD_D[8:11]"
register CFG int PDW enum "8" 3 export "LCD_D[0:7]/LCD_D[8:15]"
const LCD_CFG_MODE_BIT 0
register CFG int MODE export "Display Device Mode Select"
register CFG int MODE goto (0x0f << LCD_CFG_MODE_BIT)
register CFG int MODE enum GENERIC_TFT 0 export "16,18 bit TFT"
register CFG int MODE enum SPECIAL_TFT_1 1
register CFG int MODE enum SPECIAL_TFT_2 2
register CFG int MODE enum SPECIAL_TFT_3 3
register CFG int MODE enum NONINTER_CCIR656 4
register CFG int MODE enum INTER_CCIR656 6
register CFG int MODE enum SINGLE_CSTN 8
register CFG int MODE enum SINGLE_MSTN 9
register CFG int MODE enum DUAL_CSTN 10
register CFG int MODE enum DUAL_MSTN 11
register CFG int MODE enum SERIAL_TFT 12
register CFG int MODE enum LCM 13
//   #define LCD_CFG_MODE_SLCD  		LCD_CFG_MODE_LCM

// 
/* LCD Control Register */
register CTRL int PINMD goto 31 export "This register set Pin distribution in 16-bit parallel mode, 0: 16-bit data correspond with LCD_D[15:0], 1: 16-bit data correspond with LCD_D[17:10], LCD_D[8:1]"
const LCD_CTRL_BST_BIT 28
register CTRL int BST export "Burst Length Selection"
register CTRL int BST goto (0x07 << LCD_CTRL_BST_BIT)
register CTRL int BST enum "4" 0 export "4-word"
register CTRL int BST enum "8" 1 export "8-word"
register CTRL int BST enum "16" 2 export "16-word"
register CTRL int BST enum "32" 3 export "32-word"
register CTRL int BST enum C16 5 export "16-word"
register CTRL int BST enum "64" 4 export "64-word"
register CTRL int BST enum "16_CTN" 5 export "16-word contiue"
// #define LCD_CTRL_RGB565		(0 << 27) /* RGB565 mode(foreground 0 in OSD mode) */
register CTRL int RGB555 goto 27 export "RGB555 mode(foreground 0 in OSD mode)"
register CTRL int OFUP goto 26 export "Output FIFO underrun protection enable"
const LCD_CTRL_FRC_BIT 24
register CTRL int FRC export "STN FRC Algorithm Selection"
register CTRL int FRC goto (0x03 << LCD_CTRL_FRC_BIT)
register CTRL int FRC enum "16" 0 export "16 grayscale"
register CTRL int FRC enum "4" 1 export "4 grayscale"
register CTRL int FRC enum "2" 2 export "2 grayscale"
const LCD_CTRL_PDD_BIT 16
register CTRL int PDD export "Load Palette Delay Counter"
register CTRL int PDD goto (0xff << LCD_CTRL_PDD_BIT)
///#define LCD_CTRL_VGA		(1 << 15) /* VGA interface enable */
//#define LCD_CTRL_DACTE		(1 << 14) /* DAC loop back test */
register CTRL int EOFM goto 13 export "EOF interrupt mask"
register CTRL int SOFM goto 12 export "SOF interrupt mask"
register CTRL int OFUM goto 11 export "Output FIFO underrun interrupt mask"
register CTRL int IFUM0 goto 10 export "Input FIFO 0 underrun interrupt mask"
register CTRL int IFUM1 goto 9 export "Input FIFO 1 underrun interrupt mask"
register CTRL int LDDM goto 8 export "LCD disable done interrupt mask"
register CTRL int QDM goto 7 export "LCD quick disable done interrupt mask"
register CTRL int BEDN goto 6 export "Endian selection"
register CTRL int PEDN goto 5 export "Endian in byte:0-msb first, 1-lsb first"
register CTRL int DIS goto 4 export "Disable indicate bit"
register CTRL int ENA goto 3 export "LCD enable bit"
const LCD_CTRL_BPP_BIT 0
register CTRL int BPP export "Bits Per Pixel"
register CTRL int BPP goto (0x07 << LCD_CTRL_BPP_BIT)
register CTRL int BPP enum "1" 0 export "1 bpp"
register CTRL int BPP enum "2" 1 export "2 bpp"
register CTRL int BPP enum "4" 2 export "4 bpp"
register CTRL int BPP enum "8" 3 export "8 bpp"
register CTRL int BPP enum "16" 4 export "15/16 bpp"
register CTRL int BPP enum "18_24" 5 export "18/24/32 bpp"
register CTRL int BPP enum CMPS_24 6 export "24 compress bpp"
register CTRL int BPP enum "30" 7 export "30 bpp"

// 
/* LCD Status Register */

// 
register STATE int FEND goto 22
register STATE int PWRUP goto 20
register STATE int PWRDN goto 19

// 
register STATE int QD goto 7 export "Quick Disable Done"
register STATE int EOF goto 5 export "EOF Flag"
register STATE int SOF goto 4 export "SOF Flag"
register STATE int OFU goto 3 export "Output FIFO Underrun"
register STATE int IFU0 goto 2 export "Input FIFO 0 Underrun"
register STATE int IFU1 goto 1 export "Input FIFO 1 Underrun"
register STATE int LDD goto 0 export "LCD Disabled"

// 
/* OSD Configure Register */
register OSDC int SOFM1 goto 15 export "Start of frame interrupt mask for foreground 1"
register OSDC int EOFM1 goto 14 export "End of frame interrupt mask for foreground 1"
register OSDC int SOFM0 goto 11 export "Start of frame interrupt mask for foreground 0"
register OSDC int EOFM0 goto 10 export "End of frame interrupt mask for foreground 0"

// 
////////////////////////////////////////////////////////////
register OSDC int ENDM goto 9 export "End of frame interrupt mask for panel."
// #define LCD_OSDC_F0DIVMD	(1 << 8) /* Divide Foreground 0 into 2 parts.
// 					  * 0: Foreground 0 only has one part. */
// #define LCD_OSDC_F0P1EN		(1 << 7) /* 1: Foreground 0 PART1 is enabled.
// 					  * 0: Foreground 0 PART1 is disabled. */
// #define LCD_OSDC_F0P2MD		(1 << 6) /* 1: PART 1&2 same level and same heighth
// 					  * 0: PART 1&2 have no same line */
// #define LCD_OSDC_F0P2EN		(1 << 5) /* 1: Foreground 0 PART2 is enabled.
// 					  * 0: Foreground 0 PART2 is disabled.*/
////////////////////////////////////////////////////////////

// 
register OSDC int F1EN goto 4 export "enable foreground 1"
register OSDC int F0EN goto 3 export "enable foreground 0"
register OSDC int ALPHAEN goto 2 export "enable alpha blending"
register OSDC int ALPHAMD goto 1 export "alpha blending mode"
register OSDC int OSDEN goto 0 export "OSD mode enable"

// 
/* OSD Controll Register */
register OSDCTRL int IPU goto 15 export "input data from IPU"
// #define LCD_OSDCTRL_RGB565	(0 << 4) /* foreground 1, 16bpp, 0-RGB565, 1-RGB555 */
register OSDCTRL int RGB555 goto 4 export "foreground 1, 16bpp, 0-RGB565, 1-RGB555"
register OSDCTRL int CHANGES goto 3 export "Change size flag"
const LCD_OSDCTRL_OSDBPP_BIT 0
register OSDCTRL int OSDBPP export "Bits Per Pixel of OSD Channel 1"
register OSDCTRL int OSDBPP goto (0x7<<LCD_OSDCTRL_OSDBPP_BIT) export "Bits Per Pixel of OSD Channel 1's MASK"
register OSDCTRL int OSDBPP enum "2" 1
register OSDCTRL int OSDBPP enum "4" 2
register OSDCTRL int OSDBPP enum "16" 4 export "RGB 15,16 bit"
register OSDCTRL int OSDBPP enum "15_16" 4 export "RGB 15,16 bit"
register OSDCTRL int OSDBPP enum "18_24" 5 export "RGB 18,24 bit"
register OSDCTRL int OSDBPP enum CMPS_24 6 export "RGB compress 24 bit"
register OSDCTRL int OSDBPP enum "30" 7 export "RGB 30 bit"

// 
/* OSD State Register */
register OSDS int SOF1 goto 15 export "Start of frame flag for foreground 1"
register OSDS int EOF1 goto 14 export "End of frame flag for foreground 1"
register OSDS int SOF0 goto 11 export "Start of frame flag for foreground 0"
register OSDS int EOF0 goto 10 export "End of frame flag for foreground 0"
register OSDS int READY goto 0 export "Read for accept the change"

// 
/* Background Color Register */
const LCD_BGC_RED_BIT 16
register BGC int RED export "Red color offset"
register BGC int RED goto (0xFF<<LCD_BGC_RED_BIT)
const LCD_BGC_GREEN_BIT 8
register BGC int GREEN export "Green color offset"
register BGC int GREEN goto (0xFF<<LCD_BGC_GREEN_BIT)
const LCD_BGC_BLUE_BIT 0
register BGC int BLUE export "Blue color offset"
register BGC int BLUE goto (0xFF<<LCD_BGC_BLUE_BIT)

// 
/* Foreground Color Key Register 0,1(foreground 0, foreground 1) */
register KEY int KEYEN goto 31 export "enable color key"
register KEY int KEYMD goto 30 export "color key mode"
const LCD_KEY_RED_BIT 16
register KEY int RED export "Red color offset"
register KEY int RED goto (0xFF<<LCD_KEY_RED_BIT)
const LCD_KEY_GREEN_BIT 8
register KEY int GREEN export "Green color offset"
register KEY int GREEN goto (0xFF<<LCD_KEY_GREEN_BIT)
const LCD_KEY_BLUE_BIT 0
register KEY int BLUE export "Blue color offset"
register KEY int BLUE goto (0xFF<<LCD_KEY_BLUE_BIT)
// #define LCD_KEY_MASK		(LCD_KEY_RED_MASK|LCD_KEY_GREEN_MASK|LCD_KEY_BLUE_MASK)

// 
/* IPU Restart Register */
register IPUR int IPUREN goto 31 export "IPU restart function enable"
const LCD_IPUR_IPURMASK 0xFFFFFF

// 
/* RGB Control Register */
register RGBC int RGBDM goto 15 export "enable RGB Dummy data"
register RGBC int DMM goto 14 export "RGB Dummy mode"
register RGBC int YCC goto 8 export "RGB to YCC"
const LCD_RGBC_ODDRGB_BIT 4
register RGBC int ODDRGB export "odd line serial RGB data arrangement"
register RGBC int ODDRGB goto (0x7<<LCD_RGBC_ODDRGB_BIT)
const LCD_RGBC_ODD_RGB 0
const LCD_RGBC_ODD_RBG 1
const LCD_RGBC_ODD_GRB 2
const LCD_RGBC_ODD_GBR 3
const LCD_RGBC_ODD_BRG 4
const LCD_RGBC_ODD_BGR 5
const LCD_RGBC_EVENRGB_BIT 0
register RGBC int EVENRGB export "even line serial RGB data arrangement"
register RGBC int EVENRGB goto (0x7<<LCD_RGBC_EVENRGB_BIT)
const LCD_RGBC_EVEN_RGB 0
const LCD_RGBC_EVEN_RBG 1
const LCD_RGBC_EVEN_GRB 2
const LCD_RGBC_EVEN_GBR 3
const LCD_RGBC_EVEN_BRG 4
const LCD_RGBC_EVEN_BGR 5

// 
/* Vertical Synchronize Register */
const LCD_VSYNC_VPS_BIT 16
register VSYNC int VPS export "VSYNC pulse start in line clock, fixed to 0"
register VSYNC int VPS goto (0xffff << LCD_VSYNC_VPS_BIT)
const LCD_VSYNC_VPE_BIT 0
register VSYNC int VPE export "VSYNC pulse end in line clock"
register VSYNC int VPE goto (0xffff << LCD_VSYNC_VPE_BIT)

// 
/* Horizontal Synchronize Register */
const LCD_HSYNC_HPS_BIT 16
register HSYNC int HPS export "HSYNC pulse start position in dot clock"
register HSYNC int HPS goto (0xffff << LCD_HSYNC_HPS_BIT)
const LCD_HSYNC_HPE_BIT 0
register HSYNC int HPE export "HSYNC pulse end position in dot clock"
register HSYNC int HPE goto (0xffff << LCD_HSYNC_HPE_BIT)

// 
/* Virtual Area Setting Register */
const LCD_VAT_HT_BIT 16
register VAT int HT export "Horizontal Total size in dot clock"
register VAT int HT goto (0xffff << LCD_VAT_HT_BIT)
const LCD_VAT_VT_BIT 0
register VAT int VT export "Vertical Total size in dot clock"
register VAT int VT goto (0xffff << LCD_VAT_VT_BIT)

// 
/* Display Area Horizontal Start/End Point Register */
const LCD_DAH_HDS_BIT 16
register DAH int HDS export "Horizontal display area start in dot clock"
register DAH int HDS goto (0xffff << LCD_DAH_HDS_BIT)
const LCD_DAH_HDE_BIT 0
register DAH int HDE export "Horizontal display area end in dot clock"
register DAH int HDE goto (0xffff << LCD_DAH_HDE_BIT)

// 
/* Display Area Vertical Start/End Point Register */
const LCD_DAV_VDS_BIT 16
register DAV int VDS export "Vertical display area start in line clock"
register DAV int VDS goto (0xffff << LCD_DAV_VDS_BIT)
const LCD_DAV_VDE_BIT 0
register DAV int VDE export "Vertical display area end in line clock"
register DAV int VDE goto (0xffff << LCD_DAV_VDE_BIT)

// 
/* Foreground XY Position Register */
const LCD_XYP_YPOS_BIT 16
register XYP int YPOS export "Y position bit of foreground 0 or 1"
register XYP int YPOS goto (0xffff << LCD_XYP_YPOS_BIT)
const LCD_XYP_XPOS_BIT 0
register XYP int XPOS export "X position bit of foreground 0 or 1"
register XYP int XPOS goto (0xffff << LCD_XYP_XPOS_BIT)

// 
/* PS Signal Setting */
const LCD_PS_PSS_BIT 16
register PS int PSS export "PS signal start position in dot clock"
register PS int PSS goto (0xffff << LCD_PS_PSS_BIT)
const LCD_PS_PSE_BIT 0
register PS int PSE export "PS signal end position in dot clock"
register PS int PSE goto (0xffff << LCD_PS_PSE_BIT)

// 
/* CLS Signal Setting */
const LCD_CLS_CLSS_BIT 16
register CLS int CLSS export "CLS signal start position in dot clock"
register CLS int CLSS goto (0xffff << LCD_CLS_CLSS_BIT)
const LCD_CLS_CLSE_BIT 0
register CLS int CLSE export "CLS signal end position in dot clock"
register CLS int CLSE goto (0xffff << LCD_CLS_CLSE_BIT)

// 
/* SPL Signal Setting */
const LCD_SPL_SPLS_BIT 16
register SPL int SPLS export "SPL signal start position in dot clock"
register SPL int SPLS goto (0xffff << LCD_SPL_SPLS_BIT)
const LCD_SPL_SPLE_BIT 0
register SPL int SPLE export "SPL signal end position in dot clock"
register SPL int SPLE goto (0xffff << LCD_SPL_SPLE_BIT)

// 
/* REV Signal Setting */
const LCD_REV_REVS_BIT 16
register REV int REVS export "REV signal start position in dot clock"
register REV int REVS goto (0xffff << LCD_REV_REVS_BIT)

// 
/* DMA Command Register */
register CMD int SOFINT goto 31
register CMD int EOFINT goto 30
register CMD int CMD goto 29 export "indicate command in slcd mode"
register CMD int PAL goto 28
const LCD_CMD_LEN_BIT 0
register CMD int LEN goto (0xffffff << LCD_CMD_LEN_BIT)

// 
/* DMA Offsize Register 0,1 */

// 
/* DMA Page Width Register 0,1 */

// 
/* DMA Command Counter Register 0,1 */

// 
/* Foreground 0,1 Size Register */
const LCD_DESSIZE_HEIGHT_BIT 16
register DESSIZE int HEIGHT export "height of foreground 1"
register DESSIZE int HEIGHT goto (0xffff << LCD_DESSIZE_HEIGHT_BIT)
const LCD_DESSIZE_WIDTH_BIT 0
register DESSIZE int WIDTH export "width of foreground 1"
register DESSIZE int WIDTH goto (0xffff << LCD_DESSIZE_WIDTH_BIT)

// 

// 
/* EPD */
this class EPD goto 0xB3050000 export "EPD"

// 
register CTRL goto 0x200 export ""
register STA goto 0x204 export ""
register ISR goto 0x208 export ""
register CFG0 goto 0x20C export ""
register CFG1 goto 0x210 export ""
register PPL0 goto 0x214 export ""
register PPL1 goto 0x218 export ""
register VAT goto 0x21C export ""
register DAV goto 0x220 export ""
register DAH goto 0x224 export ""
register VSYNC goto 0x228 export ""
register HSYNC goto 0x22C export ""
register GDCLK goto 0x230 export ""
register GDOE goto 0x234 export ""
register GDSP goto 0x238 export ""
register SDOE goto 0x23C export ""
register SDSP goto 0x240 export ""
register PMGR0 goto 0x244 export ""
register PMGR1 goto 0x248 export ""
register PMGR2 goto 0x24C export ""
register PMGR3 goto 0x250 export ""
register PMGR4 goto 0x254 export ""
register VCOM0 goto 0x258 export ""
register VCOM1 goto 0x25C export ""
register VCOM2 goto 0x260 export ""
register VCOM3 goto 0x264 export ""
register VCOM4 goto 0x268 export ""
register VCOM5 goto 0x26C export ""
register BORDR goto 0x270 export ""
register PPL_POS goto (0,0x280) export ""
// #define EPD_PPL_SIZE(00   (EPD_BASE + 0x284)
register PPL_POS goto (1,0x288) export ""
register PPL_SIZE goto (1,0x28C) export ""
register PPL_POS goto (2,0x290) export ""
register PPL_SIZE goto (2,0x294) export ""
register PPL_POS goto (3,0x298) export ""
register PPL_SIZE goto (3,0x29C) export ""
register PPL_POS goto (4,0x2A0) export ""
register PPL_SIZE goto (4,0x2A4) export ""
register PPL_POS goto (5,0x2A8) export ""
register PPL_SIZE goto (5,0x2AC) export ""
register PPL_POS goto (6,0x2B0) export ""
register PPL_SIZE goto (6,0x2B4) export ""
register PPL_POS goto (7,0x2B8) export ""
register PPL_SIZE goto (7,0x2BC) export ""

// 
register CTRL sizeof 32
register STA sizeof 32
register ISR sizeof 32
register CFG0 sizeof 32
register CFG1 sizeof 32
register PPL0 sizeof 32
register PPL1 sizeof 32
register VAT sizeof 32
register DAV sizeof 32
register DAH sizeof 32
register VSYNC sizeof 32
register HSYNC sizeof 32
register GDCLK sizeof 32
register GDOE sizeof 32
register GDSP sizeof 32
register SDOE sizeof 32
register SDSP sizeof 32
register PMGR0 sizeof 32
register PMGR1 sizeof 32
register PMGR2 sizeof 32
register PMGR3 sizeof 32
register PMGR4 sizeof 32
register VCOM0 sizeof 32
register VCOM1 sizeof 32
register VCOM2 sizeof 32
register VCOM3 sizeof 32
register VCOM4 sizeof 32
register VCOM5 sizeof 32
register BORDR sizeof 32
// #define REG_EPD_PPL_POS(n)   REG32(EPD_PPL0_POS(n))   
// #define REG_EPD_PPL_SIZE(n)  REG32(EPD_PPL0_SIZE(n))  
// #define REG_EPD_PPL0_POS   REG32(EPD_PPL0_POS)   
// #define REG_EPD_PPL0_SIZE  REG32(EPD_PPL0_SIZE)  
// #define REG_EPD_PPL1_POS   REG32(EPD_PPL1_POS)   
// #define REG_EPD_PPL1_SIZE  REG32(EPD_PPL1_SIZE)  
// #define REG_EPD_PPL2_POS   REG32(EPD_PPL2_POS)   
// #define REG_EPD_PPL2_SIZE  REG32(EPD_PPL2_SIZE)  
// #define REG_EPD_PPL3_POS   REG32(EPD_PPL3_POS)   
// #define REG_EPD_PPL3_SIZE  REG32(EPD_PPL3_SIZE)  
// #define REG_EPD_PPL4_POS   REG32(EPD_PPL4_POS)    
// #define REG_EPD_PPL4_SIZE  REG32(EPD_PPL4_SIZE)  
// #define REG_EPD_PPL5_POS   REG32(EPD_PPL5_POS)   
// #define REG_EPD_PPL5_SIZE  REG32(EPD_PPL5_SIZE)  
// #define REG_EPD_PPL6_POS   REG32(EPD_PPL6_POS)   
// #define REG_EPD_PPL6_SIZE  REG32(EPD_PPL6_SIZE)  
// #define REG_EPD_PPL7_POS   REG32(EPD_PPL7_POS)   
// #define REG_EPD_PPL7_SIZE  REG32(EPD_PPL7_SIZE)  

// 
register CTRL int PPL7_FRM_INTM goto 31
register CTRL int PPL6_FRM_INTM goto 30
register CTRL int PPL5_FRM_INTM goto 29
register CTRL int PPL4_FRM_INTM goto 28
register CTRL int PPL3_FRM_INTM goto 27
register CTRL int PPL2_FRM_INTM goto 26
register CTRL int PPL1_FRM_INTM goto 25
register CTRL int PPL0_FRM_INTM goto 24
register CTRL int FRM_VCOM_INTM goto 22
register CTRL int IMG_DONE_INTM goto 21
register CTRL int FRM_DONE_INTM goto 20
register CTRL int FRM_ABT_INTM goto 19
register CTRL int PWR_OFF_INTM goto 18
register CTRL int PWR_ON_INTM goto 17
register CTRL int DMA_DONE_INTM goto 16
register CTRL int PPL7_FRM_ENA goto 15
register CTRL int PPL6_FRM_ENA goto 14
register CTRL int PPL5_FRM_ENA goto 13
register CTRL int PPL4_FRM_ENA goto 12
register CTRL int PPL3_FRM_ENA goto 11
register CTRL int PPL2_FRM_ENA goto 10
register CTRL int PPL1_FRM_ENA goto 9
register CTRL int PPL0_FRM_ENA goto 8
register CTRL int IMG_REF_ENA goto 6
register CTRL int IMG_REF_ABT goto 7
register CTRL int PWROFF goto 5
register CTRL int PWRON goto 4
register CTRL int EPD_DMA_MODE goto 1
register CTRL int EPD_ENA goto 0

// 
register ISR int PPL7_FRM_INT goto 15
register ISR int PPL6_FRM_INT goto 14
register ISR int PPL5_FRM_INT goto 13
register ISR int PPL4_FRM_INT goto 12
register ISR int PPL3_FRM_INT goto 11
register ISR int PPL2_FRM_INT goto 10
register ISR int PPL1_FRM_INT goto 9
register ISR int PPL0_FRM_INT goto 8
register ISR int FRM_VCOM_INT goto 6
register ISR int IMG_DONE_INT goto 5
register ISR int FRM_DONE_INT goto 4
register ISR int FRM_ABT_INT goto 3
register ISR int PWR_OFF_INT goto 2
register ISR int PWR_ON_INT goto 1
register ISR int DMA_DONE_INT goto 0

// 
register CFG0 int DUAL_GATE goto 31
register CFG0 int COLOR_MODE goto 30
const EPD_CFG0_COLOR_FORMAT_BIT 27
register CFG0 int COLOR_FORMAT goto (0x7 << EPD_CFG0_COLOR_FORMAT_BIT)
register CFG0 int SDSP_CAS goto 26
register CFG0 int SDSP_MODE goto 25
register CFG0 int GDCLK_MODE goto 24
const EPD_CFG0_GDOE_MODE_BIT 22
register CFG0 int GDOE_MODE goto (0x3 << EPD_CFG0_GDOE_MODE_BIT)
register CFG0 int GDUD goto 21
register CFG0 int SDRL goto 20
register CFG0 int GDCLK_POL goto 19
register CFG0 int GDOE_POL goto 18
register CFG0 int GDSP_POL goto 17
register CFG0 int SDCLK_POL goto 16
register CFG0 int SDOE_POL goto 15
register CFG0 int SDSP_POL goto 14
register CFG0 int SDCE_POL goto 13
register CFG0 int SDLE_POL goto 12
register CFG0 int GDSP_CAS goto 9
register CFG0 int COMP_MODE goto 8
const EPD_CFG0_EPD_OBPP_BIT 1
register CFG0 int EPD_OBPP goto (0x7 << EPD_CFG0_EPD_OBPP_BIT)
register CFG0 int EPD_OMODE goto 0

// 
register CFG1 int SDDO_REV goto 30
register CFG1 int PDAT_SWAP goto 29
register CFG1 int SDCE_REV goto 28
const EPD_CFG1_SDOS_BIT 16
register CFG1 int SDOS goto (0xff << EPD_CFG1_SDOS_BIT)
const EPD_CFG1_PADDING_DAT_BIT 8
register CFG1 int PADDING_DAT goto (0xff << EPD_CFG1_PADDING_DAT_BIT)
const EPD_CFG1_SDCE_STN_BIT 4
register CFG1 int SDCE_STN goto (0xf << EPD_CFG1_SDCE_STN_BIT)
const EPD_CFG1_SDCE_NUM_BIT 0
register CFG1 int SDCE_NUM goto (0xf << EPD_CFG1_SDCE_NUM_BIT)

// 
const EPD_PPL0_PPL3_FRM_NUM_BIT 24
register PPL0 int PPL3_FRM_NUM goto (0xff << EPD_PPL0_PPL3_FRM_NUM_BIT)
const EPD_PPL0_PPL2_FRM_NUM_BIT 16
register PPL0 int PPL2_FRM_NUM goto (0xff << EPD_PPL0_PPL2_FRM_NUM_BIT)
const EPD_PPL0_PPL1_FRM_NUM_BIT 8
register PPL0 int PPL1_FRM_NUM goto (0xff << EPD_PPL0_PPL1_FRM_NUM_BIT)
const EPD_PPL0_PPL0_FRM_NUM_BIT 0
register PPL0 int PPL0_FRM_NUM goto (0xff << EPD_PPL0_PPL0_FRM_NUM_BIT)

// 
const EPD_PPL1_PPL7_FRM_NUM_BIT 24
register PPL1 int PPL7_FRM_NUM goto (0xff << EPD_PPL1_PPL7_FRM_NUM_BIT)
const EPD_PPL1_PPL6_FRM_NUM_BIT 16
register PPL1 int PPL6_FRM_NUM goto (0xff << EPD_PPL1_PPL6_FRM_NUM_BIT)
const EPD_PPL1_PPL5_FRM_NUM_BIT 8
register PPL1 int PPL5_FRM_NUM goto (0xff << EPD_PPL1_PPL5_FRM_NUM_BIT)
const EPD_PPL1_PPL4_FRM_NUM_BIT 0
register PPL1 int PPL4_FRM_NUM goto (0xff << EPD_PPL1_PPL4_FRM_NUM_BIT)

// 
const EPD_VAT_VT_BIT 16
register VAT int VT goto (0xfff << EPD_VAT_VT_BIT)
const EPD_VAT_HT_BIT 0
register VAT int HT goto (0xfff << EPD_VAT_HT_BIT)

// 
const EPD_DAH_HDE_BIT 16
register DAH int HDE goto (0xfff << EPD_DAH_HDE_BIT)
const EPD_DAH_HDS_BIT 0
register DAH int HDS goto (0xfff << EPD_DAH_HDS_BIT)

// 
const EPD_DAV_VDE_BIT 16
register DAV int VDE goto (0xfff << EPD_DAV_VDE_BIT)
const EPD_DAV_VDS_BIT 0
register DAV int VDS goto (0xfff << EPD_DAV_VDS_BIT)

// 
const EPD_VSYNC_VPE_BIT 16
register VSYNC int VPE goto (0xfff << EPD_VSYNC_VPE_BIT)
const EPD_VSYNC_VPS_BIT 0
register VSYNC int VPS goto (0xfff << EPD_VSYNC_VPS_BIT)

// 
const EPD_HSYNC_HPE_BIT 16
register HSYNC int HPE goto (0xfff << EPD_HSYNC_HPE_BIT)
const EPD_HSYNC_HPS_BIT 0
register HSYNC int HPS goto (0xfff << EPD_HSYNC_HPS_BIT)

// 
const EPD_GDCLK_DIS_BIT 16
register GDCLK int DIS goto (0xfff << EPD_GDCLK_DIS_BIT)
const EPD_GDCLK_ENA_BIT 0
register GDCLK int ENA goto (0xfff << EPD_GDCLK_ENA_BIT)

// 
const EPD_GDOE_DIS_BIT 16
register GDOE int DIS goto (0xfff << EPD_GDOE_DIS_BIT)
const EPD_GDOE_ENA_BIT 0
register GDOE int ENA goto (0xfff << EPD_GDOE_ENA_BIT)

// 
const EPD_GDSP_DIS_BIT 16
register GDSP int DIS goto (0xfff << EPD_GDSP_DIS_BIT)
const EPD_GDSP_ENA_BIT 0
register GDSP int ENA goto (0xfff << EPD_GDSP_ENA_BIT)

// 
const EPD_SDOE_DIS_BIT 16
register SDOE int DIS goto (0xfff << EPD_SDOE_DIS_BIT)
const EPD_SDOE_ENA_BIT 0
register SDOE int ENA goto (0xfff << EPD_SDOE_ENA_BIT)

// 
const EPD_SDSP_DIS_BIT 16
register SDSP int DIS goto (0xfff << EPD_SDSP_DIS_BIT)
const EPD_SDSP_ENA_BIT 0
register SDSP int ENA goto (0xfff << EPD_SDSP_ENA_BIT)

// 
const EPD_PMGR0_PWR_DLY12_BIT 16
register PMGR0 int PWR_DLY12 goto (0xfff << EPD_PMGR0_PWR_DLY12_BIT)
const EPD_PMGR0_PWR_DLY01_BIT 0
register PMGR0 int PWR_DLY01 goto (0xfff << EPD_PMGR0_PWR_DLY01_BIT)

// 
const EPD_PMGR1_PWR_DLY34_BIT 16
register PMGR1 int PWR_DLY34 goto (0xfff << EPD_PMGR1_PWR_DLY34_BIT)
const EPD_PMGR1_PWR_DLY23_BIT 0
register PMGR1 int PWR_DLY23 goto (0xfff << EPD_PMGR1_PWR_DLY23_BIT)

// 
const EPD_PMGR2_PWR_DLY56_BIT 16
register PMGR2 int PWR_DLY56 goto (0xfff << EPD_PMGR2_PWR_DLY56_BIT)
const EPD_PMGR2_PWR_DLY45_BIT 0
register PMGR2 int PWR_DLY45 goto (0xfff << EPD_PMGR2_PWR_DLY45_BIT)

// 
const EPD_PMGR3_VCOM_IDLE_BIT 30
register PMGR3 int VCOM_IDLE goto (0x3 << EPD_PMGR3_VCOM_IDLE_BIT)
register PMGR3 int PWRCOM_POL goto 29
register PMGR3 int UNI_POL goto 28
register PMGR3 int PPL7_BDR_ENA goto 27
register PMGR3 int BDR_LEVEL goto 26
const EPD_PMGR3_BDR_VALUE_BIT 24
register PMGR3 int BDR_VALUE goto (0x3 << EPD_PMGR3_BDR_VALUE_BIT)
const EPD_PMGR3_PWR_POL_BIT 16
register PMGR3 int PWR_POL goto (0xff << EPD_PMGR3_PWR_POL_BIT)
const EPD_PMGR3_PWR_DLY67_BIT 0
register PMGR3 int PWR_DLY67 goto (0xfff << EPD_PMGR3_PWR_DLY67_BIT)

// 
const EPD_PMGR4_PWR_VAL_BIT 16
register PMGR4 int PWR_VAL goto (0xff << EPD_PMGR4_PWR_VAL_BIT)
const EPD_PMGR4_PWR_ENA_BIT 0
register PMGR4 int PWR_ENA goto (0xff << EPD_PMGR4_PWR_ENA_BIT)

// 
const EPD_PPL_POS_PPL_YPOS_BIT 16
register PPL_POS int PPL_YPOS goto (0xfff << EPD_PPL_POS_PPL_YPOS_BIT)
const EPD_PPL_POS_PPL_XPOS_BIT 0
register PPL_POS int PPL_XPOS goto (0xfff << EPD_PPL_POS_PPL_XPOS_BIT)

// 
const EPD_PPL_SIZE_PPL_HEIGHT_BIT 16
register PPL_SIZE int PPL_HEIGHT goto (0xfff << EPD_PPL_SIZE_PPL_HEIGHT_BIT)
const EPD_PPL_SIZE_PPL_WIDTH_BIT 0
register PPL_SIZE int PPL_WIDTH goto (0xfff << EPD_PPL_SIZE_PPL_WIDTH_BIT)

// 
// #ifndef __MIPS_ASSEMBLER

// 
/*************************************************************************
 * SLCD (Smart LCD Controller)
 *************************************************************************/
// #define __slcd_set_data_18bit() \
//   ( REG_SLCD_CFG = (REG_SLCD_CFG & ~SLCD_CFG_DWIDTH_MASK) | SLCD_CFG_DWIDTH_18BIT )
// #define __slcd_set_data_16bit() \
//   ( REG_SLCD_CFG = (REG_SLCD_CFG & ~SLCD_CFG_DWIDTH_MASK) | SLCD_CFG_DWIDTH_16BIT )
// #define __slcd_set_data_8bit_x3() \
//   ( REG_SLCD_CFG = (REG_SLCD_CFG & ~SLCD_CFG_DWIDTH_MASK) | SLCD_CFG_DWIDTH_8BIT_x3 )
// #define __slcd_set_data_8bit_x2() \
//   ( REG_SLCD_CFG = (REG_SLCD_CFG & ~SLCD_CFG_DWIDTH_MASK) | SLCD_CFG_DWIDTH_8BIT_x2 )
// #define __slcd_set_data_8bit_x1() \
//   ( REG_SLCD_CFG = (REG_SLCD_CFG & ~SLCD_CFG_DWIDTH_MASK) | SLCD_CFG_DWIDTH_8BIT_x1 )
// #define __slcd_set_data_24bit() \
//   ( REG_SLCD_CFG = (REG_SLCD_CFG & ~SLCD_CFG_DWIDTH_MASK) | SLCD_CFG_DWIDTH_24BIT )
// #define __slcd_set_data_9bit_x2() \
//   ( REG_SLCD_CFG = (REG_SLCD_CFG & ~SLCD_CFG_DWIDTH_MASK) | SLCD_CFG_DWIDTH_9BIT_x2 )

// 
// #define __slcd_set_cmd_16bit() \
//   ( REG_SLCD_CFG = (REG_SLCD_CFG & ~SLCD_CFG_CWIDTH_MASK) | SLCD_CFG_CWIDTH_16BIT )
// #define __slcd_set_cmd_8bit() \
//   ( REG_SLCD_CFG = (REG_SLCD_CFG & ~SLCD_CFG_CWIDTH_MASK) | SLCD_CFG_CWIDTH_8BIT )
// #define __slcd_set_cmd_18bit() \
//   ( REG_SLCD_CFG = (REG_SLCD_CFG & ~SLCD_CFG_CWIDTH_MASK) | SLCD_CFG_CWIDTH_18BIT )
// #define __slcd_set_cmd_24bit() \
//   ( REG_SLCD_CFG = (REG_SLCD_CFG & ~SLCD_CFG_CWIDTH_MASK) | SLCD_CFG_CWIDTH_24BIT )

// 
// #define __slcd_set_cs_high()        ( REG_SLCD_CFG |= SLCD_CFG_CS_ACTIVE_HIGH )
// #define __slcd_set_cs_low()         ( REG_SLCD_CFG &= ~SLCD_CFG_CS_ACTIVE_HIGH )

// 
// #define __slcd_set_rs_high()        ( REG_SLCD_CFG |= SLCD_CFG_RS_CMD_HIGH )
// #define __slcd_set_rs_low()         ( REG_SLCD_CFG &= ~SLCD_CFG_RS_CMD_HIGH )

// 
// #define __slcd_set_clk_falling()    ( REG_SLCD_CFG &= ~SLCD_CFG_CLK_ACTIVE_RISING )
// #define __slcd_set_clk_rising()     ( REG_SLCD_CFG |= SLCD_CFG_CLK_ACTIVE_RISING )

// 
// #define __slcd_set_parallel_type()  ( REG_SLCD_CFG &= ~SLCD_CFG_TYPE_SERIAL )
// #define __slcd_set_serial_type()    ( REG_SLCD_CFG |= SLCD_CFG_TYPE_SERIAL )

// 
/* SLCD Control Register */
// #define __slcd_enable_dma()         ( REG_SLCD_CTRL |= SLCD_CTRL_DMA_EN )
// #define __slcd_disable_dma()        ( REG_SLCD_CTRL &= ~SLCD_CTRL_DMA_EN )

// 
/* SLCD Status Register */
// #define __slcd_is_busy()            ( REG_SLCD_STATE & SLCD_STATE_BUSY )

// 
/* SLCD Data Register */
// #define __slcd_set_cmd_rs()         ( REG_SLCD_DATA |= SLCD_DATA_RS_COMMAND)
// #define __slcd_set_data_rs()        ( REG_SLCD_DATA &= ~SLCD_DATA_RS_COMMAND)

// 

// 
/***************************************************************************
 * LCD
 ***************************************************************************/

// 
/***************************************************************************
 * LCD
 ***************************************************************************/
// #define __lcd_as_smart_lcd() 		( REG_LCD_CFG |= ( LCD_CFG_LCDPIN_SLCD | LCD_CFG_MODE_SLCD))
// #define __lcd_as_general_lcd() 		( REG_LCD_CFG &= ~( LCD_CFG_LCDPIN_SLCD | LCD_CFG_MODE_SLCD))

// 
// #define __lcd_enable_tvepeh() 		( REG_LCD_CFG |= LCD_CFG_TVEPEH )
// #define __lcd_disable_tvepeh() 		( REG_LCD_CFG &= ~LCD_CFG_TVEPEH )

// 
// #define __lcd_enable_fuhold() 		( REG_LCD_CFG |= LCD_CFG_FUHOLD )
// #define __lcd_disable_fuhold() 		( REG_LCD_CFG &= ~LCD_CFG_FUHOLD )

// 
// #define __lcd_des_8word() 		( REG_LCD_CFG |= LCD_CFG_NEWDES )
// #define __lcd_des_4word() 		( REG_LCD_CFG &= ~LCD_CFG_NEWDES )

// 
// #define __lcd_enable_bypass_pal() 	( REG_LCD_CFG |= LCD_CFG_PALBP )
// #define __lcd_disable_bypass_pal() 	( REG_LCD_CFG &= ~LCD_CFG_PALBP )

// 
// #define __lcd_set_lcdpnl_term()		( REG_LCD_CFG |= LCD_CFG_TVEN )
// #define __lcd_set_tv_term()		( REG_LCD_CFG &= ~LCD_CFG_TVEN )

// 
// #define __lcd_enable_auto_recover() 	( REG_LCD_CFG |= LCD_CFG_RECOVER )
// #define __lcd_disable_auto_recover() 	( REG_LCD_CFG &= ~LCD_CFG_RECOVER )

// 
// #define __lcd_enable_dither() 	        ( REG_LCD_CFG |= LCD_CFG_DITHER )
// #define __lcd_disable_dither() 	        ( REG_LCD_CFG &= ~LCD_CFG_DITHER )

// 
// #define __lcd_disable_ps_mode()	        ( REG_LCD_CFG |= LCD_CFG_PSM )
// #define __lcd_enable_ps_mode()	        ( REG_LCD_CFG &= ~LCD_CFG_PSM )

// 
// #define __lcd_disable_cls_mode() 	( REG_LCD_CFG |= LCD_CFG_CLSM )
// #define __lcd_enable_cls_mode()	        ( REG_LCD_CFG &= ~LCD_CFG_CLSM )

// 
// #define __lcd_disable_spl_mode() 	( REG_LCD_CFG |= LCD_CFG_SPLM )
// #define __lcd_enable_spl_mode()	        ( REG_LCD_CFG &= ~LCD_CFG_SPLM )

// 
// #define __lcd_disable_rev_mode() 	( REG_LCD_CFG |= LCD_CFG_REVM )
// #define __lcd_enable_rev_mode()	        ( REG_LCD_CFG &= ~LCD_CFG_REVM )

// 
// #define __lcd_disable_hsync_mode() 	( REG_LCD_CFG |= LCD_CFG_HSYNM )
// #define __lcd_enable_hsync_mode()	( REG_LCD_CFG &= ~LCD_CFG_HSYNM )

// 
// #define __lcd_disable_pclk_mode() 	( REG_LCD_CFG |= LCD_CFG_PCLKM )
// #define __lcd_enable_pclk_mode()	( REG_LCD_CFG &= ~LCD_CFG_PCLKM )

// 
// #define __lcd_normal_outdata()          ( REG_LCD_CFG &= ~LCD_CFG_INVDAT )
// #define __lcd_inverse_outdata()         ( REG_LCD_CFG |= LCD_CFG_INVDAT )

// 
// #define __lcd_sync_input()              ( REG_LCD_CFG |= LCD_CFG_SYNDIR_IN )
// #define __lcd_sync_output()             ( REG_LCD_CFG &= ~LCD_CFG_SYNDIR_IN )

// 
// #define __lcd_hsync_active_high()       ( REG_LCD_CFG &= ~LCD_CFG_HSP )
// #define __lcd_hsync_active_low()        ( REG_LCD_CFG |= LCD_CFG_HSP )

// 
// #define __lcd_pclk_rising()             ( REG_LCD_CFG &= ~LCD_CFG_PCP )
// #define __lcd_pclk_falling()            ( REG_LCD_CFG |= LCD_CFG_PCP )

// 
// #define __lcd_de_active_high()          ( REG_LCD_CFG &= ~LCD_CFG_DEP )
// #define __lcd_de_active_low()           ( REG_LCD_CFG |= LCD_CFG_DEP )

// 
// #define __lcd_vsync_rising()            ( REG_LCD_CFG &= ~LCD_CFG_VSP )
// #define __lcd_vsync_falling()           ( REG_LCD_CFG |= LCD_CFG_VSP )

// 
// #define __lcd_set_16_tftpnl() \
//   ( REG_LCD_CFG = (REG_LCD_CFG & ~LCD_CFG_MODE_TFT_MASK) | LCD_CFG_MODE_TFT_16BIT )

// 
// #define __lcd_set_18_tftpnl() \
//   ( REG_LCD_CFG = (REG_LCD_CFG & ~LCD_CFG_MODE_TFT_MASK) | LCD_CFG_MODE_TFT_18BIT )

// 
// #define __lcd_set_24_tftpnl()		( REG_LCD_CFG |= LCD_CFG_MODE_TFT_24BIT )

// 
/* 
 * n=1,2,4,8 for single mono-STN 
 * n=4,8 for dual mono-STN
 */
// #define __lcd_set_panel_datawidth(n) 		\
// do { 						\
// 	REG_LCD_CFG &= ~LCD_CFG_PDW_MASK; 	\
// 	REG_LCD_CFG |= LCD_CFG_PDW_n##;		\
// } while (0)

// 
/* m = LCD_CFG_MODE_GENERUIC_TFT_xxx */
// #define __lcd_set_panel_mode(m) 		\
// do {						\
// 	REG_LCD_CFG &= ~LCD_CFG_MODE_MASK;	\
// 	REG_LCD_CFG |= (m);			\
// } while(0)

// 
/* n=4,8,16 */
// #define __lcd_set_burst_length(n) 		\
// do {						\
// 	REG_LCD_CTRL &= ~LCD_CTRL_BST_MASK;	\
// 	REG_LCD_CTRL |= LCD_CTRL_BST_n##;	\
// } while (0)

// 
// #define __lcd_select_rgb565()		( REG_LCD_CTRL &= ~LCD_CTRL_RGB555 )
// #define __lcd_select_rgb555()		( REG_LCD_CTRL |= LCD_CTRL_RGB555 )

// 
// #define __lcd_set_ofup()		( REG_LCD_CTRL |= LCD_CTRL_OFUP )
// #define __lcd_clr_ofup()		( REG_LCD_CTRL &= ~LCD_CTRL_OFUP )

// 
/* n=2,4,16 */
// #define __lcd_set_stn_frc(n) 			\
// do {						\
// 	REG_LCD_CTRL &= ~LCD_CTRL_FRC_MASK;	\
// 	REG_LCD_CTRL |= LCD_CTRL_FRC_n##;	\
// } while (0)

// 
// #define __lcd_enable_eof_intr()		( REG_LCD_CTRL |= LCD_CTRL_EOFM )
// #define __lcd_disable_eof_intr()	( REG_LCD_CTRL &= ~LCD_CTRL_EOFM )

// 
// #define __lcd_enable_sof_intr()		( REG_LCD_CTRL |= LCD_CTRL_SOFM )
// #define __lcd_disable_sof_intr()	( REG_LCD_CTRL &= ~LCD_CTRL_SOFM )

// 
// #define __lcd_enable_ofu_intr()		( REG_LCD_CTRL |= LCD_CTRL_OFUM )
// #define __lcd_disable_ofu_intr()	( REG_LCD_CTRL &= ~LCD_CTRL_OFUM )

// 
// #define __lcd_enable_ifu0_intr()	( REG_LCD_CTRL |= LCD_CTRL_IFUM0 )
// #define __lcd_disable_ifu0_intr()	( REG_LCD_CTRL &= ~LCD_CTRL_IFUM0 )

// 
// #define __lcd_enable_ifu1_intr()	( REG_LCD_CTRL |= LCD_CTRL_IFUM1 )
// #define __lcd_disable_ifu1_intr()	( REG_LCD_CTRL &= ~LCD_CTRL_IFUM1 )

// 
// #define __lcd_enable_ldd_intr()		( REG_LCD_CTRL |= LCD_CTRL_LDDM )
// #define __lcd_disable_ldd_intr()	( REG_LCD_CTRL &= ~LCD_CTRL_LDDM )

// 
// #define __lcd_enable_qd_intr()		( REG_LCD_CTRL |= LCD_CTRL_QDM )
// #define __lcd_disable_qd_intr()		( REG_LCD_CTRL &= ~LCD_CTRL_QDM )

// 
// #define __lcd_reverse_byte_endian()	( REG_LCD_CTRL |= LCD_CTRL_BEDN )
// #define __lcd_normal_byte_endian()	( REG_LCD_CTRL &= ~LCD_CTRL_BEDN )

// 
// #define __lcd_pixel_endian_little()	( REG_LCD_CTRL |= LCD_CTRL_PEDN )
// #define __lcd_pixel_endian_big()	( REG_LCD_CTRL &= ~LCD_CTRL_PEDN )

// 
// #define __lcd_set_dis()			( REG_LCD_CTRL |= LCD_CTRL_DIS )
// #define __lcd_clr_dis()			( REG_LCD_CTRL &= ~LCD_CTRL_DIS )

// 
// #define __lcd_set_ena()			( REG_LCD_CTRL |= LCD_CTRL_ENA )
// #define __lcd_clr_ena()			( REG_LCD_CTRL &= ~LCD_CTRL_ENA )

// 
/* n=1,2,4,8,16 */
// #define __lcd_set_bpp(n) \
//   ( REG_LCD_CTRL = (REG_LCD_CTRL & ~LCD_CTRL_BPP_MASK) | LCD_CTRL_BPP_##n )

// 
/* LCD status register indication */

// 
// #define __lcd_quick_disable_done()	( REG_LCD_STATE & LCD_STATE_QD )
// #define __lcd_disable_done()		( REG_LCD_STATE & LCD_STATE_LDD )
// #define __lcd_infifo0_underrun()	( REG_LCD_STATE & LCD_STATE_IFU0 )
// #define __lcd_infifo1_underrun()	( REG_LCD_STATE & LCD_STATE_IFU1 )
// #define __lcd_outfifo_underrun()	( REG_LCD_STATE & LCD_STATE_OFU )
// #define __lcd_start_of_frame()		( REG_LCD_STATE & LCD_STATE_SOF )
// #define __lcd_end_of_frame()		( REG_LCD_STATE & LCD_STATE_EOF )

// 
// #define __lcd_clr_outfifounderrun()	( REG_LCD_STATE &= ~LCD_STATE_OFU )
// #define __lcd_clr_sof()			( REG_LCD_STATE &= ~LCD_STATE_SOF )
// #define __lcd_clr_eof()			( REG_LCD_STATE &= ~LCD_STATE_EOF )

// 
/* OSD functions */
// #define __lcd_enable_osd() 	(REG_LCD_OSDC |= LCD_OSDC_OSDEN)
// #define __lcd_enable_f0() 	(REG_LCD_OSDC |= LCD_OSDC_F0EN)
// #define __lcd_enable_f1()	(REG_LCD_OSDC |= LCD_OSDC_F1EN)
// #define __lcd_enable_alpha() 	(REG_LCD_OSDC |= LCD_OSDC_ALPHAEN)
// #define __lcd_enable_alphamd()	(REG_LCD_OSDC |= LCD_OSDC_ALPHAMD)

// 
// #define __lcd_disable_osd()	(REG_LCD_OSDC &= ~LCD_OSDC_OSDEN)
// #define __lcd_disable_f0() 	(REG_LCD_OSDC &= ~LCD_OSDC_F0EN)
// #define __lcd_disable_f1() 	(REG_LCD_OSDC &= ~LCD_OSDC_F1EN)
// #define __lcd_disable_alpha()	(REG_LCD_OSDC &= ~LCD_OSDC_ALPHAEN)
// #define __lcd_disable_alphamd()	(REG_LCD_OSDC &= ~LCD_OSDC_ALPHAMD)

// 
/* OSD Controll Register */
// #define __lcd_fg1_use_ipu() 		(REG_LCD_OSDCTRL |= LCD_OSDCTRL_IPU)
// #define __lcd_fg1_use_dma_chan1() 	(REG_LCD_OSDCTRL &= ~LCD_OSDCTRL_IPU)
// #define __lcd_fg1_unuse_ipu() 		__lcd_fg1_use_dma_chan1()
// #define __lcd_osd_rgb555_mode()         ( REG_LCD_OSDCTRL |= LCD_OSDCTRL_RGB555 )
// #define __lcd_osd_rgb565_mode()         ( REG_LCD_OSDCTRL &= ~LCD_OSDCTRL_RGB555 )
// #define __lcd_osd_change_size()         ( REG_LCD_OSDCTRL |= LCD_OSDCTRL_CHANGES )
// #define __lcd_osd_bpp_15_16() \
//   ( REG_LCD_OSDCTRL = (REG_LCD_OSDCTRL & ~LCD_OSDCTRL_OSDBPP_MASK) | LCD_OSDCTRL_OSDBPP_15_16 )
// #define __lcd_osd_bpp_18_24() \
//   ( REG_LCD_OSDCTRL = (REG_LCD_OSDCTRL & ~LCD_OSDCTRL_OSDBPP_MASK) | LCD_OSDCTRL_OSDBPP_18_24 )

// 
/* OSD State Register */
// #define __lcd_start_of_fg1()		( REG_LCD_STATE & LCD_OSDS_SOF1 )
// #define __lcd_end_of_fg1()		( REG_LCD_STATE & LCD_OSDS_EOF1 )
// #define __lcd_start_of_fg0()		( REG_LCD_STATE & LCD_OSDS_SOF0 )
// #define __lcd_end_of_fg0()		( REG_LCD_STATE & LCD_OSDS_EOF0 )
// #define __lcd_change_is_rdy()		( REG_LCD_STATE & LCD_OSDS_READY )

// 
/* Foreground Color Key Register 0,1(foreground 0, foreground 1) */
// #define __lcd_enable_colorkey0()	(REG_LCD_KEY0 |= LCD_KEY_KEYEN)
// #define __lcd_enable_colorkey1()	(REG_LCD_KEY1 |= LCD_KEY_KEYEN)
// #define __lcd_enable_colorkey0_md() 	(REG_LCD_KEY0 |= LCD_KEY_KEYMD)
// #define __lcd_enable_colorkey1_md() 	(REG_LCD_KEY1 |= LCD_KEY_KEYMD)
// #define __lcd_set_colorkey0(key) 	(REG_LCD_KEY0 = (REG_LCD_KEY0&~0xFFFFFF)|(key))
// #define __lcd_set_colorkey1(key) 	(REG_LCD_KEY1 = (REG_LCD_KEY1&~0xFFFFFF)|(key))

// 
// #define __lcd_disable_colorkey0() 	(REG_LCD_KEY0 &= ~LCD_KEY_KEYEN)
// #define __lcd_disable_colorkey1() 	(REG_LCD_KEY1 &= ~LCD_KEY_KEYEN)
// #define __lcd_disable_colorkey0_md() 	(REG_LCD_KEY0 &= ~LCD_KEY_KEYMD)
// #define __lcd_disable_colorkey1_md() 	(REG_LCD_KEY1 &= ~LCD_KEY_KEYMD)

// 
/* IPU Restart Register */
// #define __lcd_enable_ipu_restart() 	(REG_LCD_IPUR |= LCD_IPUR_IPUREN)
// #define __lcd_disable_ipu_restart() 	(REG_LCD_IPUR &= ~LCD_IPUR_IPUREN)
// #define __lcd_set_ipu_restart_triger(n)	(REG_LCD_IPUR = (REG_LCD_IPUR&(~0xFFFFFF))|(n))

// 
/* RGB Control Register */
// #define __lcd_enable_rgb_dummy() 	(REG_LCD_RGBC |= LCD_RGBC_RGBDM)
// #define __lcd_disable_rgb_dummy() 	(REG_LCD_RGBC &= ~LCD_RGBC_RGBDM)

// 
// #define __lcd_dummy_rgb() 	(REG_LCD_RGBC |= LCD_RGBC_DMM)
// #define __lcd_rgb_dummy() 	(REG_LCD_RGBC &= ~LCD_RGBC_DMM)

// 
// #define __lcd_rgb2ycc() 	(REG_LCD_RGBC |= LCD_RGBC_YCC)
// #define __lcd_notrgb2ycc() 	(REG_LCD_RGBC &= ~LCD_RGBC_YCC)

// 
// #define __lcd_odd_mode_rgb() \
//   ( REG_LCD_RGBC = (REG_LCD_RGBC & ~LCD_RGBC_ODDRGB_MASK) | LCD_RGBC_ODD_RGB )
// #define __lcd_odd_mode_rbg() \
//   ( REG_LCD_RGBC = (REG_LCD_RGBC & ~LCD_RGBC_ODDRGB_MASK) | LCD_RGBC_ODD_RBG )
// #define __lcd_odd_mode_grb() \
//   ( REG_LCD_RGBC = (REG_LCD_RGBC & ~LCD_RGBC_ODDRGB_MASK) | LCD_RGBC_ODD_GRB)

// 
// #define __lcd_odd_mode_gbr() \
//   ( REG_LCD_RGBC = (REG_LCD_RGBC & ~LCD_RGBC_ODDRGB_MASK) | LCD_RGBC_ODD_GBR)
// #define __lcd_odd_mode_brg() \
//   ( REG_LCD_RGBC = (REG_LCD_RGBC & ~LCD_RGBC_ODDRGB_MASK) | LCD_RGBC_ODD_BRG)
// #define __lcd_odd_mode_bgr() \
//   ( REG_LCD_RGBC = (REG_LCD_RGBC & ~LCD_RGBC_ODDRGB_MASK) | LCD_RGBC_ODD_BGR)

// 
// #define __lcd_even_mode_rgb() \
//   ( REG_LCD_RGBC = (REG_LCD_RGBC & ~LCD_RGBC_EVENRGB_MASK) | LCD_RGBC_EVEN_RGB )
// #define __lcd_even_mode_rbg() \
//   ( REG_LCD_RGBC = (REG_LCD_RGBC & ~LCD_RGBC_EVENRGB_MASK) | LCD_RGBC_EVEN_RBG )
// #define __lcd_even_mode_grb() \
//   ( REG_LCD_RGBC = (REG_LCD_RGBC & ~LCD_RGBC_EVENRGB_MASK) | LCD_RGBC_EVEN_GRB)

// 
// #define __lcd_even_mode_gbr() \
//   ( REG_LCD_RGBC = (REG_LCD_RGBC & ~LCD_RGBC_EVENRGB_MASK) | LCD_RGBC_EVEN_GBR)
// #define __lcd_even_mode_brg() \
//   ( REG_LCD_RGBC = (REG_LCD_RGBC & ~LCD_RGBC_EVENRGB_MASK) | LCD_RGBC_EVEN_BRG)
// #define __lcd_even_mode_bgr() \
//   ( REG_LCD_RGBC = (REG_LCD_RGBC & ~LCD_RGBC_EVENRGB_MASK) | LCD_RGBC_EVEN_BGR)

// 
/* Vertical Synchronize Register */
// #define __lcd_vsync_get_vps() \
//   ( (REG_LCD_VSYNC & LCD_VSYNC_VPS_MASK) >> LCD_VSYNC_VPS_BIT )

// 
// #define __lcd_vsync_get_vpe() \
//   ( (REG_LCD_VSYNC & LCD_VSYNC_VPE_MASK) >> LCD_VSYNC_VPE_BIT )
// #define __lcd_vsync_set_vpe(n) 				\
// do {							\
// 	REG_LCD_VSYNC &= ~LCD_VSYNC_VPE_MASK;		\
// 	REG_LCD_VSYNC |= (n) << LCD_VSYNC_VPE_BIT;	\
// } while (0)

// 
// #define __lcd_hsync_get_hps() \
//   ( (REG_LCD_HSYNC & LCD_HSYNC_HPS_MASK) >> LCD_HSYNC_HPS_BIT )
// #define __lcd_hsync_set_hps(n) 				\
// do {							\
// 	REG_LCD_HSYNC &= ~LCD_HSYNC_HPS_MASK;		\
// 	REG_LCD_HSYNC |= (n) << LCD_HSYNC_HPS_BIT;	\
// } while (0)

// 
// #define __lcd_hsync_get_hpe() \
//   ( (REG_LCD_HSYNC & LCD_HSYNC_HPE_MASK) >> LCD_VSYNC_HPE_BIT )
// #define __lcd_hsync_set_hpe(n) 				\
// do {							\
// 	REG_LCD_HSYNC &= ~LCD_HSYNC_HPE_MASK;		\
// 	REG_LCD_HSYNC |= (n) << LCD_HSYNC_HPE_BIT;	\
// } while (0)

// 
// #define __lcd_vat_get_ht() \
//   ( (REG_LCD_VAT & LCD_VAT_HT_MASK) >> LCD_VAT_HT_BIT )
// #define __lcd_vat_set_ht(n) 				\
// do {							\
// 	REG_LCD_VAT &= ~LCD_VAT_HT_MASK;		\
// 	REG_LCD_VAT |= (n) << LCD_VAT_HT_BIT;		\
// } while (0)

// 
// #define __lcd_vat_get_vt() \
//   ( (REG_LCD_VAT & LCD_VAT_VT_MASK) >> LCD_VAT_VT_BIT )
// #define __lcd_vat_set_vt(n) 				\
// do {							\
// 	REG_LCD_VAT &= ~LCD_VAT_VT_MASK;		\
// 	REG_LCD_VAT |= (n) << LCD_VAT_VT_BIT;		\
// } while (0)

// 
// #define __lcd_dah_get_hds() \
//   ( (REG_LCD_DAH & LCD_DAH_HDS_MASK) >> LCD_DAH_HDS_BIT )
// #define __lcd_dah_set_hds(n) 				\
// do {							\
// 	REG_LCD_DAH &= ~LCD_DAH_HDS_MASK;		\
// 	REG_LCD_DAH |= (n) << LCD_DAH_HDS_BIT;		\
// } while (0)

// 
// #define __lcd_dah_get_hde() \
//   ( (REG_LCD_DAH & LCD_DAH_HDE_MASK) >> LCD_DAH_HDE_BIT )
// #define __lcd_dah_set_hde(n) 				\
// do {							\
// 	REG_LCD_DAH &= ~LCD_DAH_HDE_MASK;		\
// 	REG_LCD_DAH |= (n) << LCD_DAH_HDE_BIT;		\
// } while (0)

// 
// #define __lcd_dav_get_vds() \
//   ( (REG_LCD_DAV & LCD_DAV_VDS_MASK) >> LCD_DAV_VDS_BIT )
// #define __lcd_dav_set_vds(n) 				\
// do {							\
// 	REG_LCD_DAV &= ~LCD_DAV_VDS_MASK;		\
// 	REG_LCD_DAV |= (n) << LCD_DAV_VDS_BIT;		\
// } while (0)

// 
// #define __lcd_dav_get_vde() \
//   ( (REG_LCD_DAV & LCD_DAV_VDE_MASK) >> LCD_DAV_VDE_BIT )
// #define __lcd_dav_set_vde(n) 				\
// do {							\
// 	REG_LCD_DAV &= ~LCD_DAV_VDE_MASK;		\
// 	REG_LCD_DAV |= (n) << LCD_DAV_VDE_BIT;		\
// } while (0)

// 
/* DMA Command Register */
// #define __lcd_cmd0_set_sofint()		( REG_LCD_CMD0 |= LCD_CMD_SOFINT )
// #define __lcd_cmd0_clr_sofint()		( REG_LCD_CMD0 &= ~LCD_CMD_SOFINT )
// #define __lcd_cmd1_set_sofint()		( REG_LCD_CMD1 |= LCD_CMD_SOFINT )
// #define __lcd_cmd1_clr_sofint()		( REG_LCD_CMD1 &= ~LCD_CMD_SOFINT )

// 
// #define __lcd_cmd0_set_eofint()		( REG_LCD_CMD0 |= LCD_CMD_EOFINT )
// #define __lcd_cmd0_clr_eofint()		( REG_LCD_CMD0 &= ~LCD_CMD_EOFINT )
// #define __lcd_cmd1_set_eofint()		( REG_LCD_CMD1 |= LCD_CMD_EOFINT )
// #define __lcd_cmd1_clr_eofint()		( REG_LCD_CMD1 &= ~LCD_CMD_EOFINT )

// 
// #define __lcd_cmd0_set_pal()		( REG_LCD_CMD0 |= LCD_CMD_PAL )
// #define __lcd_cmd0_clr_pal()		( REG_LCD_CMD0 &= ~LCD_CMD_PAL )

// 
// #define __lcd_cmd0_get_len() \
//   ( (REG_LCD_CMD0 & LCD_CMD_LEN_MASK) >> LCD_CMD_LEN_BIT )
// #define __lcd_cmd1_get_len() \
//   ( (REG_LCD_CMD1 & LCD_CMD_LEN_MASK) >> LCD_CMD_LEN_BIT )

// 

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BLCDC_H__ */

// 
