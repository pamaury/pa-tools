/*
 * jz4760ost.h
 * JZ4760 OST register definition
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 *
 * Author: whxu@ingenic.cn
 */

#ifndef __JZ4760OST_H__
#define __JZ4760OST_H__

//#define CONFIG_SOC_JZ4760B 1
/*
 * Operating system timer module(OST) address definition
 */
#define	OST_BASE	0xb0002000


/*
 * OST registers offset address definition
 */
#define OST_OSTDR_OFFSET	(0xe0)  /* rw, 32, 0x???????? */
#define OST_OSTCNTL_OFFSET	(0xe4)
#define OST_OSTCNTH_OFFSET	(0xe8)
#define OST_OST_OSTCSR_OFFSET	(0xec)  /* rw, 16, 0x0000 */

#define OST_OSTCNTH_BUF_OFFSET	(0xfc)


/*
 * OST registers address definition
 */
#define OST_OSTDR	(OST_BASE + OST_OSTDR_OFFSET)
#define OST_OSTCNTL	(OST_BASE + OST_OSTCNTL_OFFSET)
#define OST_OSTCNTH	(OST_BASE + OST_OSTCNTH_OFFSET)
#define OST_OSTCSR	(OST_BASE + OST_OST_OSTCSR_OFFSET)
#define OST_OSTCNTH_BUF	(OST_BASE + OST_OSTCNTH_BUF_OFFSET)


/*
 * OST registers common define
 */

/* Operating system control register(OSTCSR) */
#define OST_OSTCSR_CNT_MD		BIT15
#define OST_OSTCSR_SD		BIT9
#define OST_OSTCSR_EXT_EN		BIT2
#define OST_OSTCSR_RTC_EN		BIT1
#define OST_OSTCSR_PCK_EN		BIT0

#define OST_OSTCSR_PRESCALE_BIT	3
#define OST_OSTCSR_PRESCALE_MASK	BITS_H2L(5, OST_OSTCSR_PRESCALE_BIT)
#define OST_OSTCSR_PRESCALE_1	(0x0 << OST_OSTCSR_PRESCALE_BIT)
#define OST_OSTCSR_PRESCALE_4	(0x1 << OST_OSTCSR_PRESCALE_BIT)
#define OST_OSTCSR_PRESCALE_16	(0x2 << OST_OSTCSR_PRESCALE_BIT)
#define OST_OSTCSR_PRESCALE_64	(0x3 << OST_OSTCSR_PRESCALE_BIT)
#define OST_OSTCSR_PRESCALE_256	(0x4 << OST_OSTCSR_PRESCALE_BIT)
#define OST_OSTCSR_PRESCALE_1024	(0x5 << OST_OSTCSR_PRESCALE_BIT)


#ifndef __MIPS_ASSEMBLER

#define REG_OST_OSTDR		REG32(OST_OSTDR)

#define REG_OST_OSTCNTL		REG32(OST_OSTCNTL)
#define REG_OST_OSTCNTH		REG32(OST_OSTCNTH)

#define REG_OST_OSTCSR		REG16(OST_OSTCSR)

#define REG_OST_OSTCNTH_BUF	REG32(OST_OSTCNTH_BUF)

#endif /* __MIPS_ASSEMBLER */

#endif /* __JZ4760OST_H__ */
