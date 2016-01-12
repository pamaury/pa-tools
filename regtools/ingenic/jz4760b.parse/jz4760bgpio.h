/*
 * jz4760bgpio.h
 * JZ4760B GPIO register definition
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 *
 * Author: whxu@ingenic.cn
 */

// 
// #ifndef __JZ4760BGPIO_H__
// #define __JZ4760BGPIO_H__

// 

// 
/* General purpose I/O port module(GPIO) address definition */
this class GPIO goto 0xb0010000 export "General purpose I/O port module(GPIO) address definition"

// 
/* GPIO group offset */
const GPIO_GOS 0x100

// 
/* Each group address */
// #define GPIO_BASEA	(GPIO_BASE + (0) * GPIO_GOS)
// #define GPIO_BASEB	(GPIO_BASE + (1) * GPIO_GOS)
// #define GPIO_BASEC	(GPIO_BASE + (2) * GPIO_GOS)
// #define GPIO_BASED	(GPIO_BASE + (3) * GPIO_GOS)
// #define GPIO_BASEE	(GPIO_BASE + (4) * GPIO_GOS)
// #define GPIO_BASEF	(GPIO_BASE + (5) * GPIO_GOS)
// 
// #define GPA(x) 		(32 * 0 + (x))
// #define GPB(x) 		(32 * 1 + (x))
// #define GPC(x) 		(32 * 2 + (x))
// #define GPD(x) 		(32 * 3 + (x))
// #define GPE(x) 		(32 * 4 + (x))
// #define GPF(x) 		(32 * 5 + (x))

// 

// 
/*
 * GPIO registers offset address definition
 */
const GPIO_PXPIN_OFFSET 0x00
const GPIO_PXDAT_OFFSET 0x10
const GPIO_PXDATS_OFFSET 0x14
const GPIO_PXDATC_OFFSET 0x18
const GPIO_PXIM_OFFSET 0x20
const GPIO_PXIMS_OFFSET 0x24
const GPIO_PXIMC_OFFSET 0x28
const GPIO_PXPE_OFFSET 0x30
const GPIO_PXPES_OFFSET 0x34
const GPIO_PXPEC_OFFSET 0x38
const GPIO_PXFUN_OFFSET 0x40
const GPIO_PXFUNS_OFFSET 0x44
const GPIO_PXFUNC_OFFSET 0x48
const GPIO_PXSEL_OFFSET 0x50
const GPIO_PXSELS_OFFSET 0x54
const GPIO_PXSELC_OFFSET 0x58
const GPIO_PXDIR_OFFSET 0x60
const GPIO_PXDIRS_OFFSET 0x64
const GPIO_PXDIRC_OFFSET 0x68
const GPIO_PXTRG_OFFSET 0x70
const GPIO_PXTRGS_OFFSET 0x74
const GPIO_PXTRGC_OFFSET 0x78
const GPIO_PXFLG_OFFSET 0x80
const GPIO_PXFLGC_OFFSET 0x14

// 
const GPIO_PXDS0_OFFSET 0xc0
const GPIO_PXDS1_OFFSET 0xd0
const GPIO_PXDS2_OFFSET 0xe0
const GPIO_PXDS0S_OFFSET 0xc4
const GPIO_PXDS1S_OFFSET 0xd4
const GPIO_PXDS2S_OFFSET 0xe4
const GPIO_PXDS0C_OFFSET 0xc8
const GPIO_PXDS1C_OFFSET 0xd8
const GPIO_PXDS2C_OFFSET 0xe8
const GPIO_PXSL_OFFSET 0xf0
const GPIO_PXSLS_OFFSET 0xf4
const GPIO_PXSLC_OFFSET 0xf8

// 

// 
/*
 * GPIO registers address definition
 */
for n 0 5
register PXPIN goto<n> "(n)*GPIO_GOS + GPIO_PXPIN_OFFSET" export ""
register PXDAT goto<n> "(n)*GPIO_GOS + GPIO_PXDAT_OFFSET" export ""
register PXDATS goto<n> "(n)*GPIO_GOS + GPIO_PXDATS_OFFSET" export ""
register PXDATC goto<n> "(n)*GPIO_GOS + GPIO_PXDATC_OFFSET" export ""
register PXIM goto<n> "(n)*GPIO_GOS + GPIO_PXIM_OFFSET" export ""
register PXIMS goto<n> "(n)*GPIO_GOS + GPIO_PXIMS_OFFSET" export ""
register PXIMC goto<n> "(n)*GPIO_GOS + GPIO_PXIMC_OFFSET" export ""
register PXPE goto<n> "(n)*GPIO_GOS + GPIO_PXPE_OFFSET" export ""
register PXPES goto<n> "(n)*GPIO_GOS + GPIO_PXPES_OFFSET" export ""
register PXPEC goto<n> "(n)*GPIO_GOS + GPIO_PXPEC_OFFSET" export ""
register PXFUN goto<n> "(n)*GPIO_GOS + GPIO_PXFUN_OFFSET" export ""
register PXFUNS goto<n> "(n)*GPIO_GOS + GPIO_PXFUNS_OFFSET" export ""
register PXFUNC goto<n> "(n)*GPIO_GOS + GPIO_PXFUNC_OFFSET" export ""
register PXSEL goto<n> "(n)*GPIO_GOS + GPIO_PXSEL_OFFSET" export ""
register PXSELS goto<n> "(n)*GPIO_GOS + GPIO_PXSELS_OFFSET" export ""
register PXSELC goto<n> "(n)*GPIO_GOS + GPIO_PXSELC_OFFSET" export ""
register PXDIR goto<n> "(n)*GPIO_GOS + GPIO_PXDIR_OFFSET" export ""
register PXDIRS goto<n> "(n)*GPIO_GOS + GPIO_PXDIRS_OFFSET" export ""
register PXDIRC goto<n> "(n)*GPIO_GOS + GPIO_PXDIRC_OFFSET" export ""
register PXTRG goto<n> "(n)*GPIO_GOS + GPIO_PXTRG_OFFSET" export ""
register PXTRGS goto<n> "(n)*GPIO_GOS + GPIO_PXTRGS_OFFSET" export ""
register PXTRGC goto<n> "(n)*GPIO_GOS + GPIO_PXTRGC_OFFSET" export ""
register PXFLG goto<n> "(n)*GPIO_GOS + GPIO_PXFLG_OFFSET" export ""
register PXFLGC goto<n> "(n)*GPIO_GOS + GPIO_PXFLGC_OFFSET" export ""
/* n (1~5) */
register PXDS0 goto<n> "(n)*GPIO_GOS + GPIO_PXDS0_OFFSET" export ""
register PXDS0S goto<n> "(n)*GPIO_GOS + GPIO_PXDS0S_OFFSET" export ""
register PXDS0C goto<n> "(n)*GPIO_GOS + GPIO_PXDS0C_OFFSET" export ""
register PXDS1 goto<n> "(n)*GPIO_GOS + GPIO_PXDS1_OFFSET" export ""
register PXDS1S goto<n> "(n)*GPIO_GOS + GPIO_PXDS1S_OFFSET" export ""
register PXDS1C goto<n> "(n)*GPIO_GOS + GPIO_PXDS1C_OFFSET" export ""
register PXDS2 goto<n> "(n)*GPIO_GOS + GPIO_PXDS2_OFFSET" export ""
register PXDS2S goto<n> "(n)*GPIO_GOS + GPIO_PXDS2S_OFFSET" export ""
register PXDS2C goto<n> "(n)*GPIO_GOS + GPIO_PXDS2C_OFFSET" export ""
register PXSL goto<n> "(n)*GPIO_GOS + GPIO_PXSL_OFFSET" export ""
register PXSLS goto<n> "(n)*GPIO_GOS + GPIO_PXSLS_OFFSET" export ""
register PXSLC goto<n> "(n)*GPIO_GOS + GPIO_PXSLC_OFFSET" export ""

// 

// 

// 
/*  */
const GPIO_PORT_NUM 6
const MAX_GPIO_NUM 192
const GPIO_WAKEUP 30

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 
//n = 0,1,2,3,4,5 (PORTA, PORTB, PORTC, PORTD, PORTE, PORTF)
register PXPIN sizeof 32
register PXDAT sizeof 32
register PXDATS sizeof 32
register PXDATC sizeof 32
register PXIM sizeof 32
register PXIMS sizeof 32
register PXIMC sizeof 32
register PXPE sizeof 32
register PXPES sizeof 32
register PXPEC sizeof 32
register PXFUN sizeof 32
register PXFUNS sizeof 32
register PXFUNC sizeof 32
register PXSEL sizeof 32
register PXSELS sizeof 32
register PXSELC sizeof 32
register PXDIR sizeof 32
register PXDIRS sizeof 32
register PXDIRC sizeof 32
register PXTRG sizeof 32
register PXTRGS sizeof 32
register PXTRGC sizeof 32
register PXFLG sizeof 32
register PXFLGC sizeof 32

// 
/* n (1~5) */
register PXDS0 sizeof 32
register PXDS0S sizeof 32
register PXDS0C sizeof 32
register PXDS1 sizeof 32
register PXDS1S sizeof 32
register PXDS1C sizeof 32
register PXDS2 sizeof 32
register PXDS2S sizeof 32
register PXDS2C sizeof 32
register PXSL sizeof 32
register PXSLS sizeof 32
register PXSLC sizeof 32

// 
/*----------------------------------------------------------------
 * p is the port number (0,1,2,3,4,5)
 * o is the pin offset (0-31) inside the port
 * n is the absolute number of a pin (0-127), regardless of the port
 */

// 
//----------------------------------------------------------------
// Function Pins Mode

// 
// #define __gpio_as_func0(n)			\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXFUNS(p) = (1 << o);		\
// 	REG_GPIO_PXTRGC(p) = (1 << o);		\
// 	REG_GPIO_PXSELC(p) = (1 << o);		\
// } while (0)

// 
// #define __gpio_as_func1(n)			\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXFUNS(p) = (1 << o);		\
// 	REG_GPIO_PXTRGC(p) = (1 << o);		\
// 	REG_GPIO_PXSELS(p) = (1 << o);		\
// } while (0)

// 
// #define __gpio_as_func2(n)			\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXFUNS(p) = (1 << o);		\
// 	REG_GPIO_PXTRGS(p) = (1 << o);		\
// 	REG_GPIO_PXSELC(p) = (1 << o);		\
// } while (0)

// 
// #define __gpio_as_func3(n)			\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXFUNS(p) = (1 << o);		\
// 	REG_GPIO_PXTRGS(p) = (1 << o);		\
// 	REG_GPIO_PXSELS(p) = (1 << o);		\
// } while (0)

// 
/*
 * UART0_TxD, UART0_RxD
 */
// #define __gpio_as_uart0()			\
// do {						\
// 	unsigned int bits = BIT3 | BIT0;	\
// 	REG_GPIO_PXFUNS(5) = bits;		\
// 	REG_GPIO_PXTRGC(5) = bits;		\
// 	REG_GPIO_PXSELC(5) = bits;		\
// 	REG_GPIO_PXPES(5)  = bits;		\
// } while (0)

// 
/*
 * UART0_TxD, UART0_RxD, UART0_CTS, UART0_RTS
 */
// #define __gpio_as_uart0_ctsrts()		\
// do {						\
// 	unsigned int bits = BITS_H2L(3, 0);	\
// 	REG_GPIO_PXFUNS(5) = bits;		\
// 	REG_GPIO_PXTRGC(5) = bits;		\
// 	REG_GPIO_PXSELC(5) = bits;		\
// 	REG_GPIO_PXPES(5)  = bits;		\
// } while (0)

// 
/*
 * UART1_TxD, UART1_RxD
 */
// #define __gpio_as_uart1()			\
// do {						\
// 	unsigned int bits = BIT28 | BIT26;	\
// 	REG_GPIO_PXFUNS(3) = bits;		\
// 	REG_GPIO_PXTRGC(3) = bits;		\
// 	REG_GPIO_PXSELC(3) = bits;		\
// 	REG_GPIO_PXPES(3)  = bits;		\
// } while (0)

// 
/*
 * UART1_TxD, UART1_RxD, UART1_CTS, UART1_RTS
 */
// #define __gpio_as_uart1_ctsrts()		\
// do {						\
// 	unsigned int bits = BITS_H2L(29, 26);	\
// 	REG_GPIO_PXFUNS(3) = bits;		\
// 	REG_GPIO_PXTRGC(3) = bits;		\
// 	REG_GPIO_PXSELC(3) = bits;		\
// 	REG_GPIO_PXPES(3)  = bits;		\
// } while (0)

// 

// 
/*
 * UART2_TxD, UART2_RxD
 */
// #define __gpio_as_uart2()			\
// do {						\
// 	unsigned int bits = BIT30 | BIT28;	\
// 	REG_GPIO_PXFUNS(2) = bits;		\
// 	REG_GPIO_PXTRGC(2) = bits;		\
// 	REG_GPIO_PXSELC(2) = bits;		\
// 	REG_GPIO_PXPES(2)  = bits;		\
// } while (0)

// 
/*
 * UART2_TxD, UART2_RxD, UART2_CTS, UART2_RTS
 */
// #define __gpio_as_uart2_ctsrts()		\
// do {						\
// 	unsigned int bits = BITS_H2L(31, 28);	\
// 	REG_GPIO_PXFUNS(2) = bits;		\
// 	REG_GPIO_PXTRGC(2) = bits;		\
// 	REG_GPIO_PXSELC(2) = bits;		\
// 	REG_GPIO_PXPES(2)  = bits;		\
// } while (0)

// 
/* WARNING: the folloing macro do NOT check */
/*
 * UART3_TxD, UART3_RxD
 */
// #define __gpio_as_uart3()           \
// do {                        \
//     unsigned int rx_bit = BIT12,tx_bit= BIT5;   \
//     REG_GPIO_PXFUNS(3) = rx_bit;        \
//     REG_GPIO_PXTRGC(3) = rx_bit;        \
//     REG_GPIO_PXSELC(3) = rx_bit;        \
//     REG_GPIO_PXPES(3)  = rx_bit;        \
//     \
//     REG_GPIO_PXFUNS(4) = tx_bit;        \
//     REG_GPIO_PXTRGC(4) = tx_bit;        \
//     REG_GPIO_PXSELS(4) = tx_bit;        \
//     REG_GPIO_PXPES(4)  = tx_bit;        \
// } while (0)

// 
/*
 * UART3_TxD, UART3_RxD, UART3_CTS, UART3_RTS
 */
// #define __gpio_as_uart3_ctsrts()            \
// do {                        \
//     unsigned int rx_bit = BIT12,tx_bit= BIT5,   \
//                 bits = BITS_H2L(9, 8); \
//     REG_GPIO_PXFUNS(3) = rx_bit;        \
//     REG_GPIO_PXTRGC(3) = rx_bit;        \
//     REG_GPIO_PXSELC(3) = rx_bit;        \
//     REG_GPIO_PXPES(3)  = rx_bit;        \
//     \
//     REG_GPIO_PXFUNS(4) = tx_bit;        \
//     REG_GPIO_PXTRGC(4) = tx_bit;        \
//     REG_GPIO_PXSELS(4) = tx_bit;        \
//     REG_GPIO_PXPES(4)  = tx_bit;        \
//     REG_GPIO_PXFUNS(4) = bits;      \
//     REG_GPIO_PXTRGC(4) = bits;      \
//     REG_GPIO_PXSELC(4) = bits;      \
//     REG_GPIO_PXPES(4)  = bits;      \
// } while (0)

// 
/*
 * SD0 ~ SD7, CS1#, CLE, ALE, FRE#, FWE#, FRB#
 * @n: chip select number(1 ~ 6)
 */
// #define __gpio_as_nand_8bit(n)						\
// do {		              						\
// 									\
// 	REG_GPIO_PXFUNS(0) = 0x000c00ff; /* SD0 ~ SD7, CS1#, FRE#, FWE# */ \
// 	REG_GPIO_PXSELC(0) = 0x000c00ff;				\
// 	REG_GPIO_PXTRGC(0) = 0x000c00ff;				\
// 	REG_GPIO_PXPES(0) = 0x000c00ff;					\
// 	REG_GPIO_PXFUNS(1) = 0x00000003; /* CLE(SA2), ALE(SA3) */	\
// 	REG_GPIO_PXSELC(1) = 0x00000003;				\
// 	REG_GPIO_PXTRGC(1) = 0x00000003;				\
// 	REG_GPIO_PXPES(1) = 0x00000003;					\
// 									\
// 	REG_GPIO_PXFUNS(0) = 0x00200000 << ((n)-1); /* CSn */		\
// 	REG_GPIO_PXSELC(0) = 0x00200000 << ((n)-1);			\
// 	REG_GPIO_PXPES(0) = 0x00200000 << ((n)-1);			\
// 									\
//  	REG_GPIO_PXFUNC(0) = 0x00100000; /* FRB#(input) */		\
// 	REG_GPIO_PXSELC(0) = 0x00100000;				\
// 	REG_GPIO_PXDIRC(0) = 0x00100000;				\
// 	REG_GPIO_PXPES(0) = 0x00100000;					\
// } while (0)

// 
// #define __gpio_as_nand_16bit(n)						\
// do {		              						\
// 									\
// 	REG_GPIO_PXFUNS(0) = 0x000cffff; /* SD0 ~ SD15, CS1#, FRE#, FWE# */ \
// 	REG_GPIO_PXSELC(0) = 0x000cffff;				\
// 	REG_GPIO_PXTRGC(0) = 0x000cffff;				\
// 	REG_GPIO_PXPES(0) = 0x000cffff;					\
// 	REG_GPIO_PXFUNS(1) = 0x00000003; /* CLE(SA2), ALE(SA3) */	\
// 	REG_GPIO_PXSELC(1) = 0x00000003;				\
// 	REG_GPIO_PXTRGC(1) = 0x00000003;				\
// 	REG_GPIO_PXPES(1) = 0x00000003;					\
// 									\
// 	REG_GPIO_PXFUNS(0) = 0x00200000 << ((n)-1); /* CSn */		\
// 	REG_GPIO_PXSELC(0) = 0x00200000 << ((n)-1);			\
// 	REG_GPIO_PXPES(0) = 0x00200000 << ((n)-1);			\
// 									\
//  	REG_GPIO_PXFUNC(0) = 0x00100000; /* FRB#(input) */		\
// 	REG_GPIO_PXSELC(0) = 0x00100000;				\
// 	REG_GPIO_PXDIRC(0) = 0x00100000;				\
// 	REG_GPIO_PXPES(0) = 0x00100000;					\
// } while (0)

// 
/*
 * LCD_R3~LCD_R7, LCD_G2~LCD_G7, LCD_B3~LCD_B7,
 * LCD_PCLK, LCD_HSYNC, LCD_VSYNC, LCD_DE
 */
// #define __gpio_as_lcd_16bit()			\
// do {						\
// 	REG_GPIO_PXFUNS(2) = 0x0f8ff3f8;	\
// 	REG_GPIO_PXTRGC(2) = 0x0f8ff3f8;	\
// 	REG_GPIO_PXSELC(2) = 0x0f8ff3f8;	\
// 	REG_GPIO_PXPES(2) = 0x0f8ff3f8;		\
// } while (0)

// 
/*
 * LCD_R2~LCD_R7, LCD_G2~LCD_G7, LCD_B2~LCD_B7,
 * LCD_PCLK, LCD_HSYNC, LCD_VSYNC, LCD_DE
 */
// #define __gpio_as_lcd_18bit()			\
// do {						\
// 	REG_GPIO_PXFUNS(2) = 0x0fcff3fc;	\
// 	REG_GPIO_PXTRGC(2) = 0x0fcff3fc;	\
// 	REG_GPIO_PXSELC(2) = 0x0fcff3fc;	\
// 	REG_GPIO_PXPES(2) = 0x0fcff3fc;		\
// } while (0)

// 
/*
 * LCD_R0~LCD_R7, LCD_G0~LCD_G7, LCD_B0~LCD_B7,
 * LCD_PCLK, LCD_HSYNC, LCD_VSYNC, LCD_DE
 */
// #define __gpio_as_lcd_24bit()			\
// do {						\
// 	REG_GPIO_PXFUNS(2) = 0x0fffffff;	\
// 	REG_GPIO_PXTRGC(2) = 0x0fffffff;	\
// 	REG_GPIO_PXSELC(2) = 0x0fffffff;	\
// 	REG_GPIO_PXPES(2) = 0x0fffffff;		\
// } while (0)

// 
/*
 *  LCD_CLS, LCD_SPL, LCD_PS, LCD_REV
 */
// #define __gpio_as_lcd_special()			\
// do {						\
// 	REG_GPIO_PXFUNS(2) = 0x0fffffff;	\
// 	REG_GPIO_PXTRGC(2) = 0x0fffffff;	\
// 	REG_GPIO_PXSELC(2) = 0x0feffbfc;	\
// 	REG_GPIO_PXSELS(2) = 0x00100403;	\
// 	REG_GPIO_PXPES(2) = 0x0fffffff;		\
// } while (0)

// 

// 
// #define __gpio_as_epd()			\
// do {						\
// 	REG_GPIO_PXFUNS(1) = 0x0003fe00;	\
// 	REG_GPIO_PXTRGS(1) = 0x0003fe00;	\
// 	REG_GPIO_PXSELS(1) = 0x0003fe00;	\
// 	REG_GPIO_PXPES(1) = 0x0003fe00;		\
// 						\
// 	REG_GPIO_PXFUNS(3) = 0x00003000;	\
// 	REG_GPIO_PXTRGS(3) = 0x00003000;	\
// 	REG_GPIO_PXSELS(3) = 0x00003000;	\
// 	REG_GPIO_PXPES(3) = 0x00003000;		\
// 						\
// 	REG_GPIO_PXFUNS(4) = 0x000000c0;	\
// 	REG_GPIO_PXTRGS(4) = 0x000000c0;	\
// 	REG_GPIO_PXSELS(4) = 0x000000c0;	\
// 	REG_GPIO_PXPES(4) = 0x000000c0;		\
// 						\
// } while (0)

// 

// 
/*
 * CIM_D0~CIM_D7, CIM_MCLK, CIM_PCLK, CIM_VSYNC, CIM_HSYNC
 */
// #define __gpio_as_cim()				\
// do {						\
// 	REG_GPIO_PXFUNS(1) = 0x0003ffc0;	\
// 	REG_GPIO_PXTRGC(1) = 0x0003ffc0;	\
// 	REG_GPIO_PXSELC(1) = 0x0003ffc0;	\
// 	REG_GPIO_PXPES(1)  = 0x0003ffc0;	\
// } while (0)

// 
/*
 * SDATO, SDATI, BCLK, SYNC, SCLK_RSTN(gpio sepc) or
 * SDATA_OUT, SDATA_IN, BIT_CLK, SYNC, SCLK_RESET(aic spec)
 */
// #define __gpio_as_aic()				\
// do {						\
// 	REG_GPIO_PXFUNS(4) = 0x16c00000;	\
// 	REG_GPIO_PXTRGC(4) = 0x02c00000;	\
// 	REG_GPIO_PXTRGS(4) = 0x14000000;	\
// 	REG_GPIO_PXSELC(4) = 0x14c00000;	\
// 	REG_GPIO_PXSELS(4) = 0x02000000;	\
// 	REG_GPIO_PXPES(4)  = 0x16c00000;	\
// } while (0)

// 
/*
 * MSC0_CMD, MSC0_CLK, MSC0_D0 ~ MSC0_D7
 */
// #define __gpio_as_msc0_boot()			\
// do {						\
// 	REG_GPIO_PXFUNS(0) = 0x00ec0000;	\
// 	REG_GPIO_PXTRGC(0) = 0x00ec0000;	\
// 	REG_GPIO_PXSELS(0) = 0x00ec0000;	\
// 	REG_GPIO_PXPES(0)  = 0x00ec0000;	\
// 	REG_GPIO_PXFUNS(0) = 0x00100000;	\
// 	REG_GPIO_PXTRGC(0) = 0x00100000;	\
// 	REG_GPIO_PXSELC(0) = 0x00100000;	\
// 	REG_GPIO_PXPES(0)  = 0x00100000;	\
// } while (0)

// 
// #define __gpio_as_msc0_8bit()			\
// do {						\
// 	REG_GPIO_PXFUNS(4) = 0x3ff00000;	\
// 	REG_GPIO_PXTRGC(4) = 0x3ff00000;	\
// 	REG_GPIO_PXSELC(4) = 0x3ff00000;	\
// 	REG_GPIO_PXPES(4)  = 0x3ff00000;	\
// } while (0)

// 
/*
 * MSC0_CMD, MSC0_CLK, MSC0_D0 ~ MSC0_D3
 */
// #define __gpio_as_msc0_4bit()			\
// do {						\
// 	REG_GPIO_PXFUNS(4) = 0x30f00000;	\
// 	REG_GPIO_PXTRGC(4) = 0x30f00000;	\
// 	REG_GPIO_PXSELC(4) = 0x30f00000;	\
// 	REG_GPIO_PXPES(4)  = 0x30f00000;	\
// } while (0)

// 
/*
 * MSC1_CMD, MSC1_CLK, MSC1_D0 ~ MSC1_D3
 */
// #if defined(CONFIG_JZ4760B_LYNX)
// #define __gpio_as_msc1_4bit()				\
// 	do {						\
// 		REG_GPIO_PXFUNS(4) = 0x30f00000;	\
// 		REG_GPIO_PXTRGC(4) = 0x30f00000;	\
// 		REG_GPIO_PXSELS(4) = 0x30f00000;	\
// 		REG_GPIO_PXPES(4)  = 0x30f00000;	\
// 		REG_GPIO_PXDS0S(4) = 0x30f00000;        \
// 	} while (0)

// 
// #elif defined(CONFIG_JZ4760_LEPUS) || defined(CONFIG_JZ4760B_LEPUS)
// #define __gpio_as_msc1_4bit()			\
// do {						\
// 	REG_GPIO_PXFUNS(3) = 0x3f00000;	\
// 	REG_GPIO_PXTRGC(3) = 0x3f00000;	\
// 	REG_GPIO_PXSELC(3) = 0x3f00000;	\
// 	REG_GPIO_PXPES(3)  = 0x3f00000;	\
// 	REG_GPIO_PXDS0S(3) = 0x03f00000; \
// } while (0)
// #endif

// 
/* Port B
 * MSC2_CMD, MSC2_CLK, MSC2_D0 ~ MSC2_D3
 */
// #define __gpio_as_msc2_4bit()			\
// do {						\
// 	REG_GPIO_PXFUNS(1) = 0xf0300000;	\
// 	REG_GPIO_PXTRGC(1) = 0xf0300000;	\
// 	REG_GPIO_PXSELC(1) = 0xf0300000;	\
// 	REG_GPIO_PXPES(1)  = 0xf0300000;	\
// } while (0)

// 
// #define __gpio_as_msc 	__gpio_as_msc0_4bit /* default as msc0 4bit */
// #define __gpio_as_msc0 	__gpio_as_msc0_4bit /* msc0 default as 4bit */
// #define __gpio_as_msc1 	__gpio_as_msc1_4bit /* msc1 only support 4bit */

// 
/*
 * TSCLK, TSSTR, TSFRM, TSFAIL, TSDI0~7
 */
// #define __gpio_as_tssi_1()			\
// do {						\
// 	REG_GPIO_PXFUNS(1) = 0x0003ffc0;	\
// 	REG_GPIO_PXTRGC(1) = 0x0003ffc0;	\
// 	REG_GPIO_PXSELS(1) = 0x0003ffc0;	\
// 	REG_GPIO_PXPES(1)  = 0x0003ffc0;	\
// } while (0)

// 
/*
 * TSCLK, TSSTR, TSFRM, TSFAIL, TSDI0~7
 */
// #define __gpio_as_tssi_2()			\
// do {						\
// 	REG_GPIO_PXFUNS(1) = 0xfff00000;	\
// 	REG_GPIO_PXTRGC(1) = 0x0fc00000;	\
// 	REG_GPIO_PXTRGS(1) = 0xf0300000;	\
// 	REG_GPIO_PXSELC(1) = 0xfff00000;	\
// 	REG_GPIO_PXPES(1)  = 0xfff00000;	\
// } while (0)

// 
/*
 * SSI_CE0, SSI_CE1, SSI_GPC, SSI_CLK, SSI_DT, SSI_DR
 */
// #define __gpio_as_ssi()				\
// do {						\
// 	REG_GPIO_PXFUNS(0) = 0x002c0000; /* SSI0_CE0, SSI0_CLK, SSI0_DT	*/ \
// 	REG_GPIO_PXTRGS(0) = 0x002c0000;	\
// 	REG_GPIO_PXSELC(0) = 0x002c0000;	\
// 	REG_GPIO_PXPES(0)  = 0x002c0000;	\
// 						\
// 	REG_GPIO_PXFUNS(0) = 0x00100000; /* SSI0_DR */	\
// 	REG_GPIO_PXTRGC(0) = 0x00100000;	\
// 	REG_GPIO_PXSELS(0) = 0x00100000;	\
// 	REG_GPIO_PXPES(0)  = 0x00100000;	\
// } while (0)
// #define __gpio_as_ssi0()				\
// do {						\
// 	REG_GPIO_PXFUNS(4) = 0x000fc000; /* SSI0: SSI0_CE0, SSI0_CE1, SSI0_CLK, SSI0_DT, SSI0_DR,SSI0_GPC*/\
// 	REG_GPIO_PXTRGC(4) = 0x000fc000;	\
// 	REG_GPIO_PXSELC(4) = 0x000fc000;	\
// 	REG_GPIO_PXPES(4)  = 0x000fc000;	\
// } while (0)
// #define __gpio_as_ssi0_x()			\
// do {						\
// 	REG_GPIO_PXFUNS(4) = 0x0002c000; /*  SSI0_CLK, SSI0_DT, SSI0_DR	*/ \
// 	REG_GPIO_PXTRGC(4) = 0x0002c000;	\
// 	REG_GPIO_PXSELC(4) = 0x0002c000;	\
// 	REG_GPIO_PXPES(4)  = 0x0002c000;	\
// } while (0)

// 
// #define __gpio_as_ssi0_1()				\
// do {						\
// 	REG_GPIO_PXFUNS(1) = 0xf0300000; /* SSI0 */	\
// 	REG_GPIO_PXTRGC(1) = 0xf0300000;	\
// 	REG_GPIO_PXSELS(1) = 0xf0300000;	\
// 	REG_GPIO_PXPES(1)  = 0xf0300000;	\
// } while (0)

// 
// #define __gpio_as_ssi0_x1()				\
// do {						\
// 	REG_GPIO_PXFUNS(1) = 0x10300000; /* SSI0_CLK, SSI0_DT,SSI0_DR	*/ \
// 	REG_GPIO_PXTRGS(1) = 0x10300000;	\
// 	REG_GPIO_PXSELC(1) = 0x10300000;	\
// 	REG_GPIO_PXPES(1)  = 0x10300000;	\
// } while (0)
// #define __gpio_as_ssi0_2()				\
// do {						\
// 	REG_GPIO_PXFUNS(0) = 0x00100000; /* SSI0 */	\
// 	REG_GPIO_PXTRGC(0) = 0x00100000;	\
// 	REG_GPIO_PXSELS(0) = 0x00100000;	\
// 	REG_GPIO_PXPES(0)  = 0x00100000;	\
// 										\
// 	REG_GPIO_PXFUNS(0) = 0x002c0000; /* SSI0_CE0, SSI0_CLK, SSI0_DT	*/ \
// 	REG_GPIO_PXTRGS(0) = 0x002c0000;	\
// 	REG_GPIO_PXSELC(0) = 0x002c0000;	\
// 	REG_GPIO_PXPES(0)  = 0x002c0000;	\
// } while (0)
// #define __gpio_as_ssi0_x2()			\
// do {						\
// 	REG_GPIO_PXFUNS(0) = 0x00240000; /*  SSI0_CLK, SSI0_DT	*/ \
// 	REG_GPIO_PXTRGS(0) = 0x00240000;	\
// 	REG_GPIO_PXSELC(0) = 0x00240000;	\
// 	REG_GPIO_PXPES(0)  = 0x00240000;	\
// 						\
// 	REG_GPIO_PXFUNS(0) = 0x00100000; /* SSI0_DR */	\
// 	REG_GPIO_PXTRGC(0) = 0x00100000;	\
// 	REG_GPIO_PXSELS(0) = 0x00100000;	\
// 	REG_GPIO_PXPES(0)  = 0x00100000;	\
// } while (0)
/***************** SSI 1 ***********************/
// #define __gpio_as_ssi1()				\
// do {						\
// 	REG_GPIO_PXFUNS(4) = 0x000fc000; /* SSI1: SSI1_CE0, SSI1_CE1, SSI1_CLK, SSI1_DT, SSI1_DR,SSI1_GPC*/	\
// 	REG_GPIO_PXTRGC(4) = 0x000fc000;	\
// 	REG_GPIO_PXSELS(4) = 0x000fc000;	\
// 	REG_GPIO_PXPES(4)  = 0x000fc000;	\
// } while (0)
// #define __gpio_as_ssi1_x()			\
// do {						\
// 	REG_GPIO_PXFUNS(4) = 0x0002c000; /*  SSI1_CLK, SSI1_DT, SSI1_DR	*/ \
// 	REG_GPIO_PXTRGC(4) = 0x0002c000;	\
// 	REG_GPIO_PXSELS(4) = 0x0002c000;	\
// 	REG_GPIO_PXPES(4)  = 0x0002c000;	\
// } while (0)

// 
// #define __gpio_as_ssi1_1()				\
// do {						\
// 	REG_GPIO_PXFUNS(1) = 0xf0300000; /* SSI1*/\
// 	REG_GPIO_PXTRGC(1) = 0xf0300000;	\
// 	REG_GPIO_PXSELS(1) = 0xf0300000;	\
// 	REG_GPIO_PXPES(1)  = 0xf0300000;	\
// } while (0)
// #define __gpio_as_ssi1_x1()				\
// do {						\
// 	REG_GPIO_PXFUNS(1) = 0x10300000; /* SSI1_x*/\
// 	REG_GPIO_PXTRGC(1) = 0x10300000;	\
// 	REG_GPIO_PXSELS(1) = 0x10300000;	\
// 	REG_GPIO_PXPES(1)  = 0x10300000;	\
// } while (0)

// 
// #define __gpio_as_ssi1_2()				\
// do {						\
// 	REG_GPIO_PXFUNS(1) = 0x000003c0; /* SSI1*/\
// 	REG_GPIO_PXTRGC(1) = 0x000003c0;	\
// 	REG_GPIO_PXSELS(1) = 0x000003c0;	\
// 	REG_GPIO_PXPES(1)  = 0x000003c0;	\
// } while (0)
// #define __gpio_as_ssi1_x2()				\
// do {						\
// 	REG_GPIO_PXFUNS(1) = 0x000002c0; /* SSI1_x*/\
// 	REG_GPIO_PXTRGC(1) = 0x000002c0;	\
// 	REG_GPIO_PXSELS(1) = 0x000002c0;	\
// 	REG_GPIO_PXPES(1)  = 0x000002c0;	\
// } while (0)

// 
/*
 * I2C_SCK, I2C_SDA
 */
// #define __gpio_as_i2c(n)		       \
// do {						\
// 	REG_GPIO_PXFUNS(3+(n)) = 0xc0000000;	\
// 	REG_GPIO_PXTRGC(3+(n)) = 0xc0000000;	\
// 	REG_GPIO_PXSELC(3+(n)) = 0xc0000000;	\
// 	REG_GPIO_PXPES(3+(n))  = 0xc0000000;	\
// } while (0)

// 
/*
 * PWM0
 */
// #define __gpio_as_pwm0()			\
// do {						\
// 	REG_GPIO_PXFUNS(4) = 0x00100000;	\
// 	REG_GPIO_PXSELC(4) = 0x00100000;	\
// 	REG_GPIO_PXPES(4) = 0x00100000;		\
// } while (0)

// 
/*
 * PWM1
 */
// #define __gpio_as_pwm1()			\
// do {						\
// 	REG_GPIO_PXFUNS(4) = 0x2;	        \
// 	REG_GPIO_PXTRGC(4) = 0x2;		\
// 	REG_GPIO_PXSELC(4) = 0x2;		\
// 	REG_GPIO_PXPEC(4) = 0x2;		\
// } while (0)

// 
/*
 * PWM2
 */
// #define __gpio_as_pwm2()			\
// do {						\
// 	REG_GPIO_PXFUNS(4) = 0x00400000;	\
// 	REG_GPIO_PXSELC(4) = 0x00400000;	\
// 	REG_GPIO_PXPES(4) = 0x00400000;		\
// } while (0)

// 
/*
 * PWM3
 */
// #define __gpio_as_pwm3()			\
// do {						\
// 	REG_GPIO_PXFUNS(4) = 0x00800000;	\
// 	REG_GPIO_PXSELC(4) = 0x00800000;	\
// 	REG_GPIO_PXPES(4) = 0x00800000;		\
// } while (0)

// 
/*
 * PWM4
 */
// #define __gpio_as_pwm4()			\
// do {						\
// 	REG_GPIO_PXFUNS(4) = 0x01000000;	\
// 	REG_GPIO_PXSELC(4) = 0x01000000;	\
// 	REG_GPIO_PXPES(4) = 0x01000000;		\
// } while (0)

// 
/*
 * PWM5
 */
// #define __gpio_as_pwm5()			\
// do {						\
// 	REG_GPIO_PXFUNS(4) = 0x02000000;	\
// 	REG_GPIO_PXSELC(4) = 0x02000000;	\
// 	REG_GPIO_PXPES(4) = 0x02000000;		\
// } while (0)

// 
/*
 * n = 0 ~ 5
 */
// #define __gpio_as_pwm(n)	__gpio_as_pwm##n()

// 
/*
 * OWI - PA29 function 1
 */
// #define __gpio_as_owi()				\
// do {						\
// 	REG_GPIO_PXFUNS(0) = 0x20000000;	\
// 	REG_GPIO_PXTRGC(0) = 0x20000000;	\
// 	REG_GPIO_PXSELS(0) = 0x20000000;	\
// } while (0)

// 
/*
 * SCC - PD08 function 0
 *       PD09 function 0
 */
// #define __gpio_as_scc()				\
// do {						\
// 	REG_GPIO_PXFUNS(3) = 0xc0000300;	\
// 	REG_GPIO_PXTRGC(3) = 0xc0000300;	\
// 	REG_GPIO_PXSELC(3) = 0xc0000300;	\
// } while (0)

// 
// #define __gpio_as_otg_drvvbus()	\
// do {	\
// 	REG_GPIO_PXDATC(4) = (1 << 10);		\
// 	REG_GPIO_PXPEC(4) = (1 << 10);		\
// 	REG_GPIO_PXSELC(4) = (1 << 10);		\
// 	REG_GPIO_PXTRGC(4) = (1 << 10);		\
// 	REG_GPIO_PXFUNS(4) = (1 << 10);		\
// } while (0)

// 
//-------------------------------------------
// GPIO or Interrupt Mode

// 
// #define __gpio_get_port(p)	(REG_GPIO_PXPIN(p))

// 
// #define __gpio_port_as_output(p, o)		\
// do {						\
//     REG_GPIO_PXFUNC(p) = (1 << (o));		\
//     REG_GPIO_PXSELC(p) = (1 << (o));		\
//     REG_GPIO_PXDIRS(p) = (1 << (o));		\
//     REG_GPIO_PXPES(p) = (1 << (o));		\
// } while (0)

// 
// #define __gpio_port_as_input(p, o)		\
// do {						\
//     REG_GPIO_PXFUNC(p) = (1 << (o));		\
//     REG_GPIO_PXSELC(p) = (1 << (o));		\
//     REG_GPIO_PXDIRC(p) = (1 << (o));		\
// } while (0)

// 
// #define __gpio_as_output(n)			\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	__gpio_port_as_output(p, o);		\
// } while (0)

// 
// #define __gpio_as_input(n)			\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	__gpio_port_as_input(p, o);		\
// } while (0)

// 
// #define __gpio_set_pin(n)			\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXDATS(p) = (1 << o);		\
// } while (0)

// 
// #define __gpio_clear_pin(n)			\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXDATC(p) = (1 << o);		\
// } while (0)

// 
// #define __gpio_get_pin(n)			\
// ({						\
// 	unsigned int p, o, v;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	if (__gpio_get_port(p) & (1 << o))	\
// 		v = 1;				\
// 	else					\
// 		v = 0;				\
// 	v;					\
// })

// 
// #define __gpio_as_irq_high_level(n)		\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXIMS(p) = (1 << o);		\
// 	REG_GPIO_PXTRGC(p) = (1 << o);		\
// 	REG_GPIO_PXFUNC(p) = (1 << o);		\
// 	REG_GPIO_PXSELS(p) = (1 << o);		\
// 	REG_GPIO_PXDIRS(p) = (1 << o);		\
// 	REG_GPIO_PXFLGC(p) = (1 << o);		\
// 	REG_GPIO_PXIMC(p) = (1 << o);		\
// } while (0)

// 
// #define __gpio_as_irq_low_level(n)		\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXIMS(p) = (1 << o);		\
// 	REG_GPIO_PXTRGC(p) = (1 << o);		\
// 	REG_GPIO_PXFUNC(p) = (1 << o);		\
// 	REG_GPIO_PXSELS(p) = (1 << o);		\
// 	REG_GPIO_PXDIRC(p) = (1 << o);		\
// 	REG_GPIO_PXFLGC(p) = (1 << o);		\
// 	REG_GPIO_PXIMC(p) = (1 << o);		\
// } while (0)

// 
// #define __gpio_as_irq_rise_edge(n)		\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXIMS(p) = (1 << o);		\
// 	REG_GPIO_PXTRGS(p) = (1 << o);		\
// 	REG_GPIO_PXFUNC(p) = (1 << o);		\
// 	REG_GPIO_PXSELS(p) = (1 << o);		\
// 	REG_GPIO_PXDIRS(p) = (1 << o);		\
// 	REG_GPIO_PXFLGC(p) = (1 << o);		\
// 	REG_GPIO_PXIMC(p) = (1 << o);		\
// } while (0)

// 
// #define __gpio_as_irq_fall_edge(n)		\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXIMS(p) = (1 << o);		\
// 	REG_GPIO_PXTRGS(p) = (1 << o);		\
// 	REG_GPIO_PXFUNC(p) = (1 << o);		\
// 	REG_GPIO_PXSELS(p) = (1 << o);		\
// 	REG_GPIO_PXDIRC(p) = (1 << o);		\
// 	REG_GPIO_PXFLGC(p) = (1 << o);		\
// 	REG_GPIO_PXIMC(p) = (1 << o);		\
// } while (0)

// 
// #define __gpio_mask_irq(n)			\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXIMS(p) = (1 << o);		\
// } while (0)

// 
// #define __gpio_unmask_irq(n)			\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXIMC(p) = (1 << o);		\
// } while (0)

// 
// #define __gpio_ack_irq(n)			\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXFLGC(p) = (1 << o);		\
// } while (0)

// 
// #define __gpio_get_irq()			\
// ({						\
// 	unsigned int p, i, tmp, v = 0;		\
// 	for (p = 3; p >= 0; p--) {		\
// 		tmp = REG_GPIO_PXFLG(p);	\
// 		for (i = 0; i < 32; i++)	\
// 			if (tmp & (1 << i))	\
// 				v = (32*p + i);	\
// 	}					\
// 	v;					\
// })

// 
// #define __gpio_group_irq(n)			\
// ({						\
// 	register int tmp, i;			\
// 	tmp = REG_GPIO_PXFLG(n) & (~REG_GPIO_PXIM(n));	\
// 	for (i=31;i>=0;i--)			\
// 		if (tmp & (1 << i))		\
// 			break;			\
// 	i;					\
// })

// 
// #define __gpio_enable_pull(n)			\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXPEC(p) = (1 << o);		\
// } while (0)

// 
// #define __gpio_disable_pull(n)			\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXPES(p) = (1 << o);		\
// } while (0)

// 
/* gpio driver strength function */
// #define __gpio_get_ds0(n)			\
// ({						\
// 	unsigned int p, o, v;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	if (REG_GPIO_PXDS0(p) & (1 << o))	\
// 		v = 1;				\
// 	else					\
// 		v = 0;				\
// 	v;					\
// })
// #define __gpio_set_ds0(n)			\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXDS0S(p) = (1 << o);		\
// } while (0)
// #define __gpio_clear_ds0(n)			\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXDS0C(p) = (1 << o);		\
// } while (0)
// #define __gpio_get_ds1(n)			\
// ({						\
// 	unsigned int p, o, v;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	if (REG_GPIO_PXDS1(p) & (1 << o))	\
// 		v = 1;				\
// 	else					\
// 		v = 0;				\
// 	v;					\
// })

// 
// #define __gpio_set_ds1(n)			\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXDS1S(p) = (1 << o);		\
// } while (0)
// #define __gpio_clear_ds1(n)			\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXDS1C(p) = (1 << o);		\
// } while (0)
// #define __gpio_get_ds2(n)			\
// ({						\
// 	unsigned int p, o, v;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	if (REG_GPIO_PXDS2(p) & (1 << o))	\
// 		v = 1;				\
// 	else					\
// 		v = 0;				\
// 	v;					\
// })
// #define __gpio_set_ds2(n)			\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXDS2S(p) = (1 << o);		\
// } while (0)
// #define __gpio_clear_ds2(n)			\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXDS2C(p) = (1 << o);		\
// } while (0)

// 
// #define __gpio_get_slew_rate(n)			\
// ({						\
// 	unsigned int p, o, v;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	if (REG_GPIO_PXSL(p) & (1 << o))	\
// 		v = 1;				\
// 	else					\
// 		v = 0;				\
// 	v;					\
// })
// #define __gpio_set_fast_slew_rate(n)		\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXSLC(p) = (1 << o);		\
// } while (0)
// #define __gpio_set_low_slew_rate(n)		\
// do {						\
// 	unsigned int p, o;			\
// 	p = (n) / 32;				\
// 	o = (n) % 32;				\
// 	REG_GPIO_PXSLS(p) = (1 << o);		\
// } while (0)

// 

// 

// 

// 

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BGPIO_H__ */
