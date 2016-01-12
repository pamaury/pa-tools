/*
 * jz4760brtc.h
 * JZ4760B RTC register definition
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 *
 * Author: cjwang@ingenic.cn
 */

// 
// #ifndef __JZ4760BRTC_H__
// #define __JZ4760BRTC_H__

// 

// 
/* Real time clock module(RTC) address definition */
this class RTC goto 0xb0003000 export "Real time clock module(RTC) address definition"

// 

// 
/*
 * RTC registers offset address definition
 */
const RTC_RTCCR_OFFSET 0x00
const RTC_RTCSR_OFFSET 0x04
const RTC_RTCSAR_OFFSET 0x08
const RTC_RTCGR_OFFSET 0x0c

// 
const RTC_HCR_OFFSET 0x20
const RTC_HWFCR_OFFSET 0x24
const RTC_HRCR_OFFSET 0x28
const RTC_HWCR_OFFSET 0x2c
const RTC_HWRSR_OFFSET 0x30
const RTC_HSPR_OFFSET 0x34
const RTC_WENR_OFFSET 0x3c

// 

// 
/*
 * RTC registers address definition
 */
register RTCCR goto RTC_RTCCR_OFFSET export ""
register RTCSR goto RTC_RTCSR_OFFSET export ""
register RTCSAR goto RTC_RTCSAR_OFFSET export ""
register RTCGR goto RTC_RTCGR_OFFSET export ""

// 
register HCR goto RTC_HCR_OFFSET export ""
register HWFCR goto RTC_HWFCR_OFFSET export ""
register HRCR goto RTC_HRCR_OFFSET export ""
register HWCR goto RTC_HWCR_OFFSET export ""
register HWRSR goto RTC_HWRSR_OFFSET export ""
register HSPR goto RTC_HSPR_OFFSET export ""
register WENR goto RTC_WENR_OFFSET export ""

// 

// 
/*
 * RTC registers common define
 */

// 
register RTCCR export "RTC control register"
register RTCCR int WRDY goto 7
register RTCCR int "1HZ" goto 6
register RTCCR int "1HZIE" goto 5
register RTCCR int AF goto 4
register RTCCR int AIE goto 3
register RTCCR int AE goto 2
register RTCCR int SELEXC goto 1
register RTCCR int RTCE goto 0

// 
register RTCGR export "RTC regulator register"
register RTCGR int LOCK goto 31

// 
const RTC_RTCGR_ADJC_BIT 16
register RTCGR int ADJC goto (25, RTC_RTCGR_ADJC_BIT)

// 
const RTC_RTCGR_NC1HZ_BIT 0
register RTCGR int NC1HZ goto (15, RTC_RTCGR_NC1HZ_BIT)

// 
register HCR export "Hibernate control register"
register HCR int PD goto 0

// 
register HWFCR export "Hibernate wakeup filter counter register"
const RTC_HWFCR_HWFCR_BIT 5
register HWFCR int HWFCR goto (15, RTC_HWFCR_HWFCR_BIT)
// #define RTC_HWFCR_WAIT_TIME(ms)	(((ms) << RTC_HWFCR_BIT) > RTC_HWFCR_MASK ? RTC_HWFCR_MASK : ((ms) << RTC_HWFCR_BIT))

// 
register HRCR export "Hibernate reset counter register"
const RTC_HRCR_HRCR_BIT 5
register HRCR int HRCR goto (11, RTC_HRCR_HRCR_BIT)
// #define RTC_HRCR_WAIT_TIME(ms)     (((ms) << RTC_HRCR_BIT) > RTC_HRCR_MASK ? RTC_HRCR_MASK : ((ms) << RTC_HRCR_BIT))

// 
register HWCR export "Hibernate wakeup control register"
register HWCR int EPDET goto 3
register HWCR int WKUPVL goto 2
register HWCR int EALM goto 0

// 
register HWRSR export "Hibernate wakeup status register"
register HWRSR int APD goto 8
register HWRSR int HR goto 5
register HWRSR int PPR goto 4
register HWRSR int PIN goto 1
register HWRSR int ALM goto 0

// 
register WENR export "write enable pattern register"
register WENR int WEN goto 31

// 
const RTC_WENR_WENPAT_BIT 0
register WENR int WENPAT goto (15, RTC_WENR_WENPAT_BIT)
const RTC_WENR_WENPAT_WRITABLE 0xa55a

// 
register HSPR export "Hibernate scratch pattern register"
const RTC_HSPR_RTCV 0x52544356

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 
/* Waiting for the RTC register writing finish */
// #define __wait_write_ready()						\
// do {									\
// 	unsigned int timeout = 1;					\
// 	while (!(rtc_read_reg(RTC_RTCCR) & RTC_RTCCR_WRDY) && timeout++);	\
// }while(0);

// 
/* Waiting for the RTC register writable */
// #define __wait_writable()						\
// do {									\
// 	unsigned int timeout = 1;					\
// 	__wait_write_ready();						\
// 	OUTREG32(RTC_WENR, RTC_WENR_WENPAT_WRITABLE);			\
// 	__wait_write_ready();						\
// 	while (!(rtc_read_reg(RTC_WENR) & RTC_WENR_WEN) && timeout++);	\
// }while(0);

// 
/* Basic RTC ops */
// #define rtc_read_reg(reg)				\
// ({							\
// 	unsigned int data;				\
// 	do {						\
// 		data = INREG32(reg);			\
// 	} while (INREG32(reg) != data);			\
// 	data;						\
// })

// 
// #define rtc_write_reg(reg, data)			\
// do {							\
// 	__wait_writable();				\
// 	OUTREG32(reg, data);				\
// 	__wait_write_ready();				\
// }while(0);

// 
// #define rtc_set_reg(reg, data)	rtc_write_reg(reg, rtc_read_reg(reg) | (data))
// #define rtc_clr_reg(reg, data)	rtc_write_reg(reg, rtc_read_reg(reg) & ~(data))

// 
// typedef volatile struct
// {
// 	unsigned int RTCCR;
// 	unsigned int RTCSR;
// 	unsigned int RTCSAR;
// 	unsigned int RTCGR;

// 
// 	unsigned int RTCRSV[(RTC_HCR_OFFSET - RTC_RTCGR_OFFSET)/4];

// 
// 	unsigned int HCR;
// 	unsigned int HWFCR;
// 	unsigned int HRCR;
// 	unsigned int HWCR;
// 	unsigned int HWRSR;
// 	unsigned int HSPR;
// 	unsigned int WENR;
// } JZ4760B_RTC, *PJZ4760B_RTC;

// 

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BRTC_H__ */
