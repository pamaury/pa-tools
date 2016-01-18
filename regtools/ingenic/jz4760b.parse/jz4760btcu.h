/*
 * jz4760btcu.h
 * JZ4760B TCU register definition
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 *
 * Author: fyliao@ingenic.cn
 */

// 
// #ifndef __JZ4760BTCU_H__
// #define __JZ4760BTCU_H__

// 

// 
/* Timer and counter unit module */
this class TCU goto 0xb0002000 export "Timer and counter unit module"

// 
/* TCU group offset */
const TCU_GOS 0x10

// 
/* TCU total channel number */
const TCU_CHANNEL_NUM 8

// 

// 
/*
 * TCU registers offset definition
 */
const TCU_TER_OFFSET 0x10
const TCU_TESR_OFFSET 0x14
const TCU_TECR_OFFSET 0x18
const TCU_TSR_OFFSET 0x1c
const TCU_TFR_OFFSET 0x20
const TCU_TFSR_OFFSET 0x24
const TCU_TFCR_OFFSET 0x28
const TCU_TSSR_OFFSET 0x2c
const TCU_TMR_OFFSET 0x30
const TCU_TMSR_OFFSET 0x34
const TCU_TMCR_OFFSET 0x38
const TCU_TSCR_OFFSET 0x3c

// 
const TCU_TDFR_OFFSET 0x40
const TCU_TDHR_OFFSET 0x44
const TCU_TCNT_OFFSET 0x48
const TCU_TCSR_OFFSET 0x4c

// 
const TCU_TSTR_OFFSET 0xf0
const TCU_TSTSR_OFFSET 0xf4
const TCU_TSTCR_OFFSET 0xf8

// 

// 
/*
 * TCU registers address definition
 */
register TER goto TCU_TER_OFFSET export ""
register TESR goto TCU_TESR_OFFSET export ""
register TECR goto TCU_TECR_OFFSET export ""
register TSR goto TCU_TSR_OFFSET export ""
register TFR goto TCU_TFR_OFFSET export ""
register TFSR goto TCU_TFSR_OFFSET export ""
register TFCR goto TCU_TFCR_OFFSET export ""
register TSSR goto TCU_TSSR_OFFSET export ""
register TMR goto TCU_TMR_OFFSET export ""
register TMSR goto TCU_TMSR_OFFSET export ""
register TMCR goto TCU_TMCR_OFFSET export ""
register TSCR goto TCU_TSCR_OFFSET export ""
register TSTR goto TCU_TSTR_OFFSET export ""
register TSTSR goto TCU_TSTSR_OFFSET export ""
register TSTCR goto TCU_TSTCR_OFFSET export ""

// 
for n 0 7
register TDFR goto<n> "(n) * TCU_GOS + TCU_TDFR_OFFSET" export ""
register TDHR goto<n> "(n) * TCU_GOS + TCU_TDHR_OFFSET" export ""
register TCNT goto<n> "(n) * TCU_GOS + TCU_TCNT_OFFSET" export ""
register TCSR goto<n> "(n) * TCU_GOS + TCU_TCSR_OFFSET" export ""

// 

// 
/*
 * TCU registers bit field common define
 */

// 
/* When n is NOT less than TCU_CHANNEL_NUM, change to TCU_CHANNEL_NUM - 1 */
// #define __TIMER(n)	(1 << ((n) < TCU_CHANNEL_NUM ? (n) : (TCU_CHANNEL_NUM - 1)))

// 
register TER export "Timer counter enable register"
register TER int OSTEN goto 15
const TCU_TER_TCEN_BIT 0
register TER int TCEN goto (0xff << TCU_TER_TCEN_BIT)

// 
register TESR export "Timer counter enable set register"
register TESR int OST goto 15
const TCU_TESR_TIMER_BIT 0
register TESR int TIMER goto (0xff << TCU_TESR_TIMER_BIT)

// 
register TECR export "Timer counter enable clear register"
register TECR int OST goto 15
const TCU_TECR_TIMER_BIT 0
register TECR int TIMER goto (0xff << TCU_TECR_TIMER_BIT)

// 
register TSR export "Timer stop register"
register TSR int WDT_STOP goto 16
register TSR int OST_STOP goto 15
const TCU_TSR_TIMER_STOP_BIT 0
register TSR int TIMER_STOP goto (0xff << TCU_TSR_TIMER_STOP_BIT)

// 
register TSSR export "Timer stop set register"
register TSSR int WDT goto 16
register TSSR int OST goto 15
const TCU_TSSR_TIMER_BIT 0
register TSSR int TIMER goto (0xff << TCU_TSSR_TIMER_BIT)

// 
register TSCR export "Timer stop clear register"
register TSCR int WDT goto 16
register TSCR int OST goto 15
const TCU_TSCR_TIMER_BIT 0
register TSCR int TIMER goto (0xff << TCU_TSCR_TIMER_BIT)

// 
register TFR export "Timer flag register"
const TCU_TFR_HFLAG_BIT 16
register TFR int HFLAG goto (0xff << TCU_TFR_HFLAG_BIT)
register TFR int OSTFLAG goto 15
const TCU_TFR_FFLAG_BIT 0
register TFR int FFLAG goto (0xff << TCU_TFR_FFLAG_BIT)

// 
register TFSR export "Timer flag set register"
const TCU_TFSR_HFLAG_BIT 16
register TFSR int HFLAG goto (0xff << TCU_TFSR_HFLAG_BIT)
register TFSR int OSTFLAG goto 15
const TCU_TFSR_FFLAG_BIT 0
register TFSR int FFLAG goto (0xff << TCU_TFSR_FFLAG_BIT)

// 
register TFCR export "Timer flag clear register"
const TCU_TFCR_HFLAG_BIT 16
register TFCR int HFLAG goto (0xff << TCU_TFCR_HFLAG_BIT)
register TFCR int OSTFLAG goto 15
const TCU_TFCR_FFLAG_BIT 0
register TFCR int FFLAG goto (0xff << TCU_TFCR_FFLAG_BIT)

// 
register TMR export "Timer mast register"
const TCU_TMR_HMASK_BIT 16
register TMR int HMASK goto (0xff << TCU_TMR_HMASK_BIT)
register TMR int OSTMASK goto 15
const TCU_TMR_FMASK_BIT 0
register TMR int FMASK goto (0xff << TCU_TMR_FMASK_BIT)

// 
register TMSR export "Timer mask set register"
const TCU_TMSR_HMASK_BIT 16
register TMSR int HMASK goto (0xff << TCU_TMSR_HMASK_BIT)
register TMSR int OSTMASK goto 15
const TCU_TMSR_FMASK_BIT 0
register TMSR int FMASK goto (0xff << TCU_TMSR_FMASK_BIT)

// 
register TMCR export "Timer mask clear register"
const TCU_TMCR_HMASK_BIT 16
register TMCR int HMASK goto (0xff << TCU_TMCR_HMASK_BIT)
register TMCR int OSTMASK goto 15
const TCU_TMCR_FMASK_BIT 0
register TMCR int FMASK goto (0xff << TCU_TMCR_FMASK_BIT)

// 
register TCSR export "Timer control register"
register TCSR int CLRZ goto 10
register TCSR int SD_ABRUPT goto 9
register TCSR int INITL_HIGH goto 8
register TCSR int PWM_EN goto 7
register TCSR int PWM_IN_EN goto 6
register TCSR int EXT_EN goto 2
register TCSR int RTC_EN goto 1
register TCSR int PCK_EN goto 0

// 
const TCU_TCSR_PRESCALE_BIT 3
register TCSR int PRESCALE goto (5, TCU_TCSR_PRESCALE_BIT)
register TCSR int PRESCALE enum "1" 0x0
register TCSR int PRESCALE enum "4" 0x1
register TCSR int PRESCALE enum "16" 0x2
register TCSR int PRESCALE enum "64" 0x3
register TCSR int PRESCALE enum "256" 0x4
register TCSR int PRESCALE enum "1024" 0x5

// 
register TDFR export "Timer data full register"
const TCU_TDFR_TDFR_BIT 0
register TDFR int TDFR goto (15, TCU_TDFR_TDFR_BIT)

// 
register TDHR export "Timer data half register"
const TCU_TDHR_TDHR_BIT 0
register TDHR int TDHR goto (15, TCU_TDHR_TDHR_BIT)

// 
register TCNT export "Timer counter register"
const TCU_TCNT_TCNT_BIT 0
register TCNT int TCNT goto (15, TCU_TCNT_TCNT_BIT)

// 
register TSTR export "Timer status register"
register TSTR int REAL2 goto 18
register TSTR int REAL1 goto 17
register TSTR int BUSY2 goto 2
register TSTR int BUSY1 goto 1

// 
register TSTSR export "Timer status set register"
register TSTSR int REALS2 goto 18
register TSTSR int REALS1 goto 17
register TSTSR int BUSYS2 goto 2
register TSTSR int BUSYS1 goto 1

// 
register TSTCR export "Timer status clear register"
register TSTCR int REALC2 goto 18
register TSTCR int REALC1 goto 17
register TSTCR int BUSYC2 goto 2
register TSTCR int BUSYC1 goto 1

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 
register TER sizeof 16
register TESR sizeof 16
register TECR sizeof 16
register TSR sizeof 32
register TFR sizeof 32
register TFSR sizeof 32
register TFCR sizeof 32
register TSSR sizeof 32
register TMR sizeof 32
register TMSR sizeof 32
register TMCR sizeof 32
register TSCR sizeof 32
register TSTR sizeof 32
register TSTSR sizeof 32
register TSTCR sizeof 32

// 
register TDFR sizeof 16
register TDHR sizeof 16
register TCNT sizeof 16
register TCSR sizeof 16

// 

// 
// where 'n' is the TCU channel
// #define __tcu_select_extalclk(n) \
// 	(REG_TCU_TCSR((n)) = (REG_TCU_TCSR((n)) & ~(TCSR_EXT_EN | TCU_TCSR_RTC_EN | TCU_TCSR_PCK_EN)) | TCU_TCSR_EXT_EN)
// #define __tcu_select_rtcclk(n) \
// 	(REG_TCU_TCSR((n)) = (REG_TCU_TCSR((n)) & ~(TCSR_EXT_EN | TCU_TCSR_RTC_EN | TCU_TCSR_PCK_EN)) | TCU_TCSR_RTC_EN)
// #define __tcu_select_pclk(n) \
// 	(REG_TCU_TCSR((n)) = (REG_TCU_TCSR((n)) & ~(TCSR_EXT_EN | TCU_TCSR_RTC_EN | TCU_TCSR_PCK_EN)) | TCU_TCSR_PCK_EN)
// #define __tcu_disable_pclk(n) \
// 	REG_TCU_TCSR(n) = (REG_TCU_TCSR((n)) & ~TCSR_PCK_EN);
// #define __tcu_select_clk_div1(n) \
// 	(REG_TCU_TCSR((n)) = (REG_TCU_TCSR((n)) & ~TCSR_PRESCALE_MASK) | TCU_TCSR_PRESCALE1)
// #define __tcu_select_clk_div4(n) \
// 	(REG_TCU_TCSR((n)) = (REG_TCU_TCSR((n)) & ~TCSR_PRESCALE_MASK) | TCU_TCSR_PRESCALE4)
// #define __tcu_select_clk_div16(n) \
// 	(REG_TCU_TCSR((n)) = (REG_TCU_TCSR((n)) & ~TCSR_PRESCALE_MASK) | TCU_TCSR_PRESCALE16)
// #define __tcu_select_clk_div64(n) \
// 	(REG_TCU_TCSR((n)) = (REG_TCU_TCSR((n)) & ~TCSR_PRESCALE_MASK) | TCU_TCSR_PRESCALE64)
// #define __tcu_select_clk_div256(n) \
// 	(REG_TCU_TCSR((n)) = (REG_TCU_TCSR((n)) & ~TCSR_PRESCALE_MASK) | TCU_TCSR_PRESCALE256)
// #define __tcu_select_clk_div1024(n) \
// 	(REG_TCU_TCSR((n)) = (REG_TCU_TCSR((n)) & ~TCSR_PRESCALE_MASK) | TCU_TCSR_PRESCALE1024)

// 
// #define __tcu_enable_pwm_output(n)	(REG_TCU_TCSR((n)) |= TCU_TCSR_PWM_EN)
// #define __tcu_disable_pwm_output(n)	(REG_TCU_TCSR((n)) &= ~TCSR_PWM_EN)

// 
// #define __tcu_init_pwm_output_high(n)	(REG_TCU_TCSR((n)) |= TCU_TCSR_INITL_HIGH)
// #define __tcu_init_pwm_output_low(n)	(REG_TCU_TCSR((n)) &= ~TCSR_INITL_HIGH)

// 
// #define __tcu_set_pwm_output_shutdown_graceful(n)	(REG_TCU_TCSR((n)) &= ~TCSR_SD_ABRUPT)
// #define __tcu_set_pwm_output_shutdown_abrupt(n)		(REG_TCU_TCSR((n)) |= TCU_TCSR_SD_ABRUPT)

// 
// #define __tcu_clear_counter_to_zero(n)	(REG_TCU_TCSR((n)) |= TCU_TCSR_CLRZ)

// 
// #define __tcu_ost_enabled()		(REG_TCU_TER & TCU_TER_OSTEN)
// #define __tcu_enable_ost()		(REG_TCU_TESR = TCU_TESR_OST)
// #define __tcu_disable_ost()		(REG_TCU_TECR = TCU_TECR_OST)

// 
// #define __tcu_counter_enabled(n)	(REG_TCU_TER & (1 << (n)))
// #define __tcu_start_counter(n)		(REG_TCU_TESR |= (1 << (n)))
// #define __tcu_stop_counter(n)		(REG_TCU_TECR |= (1 << (n)))

// 
// #define __tcu_half_match_flag(n)	(REG_TCU_TFR & (1 << ((n) + 16)))
// #define __tcu_full_match_flag(n)	(REG_TCU_TFR & (1 << (n)))
// #define __tcu_set_half_match_flag(n)	(REG_TCU_TFSR = (1 << ((n) + 16)))
// #define __tcu_set_full_match_flag(n)	(REG_TCU_TFSR = (1 << (n)))
// #define __tcu_clear_half_match_flag(n)	(REG_TCU_TFCR = (1 << ((n) + 16)))
// #define __tcu_clear_full_match_flag(n)	(REG_TCU_TFCR = (1 << (n)))
// #define __tcu_mask_half_match_irq(n)	(REG_TCU_TMSR = (1 << ((n) + 16)))
// #define __tcu_mask_full_match_irq(n)	(REG_TCU_TMSR = (1 << (n)))
// #define __tcu_unmask_half_match_irq(n)	(REG_TCU_TMCR = (1 << ((n) + 16)))
// #define __tcu_unmask_full_match_irq(n)	(REG_TCU_TMCR = (1 << (n)))

// 
// #define __tcu_ost_match_flag()		(REG_TCU_TFR & TCU_TFR_OSTFLAG)
// #define __tcu_set_ost_match_flag()	(REG_TCU_TFSR = TCU_TFSR_OSTFLAG)
// #define __tcu_clear_ost_match_flag()	(REG_TCU_TFCR = TCU_TFCR_OSTFLAG)
// #define __tcu_ost_match_irq_masked()	(REG_TCU_TMR & TCU_TMR_OSTMASK)
// #define __tcu_mask_ost_match_irq()	(REG_TCU_TMSR = TCU_TMSR_OSTMASK)
// #define __tcu_unmask_ost_match_irq()	(REG_TCU_TMCR = TCU_TMCR_OSTMASK)

// 
// #define __tcu_wdt_clock_stopped()	(REG_TCU_TSR &TCU_TSR_WDT_STOP)
// #define __tcu_ost_clock_stopped()	(REG_TCU_TSR &TCU_TSR_OST_STOP)
// #define __tcu_timer_clock_stopped(n)	(REG_TCU_TSR & (1 << (n)))

// 
// #define __tcu_start_wdt_clock()		(REG_TCU_TSCR = TCU_TSCR_WDT)
// #define __tcu_start_ost_clock()		(REG_TCU_TSCR = TCU_TSCR_OST)
// #define __tcu_start_timer_clock(n)	(REG_TCU_TSCR = (1 << (n)))

// 
// #define __tcu_stop_wdt_clock()		(REG_TCU_TSSR = TCU_TSSR_WDT)
// #define __tcu_stop_ost_clock()		(REG_TCU_TSSR = TCU_TSSR_OST)
// #define __tcu_stop_timer_clock(n)	(REG_TCU_TSSR = (1 << (n)))

// 
// #define __tcu_get_count(n)		(REG_TCU_TCNT((n)))
// #define __tcu_set_count(n,v)		(REG_TCU_TCNT((n)) = (v))
// #define __tcu_set_full_data(n,v)	(REG_TCU_TDFR((n)) = (v))
// #define __tcu_set_half_data(n,v)	(REG_TCU_TDHR((n)) = (v))

// 
/* TCU2, counter 1, 2*/
// #define __tcu_read_real_value(n)	(REG_TCU_TSTR & (1 << ((n) + 16)))
// #define __tcu_read_false_value(n)	(REG_TCU_TSTR & (1 << ((n) + 16)))
// #define __tcu_counter_busy(n)		(REG_TCU_TSTR & (1 << (n)))
// #define __tcu_counter_ready(n)		(REG_TCU_TSTR & (1 << (n)))

// 
// #define __tcu_set_read_real_value(n)	(REG_TCU_TSTSR = (1 << ((n) + 16)))
// #define __tcu_set_read_false_value(n)	(REG_TCU_TSTCR = (1 << ((n) + 16)))
// #define __tcu_set_counter_busy(n)	(REG_TCU_TSTSR = (1 << (n)))
// #define __tcu_set_counter_ready(n)	(REG_TCU_TSTCR = (1 << (n)))

// 
// #endif /* __MIPS_ASSEMBLER */

// 

// 
// #endif /* __JZ4760BTCU_H__ */
