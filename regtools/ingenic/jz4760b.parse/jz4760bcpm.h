/*
 * jz4760bcpm.h
 * JZ4760B CPM register definition
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 *
 * Author: whxu@ingenic.cn
 */

// 
// #ifndef __JZ4760BCPM_H__
// #define __JZ4760BCPM_H__

// 
// #ifndef JZ_EXTAL
const JZ_EXTAL 12000000
// #endif
// #ifndef JZ_EXTAL2
const JZ_EXTAL2 32768
// #endif

// 
/*
 * Clock reset and power controller module(CPM) address definition
 */
this class CPM goto 0xb0000000

// 

// 
/*
 * CPM registers offset address definition
 */
const CPM_CPCCR_OFFSET 0x00
const CPM_LCR_OFFSET 0x04
const CPM_RSR_OFFSET 0x08
const CPM_CPPCR0_OFFSET 0x10
const CPM_CPPSR_OFFSET 0x14
const CPM_CLKGR0_OFFSET 0x20
const CPM_OPCR_OFFSET 0x24
const CPM_CLKGR1_OFFSET 0x28
const CPM_CPPCR1_OFFSET 0x30
const CPM_CPSPR_OFFSET 0x34
const CPM_CPSPPR_OFFSET 0x38
const CPM_USBPCR_OFFSET 0x3c
const CPM_USBRDT_OFFSET 0x40
const CPM_USBVBFIL_OFFSET 0x44
const CPM_USBCDR_OFFSET 0x50
const CPM_I2SCDR_OFFSET 0x60
const CPM_LPCDR_OFFSET 0x64
const CPM_MSCCDR_OFFSET 0x68
const CPM_UHCCDR_OFFSET 0x6c
const CPM_SSICDR_OFFSET 0x74
const CPM_CIMCDR_OFFSET 0x7c
const CPM_GPSCDR_OFFSET 0x80
const CPM_PCMCDR_OFFSET 0x84
const CPM_GPUCDR_OFFSET 0x88
const CPM_PSWC0ST_OFFSET 0x90
const CPM_PSWC1ST_OFFSET 0x94
const CPM_PSWC2ST_OFFSET 0x98
const CPM_PSWC3ST_OFFSET 0x9c

// 

// 
/*
 * CPM registers address definition
 */
register CPCCR goto CPM_CPCCR_OFFSET export ""
register LCR goto CPM_LCR_OFFSET export ""
register RSR goto CPM_RSR_OFFSET export ""
register CPPCR0 goto CPM_CPPCR0_OFFSET export ""
register CPPSR goto CPM_CPPSR_OFFSET export ""
register CLKGR0 goto CPM_CLKGR0_OFFSET export ""
register OPCR goto CPM_OPCR_OFFSET export ""
register CLKGR1 goto CPM_CLKGR1_OFFSET export ""
register CPPCR1 goto CPM_CPPCR1_OFFSET export ""
register CPSPR goto CPM_CPSPR_OFFSET export ""
register CPSPPR goto CPM_CPSPPR_OFFSET export ""
register USBPCR goto CPM_USBPCR_OFFSET export ""
register USBRDT goto CPM_USBRDT_OFFSET export ""
register USBVBFIL goto CPM_USBVBFIL_OFFSET export ""
register USBCDR goto CPM_USBCDR_OFFSET export ""
register I2SCDR goto CPM_I2SCDR_OFFSET export ""
register LPCDR goto CPM_LPCDR_OFFSET export ""
register MSCCDR goto CPM_MSCCDR_OFFSET export ""
register UHCCDR goto CPM_UHCCDR_OFFSET export ""
register SSICDR goto CPM_SSICDR_OFFSET export ""
register CIMCDR goto CPM_CIMCDR_OFFSET export ""
register GPSCDR goto CPM_GPSCDR_OFFSET export ""
register PCMCDR goto CPM_PCMCDR_OFFSET export ""
register GPUCDR goto CPM_GPUCDR_OFFSET export ""
register PSWC0ST goto CPM_PSWC0ST_OFFSET export ""
register PSWC1ST goto CPM_PSWC1ST_OFFSET export ""
register PSWC2ST goto CPM_PSWC2ST_OFFSET export ""
register PSWC3ST goto CPM_PSWC3ST_OFFSET export ""

// 

// 
/*
 * CPM registers common define
 */

// 
register CPCCR export "Clock control register"
register CPCCR int ECS goto 31
register CPCCR int MEM goto 30
register CPCCR int CE goto 22
register CPCCR int PCS goto 21

// 
const CPM_CPCCR_SDIV_LSB 24
register CPCCR int SDIV goto (27, CPM_CPCCR_SDIV_LSB)

// 
const CPM_CPCCR_H2DIV_LSB 16
register CPCCR int H2DIV goto (19, CPM_CPCCR_H2DIV_LSB)

// 
const CPM_CPCCR_MDIV_LSB 12
register CPCCR int MDIV goto (15, CPM_CPCCR_MDIV_LSB)

// 
const CPM_CPCCR_PDIV_LSB 8
register CPCCR int PDIV goto (11, CPM_CPCCR_PDIV_LSB)

// 
const CPM_CPCCR_HDIV_LSB 4
register CPCCR int HDIV goto (7, CPM_CPCCR_HDIV_LSB)

// 
const CPM_CPCCR_CDIV_LSB 0
register CPCCR int CDIV goto (3, CPM_CPCCR_CDIV_LSB)

// 
register LCR export "Low power control register"
register LCR int PDAHB1 goto 30
register LCR int VBATIR goto 29
register LCR int PDGPS goto 28
register LCR int PDAHB1S goto 26
register LCR int PDGPSS goto 24
register LCR int DOZE goto 2

// 
const CPM_LCR_PST_LSB 8
register LCR int PST goto (19, CPM_LCR_PST_LSB)

// 
const CPM_LCR_DUTY_LSB 3
register LCR int DUTY goto (7, CPM_LCR_DUTY_LSB)

// 
const CPM_LCR_LPM_LSB 0
register LCR int LPM goto (1, CPM_LCR_LPM_LSB)
// #define CPM_LCR_LPM_IDLE            (0x0 << CPM_LCR_LPM_LSB)
// #define CPM_LCR_LPM_SLEEP           (0x1 << CPM_LCR_LPM_LSB)

// 
register RSR export "Reset status register"
register RSR int P0R goto 2
register RSR int WR goto 1
register RSR int PR goto 0

// 
register CPPCR0 export "PLL control register 0"
register CPPCR0 int LOCK goto 15 export "LOCK0 bit"
register CPPCR0 int ENLOCK goto 14
register CPPCR0 int PLLS goto 10
register CPPCR0 int PLLBP goto 9
register CPPCR0 int PLLEN goto 8

// 
const CPM_CPPCR0_PLLM_LSB 24
register CPPCR0 int PLLM goto (30, CPM_CPPCR0_PLLM_LSB)

// 
const CPM_CPPCR0_PLLN_LSB 18
register CPPCR0 int PLLN goto (21, CPM_CPPCR0_PLLN_LSB)

// 
const CPM_CPPCR0_PLLOD_LSB 16
register CPPCR0 int PLLOD goto (17, CPM_CPPCR0_PLLOD_LSB)

// 
const CPM_CPPCR0_PLLST_LSB 0
register CPPCR0 int PLLST goto (7, CPM_CPPCR0_PLLST_LSB)

// 
register CPPSR export "PLL switch and status register"
register CPPSR int PLLOFF goto 31
register CPPSR int PLLBP goto 30
register CPPSR int PLLON goto 29
register CPPSR int PS goto 28
register CPPSR int FS goto 27
register CPPSR int CS goto 26
register CPPSR int SM goto 2
register CPPSR int PM goto 1
register CPPSR int FM goto 0

// 
register CLKGR0 export "Clock gate register 0"
register CLKGR0 int EMC goto 31
register CLKGR0 int DDR goto 30
register CLKGR0 int IPU goto 29
register CLKGR0 int LCD goto 28
register CLKGR0 int TVE goto 27
register CLKGR0 int CIM goto 26
register CLKGR0 int MDMA goto 25
register CLKGR0 int UHC goto 24
register CLKGR0 int MAC goto 23
register CLKGR0 int GPS goto 22
register CLKGR0 int DMAC goto 21
register CLKGR0 int SSI2 goto 20
register CLKGR0 int SSI1 goto 19
register CLKGR0 int UART3 goto 18
register CLKGR0 int UART2 goto 17
register CLKGR0 int UART1 goto 16
register CLKGR0 int UART0 goto 15
register CLKGR0 int SADC goto 14
register CLKGR0 int KBC goto 13
register CLKGR0 int MSC2 goto 12
register CLKGR0 int MSC1 goto 11
register CLKGR0 int OWI goto 10
register CLKGR0 int TSSI goto 9
register CLKGR0 int AIC goto 8
register CLKGR0 int SCC goto 7
register CLKGR0 int I2C1 goto 6
register CLKGR0 int I2C0 goto 5
register CLKGR0 int SSI0 goto 4
register CLKGR0 int MSC0 goto 3
register CLKGR0 int OTG goto 2
register CLKGR0 int BCH goto 1
register CLKGR0 int NEMC goto 0

// 
register OPCR export "Oscillator and power control register"
register OPCR int OTGPHY_ENABLE goto 7 export "SPENDN bit"
register OPCR int GPSEN goto 6
register OPCR int UHCPHY_DISABLE goto 5 export "SPENDH bit"
register OPCR int O1SE goto 4
register OPCR int PD goto 3
register OPCR int ERCS goto 2

// 
const CPM_OPCR_O1ST_LSB 8
register OPCR int O1ST goto (15, CPM_OPCR_O1ST_LSB)

// 
register CLKGR1 export "Clock gate register 1"
register CLKGR1 int AUX goto 11
register CLKGR1 int OSD goto 10
register CLKGR1 int GPU goto 9
register CLKGR1 int PCM goto 8
register CLKGR1 int AHB1 goto 7
register CLKGR1 int CABAC goto 6
register CLKGR1 int SRAM goto 5
register CLKGR1 int DCT goto 4
register CLKGR1 int ME goto 3
register CLKGR1 int DBLK goto 2
register CLKGR1 int MC goto 1
register CLKGR1 int BDMA goto 0

// 
register CPPCR1 export "PLL control register 1"
register CPPCR1 int P1SCS goto 15
register CPPCR1 int PLL1EN goto 7
register CPPCR1 int PLL1S goto 6
register CPPCR1 int LOCK goto 2 export "LOCK1 bit"
register CPPCR1 int PLL1OFF goto 1
register CPPCR1 int PLL1ON goto 0

// 
const CPM_CPPCR1_PLL1M_LSB 24
register CPPCR1 int PLL1M goto (30, CPM_CPPCR1_PLL1M_LSB)

// 
const CPM_CPPCR1_PLL1N_LSB 18
register CPPCR1 int PLL1N goto (21, CPM_CPPCR1_PLL1N_LSB)

// 
const CPM_CPPCR1_PLL1OD_LSB 16
register CPPCR1 int PLL1OD goto (17, CPM_CPPCR1_PLL1OD_LSB)

// 
const CPM_CPPCR1_P1SDIV_LSB 9
register CPPCR1 int P1SDIV goto (14, CPM_CPPCR1_P1SDIV_LSB)

// 
register CPSPPR export "CPM scratch pad protected register"
const CPM_CPSPPR_CPSPR_WRITABLE 0x00005a5a

// 
register USBPCR export "OTG parameter control register"
register USBPCR int USB_MODE goto 31
register USBPCR int AVLD_REG goto 30
register USBPCR int INCRM goto 27 export "INCR_MASK bit"
register USBPCR int CLK12_EN goto 26
register USBPCR int COMMONONN goto 25
register USBPCR int VBUSVLDEXT goto 24
register USBPCR int VBUSVLDEXTSEL goto 23
register USBPCR int POR goto 22
register USBPCR int SIDDQ goto 21
register USBPCR int OTG_DISABLE goto 20
register USBPCR int TXPREEMPHTUNE goto 6

// 
const CPM_USBPCR_IDPULLUP_LSB 28
register USBPCR int IDPULLUP goto (29, CPM_USBPCR_IDPULLUP_LSB)

// 
const CPM_USBPCR_COMPDISTUNE_LSB 17
register USBPCR int COMPDISTUNE goto (19, CPM_USBPCR_COMPDISTUNE_LSB)

// 
const CPM_USBPCR_OTGTUNE_LSB 14
register USBPCR int OTGTUNE goto (16, CPM_USBPCR_OTGTUNE_LSB)

// 
const CPM_USBPCR_SQRXTUNE_LSB 11
register USBPCR int SQRXTUNE goto (13, CPM_USBPCR_SQRXTUNE_LSB)

// 
const CPM_USBPCR_TXFSLSTUNE_LSB 7
register USBPCR int TXFSLSTUNE goto (10, CPM_USBPCR_TXFSLSTUNE_LSB)

// 
const CPM_USBPCR_TXRISETUNE_LSB 4
register USBPCR int TXRISETUNE goto (5, CPM_USBPCR_TXRISETUNE_LSB)

// 
const CPM_USBPCR_TXVREFTUNE_LSB 0
register USBPCR int TXVREFTUNE goto (3, CPM_USBPCR_TXVREFTUNE_LSB)

// 
register USBRDT export "OTG reset detect timer register"
register USBRDT int VBFIL_LD_EN goto 25
register USBRDT int IDDIG_EN goto 24
register USBRDT int IDDIG_REG goto 23

// 
const CPM_USBRDT_USBRDT_LSB 0
register USBRDT int USBRDT goto (22, CPM_USBRDT_USBRDT_LSB)

// 
register USBCDR export "OTG PHY clock divider register"
register USBCDR int UCS goto 31
register USBCDR int UPCS goto 30

// 
const CPM_USBCDR_OTGDIV_LSB 0
register USBCDR int OTGDIV goto (5, CPM_USBCDR_OTGDIV_LSB)

// 
register I2SCDR export "I2S device clock divider register"
register I2SCDR int I2CS goto 31
register I2SCDR int I2PCS goto 30

// 
const CPM_I2SCDR_I2SDIV_LSB 0
register I2SCDR int I2SDIV goto (8, CPM_I2SCDR_I2SDIV_LSB)

// 
register LPCDR export "LCD pix clock divider register"
register LPCDR int LTCS goto 30
register LPCDR int LPCS goto 29

// 
const CPM_LPCDR_PIXDIV_LSB 0
register LPCDR int PIXDIV goto (10, CPM_LPCDR_PIXDIV_LSB)

// 
register MSCCDR export "MSC clock divider register"
register MSCCDR int MCS goto 31

// 
const CPM_MSCCDR_MSCDIV_LSB 0
register MSCCDR int MSCDIV goto (5, CPM_MSCCDR_MSCDIV_LSB)

// 
register UHCCDR export "UHC device clock divider register"
register UHCCDR int UHPCS goto 31

// 
const CPM_UHCCDR_UHCDIV_LSB 0
register UHCCDR int UHCDIV goto (3, CPM_UHCCDR_UHCDIV_LSB)

// 
register SSICDR export "SSI clock divider register"
register SSICDR int SCS goto 31

// 
const CPM_SSICDR_SSIDIV_LSB 0
register SSICDR int SSIDIV goto (5, CPM_SSICDR_SSIDIV_LSB)

// 
register CIMCDR export "CIM mclk clock divider register"
const CPM_CIMCDR_CIMDIV_LSB 0
register CIMCDR int CIMDIV goto (7, CPM_CIMCDR_CIMDIV_LSB)

// 
register GPSCDR export "GPS clock divider register"
register GPSCDR int GPCS goto 31

// 
const CPM_GPSCDR_GPSDIV_LSB 0
// #define GSPCDR_GPSDIV_MASK      BITS_H2L(3, CPM_GPSCDR_GPSDIV_LSB)

// 
register PCMCDR export "PCM device clock divider register"
register PCMCDR int PCMS goto 31
register PCMCDR int PCMPCS goto 30

// 
const CPM_PCMCDR_PCMDIV_LSB 0
register PCMCDR int PCMDIV goto (8, CPM_PCMCDR_PCMDIV_LSB)

// 
/* GPU clock divider register */
register GPUCDR int GPCS goto 31
const CPM_GPUCDR_GPUDIV_LSB 0
register GPUCDR int GPUDIV goto (2, CPM_GPUCDR_GPUDIV_LSB)

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 
register CPCCR sizeof 32
register RSR sizeof 32
register CPPCR0 sizeof 32
register CPPSR sizeof 32
register CPPCR1 sizeof 32
register CPSPR sizeof 32
register CPSPPR sizeof 32
register USBPCR sizeof 32
register USBRDT sizeof 32
register USBVBFIL sizeof 32
register USBCDR sizeof 32
register I2SCDR sizeof 32
register LPCDR sizeof 32
register MSCCDR sizeof 32
register UHCCDR sizeof 32
register SSICDR sizeof 32
register CIMCDR sizeof 32
register GPSCDR sizeof 32
register PCMCDR sizeof 32
register GPUCDR sizeof 32

// 
register PSWC0ST sizeof 32
register PSWC1ST sizeof 32
register PSWC2ST sizeof 32
register PSWC3ST sizeof 32

// 
register LCR sizeof 32
register CLKGR0 sizeof 32
register OPCR sizeof 32
register CLKGR1 sizeof 32
register CLKGR0 sizeof 32

// 
// typedef enum {
//         CGM_NEMC = 0,
//         CGM_BCH  = 1,
//         CGM_OTG  = 2,
//         CGM_MSC0 = 3,
//         CGM_SSI0 = 4,
//         CGM_I2C0 = 5,
//         CGM_I2C1 = 6,
//         CGM_SCC  = 7,
//         CGM_AIC         = 8,
//         CGM_TSSI        = 9,
//         CGM_OWI         = 10,
//         CGM_MSC1        = 11,
//         CGM_MSC2        = 12,
//         CGM_KBC         = 13,
//         CGM_SADC        = 14,
//         CGM_UART0       = 15,
//         CGM_UART1 = 16,
//         CGM_UART2 = 17,
//         CGM_UART3 = 18,
//         CGM_SSI1  = 19,
//         CGM_SSI2  = 20,
//         CGM_DMAC  = 21,
//         CGM_GPS   = 22,
//         CGM_MAC   = 23,
//         CGM_UHC         = 24,
//         CGM_MDMA        = 25,
//         CGM_CIM         = 26,
//         CGM_TVE         = 27,
//         CGM_LCD         = 28,
//         CGM_IPU         = 29,
//         CGM_DDR         = 30,
//         CGM_EMC         = 31,
//         CGM_BDMA  = 32 + 0,
//         CGM_MC    = 32 + 1,
//         CGM_DBLK  = 32 + 2,
//         CGM_ME    = 32 + 3,
//         CGM_DCT   = 32 + 4,
//         CGM_SRAM  = 32 + 5,
//         CGM_CABAC = 32 + 6,
//         CGM_AHB1  = 32 + 7,
//         CGM_PCM         = 32 + 8,
//         CGM_GPU         = 32 + 9,
//         CGM_OSD         = 32 + 10,
//         CGM_AUX         = 32 + 11,
//         CGM_ALL_MODULE,
// } clock_gate_module;

// 

// 
const __CGU_CLOCK_BASE__ 0x1000

// 
// typedef enum {
//         /* Clock source is pll0 */
//         CGU_CCLK = __CGU_CLOCK_BASE__ + 0,
//         CGU_HCLK,
//         CGU_PCLK,
//         CGU_MCLK,
//         CGU_H2CLK,
//         CGU_SCLK,

// 
//         /* Clock source is exclk, pll0 or pll0/2 */
//         CGU_MSCCLK,
//         CGU_SSICLK,

// 
//         /* Clock source is pll0 or pll0/2 */
//         CGU_CIMCLK,

// 
//         /* Clock source is exclk, pll0, pll0/2 or pll1 */
//         CGU_TVECLK,

// 
//         /* Clock source is pll0 */
//         CGU_LPCLK,

// 
//         /* Clock source is exclk, exclk/2, pll0, pll0/2 or pll1 */
//         CGU_I2SCLK,
//         CGU_PCMCLK,
//         CGU_OTGCLK,

// 
//         /* Clock source is pll0, pll0/2 or pll1 */
//         CGU_UHCCLK,
//         CGU_GPSCLK,
//         CGU_GPUCLK,

// 
//         /* Clock source is exclk or exclk/2 */
//         CGU_UARTCLK,
//         CGU_SADCCLK,

// 
//         /* Clock source is exclk */
//         CGU_TCUCLK,

// 
// 	/* Clock source is external rtc clock */
// 	CGU_RTCCLK,

// 
//         CGU_CLOCK_MAX,
// } cgu_clock;

// 
/*
 * JZ4760B clocks structure
 */
// typedef struct {
// 	unsigned int cclk;	/* CPU clock				*/
// 	unsigned int hclk;	/* System bus clock: AHB0,AHB1		*/
// 	unsigned int h1clk;	/* For compatible, the same as h1clk	*/
// 	unsigned int h2clk;	/* System bus clock: AHB2		*/
// 	unsigned int pclk;	/* Peripheral bus clock			*/
// 	unsigned int mclk;	/* EMC or DDR controller clock		*/
// 	unsigned int sclk;	/* NEMC controller clock		*/
// 	unsigned int cko;	/* SDRAM or DDR clock			*/
// 	unsigned int pixclk;	/* LCD pixel clock			*/
// 	unsigned int tveclk;	/* TV encoder 27M  clock		*/
// 	unsigned int cimmclk;	/* Clock output from CIM module		*/
// 	unsigned int cimpclk;	/* Clock input to CIM module		*/
// 	unsigned int gpuclk;	/* GPU clock				*/
// 	unsigned int gpsclk;	/* GPS clock				*/
// 	unsigned int i2sclk;	/* I2S codec clock			*/
// 	unsigned int bitclk;	/* AC97 bit clock			*/
// 	unsigned int pcmclk;	/* PCM clock				*/
// 	unsigned int mscclk;	/* MSC clock				*/
// 	unsigned int ssiclk;	/* SSI clock				*/
// 	unsigned int tssiclk;	/* TSSI clock				*/
// 	unsigned int otgclk;	/* USB OTG clock			*/
// 	unsigned int uhcclk;	/* USB UHCI clock			*/
// 	unsigned int extalclk;	/* EXTAL clock for
// 				   UART,I2C,TCU,USB2.0-PHY,AUDIO CODEC	*/
// 	unsigned int rtcclk;	/* RTC clock for CPM,INTC,RTC,TCU,WDT	*/
// } jz_clocks_t;

// 
// void cpm_start_clock(clock_gate_module module_name);
// void cpm_stop_clock(clock_gate_module module_name);

// 
// unsigned int cpm_set_clock(cgu_clock clock_name, unsigned int clock_hz);
// unsigned int cpm_get_clock(cgu_clock clock_name);
// unsigned int cpm_get_pllout(void);

// 
// void cpm_uhc_phy(unsigned int en);

// 
/**************remove me if android's kernel support these operations********start*********  */
// #define __cpm_stop_lcd()	(REG_CPM_CLKGR0 |= CLKGR0_LCD)
// #define __cpm_start_lcd()	(REG_CPM_CLKGR0 &= ~CLKGR0_LCD)
// #define __cpm_set_pixdiv(v) \
// 	(REG_CPM_LPCDR = (REG_CPM_LPCDR & ~LPCDR_PIXDIV_MASK) | ((v) << (LPCDR_PIXDIV_LSB)))

// 
// #define __cpm_get_pixdiv() \
// 	((REG_CPM_LPCDR & LPCDR_PIXDIV_MASK) >> LPCDR_PIXDIV_LSB)

// 
// #define __cpm_select_pixclk_lcd()	(REG_CPM_LPCDR &= ~LPCDR_LTCS)
// #define __cpm_select_pixclk_tve()	(REG_CPM_LPCDR |= LPCDR_LTCS)

// 
// static __inline__ unsigned int __cpm_get_pllout2(void)
// {
// #if defined(CONFIG_FPGA)
// 	return cpm_get_pllout();
// #else
// 	if (REG_CPM_CPCCR & CPCCR_PCS)
// 		return cpm_get_pllout();
// 	else
// 		return cpm_get_pllout()/2;
// #endif
// }

// 
// static __inline__ unsigned int __cpm_get_pixclk(void)
// {
// 	return __cpm_get_pllout2() / (__cpm_get_pixdiv() + 1);
// }

// 
/* EXTAL clock */
// static __inline__ unsigned int __cpm_get_extalclk0(void)
// {
// 	return JZ_EXTAL;
// }

// 
/* EXTAL clock for UART,I2C,SSI,SADC,USB-PHY */
// static __inline__ unsigned int __cpm_get_extalclk(void)
// {
// #if defined(CONFIG_FPGA)
// 	return __cpm_get_extalclk0() / CFG_DIV;
// #else
// 	if (REG_CPM_CPCCR & CPCCR_ECS)
// 		return __cpm_get_extalclk0() / 2;
// 	else
// 		return __cpm_get_extalclk0();
// #endif

// 
// }

// 
/* RTC clock for CPM,INTC,RTC,TCU,WDT */
// static __inline__ unsigned int __cpm_get_rtcclk(void)
// {
// 	return JZ_EXTAL2;
// }

// 
// extern jz_clocks_t jz_clocks;

// 
// #define __cpm_select_i2sclk_exclk()	(REG_CPM_I2SCDR &= ~I2SCDR_I2CS)
// #define __cpm_enable_pll_change()	(REG_CPM_CPCCR |= CPCCR_CE)

// 
// #define __cpm_suspend_otg_phy()		(REG_CPM_OPCR &= ~OPCR_OTGPHY_ENABLE)
// #define __cpm_enable_otg_phy()		(REG_CPM_OPCR |=  OPCR_OTGPHY_ENABLE)

// 
// #define __cpm_suspend_uhc_phy()		(REG_CPM_OPCR |= OPCR_UHCPHY_DISABLE)
// #define __cpm_enable_uhc_phy()		(REG_CPM_OPCR &= ~OPCR_UHCPHY_DISABLE)
// #define __cpm_suspend_gps()        (REG_CPM_OPCR &= ~OPCR_GPSEN)
// #define __cpm_disable_osc_in_sleep()	(REG_CPM_OPCR &= ~OPCR_O1SE)
// #define __cpm_select_rtcclk_rtc()	(REG_CPM_OPCR |= OPCR_ERCS)

// 
// #define __cpm_get_pllm() \
// 	((REG_CPM_CPPCR0 & CPPCR0_PLLM_MASK) >> CPPCR0_PLLM_LSB)
// #define __cpm_get_plln() \
// 	((REG_CPM_CPPCR0 & CPPCR0_PLLN_MASK) >> CPPCR0_PLLN_LSB)
// #define __cpm_get_pllod() \
// 	((REG_CPM_CPPCR0 & CPPCR0_PLLOD_MASK) >> CPPCR0_PLLOD_LSB)

// 
// #define __cpm_get_pll1m() \
// 	((REG_CPM_CPPCR1 & CPPCR1_PLL1M_MASK) >> CPPCR1_PLL1M_LSB)
// #define __cpm_get_pll1n() \
// 	((REG_CPM_CPPCR1 & CPPCR1_PLL1N_MASK) >> CPPCR1_PLL1N_LSB)
// #define __cpm_get_pll1od() \
// 	((REG_CPM_CPPCR1 & CPPCR1_PLL1OD_MASK) >> CPPCR1_PLL1OD_LSB)

// 
// #define __cpm_get_cdiv() \
// 	((REG_CPM_CPCCR & CPCCR_CDIV_MASK) >> CPCCR_CDIV_LSB)
// #define __cpm_get_hdiv() \
// 	((REG_CPM_CPCCR & CPCCR_HDIV_MASK) >> CPCCR_HDIV_LSB)
// #define __cpm_get_h2div() \
// 	((REG_CPM_CPCCR & CPCCR_H2DIV_MASK) >> CPCCR_H2DIV_LSB)
// #define __cpm_get_otgdiv() \
// 	((REG_CPM_USBCDR & USBCDR_OTGDIV_MASK) >> USBCDR_OTGDIV_LSB)
// #define __cpm_get_pdiv() \
// 	((REG_CPM_CPCCR & CPCCR_PDIV_MASK) >> CPCCR_PDIV_LSB)
// #define __cpm_get_mdiv() \
// 	((REG_CPM_CPCCR & CPCCR_MDIV_MASK) >> CPCCR_MDIV_LSB)
// #define __cpm_get_sdiv() \
// 	((REG_CPM_CPCCR & CPCCR_SDIV_MASK) >> CPCCR_SDIV_LSB)
// #define __cpm_get_i2sdiv() \
// 	((REG_CPM_I2SCDR & I2SCDR_I2SDIV_MASK) >> I2SCDR_I2SDIV_LSB)
// #define __cpm_get_pixdiv() \
// 	((REG_CPM_LPCDR & LPCDR_PIXDIV_MASK) >> LPCDR_PIXDIV_LSB)
// #define __cpm_get_mscdiv() \
// 	((REG_CPM_MSCCDR & MSCCDR_MSCDIV_MASK) >> MSCCDR_MSCDIV_LSB)

// 
/*
#define __cpm_get_mscdiv(n) \
	((REG_CPM_MSCCDR(n) & MSCCDR_MSCDIV_MASK) >> MSCCDR_MSCDIV_LSB)
*/
// #define __cpm_get_ssidiv() \
// 	((REG_CPM_SSICDR & SSICDR_SSIDIV_MASK) >> SSICDR_SSIDIV_LSB)
// #define __cpm_get_pcmdiv() \
// 	((REG_CPM_PCMCDR & PCMCDR_PCMCD_MASK) >> PCMCDR_PCMCD_LSB)
// #define __cpm_get_pll1div() \
// 	((REG_CPM_CPPCR1 & CPCCR1_P1SDIV_MASK) >> CPCCR1_P1SDIV_LSB)

// 

// 
// #define __cpm_set_ssidiv(v) \
// 	(REG_CPM_SSICDR = (REG_CPM_SSICDR & ~SSICDR_SSIDIV_MASK) | ((v) << (SSICDR_SSIDIV_LSB)))

// 
// #define __cpm_exclk_direct()		(REG_CPM_CPCCR &= ~CPM_CPCCR_ECS)
// #define __cpm_exclk_div2()          (REG_CPM_CPCCR |= CPM_CPCCR_ECS)
// #define __cpm_pllout_direct()		(REG_CPM_CPCCR |= CPM_CPCCR_PCS)
// #define __cpm_pllout_div2()			(REG_CPM_CPCCR &= ~CPM_CPCCR_PCS)

// 
// #define __ssi_select_exclk()		(REG_CPM_SSICDR &= ~SSICDR_SCS)
// #define __ssi_select_pllclk()		(REG_CPM_SSICDR |= SSICDR_SCS)

// 
// #define cpm_get_scrpad()	INREG32(CPM_CPSPR)
// #define cpm_set_scrpad(data)				\
// do {							\
// 	OUTREG32(CPM_CPSPPR, CPSPPR_CPSPR_WRITABLE);	\
// 	OUTREG32(CPM_CPSPR, data);			\
// 	OUTREG32(CPM_CPSPPR, ~CPSPPR_CPSPR_WRITABLE);	\
// } while (0)

// 
/**************remove me if android's kernel support these operations********end*********  */

// 
// extern int jz_pm_init(void);

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BCPM_H__ */
