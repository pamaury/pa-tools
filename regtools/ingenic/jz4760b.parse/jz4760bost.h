/*
 * jz4760ost.h
 * JZ4760 OST register definition
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 *
 * Author: whxu@ingenic.cn
 */

// 
// #ifndef __JZ4760OST_H__
// #define __JZ4760OST_H__

// 
//#define CONFIG_SOC_JZ4760B 1
/*
 * Operating system timer module(OST) address definition
 */
this class OST goto 0xb0002000

// 

// 
/*
 * OST registers offset address definition
 */
const OST_OSTDR_OFFSET 0xe0
const OST_OSTCNTL_OFFSET 0xe4
const OST_OSTCNTH_OFFSET 0xe8
const OST_OST_OSTCSR_OFFSET 0xec

// 
const OST_OSTCNTH_BUF_OFFSET 0xfc

// 

// 
/*
 * OST registers address definition
 */
register OSTDR goto OST_OSTDR_OFFSET export ""
register OSTCNTL goto OST_OSTCNTL_OFFSET export ""
register OSTCNTH goto OST_OSTCNTH_OFFSET export ""
register OSTCSR goto OST_OST_OSTCSR_OFFSET export ""
register OSTCNTH_BUF goto OST_OSTCNTH_BUF_OFFSET export ""

// 

// 
/*
 * OST registers common define
 */

// 
register OSTCSR export "Operating system control register"
register OSTCSR int CNT_MD goto 15
register OSTCSR int SD goto 9
register OSTCSR int EXT_EN goto 2
register OSTCSR int RTC_EN goto 1
register OSTCSR int PCK_EN goto 0

// 
const OST_OSTCSR_PRESCALE_BIT 3
register OSTCSR int PRESCALE goto (5, OST_OSTCSR_PRESCALE_BIT)
register OSTCSR int PRESCALE enum "1" 0x0
register OSTCSR int PRESCALE enum "4" 0x1
register OSTCSR int PRESCALE enum "16" 0x2
register OSTCSR int PRESCALE enum "64" 0x3
register OSTCSR int PRESCALE enum "256" 0x4
register OSTCSR int PRESCALE enum "1024" 0x5

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 
register OSTDR sizeof 32

// 
register OSTCNTL sizeof 32
register OSTCNTH sizeof 32

// 
register OSTCSR sizeof 16

// 
// #define REG_OST_OSTCNTH_BUF	REG32(OST_OSTCNTH_BUF)

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760OST_H__ */
