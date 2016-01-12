/*
 * jz4760bsadc.h
 * JZ4760B SADC register definition.
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 *
 * Author:jfli@ingenic.cn
 */

#ifndef __JZ4760BSADC_H__
#define __JZ4760BSADC_H__


/* SAR A/D Controller */
#define	SADC_BASE		0xb0070000


/*
 * SADC registers offset definition
 */
#define SADC_ADENA_OFFSET	(0x00)	/* rw,  8, 0x00 */
#define SADC_ADCFG_OFFSET       (0x04)  /* rw, 32, 0x0002000c */
#define SADC_ADCTRL_OFFSET      (0x08)  /* rw,  8, 0x3f */
#define SADC_ADSTATE_OFFSET     (0x0c)  /* rw,  8, 0x00 */
#define SADC_ADSAME_OFFSET    	(0x10)  /* rw, 16, 0x0000 */
#define SADC_ADWAIT_OFFSET    	(0x14)  /* rw, 16, 0x0000 */
#define SADC_ADTCH_OFFSET       (0x18)  /* rw, 32, 0x00000000 */
#define SADC_ADVDAT_OFFSET      (0x1c)  /* rw, 16, 0x0000 */
#define SADC_ADADAT_OFFSET      (0x20)  /* rw, 16, 0x0000 */
#define SADC_ADFLT_OFFSET       (0x24)  /* rw, 16, 0x0000 */
#define SADC_ADCLK_OFFSET       (0x28)  /* rw, 32, 0x00000000 */


/*
 * SADC registers address definition
 */
#define SADC_ADENA		(SADC_BASE + SADC_ADENA_OFFSET)	 /* ADC Enable Register */
#define SADC_ADCFG		(SADC_BASE + SADC_ADCFG_OFFSET)	 /* ADC Configure Register */
#define SADC_ADCTRL		(SADC_BASE + SADC_ADCTRL_OFFSET) /* ADC Control Register */
#define SADC_ADSTATE		(SADC_BASE + SADC_ADSTATE_OFFSET)/* ADC Status Register*/
#define SADC_ADSAME		(SADC_BASE + SADC_ADSAME_OFFSET) /* ADC Same Point Time Register */
#define SADC_ADWAIT		(SADC_BASE + SADC_ADWAIT_OFFSET) /* ADC Wait Time Register */
#define SADC_ADTCH		(SADC_BASE + SADC_ADTCH_OFFSET)  /* ADC Touch Screen Data Register */
#define SADC_ADVDAT		(SADC_BASE + SADC_ADVDAT_OFFSET) /* ADC VBAT Data Register */
#define SADC_ADADAT		(SADC_BASE + SADC_ADADAT_OFFSET) /* ADC AUX Data Register */
#define SADC_ADFLT		(SADC_BASE + SADC_ADFLT_OFFSET)  /* ADC Filter Register */
#define SADC_ADCLK		(SADC_BASE + SADC_ADCLK_OFFSET)  /* ADC Clock Divide Register */


/*
 * SADC registers common define
 */

/* ADC Enable Register (ADENA) */
#define SADC_ADENA_POWER		BIT7
#define SADC_ADENA_SLP_MD		BIT6
#define SADC_ADENA_TCHEN		BIT2
#define SADC_ADENA_VBATEN		BIT1
#define SADC_ADENA_AUXEN		BIT0

/* ADC Configure Register (ADCFG) */
#define SADC_ADCFG_SPZZ           	BIT31
#define SADC_ADCFG_DMA_EN		BIT15

#define SADC_ADCFG_XYZ_BIT		13
#define SADC_ADCFG_XYZ_MASK		BITS_H2L(14, SADC_ADCFG_XYZ_BIT)
 #define SADC_ADCFG_XYZ_XYS		(0x0 << SADC_ADCFG_XYZ_BIT)
 #define SADC_ADCFG_XYZ_XYD		(0x1 << SADC_ADCFG_XYZ_BIT)
 #define SADC_ADCFG_XYZ_XYZ1Z2	(0x2 << SADC_ADCFG_XYZ_BIT)

#define SADC_ADCFG_SNUM_BIT		10
#define SADC_ADCFG_SNUM_MASK		BITS_H2L(12, SADC_ADCFG_SNUM_BIT)
 #define SADC_ADCFG_SNUM(n)          (((n) <= 6 ? ((n)-1) : ((n)-2)) << SADC_ADCFG_SNUM_BIT)

#define SADC_ADCFG_CMD_BIT		0
#define SADC_ADCFG_CMD_MASK		BITS_H2L(1, SADC_ADCFG_CMD_BIT)
 #define SADC_ADCFG_CMD_AUX(n)	((n) << SADC_ADCFG_CMD_BIT)

/* ADC Control Register (ADCTRL) */
#define SADC_ADCTRL_SLPENDM		BIT5
#define SADC_ADCTRL_PENDM		BIT4
#define SADC_ADCTRL_PENUM		BIT3
#define SADC_ADCTRL_DTCHM		BIT2
#define SADC_ADCTRL_VRDYM		BIT1
#define SADC_ADCTRL_ARDYM		BIT0
#define SADC_ADCTRL_MASK_ALL         (ADCTRL_SLPENDM | SADC_ADCTRL_PENDM | SADC_ADCTRL_PENUM \
                                | SADC_ADCTRL_DTCHM | SADC_ADCTRL_VRDYM | SADC_ADCTRL_ARDYM)

/*  ADC Status Register  (ADSTATE) */
#define SADC_ADSTATE_SLP_RDY		BIT7
#define SADC_ADSTATE_SLPEND		BIT5
#define SADC_ADSTATE_PEND		BIT4
#define SADC_ADSTATE_PENU		BIT3
#define SADC_ADSTATE_DTCH		BIT2
#define SADC_ADSTATE_VRDY		BIT1
#define SADC_ADSTATE_ARDY		BIT0

/* ADC Same Point Time Register (ADSAME) */
#define SADC_ADSAME_SCNT_BIT		0
#define SADC_ADSAME_SCNT_MASK	BITS_H2L(15, SADC_ADSAME_SCNT_BIT)

/* ADC Wait Pen Down Time Register (ADWAIT) */
#define SADC_ADWAIT_WCNT_BIT		0
#define SADC_ADWAIT_WCNT_MASK	BITS_H2L(15, SADC_ADWAIT_WCNT_BIT)

/* ADC Touch Screen Data Register (ADTCH) */
#define SADC_ADTCH_TYPE1		BIT31
#define SADC_ADTCH_TYPE0		BIT15

#define SADC_ADTCH_DATA1_BIT		16
#define SADC_ADTCH_DATA1_MASK	BITS_H2L(27, SADC_ADTCH_DATA1_BIT)

#define SADC_ADTCH_DATA0_BIT		0
#define SADC_ADTCH_DATA0_MASK	BITS_H2L(11, SADC_ADTCH_DATA0_BIT)

/* ADC VBAT Date Register (ADVDAT) */
#define SADC_ADVDAT_VDATA_BIT	0
#define SADC_ADVDAT_VDATA_MASK	BITS_H2L(11, SADC_ADVDAT_VDATA_BIT)

/* ADC AUX Data Register (ADADAT) */
#define SADC_ADADAT_ADATA_BIT	0
#define SADC_ADADAT_ADATA_MASK	BITS_H2L(11, SADC_ADADAT_ADATA_BIT)

/*  ADC Clock Divide Register (ADCLK) */
#define SADC_ADCLK_CLKDIV_MS_BIT	16
#define SADC_ADCLK_CLKDIV_MS_MASK	BITS_H2L(31, SADC_ADCLK_CLKDIV_MS_BIT)

#define SADC_ADCLK_CLKDIV_US_BIT	8
#define SADC_ADCLK_CLKDIV_US_MASK	BITS_H2L(15, SADC_ADCLK_CLKDIV_US_BIT)

#define SADC_ADCLK_CLKDIV_BIT	0
#define SADC_ADCLK_CLKDIV_MASK	BITS_H2L(7, SADC_ADCLK_CLKDIV_BIT)

/* ADC Filter Register (ADFLT) */
#define SADC_ADFLT_FLT_EN		BIT15

#define SADC_ADFLT_FLT_D_BIT		0
#define SADC_ADFLT_FLT_D_MASK	BITS_H2L(11, SADC_ADFLT_FLT_D_BIT)


#ifndef __MIPS_ASSEMBLER

#define REG_SADC_ADENA          REG8(SADC_ADENA)
#define REG_SADC_ADCFG          REG32(SADC_ADCFG)
#define REG_SADC_ADCTRL         REG8(SADC_ADCTRL)
#define REG_SADC_ADSTATE        REG8(SADC_ADSTATE)
#define REG_SADC_ADSAME         REG16(SADC_ADSAME)
#define REG_SADC_ADWAIT         REG16(SADC_ADWAIT)
#define REG_SADC_ADTCH          REG32(SADC_ADTCH)
#define REG_SADC_ADVDAT         REG16(SADC_ADVDAT)
#define REG_SADC_ADADAT         REG16(SADC_ADADAT)
#define REG_SADC_ADFLT          REG16(SADC_ADFLT)
#define REG_SADC_ADCLK          REG32(SADC_ADCLK)


typedef volatile struct
{
        unsigned char   ADENA;
        unsigned char   ADENARSV[3];
        unsigned int    ADCFG;
        unsigned char   ADCTRL;
        unsigned char   ADCTRLRSV[3];
        unsigned char   ADSTATE;
        unsigned char   ADSTATERSV[3];
        unsigned short  ADSAME;
        unsigned short  ADSAMERSV[1];
        unsigned short  ADWAIT;
        unsigned short  ADWAITRSV[1];
        unsigned int    ADTCH;
        unsigned short  ADVDAT;
        unsigned short  ADVDATRSV[1];
        unsigned short  ADADAT;
        unsigned short  ADADATRSV[1];
        unsigned short  ADFLT;
        unsigned short  ADFLTRSV[1];
        unsigned int    ADCLK;
} JZ4760B_SADC, *PJZ4760B_SADC;

#endif /* __MIPS_ASSEMBLER */

#endif /* __JZ4760BSADC_H__ */
