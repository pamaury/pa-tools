/*
 * jz4760bsadc.h
 * JZ4760B SADC register definition.
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 *
 * Author:jfli@ingenic.cn
 */

// 
// #ifndef __JZ4760BSADC_H__
// #define __JZ4760BSADC_H__

// 

// 
/* SAR A/D Controller */
this class SADC goto 0xb0070000 export "SAR A/D Controller"

// 

// 
/*
 * SADC registers offset definition
 */
const SADC_ADENA_OFFSET 0x00
const SADC_ADCFG_OFFSET 0x04
const SADC_ADCTRL_OFFSET 0x08
const SADC_ADSTATE_OFFSET 0x0c
const SADC_ADSAME_OFFSET 0x10
const SADC_ADWAIT_OFFSET 0x14
const SADC_ADTCH_OFFSET 0x18
const SADC_ADVDAT_OFFSET 0x1c
const SADC_ADADAT_OFFSET 0x20
const SADC_ADFLT_OFFSET 0x24
const SADC_ADCLK_OFFSET 0x28

// 

// 
/*
 * SADC registers address definition
 */
register ADENA goto SADC_ADENA_OFFSET export "ADC Enable Register"
register ADCFG goto SADC_ADCFG_OFFSET export "ADC Configure Register"
register ADCTRL goto SADC_ADCTRL_OFFSET export "ADC Control Register"
register ADSTATE goto SADC_ADSTATE_OFFSET export "ADC Status Register"
register ADSAME goto SADC_ADSAME_OFFSET export "ADC Same Point Time Register"
register ADWAIT goto SADC_ADWAIT_OFFSET export "ADC Wait Time Register"
register ADTCH goto SADC_ADTCH_OFFSET export "ADC Touch Screen Data Register"
register ADVDAT goto SADC_ADVDAT_OFFSET export "ADC VBAT Data Register"
register ADADAT goto SADC_ADADAT_OFFSET export "ADC AUX Data Register"
register ADFLT goto SADC_ADFLT_OFFSET export "ADC Filter Register"
register ADCLK goto SADC_ADCLK_OFFSET export "ADC Clock Divide Register"

// 

// 
/*
 * SADC registers common define
 */

// 
register ADENA export "ADC Enable Register"
register ADENA int POWER goto 7
register ADENA int SLP_MD goto 6
register ADENA int TCHEN goto 2
register ADENA int VBATEN goto 1
register ADENA int AUXEN goto 0

// 
register ADCFG export "ADC Configure Register"
register ADCFG int SPZZ goto 31
register ADCFG int DMA_EN goto 15

// 
const SADC_ADCFG_XYZ_BIT 13
register ADCFG int XYZ goto (14, SADC_ADCFG_XYZ_BIT)
register ADCFG int XYZ enum XYS 0x0
register ADCFG int XYZ enum XYD 0x1
register ADCFG int XYZ enum XYZ1Z2 0x2

// 
const SADC_ADCFG_SNUM_BIT 10
register ADCFG int SNUM goto (12, SADC_ADCFG_SNUM_BIT)
//  #define SADC_ADCFG_SNUM(n)          (((n) <= 6 ? ((n)-1) : ((n)-2)) << SADC_ADCFG_SNUM_BIT)

// 
const SADC_ADCFG_CMD_BIT 0
register ADCFG int CMD goto (1, SADC_ADCFG_CMD_BIT)
//  #define SADC_ADCFG_CMD_AUX(n)	((n) << SADC_ADCFG_CMD_BIT)

// 
register ADCTRL export "ADC Control Register"
register ADCTRL int SLPENDM goto 5
register ADCTRL int PENDM goto 4
register ADCTRL int PENUM goto 3
register ADCTRL int DTCHM goto 2
register ADCTRL int VRDYM goto 1
register ADCTRL int ARDYM goto 0
// #define SADC_ADCTRL_MASK_ALL         (ADCTRL_SLPENDM | SADC_ADCTRL_PENDM | SADC_ADCTRL_PENUM \
//                                 | SADC_ADCTRL_DTCHM | SADC_ADCTRL_VRDYM | SADC_ADCTRL_ARDYM)

// 
register ADSTATE export "ADC Status Register"
register ADSTATE int SLP_RDY goto 7
register ADSTATE int SLPEND goto 5
register ADSTATE int PEND goto 4
register ADSTATE int PENU goto 3
register ADSTATE int DTCH goto 2
register ADSTATE int VRDY goto 1
register ADSTATE int ARDY goto 0

// 
register ADSAME export "ADC Same Point Time Register"
const SADC_ADSAME_SCNT_BIT 0
register ADSAME int SCNT goto (15, SADC_ADSAME_SCNT_BIT)

// 
register ADWAIT export "ADC Wait Pen Down Time Register"
const SADC_ADWAIT_WCNT_BIT 0
register ADWAIT int WCNT goto (15, SADC_ADWAIT_WCNT_BIT)

// 
register ADTCH export "ADC Touch Screen Data Register"
register ADTCH int TYPE1 goto 31
register ADTCH int TYPE0 goto 15

// 
const SADC_ADTCH_DATA1_BIT 16
register ADTCH int DATA1 goto (27, SADC_ADTCH_DATA1_BIT)

// 
const SADC_ADTCH_DATA0_BIT 0
register ADTCH int DATA0 goto (11, SADC_ADTCH_DATA0_BIT)

// 
register ADVDAT export "ADC VBAT Date Register"
const SADC_ADVDAT_VDATA_BIT 0
register ADVDAT int VDATA goto (11, SADC_ADVDAT_VDATA_BIT)

// 
register ADADAT export "ADC AUX Data Register"
const SADC_ADADAT_ADATA_BIT 0
register ADADAT int ADATA goto (11, SADC_ADADAT_ADATA_BIT)

// 
register ADCLK export "ADC Clock Divide Register"
const SADC_ADCLK_CLKDIV_MS_BIT 16
register ADCLK int CLKDIV_MS goto (31, SADC_ADCLK_CLKDIV_MS_BIT)

// 
const SADC_ADCLK_CLKDIV_US_BIT 8
register ADCLK int CLKDIV_US goto (15, SADC_ADCLK_CLKDIV_US_BIT)

// 
const SADC_ADCLK_CLKDIV_BIT 0
register ADCLK int CLKDIV goto (7, SADC_ADCLK_CLKDIV_BIT)

// 
register ADFLT export "ADC Filter Register"
register ADFLT int FLT_EN goto 15

// 
const SADC_ADFLT_FLT_D_BIT 0
register ADFLT int FLT_D goto (11, SADC_ADFLT_FLT_D_BIT)

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 
register ADENA sizeof 8
register ADCFG sizeof 32
register ADCTRL sizeof 8
register ADSTATE sizeof 8
register ADSAME sizeof 16
register ADWAIT sizeof 16
register ADTCH sizeof 32
register ADVDAT sizeof 16
register ADADAT sizeof 16
register ADFLT sizeof 16
register ADCLK sizeof 32

// 

// 
// typedef volatile struct
// {
//         unsigned char   ADENA;
//         unsigned char   ADENARSV[3];
//         unsigned int    ADCFG;
//         unsigned char   ADCTRL;
//         unsigned char   ADCTRLRSV[3];
//         unsigned char   ADSTATE;
//         unsigned char   ADSTATERSV[3];
//         unsigned short  ADSAME;
//         unsigned short  ADSAMERSV[1];
//         unsigned short  ADWAIT;
//         unsigned short  ADWAITRSV[1];
//         unsigned int    ADTCH;
//         unsigned short  ADVDAT;
//         unsigned short  ADVDATRSV[1];
//         unsigned short  ADADAT;
//         unsigned short  ADADATRSV[1];
//         unsigned short  ADFLT;
//         unsigned short  ADFLTRSV[1];
//         unsigned int    ADCLK;
// } JZ4760B_SADC, *PJZ4760B_SADC;

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BSADC_H__ */
