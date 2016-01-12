/*
 * jz4760brtc.h
 * JZ4760B RTC register definition
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 *
 * Author: cjwang@ingenic.cn
 */

#ifndef __JZ4760BRTC_H__
#define __JZ4760BRTC_H__


/* Real time clock module(RTC) address definition */
#define	RTC_BASE	0xb0003000


/*
 * RTC registers offset address definition
 */
#define RTC_RTCCR_OFFSET	(0x00)	/* rw, 32, 0x00000081 */
#define RTC_RTCSR_OFFSET	(0x04)	/* rw, 32, 0x???????? */
#define RTC_RTCSAR_OFFSET	(0x08)	/* rw, 32, 0x???????? */
#define RTC_RTCGR_OFFSET	(0x0c)	/* rw, 32, 0x0??????? */

#define RTC_HCR_OFFSET		(0x20)  /* rw, 32, 0x00000000 */
#define RTC_HWFCR_OFFSET	(0x24)  /* rw, 32, 0x0000???0 */
#define RTC_HRCR_OFFSET		(0x28)  /* rw, 32, 0x00000??0 */
#define RTC_HWCR_OFFSET		(0x2c)  /* rw, 32, 0x00000008 */
#define RTC_HWRSR_OFFSET	(0x30)  /* rw, 32, 0x00000000 */
#define RTC_HSPR_OFFSET		(0x34)  /* rw, 32, 0x???????? */
#define RTC_WENR_OFFSET		(0x3c)  /* rw, 32, 0x00000000 */


/*
 * RTC registers address definition
 */
#define RTC_RTCCR	(RTC_BASE + RTC_RTCCR_OFFSET)
#define RTC_RTCSR	(RTC_BASE + RTC_RTCSR_OFFSET)
#define RTC_RTCSAR	(RTC_BASE + RTC_RTCSAR_OFFSET)
#define RTC_RTCGR	(RTC_BASE + RTC_RTCGR_OFFSET)

#define RTC_HCR		(RTC_BASE + RTC_HCR_OFFSET)
#define RTC_HWFCR	(RTC_BASE + RTC_HWFCR_OFFSET)
#define RTC_HRCR	(RTC_BASE + RTC_HRCR_OFFSET)
#define RTC_HWCR	(RTC_BASE + RTC_HWCR_OFFSET)
#define RTC_HWRSR	(RTC_BASE + RTC_HWRSR_OFFSET)
#define RTC_HSPR	(RTC_BASE + RTC_HSPR_OFFSET)
#define RTC_WENR	(RTC_BASE + RTC_WENR_OFFSET)


/*
 * RTC registers common define
 */

/* RTC control register(RTCCR) */
#define RTC_RTCCR_WRDY		BIT7
#define RTC_RTCCR_1HZ		BIT6
#define RTC_RTCCR_1HZIE		BIT5
#define RTC_RTCCR_AF		BIT4
#define RTC_RTCCR_AIE		BIT3
#define RTC_RTCCR_AE		BIT2
#define RTC_RTCCR_SELEXC		BIT1
#define RTC_RTCCR_RTCE		BIT0

/* RTC regulator register(RTCGR) */
#define RTC_RTCGR_LOCK		BIT31

#define RTC_RTCGR_ADJC_BIT		16
#define RTC_RTCGR_ADJC_MASK		BITS_H2L(25, RTC_RTCGR_ADJC_BIT)

#define RTC_RTCGR_NC1HZ_BIT		0
#define RTC_RTCGR_NC1HZ_MASK	BITS_H2L(15, RTC_RTCGR_NC1HZ_BIT)

/* Hibernate control register(HCR) */
#define RTC_HCR_PD			BIT0

/* Hibernate wakeup filter counter register(HWFCR) */
#define RTC_HWFCR_HWFCR_BIT		5
#define RTC_HWFCR_HWFCR_MASK		BITS_H2L(15, RTC_HWFCR_HWFCR_BIT)
#define RTC_HWFCR_WAIT_TIME(ms)	(((ms) << RTC_HWFCR_BIT) > RTC_HWFCR_MASK ? RTC_HWFCR_MASK : ((ms) << RTC_HWFCR_BIT))

/* Hibernate reset counter register(HRCR) */
#define RTC_HRCR_HRCR_BIT		5
#define RTC_HRCR_HRCR_MASK		BITS_H2L(11, RTC_HRCR_HRCR_BIT)
#define RTC_HRCR_WAIT_TIME(ms)     (((ms) << RTC_HRCR_BIT) > RTC_HRCR_MASK ? RTC_HRCR_MASK : ((ms) << RTC_HRCR_BIT))

/* Hibernate wakeup control register(HWCR) */
#define RTC_HWCR_EPDET		BIT3
#define RTC_HWCR_WKUPVL		BIT2
#define RTC_HWCR_EALM		BIT0

/* Hibernate wakeup status register(HWRSR) */
#define RTC_HWRSR_APD		BIT8
#define RTC_HWRSR_HR		BIT5
#define RTC_HWRSR_PPR		BIT4
#define RTC_HWRSR_PIN		BIT1
#define RTC_HWRSR_ALM		BIT0

/* write enable pattern register(WENR) */
#define RTC_WENR_WEN		BIT31

#define RTC_WENR_WENPAT_BIT		0
#define RTC_WENR_WENPAT_MASK	BITS_H2L(15, RTC_WENR_WENPAT_BIT)
#define RTC_WENR_WENPAT_WRITABLE	(0xa55a)

/* Hibernate scratch pattern register(HSPR) */
#define RTC_HSPR_RTCV               0x52544356      /* The value is 'RTCV', means rtc is valid */ 


#ifndef __MIPS_ASSEMBLER

/* Waiting for the RTC register writing finish */
#define __wait_write_ready()						\
do {									\
	unsigned int timeout = 1;					\
	while (!(rtc_read_reg(RTC_RTCCR) & RTC_RTCCR_WRDY) && timeout++);	\
}while(0);

/* Waiting for the RTC register writable */
#define __wait_writable()						\
do {									\
	unsigned int timeout = 1;					\
	__wait_write_ready();						\
	OUTREG32(RTC_WENR, RTC_WENR_WENPAT_WRITABLE);			\
	__wait_write_ready();						\
	while (!(rtc_read_reg(RTC_WENR) & RTC_WENR_WEN) && timeout++);	\
}while(0);

/* Basic RTC ops */
#define rtc_read_reg(reg)				\
({							\
	unsigned int data;				\
	do {						\
		data = INREG32(reg);			\
	} while (INREG32(reg) != data);			\
	data;						\
})

#define rtc_write_reg(reg, data)			\
do {							\
	__wait_writable();				\
	OUTREG32(reg, data);				\
	__wait_write_ready();				\
}while(0);

#define rtc_set_reg(reg, data)	rtc_write_reg(reg, rtc_read_reg(reg) | (data))
#define rtc_clr_reg(reg, data)	rtc_write_reg(reg, rtc_read_reg(reg) & ~(data))

typedef volatile struct
{
	unsigned int RTCCR;
	unsigned int RTCSR;
	unsigned int RTCSAR;
	unsigned int RTCGR;

	unsigned int RTCRSV[(RTC_HCR_OFFSET - RTC_RTCGR_OFFSET)/4];

	unsigned int HCR;
	unsigned int HWFCR;
	unsigned int HRCR;
	unsigned int HWCR;
	unsigned int HWRSR;
	unsigned int HSPR;
	unsigned int WENR;
} JZ4760B_RTC, *PJZ4760B_RTC;


#endif /* __MIPS_ASSEMBLER */

#endif /* __JZ4760BRTC_H__ */
