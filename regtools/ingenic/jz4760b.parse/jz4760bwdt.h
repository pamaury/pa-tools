/*
 * jz4760bwdt.h
 * JZ4760B WDT register definition
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 *
 * Author: whxu@ingenic.cn
 * 	   twxie@ingenic.cn
 *
 * Revision historty
 *  - 2012/02/22/:add some macro.<twxie>
 */

// 
// #ifndef __JZ4760BWDT_H__
// #define __JZ4760BWDT_H__

// 

// 
/* Watchdog timer module */
this class WDT goto 0xb0002000 export "Watchdog timer module"

// 

// 
/*
 * WDT registers offset address definition
 */
const WDT_WDR_OFFSET 0x00
const WDT_WCER_OFFSET 0x04
const WDT_WCNT_OFFSET 0x08
const WDT_WCSR_OFFSET 0x0c

// 

// 
/*
 * WDT registers address definition
 */
register WDR goto WDT_WDR_OFFSET export ""
register WCER goto WDT_WCER_OFFSET export ""
register WCNT goto WDT_WCNT_OFFSET export ""
register WCSR goto WDT_WCSR_OFFSET export ""

// 

// 
/*
 * WDT registers common define
 */

// 
register WCER export "Watchdog counter enable register"
register WCER int TCEN goto 0

// 
register WCSR export "Watchdog control register"
const WDT_WCSR_PRESCALE_BIT 3
register WCSR int PRESCALE goto (5, WDT_WCSR_PRESCALE_BIT)
register WCSR int PRESCALE enum "1" 0x0
register WCSR int PRESCALE enum "4" 0x1
register WCSR int PRESCALE enum "16" 0x2
register WCSR int PRESCALE enum "64" 0x3
register WCSR int PRESCALE enum "256" 0x4
register WCSR int PRESCALE enum "1024" 0x5

// 
const WDT_WCSR_CLKIN_BIT 0
register WCSR int CLKIN goto (2, WDT_WCSR_CLKIN_BIT)
register WCSR int CLKIN enum PCK 0x1
register WCSR int CLKIN enum RTC 0x2
register WCSR int CLKIN enum EXT 0x4

// 
// #ifndef __MIPS_ASSEMBLER

// 
register WDR sizeof 16
register WCER sizeof 8
register WCNT sizeof 16
register WCSR sizeof 16

// 
/*
 * WDT
 */
// #define __wdt_start()			( REG_WDT_WCER |= WDT_WCER_TCEN )
// #define __wdt_stop()			( REG_WDT_WCER &= ~WCER_TCEN )
// #define __wdt_set_count(v)		( REG_WDT_WCNT = (v) )
// #define __wdt_set_data(v)		( REG_WDT_WDR = (v) )

// 
// #define __wdt_select_extalclk() \
// 	(REG_WDT_WCSR = (REG_WDT_WCSR & ~(WCSR_CLKIN_EXT | WDT_WCSR_CLKIN_RTC | WDT_WCSR_CLKIN_PCK)) | WDT_WCSR_CLKIN_EXT)
// #define __wdt_select_rtcclk() \
// 	(REG_WDT_WCSR = (REG_WDT_WCSR & ~(WCSR_CLKIN_EXT | WDT_WCSR_CLKIN_RTC | WDT_WCSR_CLKIN_PCK)) | WDT_WCSR_CLKIN_RTC)
// #define __wdt_select_pclk() \
// 	(REG_WDT_WCSR = (REG_WDT_WCSR & ~(WCSR_CLKIN_EXT | WDT_WCSR_CLKIN_RTC | WDT_WCSR_CLKIN_PCK)) | WDT_WCSR_CLKIN_PCK)

// 
// #define __wdt_select_clk_div1() \
// 	(REG_WDT_WCSR = (REG_WDT_WCSR & ~WCSR_PRESCALE_MASK) | WDT_WCSR_PRESCALE1)
// #define __wdt_select_clk_div4() \
// 	(REG_WDT_WCSR = (REG_WDT_WCSR & ~WCSR_PRESCALE_MASK) | WDT_WCSR_PRESCALE4)
// #define __wdt_select_clk_div16() \
// 	(REG_WDT_WCSR = (REG_WDT_WCSR & ~WCSR_PRESCALE_MASK) | WDT_WCSR_PRESCALE16)
// #define __wdt_select_clk_div64() \
// 	(REG_WDT_WCSR = (REG_WDT_WCSR & ~WCSR_PRESCALE_MASK) | WDT_WCSR_PRESCALE64)
// #define __wdt_select_clk_div256() \
// 	(REG_WDT_WCSR = (REG_WDT_WCSR & ~WCSR_PRESCALE_MASK) | WDT_WCSR_PRESCALE256)
// #define __wdt_select_clk_div1024() \
// 	(REG_WDT_WCSR = (REG_WDT_WCSR & ~WCSR_PRESCALE_MASK) | WDT_WCSR_PRESCALE1024)

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BWDT_H__ */