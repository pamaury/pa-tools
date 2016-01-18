/*
 * jz4760bcpm.h
 * JZ4760B CPM register definition
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 *
 * Author: whxu@ingenic.cn
 */

#ifndef __JZ4760BCPM_H__
#define __JZ4760BCPM_H__

#ifndef JZ_EXTAL
#define JZ_EXTAL		12000000   /* 3.6864 MHz */
#endif
#ifndef JZ_EXTAL2
#define JZ_EXTAL2		32768     /* 32.768 KHz */
#endif

/*
 * Clock reset and power controller module(CPM) address definition
 */
#define	CPM_BASE	0xb0000000


/*
 * CPM registers offset address definition
 */
#define CPM_CPCCR_OFFSET        (0x00)  /* rw, 32, 0x01011100 */
#define CPM_LCR_OFFSET          (0x04)  /* rw, 32, 0x000000f8 */
#define CPM_RSR_OFFSET          (0x08)  /* rw, 32, 0x???????? */
#define CPM_CPPCR0_OFFSET       (0x10)  /* rw, 32, 0x28080011 */
#define CPM_CPPSR_OFFSET        (0x14)  /* rw, 32, 0x80000000 */
#define CPM_CLKGR0_OFFSET       (0x20)  /* rw, 32, 0x3fffffe0 */
#define CPM_OPCR_OFFSET         (0x24)  /* rw, 32, 0x00001570 */
#define CPM_CLKGR1_OFFSET       (0x28)  /* rw, 32, 0x0000017f */
#define CPM_CPPCR1_OFFSET       (0x30)  /* rw, 32, 0x28080002 */
#define CPM_CPSPR_OFFSET        (0x34)  /* rw, 32, 0x???????? */
#define CPM_CPSPPR_OFFSET       (0x38)  /* rw, 32, 0x0000a5a5 */
#define CPM_USBPCR_OFFSET       (0x3c)  /* rw, 32, 0x42992198 */
#define CPM_USBRDT_OFFSET       (0x40)  /* rw, 32, 0x00000096 */
#define CPM_USBVBFIL_OFFSET     (0x44)  /* rw, 32, 0x00000080 */
#define CPM_USBCDR_OFFSET       (0x50)  /* rw, 32, 0x00000000 */
#define CPM_I2SCDR_OFFSET       (0x60)  /* rw, 32, 0x00000000 */
#define CPM_LPCDR_OFFSET        (0x64)  /* rw, 32, 0x00000000 */
#define CPM_MSCCDR_OFFSET       (0x68)  /* rw, 32, 0x00000000 */
#define CPM_UHCCDR_OFFSET       (0x6c)  /* rw, 32, 0x00000000 */
#define CPM_SSICDR_OFFSET       (0x74)  /* rw, 32, 0x00000000 */
#define CPM_CIMCDR_OFFSET       (0x7c)  /* rw, 32, 0x00000000 */
#define CPM_GPSCDR_OFFSET       (0x80)  /* rw, 32, 0x00000000 */
#define CPM_PCMCDR_OFFSET       (0x84)  /* rw, 32, 0x00000000 */
#define CPM_GPUCDR_OFFSET       (0x88)  /* rw, 32, 0x00000000 */
#define CPM_PSWC0ST_OFFSET      (0x90)  /* rw, 32, 0x00000000 */
#define CPM_PSWC1ST_OFFSET      (0x94)  /* rw, 32, 0x00000000 */
#define CPM_PSWC2ST_OFFSET      (0x98)  /* rw, 32, 0x00000000 */
#define CPM_PSWC3ST_OFFSET      (0x9c)  /* rw, 32, 0x00000000 */


/*
 * CPM registers address definition
 */
#define CPM_CPCCR        (CPM_BASE + CPM_CPCCR_OFFSET)
#define CPM_LCR          (CPM_BASE + CPM_LCR_OFFSET)
#define CPM_RSR          (CPM_BASE + CPM_RSR_OFFSET)
#define CPM_CPPCR0       (CPM_BASE + CPM_CPPCR0_OFFSET)
#define CPM_CPPSR        (CPM_BASE + CPM_CPPSR_OFFSET)
#define CPM_CLKGR0       (CPM_BASE + CPM_CLKGR0_OFFSET)
#define CPM_OPCR         (CPM_BASE + CPM_OPCR_OFFSET)
#define CPM_CLKGR1       (CPM_BASE + CPM_CLKGR1_OFFSET)
#define CPM_CPPCR1       (CPM_BASE + CPM_CPPCR1_OFFSET)
#define CPM_CPSPR        (CPM_BASE + CPM_CPSPR_OFFSET)
#define CPM_CPSPPR       (CPM_BASE + CPM_CPSPPR_OFFSET)
#define CPM_USBPCR       (CPM_BASE + CPM_USBPCR_OFFSET)
#define CPM_USBRDT       (CPM_BASE + CPM_USBRDT_OFFSET)
#define CPM_USBVBFIL     (CPM_BASE + CPM_USBVBFIL_OFFSET)
#define CPM_USBCDR       (CPM_BASE + CPM_USBCDR_OFFSET)
#define CPM_I2SCDR       (CPM_BASE + CPM_I2SCDR_OFFSET)
#define CPM_LPCDR        (CPM_BASE + CPM_LPCDR_OFFSET)
#define CPM_MSCCDR       (CPM_BASE + CPM_MSCCDR_OFFSET)
#define CPM_UHCCDR       (CPM_BASE + CPM_UHCCDR_OFFSET)
#define CPM_SSICDR       (CPM_BASE + CPM_SSICDR_OFFSET)
#define CPM_CIMCDR       (CPM_BASE + CPM_CIMCDR_OFFSET)
#define CPM_GPSCDR       (CPM_BASE + CPM_GPSCDR_OFFSET)
#define CPM_PCMCDR       (CPM_BASE + CPM_PCMCDR_OFFSET)
#define CPM_GPUCDR       (CPM_BASE + CPM_GPUCDR_OFFSET)
#define CPM_PSWC0ST      (CPM_BASE + CPM_PSWC0ST_OFFSET)
#define CPM_PSWC1ST      (CPM_BASE + CPM_PSWC1ST_OFFSET)
#define CPM_PSWC2ST      (CPM_BASE + CPM_PSWC2ST_OFFSET)
#define CPM_PSWC3ST      (CPM_BASE + CPM_PSWC3ST_OFFSET)


/*
 * CPM registers common define
 */

/* Clock control register(CPCCR) */
#define CPM_CPCCR_ECS               BIT31
#define CPM_CPCCR_MEM               BIT30
#define CPM_CPCCR_CE                BIT22
#define CPM_CPCCR_PCS               BIT21

#define CPM_CPCCR_SDIV_BIT          24
#define CPM_CPCCR_SDIV_MASK         BITS_H2L(27, CPM_CPCCR_SDIV_BIT)

#define CPM_CPCCR_H2DIV_BIT         16
#define CPM_CPCCR_H2DIV_MASK        BITS_H2L(19, CPM_CPCCR_H2DIV_BIT)

#define CPM_CPCCR_MDIV_BIT          12
#define CPM_CPCCR_MDIV_MASK         BITS_H2L(15, CPM_CPCCR_MDIV_BIT)

#define CPM_CPCCR_PDIV_BIT		8
#define CPM_CPCCR_PDIV_MASK         BITS_H2L(11, CPM_CPCCR_PDIV_BIT)

#define CPM_CPCCR_HDIV_BIT		4
#define CPM_CPCCR_HDIV_MASK         BITS_H2L(7, CPM_CPCCR_HDIV_BIT)

#define CPM_CPCCR_CDIV_BIT		0
#define CPM_CPCCR_CDIV_MASK         BITS_H2L(3, CPM_CPCCR_CDIV_BIT)

/* Low power control register(LCR) */
#define CPM_LCR_PDAHB1              BIT30
#define CPM_LCR_VBATIR              BIT29
#define CPM_LCR_PDGPS               BIT28
#define CPM_LCR_PDAHB1S             BIT26
#define CPM_LCR_PDGPSS              BIT24
#define CPM_LCR_DOZE                BIT2

#define CPM_LCR_PST_BIT             8
#define CPM_LCR_PST_MASK            BITS_H2L(19, CPM_LCR_PST_BIT)

#define CPM_LCR_DUTY_BIT            3
#define CPM_LCR_DUTY_MASK           BITS_H2L(7, CPM_LCR_DUTY_BIT)

#define CPM_LCR_LPM_BIT             0
#define CPM_LCR_LPM_MASK            BITS_H2L(1, CPM_LCR_LPM_BIT)
#define CPM_LCR_LPM_IDLE            (0x0 << CPM_LCR_LPM_BIT)
#define CPM_LCR_LPM_SLEEP           (0x1 << CPM_LCR_LPM_BIT)

/* Reset status register(RSR) */
#define CPM_RSR_P0R         BIT2
#define CPM_RSR_WR          BIT1
#define CPM_RSR_PR          BIT0

/* PLL control register 0(CPPCR0) */
#define CPM_CPPCR0_LOCK             BIT15   /* LOCK0 bit */
#define CPM_CPPCR0_ENLOCK           BIT14
#define CPM_CPPCR0_PLLS             BIT10
#define CPM_CPPCR0_PLLBP            BIT9
#define CPM_CPPCR0_PLLEN            BIT8

#define CPM_CPPCR0_PLLM_BIT         24
#define CPM_CPPCR0_PLLM_MASK        BITS_H2L(30, CPM_CPPCR0_PLLM_BIT)

#define CPM_CPPCR0_PLLN_BIT         18
#define CPM_CPPCR0_PLLN_MASK        BITS_H2L(21, CPM_CPPCR0_PLLN_BIT)

#define CPM_CPPCR0_PLLOD_BIT        16
#define CPM_CPPCR0_PLLOD_MASK       BITS_H2L(17, CPM_CPPCR0_PLLOD_BIT)

#define CPM_CPPCR0_PLLST_BIT        0
#define CPM_CPPCR0_PLLST_MASK       BITS_H2L(7, CPM_CPPCR0_PLLST_BIT)

/* PLL switch and status register(CPPSR) */
#define CPM_CPPSR_PLLOFF            BIT31
#define CPM_CPPSR_PLLBP             BIT30
#define CPM_CPPSR_PLLON             BIT29
#define CPM_CPPSR_PS                BIT28
#define CPM_CPPSR_FS                BIT27
#define CPM_CPPSR_CS                BIT26
#define CPM_CPPSR_SM                BIT2
#define CPM_CPPSR_PM                BIT1
#define CPM_CPPSR_FM                BIT0

/* Clock gate register 0(CLKGR0) */
#define CPM_CLKGR0_EMC              BIT31
#define CPM_CLKGR0_DDR              BIT30
#define CPM_CLKGR0_IPU              BIT29
#define CPM_CLKGR0_LCD              BIT28
#define CPM_CLKGR0_TVE              BIT27
#define CPM_CLKGR0_CIM              BIT26
#define CPM_CLKGR0_MDMA             BIT25
#define CPM_CLKGR0_UHC              BIT24
#define CPM_CLKGR0_MAC              BIT23
#define CPM_CLKGR0_GPS              BIT22
#define CPM_CLKGR0_DMAC             BIT21
#define CPM_CLKGR0_SSI2             BIT20
#define CPM_CLKGR0_SSI1             BIT19
#define CPM_CLKGR0_UART3            BIT18
#define CPM_CLKGR0_UART2            BIT17
#define CPM_CLKGR0_UART1            BIT16
#define CPM_CLKGR0_UART0            BIT15
#define CPM_CLKGR0_SADC             BIT14
#define CPM_CLKGR0_KBC              BIT13
#define CPM_CLKGR0_MSC2             BIT12
#define CPM_CLKGR0_MSC1             BIT11
#define CPM_CLKGR0_OWI              BIT10
#define CPM_CLKGR0_TSSI             BIT9
#define CPM_CLKGR0_AIC              BIT8
#define CPM_CLKGR0_SCC              BIT7
#define CPM_CLKGR0_I2C1             BIT6
#define CPM_CLKGR0_I2C0             BIT5
#define CPM_CLKGR0_SSI0             BIT4
#define CPM_CLKGR0_MSC0             BIT3
#define CPM_CLKGR0_OTG              BIT2
#define CPM_CLKGR0_BCH              BIT1
#define CPM_CLKGR0_NEMC             BIT0

/* Oscillator and power control register(OPCR) */
#define CPM_OPCR_OTGPHY_ENABLE      BIT7    /* SPENDN bit */
#define CPM_OPCR_GPSEN              BIT6
#define CPM_OPCR_UHCPHY_DISABLE     BIT5    /* SPENDH bit */
#define CPM_OPCR_O1SE               BIT4
#define CPM_OPCR_PD                 BIT3
#define CPM_OPCR_ERCS               BIT2

#define CPM_OPCR_O1ST_BIT           8
#define CPM_OPCR_O1ST_MASK          BITS_H2L(15, CPM_OPCR_O1ST_BIT)

/* Clock gate register 1(CLKGR1) */
#define CPM_CLKGR1_AUX              BIT11
#define CPM_CLKGR1_OSD              BIT10
#define CPM_CLKGR1_GPU              BIT9
#define CPM_CLKGR1_PCM              BIT8
#define CPM_CLKGR1_AHB1             BIT7
#define CPM_CLKGR1_CABAC            BIT6
#define CPM_CLKGR1_SRAM             BIT5
#define CPM_CLKGR1_DCT              BIT4
#define CPM_CLKGR1_ME               BIT3
#define CPM_CLKGR1_DBLK             BIT2
#define CPM_CLKGR1_MC               BIT1
#define CPM_CLKGR1_BDMA             BIT0

/* PLL control register 1(CPPCR1) */
#define CPM_CPPCR1_P1SCS            BIT15
#define CPM_CPPCR1_PLL1EN           BIT7
#define CPM_CPPCR1_PLL1S            BIT6
#define CPM_CPPCR1_LOCK             BIT2    /* LOCK1 bit */
#define CPM_CPPCR1_PLL1OFF          BIT1
#define CPM_CPPCR1_PLL1ON           BIT0

#define CPM_CPPCR1_PLL1M_BIT        24
#define CPM_CPPCR1_PLL1M_MASK       BITS_H2L(30, CPM_CPPCR1_PLL1M_BIT)

#define CPM_CPPCR1_PLL1N_BIT        18
#define CPM_CPPCR1_PLL1N_MASK       BITS_H2L(21, CPM_CPPCR1_PLL1N_BIT)

#define CPM_CPPCR1_PLL1OD_BIT       16
#define CPM_CPPCR1_PLL1OD_MASK      BITS_H2L(17, CPM_CPPCR1_PLL1OD_BIT)

#define CPM_CPPCR1_P1SDIV_BIT       9
#define CPM_CPPCR1_P1SDIV_MASK      BITS_H2L(14, CPM_CPPCR1_P1SDIV_BIT)

/* CPM scratch pad protected register(CPSPPR) */
#define CPM_CPSPPR_CPSPR_WRITABLE   (0x00005a5a)

/* OTG parameter control register(USBPCR) */
#define CPM_USBPCR_USB_MODE         BIT31
#define CPM_USBPCR_AVLD_REG         BIT30
#define CPM_USBPCR_INCRM            BIT27   /* INCR_MASK bit */
#define CPM_USBPCR_CLK12_EN         BIT26
#define CPM_USBPCR_COMMONONN        BIT25
#define CPM_USBPCR_VBUSVLDEXT       BIT24
#define CPM_USBPCR_VBUSVLDEXTSEL    BIT23
#define CPM_USBPCR_POR              BIT22
#define CPM_USBPCR_SIDDQ            BIT21
#define CPM_USBPCR_OTG_DISABLE      BIT20
#define CPM_USBPCR_TXPREEMPHTUNE    BIT6

#define CPM_USBPCR_IDPULLUP_BIT             28   /* IDPULLUP_MASK bit */
#define CPM_USBPCR_IDPULLUP_MASK            BITS_H2L(29, CPM_USBPCR_IDPULLUP_BIT)

#define CPM_USBPCR_COMPDISTUNE_BIT          17
#define CPM_USBPCR_COMPDISTUNE_MASK         BITS_H2L(19, CPM_USBPCR_COMPDISTUNE_BIT)

#define CPM_USBPCR_OTGTUNE_BIT              14
#define CPM_USBPCR_OTGTUNE_MASK             BITS_H2L(16, CPM_USBPCR_OTGTUNE_BIT)

#define CPM_USBPCR_SQRXTUNE_BIT             11
#define CPM_USBPCR_SQRXTUNE_MASK            BITS_H2L(13, CPM_USBPCR_SQRXTUNE_BIT)

#define CPM_USBPCR_TXFSLSTUNE_BIT           7
#define CPM_USBPCR_TXFSLSTUNE_MASK          BITS_H2L(10, CPM_USBPCR_TXFSLSTUNE_BIT)

#define CPM_USBPCR_TXRISETUNE_BIT           4
#define CPM_USBPCR_TXRISETUNE_MASK          BITS_H2L(5, CPM_USBPCR_TXRISETUNE_BIT)

#define CPM_USBPCR_TXVREFTUNE_BIT           0
#define CPM_USBPCR_TXVREFTUNE_MASK          BITS_H2L(3, CPM_USBPCR_TXVREFTUNE_BIT)

/* OTG reset detect timer register(USBRDT) */
#define CPM_USBRDT_VBFIL_LD_EN      BIT25
#define CPM_USBRDT_IDDIG_EN         BIT24
#define CPM_USBRDT_IDDIG_REG        BIT23

#define CPM_USBRDT_USBRDT_BIT       0
#define CPM_USBRDT_USBRDT_MASK      BITS_H2L(22, CPM_USBRDT_USBRDT_BIT)

/* OTG PHY clock divider register(USBCDR) */
#define CPM_USBCDR_UCS              BIT31
#define CPM_USBCDR_UPCS             BIT30

#define CPM_USBCDR_OTGDIV_BIT       0       /* USBCDR bit */
#define CPM_USBCDR_OTGDIV_MASK      BITS_H2L(5, CPM_USBCDR_OTGDIV_BIT)

/* I2S device clock divider register(I2SCDR) */
#define CPM_I2SCDR_I2CS             BIT31
#define CPM_I2SCDR_I2PCS            BIT30

#define CPM_I2SCDR_I2SDIV_BIT       0       /* I2SCDR bit */
#define CPM_I2SCDR_I2SDIV_MASK      BITS_H2L(8, CPM_I2SCDR_I2SDIV_BIT)

/* LCD pix clock divider register(LPCDR) */
#define CPM_LPCDR_LTCS              BIT30
#define CPM_LPCDR_LPCS              BIT29

#define CPM_LPCDR_PIXDIV_BIT        0       /* LPCDR bit */
#define CPM_LPCDR_PIXDIV_MASK       BITS_H2L(10, CPM_LPCDR_PIXDIV_BIT)

/* MSC clock divider register(MSCCDR) */
#define CPM_MSCCDR_MCS              BIT31

#define CPM_MSCCDR_MSCDIV_BIT       0       /* MSCCDR bit */
#define CPM_MSCCDR_MSCDIV_MASK      BITS_H2L(5, CPM_MSCCDR_MSCDIV_BIT)

/* UHC device clock divider register(UHCCDR) */
#define CPM_UHCCDR_UHPCS            BIT31

#define CPM_UHCCDR_UHCDIV_BIT       0       /* UHCCDR bit */
#define CPM_UHCCDR_UHCDIV_MASK      BITS_H2L(3, CPM_UHCCDR_UHCDIV_BIT)

/* SSI clock divider register(SSICDR) */
#define CPM_SSICDR_SCS              BIT31

#define CPM_SSICDR_SSIDIV_BIT       0       /* SSICDR bit */
#define CPM_SSICDR_SSIDIV_MASK      BITS_H2L(5, CPM_SSICDR_SSIDIV_BIT)

/* CIM mclk clock divider register(CIMCDR) */
#define CPM_CIMCDR_CIMDIV_BIT       0       /* CIMCDR bit */
#define CPM_CIMCDR_CIMDIV_MASK      BITS_H2L(7, CPM_CIMCDR_CIMDIV_BIT)

/* GPS clock divider register(GPSCDR) */
#define CPM_GPSCDR_GPCS             BIT31

#define CPM_GPSCDR_GPSDIV_BIT       0       /* GPSCDR bit */
#define CPM_GPSCDR_GPSDIV_MASK      BITS_H2L(3, CPM_GPSCDR_GPSDIV_BIT)

/* PCM device clock divider register(PCMCDR) */
#define CPM_PCMCDR_PCMS             BIT31
#define CPM_PCMCDR_PCMPCS           BIT30

#define CPM_PCMCDR_PCMDIV_BIT       0       /* PCMCDR bit */
#define CPM_PCMCDR_PCMDIV_MASK      BITS_H2L(8, CPM_PCMCDR_PCMDIV_BIT)

/* GPU clock divider register */
#define CPM_GPUCDR_GPCS             BIT31
#define CPM_GPUCDR_GPUDIV_BIT       0       /* GPUCDR bit */
#define CPM_GPUCDR_GPUDIV_MASK      BITS_H2L(2, CPM_GPUCDR_GPUDIV_BIT)


#ifndef __MIPS_ASSEMBLER

#define REG_CPM_CPCCR           REG32(CPM_CPCCR)
#define REG_CPM_RSR             REG32(CPM_RSR)
#define REG_CPM_CPPCR0          REG32(CPM_CPPCR0)
#define REG_CPM_CPPSR           REG32(CPM_CPPSR)
#define REG_CPM_CPPCR1          REG32(CPM_CPPCR1)
#define REG_CPM_CPSPR           REG32(CPM_CPSPR)
#define REG_CPM_CPSPPR          REG32(CPM_CPSPPR)
#define REG_CPM_USBPCR          REG32(CPM_USBPCR)
#define REG_CPM_USBRDT          REG32(CPM_USBRDT)
#define REG_CPM_USBVBFIL        REG32(CPM_USBVBFIL)
#define REG_CPM_USBCDR          REG32(CPM_USBCDR)
#define REG_CPM_I2SCDR          REG32(CPM_I2SCDR)
#define REG_CPM_LPCDR           REG32(CPM_LPCDR)
#define REG_CPM_MSCCDR          REG32(CPM_MSCCDR)
#define REG_CPM_UHCCDR          REG32(CPM_UHCCDR)
#define REG_CPM_SSICDR          REG32(CPM_SSICDR)
#define REG_CPM_CIMCDR          REG32(CPM_CIMCDR)
#define REG_CPM_GPSCDR          REG32(CPM_GPSCDR)
#define REG_CPM_PCMCDR          REG32(CPM_PCMCDR)
#define REG_CPM_GPUCDR          REG32(CPM_GPUCDR)

#define REG_CPM_PSWC0ST         REG32(CPM_PSWC0ST)
#define REG_CPM_PSWC1ST         REG32(CPM_PSWC1ST)
#define REG_CPM_PSWC2ST         REG32(CPM_PSWC2ST)
#define REG_CPM_PSWC3ST         REG32(CPM_PSWC3ST)

#define REG_CPM_LCR             REG32(CPM_LCR)
#define REG_CPM_CLKGR0          REG32(CPM_CLKGR0)
#define REG_CPM_OPCR            REG32(CPM_OPCR)
#define REG_CPM_CLKGR1          REG32(CPM_CLKGR1)
#define REG_CPM_CLKGR           REG32(CPM_CLKGR0)

typedef enum {
        CGM_NEMC = 0,
        CGM_BCH  = 1,
        CGM_OTG  = 2,
        CGM_MSC0 = 3,
        CGM_SSI0 = 4,
        CGM_I2C0 = 5,
        CGM_I2C1 = 6,
        CGM_SCC  = 7,
        CGM_AIC         = 8,
        CGM_TSSI        = 9,
        CGM_OWI         = 10,
        CGM_MSC1        = 11,
        CGM_MSC2        = 12,
        CGM_KBC         = 13,
        CGM_SADC        = 14,
        CGM_UART0       = 15,
        CGM_UART1 = 16,
        CGM_UART2 = 17,
        CGM_UART3 = 18,
        CGM_SSI1  = 19,
        CGM_SSI2  = 20,
        CGM_DMAC  = 21,
        CGM_GPS   = 22,
        CGM_MAC   = 23,
        CGM_UHC         = 24,
        CGM_MDMA        = 25,
        CGM_CIM         = 26,
        CGM_TVE         = 27,
        CGM_LCD         = 28,
        CGM_IPU         = 29,
        CGM_DDR         = 30,
        CGM_EMC         = 31,
        CGM_BDMA  = 32 + 0,
        CGM_MC    = 32 + 1,
        CGM_DBLK  = 32 + 2,
        CGM_ME    = 32 + 3,
        CGM_DCT   = 32 + 4,
        CGM_SRAM  = 32 + 5,
        CGM_CABAC = 32 + 6,
        CGM_AHB1  = 32 + 7,
        CGM_PCM         = 32 + 8,
        CGM_GPU         = 32 + 9,
        CGM_OSD         = 32 + 10,
        CGM_AUX         = 32 + 11,
        CGM_ALL_MODULE,
} clock_gate_module;


#define __CGU_CLOCK_BASE__      0x1000

typedef enum {
        /* Clock source is pll0 */
        CGU_CCLK = __CGU_CLOCK_BASE__ + 0,
        CGU_HCLK,
        CGU_PCLK,
        CGU_MCLK,
        CGU_H2CLK,
        CGU_SCLK,

        /* Clock source is exclk, pll0 or pll0/2 */
        CGU_MSCCLK,
        CGU_SSICLK,

        /* Clock source is pll0 or pll0/2 */
        CGU_CIMCLK,

        /* Clock source is exclk, pll0, pll0/2 or pll1 */
        CGU_TVECLK,

        /* Clock source is pll0 */
        CGU_LPCLK,

        /* Clock source is exclk, exclk/2, pll0, pll0/2 or pll1 */
        CGU_I2SCLK,
        CGU_PCMCLK,
        CGU_OTGCLK,

        /* Clock source is pll0, pll0/2 or pll1 */
        CGU_UHCCLK,
        CGU_GPSCLK,
        CGU_GPUCLK,

        /* Clock source is exclk or exclk/2 */
        CGU_UARTCLK,
        CGU_SADCCLK,

        /* Clock source is exclk */
        CGU_TCUCLK,

	/* Clock source is external rtc clock */
	CGU_RTCCLK,

        CGU_CLOCK_MAX,
} cgu_clock;

/*
 * JZ4760B clocks structure
 */
typedef struct {
	unsigned int cclk;	/* CPU clock				*/
	unsigned int hclk;	/* System bus clock: AHB0,AHB1		*/
	unsigned int h1clk;	/* For compatible, the same as h1clk	*/
	unsigned int h2clk;	/* System bus clock: AHB2		*/
	unsigned int pclk;	/* Peripheral bus clock			*/
	unsigned int mclk;	/* EMC or DDR controller clock		*/
	unsigned int sclk;	/* NEMC controller clock		*/
	unsigned int cko;	/* SDRAM or DDR clock			*/
	unsigned int pixclk;	/* LCD pixel clock			*/
	unsigned int tveclk;	/* TV encoder 27M  clock		*/
	unsigned int cimmclk;	/* Clock output from CIM module		*/
	unsigned int cimpclk;	/* Clock input to CIM module		*/
	unsigned int gpuclk;	/* GPU clock				*/
	unsigned int gpsclk;	/* GPS clock				*/
	unsigned int i2sclk;	/* I2S codec clock			*/
	unsigned int bitclk;	/* AC97 bit clock			*/
	unsigned int pcmclk;	/* PCM clock				*/
	unsigned int mscclk;	/* MSC clock				*/
	unsigned int ssiclk;	/* SSI clock				*/
	unsigned int tssiclk;	/* TSSI clock				*/
	unsigned int otgclk;	/* USB OTG clock			*/
	unsigned int uhcclk;	/* USB UHCI clock			*/
	unsigned int extalclk;	/* EXTAL clock for
				   UART,I2C,TCU,USB2.0-PHY,AUDIO CODEC	*/
	unsigned int rtcclk;	/* RTC clock for CPM,INTC,RTC,TCU,WDT	*/
} jz_clocks_t;

void cpm_start_clock(clock_gate_module module_name);
void cpm_stop_clock(clock_gate_module module_name);

unsigned int cpm_set_clock(cgu_clock clock_name, unsigned int clock_hz);
unsigned int cpm_get_clock(cgu_clock clock_name);
unsigned int cpm_get_pllout(void);

void cpm_uhc_phy(unsigned int en);

/**************remove me if android's kernel support these operations********start*********  */
#define __cpm_stop_lcd()	(REG_CPM_CLKGR0 |= CLKGR0_LCD)
#define __cpm_start_lcd()	(REG_CPM_CLKGR0 &= ~CLKGR0_LCD)
#define __cpm_set_pixdiv(v) \
	(REG_CPM_LPCDR = (REG_CPM_LPCDR & ~LPCDR_PIXDIV_MASK) | ((v) << (LPCDR_PIXDIV_BIT)))

#define __cpm_get_pixdiv() \
	((REG_CPM_LPCDR & LPCDR_PIXDIV_MASK) >> LPCDR_PIXDIV_BIT)

#define __cpm_select_pixclk_lcd()	(REG_CPM_LPCDR &= ~LPCDR_LTCS)
#define __cpm_select_pixclk_tve()	(REG_CPM_LPCDR |= LPCDR_LTCS)

static __inline__ unsigned int __cpm_get_pllout2(void)
{
#if defined(CONFIG_FPGA)
	return cpm_get_pllout();
#else
	if (REG_CPM_CPCCR & CPCCR_PCS)
		return cpm_get_pllout();
	else
		return cpm_get_pllout()/2;
#endif
}

static __inline__ unsigned int __cpm_get_pixclk(void)
{
	return __cpm_get_pllout2() / (__cpm_get_pixdiv() + 1);
}

/* EXTAL clock */
static __inline__ unsigned int __cpm_get_extalclk0(void)
{
	return JZ_EXTAL;
}

/* EXTAL clock for UART,I2C,SSI,SADC,USB-PHY */
static __inline__ unsigned int __cpm_get_extalclk(void)
{
#if defined(CONFIG_FPGA)
	return __cpm_get_extalclk0() / CFG_DIV;
#else
	if (REG_CPM_CPCCR & CPCCR_ECS)
		return __cpm_get_extalclk0() / 2;
	else
		return __cpm_get_extalclk0();
#endif

}

/* RTC clock for CPM,INTC,RTC,TCU,WDT */
static __inline__ unsigned int __cpm_get_rtcclk(void)
{
	return JZ_EXTAL2;
}

extern jz_clocks_t jz_clocks;

#define __cpm_select_i2sclk_exclk()	(REG_CPM_I2SCDR &= ~I2SCDR_I2CS)
#define __cpm_enable_pll_change()	(REG_CPM_CPCCR |= CPCCR_CE)

#define __cpm_suspend_otg_phy()		(REG_CPM_OPCR &= ~OPCR_OTGPHY_ENABLE)
#define __cpm_enable_otg_phy()		(REG_CPM_OPCR |=  OPCR_OTGPHY_ENABLE)

#define __cpm_suspend_uhc_phy()		(REG_CPM_OPCR |= OPCR_UHCPHY_DISABLE)
#define __cpm_enable_uhc_phy()		(REG_CPM_OPCR &= ~OPCR_UHCPHY_DISABLE)
#define __cpm_suspend_gps()        (REG_CPM_OPCR &= ~OPCR_GPSEN)
#define __cpm_disable_osc_in_sleep()	(REG_CPM_OPCR &= ~OPCR_O1SE)
#define __cpm_select_rtcclk_rtc()	(REG_CPM_OPCR |= OPCR_ERCS)

#define __cpm_get_pllm() \
	((REG_CPM_CPPCR0 & CPPCR0_PLLM_MASK) >> CPPCR0_PLLM_BIT)
#define __cpm_get_plln() \
	((REG_CPM_CPPCR0 & CPPCR0_PLLN_MASK) >> CPPCR0_PLLN_BIT)
#define __cpm_get_pllod() \
	((REG_CPM_CPPCR0 & CPPCR0_PLLOD_MASK) >> CPPCR0_PLLOD_BIT)

#define __cpm_get_pll1m() \
	((REG_CPM_CPPCR1 & CPPCR1_PLL1M_MASK) >> CPPCR1_PLL1M_BIT)
#define __cpm_get_pll1n() \
	((REG_CPM_CPPCR1 & CPPCR1_PLL1N_MASK) >> CPPCR1_PLL1N_BIT)
#define __cpm_get_pll1od() \
	((REG_CPM_CPPCR1 & CPPCR1_PLL1OD_MASK) >> CPPCR1_PLL1OD_BIT)

#define __cpm_get_cdiv() \
	((REG_CPM_CPCCR & CPCCR_CDIV_MASK) >> CPCCR_CDIV_BIT)
#define __cpm_get_hdiv() \
	((REG_CPM_CPCCR & CPCCR_HDIV_MASK) >> CPCCR_HDIV_BIT)
#define __cpm_get_h2div() \
	((REG_CPM_CPCCR & CPCCR_H2DIV_MASK) >> CPCCR_H2DIV_BIT)
#define __cpm_get_otgdiv() \
	((REG_CPM_USBCDR & USBCDR_OTGDIV_MASK) >> USBCDR_OTGDIV_BIT)
#define __cpm_get_pdiv() \
	((REG_CPM_CPCCR & CPCCR_PDIV_MASK) >> CPCCR_PDIV_BIT)
#define __cpm_get_mdiv() \
	((REG_CPM_CPCCR & CPCCR_MDIV_MASK) >> CPCCR_MDIV_BIT)
#define __cpm_get_sdiv() \
	((REG_CPM_CPCCR & CPCCR_SDIV_MASK) >> CPCCR_SDIV_BIT)
#define __cpm_get_i2sdiv() \
	((REG_CPM_I2SCDR & I2SCDR_I2SDIV_MASK) >> I2SCDR_I2SDIV_BIT)
#define __cpm_get_pixdiv() \
	((REG_CPM_LPCDR & LPCDR_PIXDIV_MASK) >> LPCDR_PIXDIV_BIT)
#define __cpm_get_mscdiv() \
	((REG_CPM_MSCCDR & MSCCDR_MSCDIV_MASK) >> MSCCDR_MSCDIV_BIT)

/*
#define __cpm_get_mscdiv(n) \
	((REG_CPM_MSCCDR(n) & MSCCDR_MSCDIV_MASK) >> MSCCDR_MSCDIV_BIT)
*/
#define __cpm_get_ssidiv() \
	((REG_CPM_SSICDR & SSICDR_SSIDIV_MASK) >> SSICDR_SSIDIV_BIT)
#define __cpm_get_pcmdiv() \
	((REG_CPM_PCMCDR & PCMCDR_PCMCD_MASK) >> PCMCDR_PCMCD_BIT)
#define __cpm_get_pll1div() \
	((REG_CPM_CPPCR1 & CPCCR1_P1SDIV_MASK) >> CPCCR1_P1SDIV_BIT)


#define __cpm_set_ssidiv(v) \
	(REG_CPM_SSICDR = (REG_CPM_SSICDR & ~SSICDR_SSIDIV_MASK) | ((v) << (SSICDR_SSIDIV_BIT)))

#define __cpm_exclk_direct()		(REG_CPM_CPCCR &= ~CPM_CPCCR_ECS)
#define __cpm_exclk_div2()          (REG_CPM_CPCCR |= CPM_CPCCR_ECS)
#define __cpm_pllout_direct()		(REG_CPM_CPCCR |= CPM_CPCCR_PCS)
#define __cpm_pllout_div2()			(REG_CPM_CPCCR &= ~CPM_CPCCR_PCS)

#define __ssi_select_exclk()		(REG_CPM_SSICDR &= ~SSICDR_SCS)
#define __ssi_select_pllclk()		(REG_CPM_SSICDR |= SSICDR_SCS)

#define cpm_get_scrpad()	INREG32(CPM_CPSPR)
#define cpm_set_scrpad(data)				\
do {							\
	OUTREG32(CPM_CPSPPR, CPSPPR_CPSPR_WRITABLE);	\
	OUTREG32(CPM_CPSPR, data);			\
	OUTREG32(CPM_CPSPPR, ~CPSPPR_CPSPR_WRITABLE);	\
} while (0)

/**************remove me if android's kernel support these operations********end*********  */

extern int jz_pm_init(void);

#endif /* __MIPS_ASSEMBLER */

#endif /* __JZ4760BCPM_H__ */
