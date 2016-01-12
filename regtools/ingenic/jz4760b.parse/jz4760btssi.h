/*
 * linux/include/asm-mips/mach-jz4810/jz4810tssi.h
 *
 * JZ4810 TSSI register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

// 
// #ifndef __JZ4760TSSI_H__
// #define __JZ4760TSSI_H__

// 

// 
/* TSSI MPEG 2-TS slave interface */
this class TSSI goto 0xB0073000 export "TSSI MPEG 2-TS slave interface"

// 
register ENA goto 0x00 export "TSSI enable register"
register CFG goto 0x04 export "TSSI configure register"
register CTRL goto 0x08 export "TSSI control register"
register STAT goto 0x0c export "TSSI state register"
register FIFO goto 0x10 export "TSSI FIFO register"
register PEN goto 0x14 export "TSSI PID enable register"
register NUM goto 0x18 export ""
register DTR goto 0x1c export ""
for n 0 15
register PID goto<n> "0x20 + 4*(n)" export "TSSI PID filter register"
// #define TSSI_PID0      (TSSI_BASE + 0x20)
// #define TSSI_PID1      (TSSI_BASE + 0x24)
// #define TSSI_PID2      (TSSI_BASE + 0x28)
// #define TSSI_PID3      (TSSI_BASE + 0x2c)
// #define TSSI_PID4      (TSSI_BASE + 0x30)
// #define TSSI_PID5      (TSSI_BASE + 0x34)
// #define TSSI_PID6      (TSSI_BASE + 0x38)
// #define TSSI_PID7      (TSSI_BASE + 0x3c)
// #define TSSI_PID8      (TSSI_BASE + 0x40)
// #define TSSI_PID9      (TSSI_BASE + 0x44)
// #define TSSI_PID10     (TSSI_BASE + 0x48)
// #define TSSI_PID11     (TSSI_BASE + 0x4c)
// #define TSSI_PID12     (TSSI_BASE + 0x50)
// #define TSSI_PID13     (TSSI_BASE + 0x54)
// #define TSSI_PID14     (TSSI_BASE + 0x58)
// #define TSSI_PID15     (TSSI_BASE + 0x5c)
const TSSI_PID_MAX 16

// 
register DDA goto 0x60 export ""
register DTA goto 0x64 export ""
register DID goto 0x68 export ""
register DCMD goto 0x6c export ""
register DST goto 0x70 export ""
register TC goto 0x74 export ""

//  
register ENA sizeof 8
register CFG sizeof 16
register CTRL sizeof 8
register STAT sizeof 8
register FIFO sizeof 32
register PEN sizeof 32
register NUM sizeof 32
register DTR sizeof 32
register PID sizeof 32
// #define REG_TSSI_PID0      REG32(TSSI_PID0)
// #define REG_TSSI_PID1      REG32(TSSI_PID1)
// #define REG_TSSI_PID2      REG32(TSSI_PID2)
// #define REG_TSSI_PID3      REG32(TSSI_PID3)
// #define REG_TSSI_PID4      REG32(TSSI_PID4)
// #define REG_TSSI_PID5      REG32(TSSI_PID5)
// #define REG_TSSI_PID6      REG32(TSSI_PID6)
// #define REG_TSSI_PID7      REG32(TSSI_PID7)
// #define REG_TSSI_PID8      REG32(TSSI_PID8)
// #define REG_TSSI_PID9      REG32(TSSI_PID9)
// #define REG_TSSI_PID10     REG32(TSSI_PID10)
// #define REG_TSSI_PID11     REG32(TSSI_PID11)
// #define REG_TSSI_PID12     REG32(TSSI_PID12)
// #define REG_TSSI_PID13     REG32(TSSI_PID13)
// #define REG_TSSI_PID14     REG32(TSSI_PID14)
// #define REG_TSSI_PID15     REG32(TSSI_PID15)

// 
/* TSSI enable register */
register ENA int SFT_RST goto 7 export "soft reset bit"
register ENA int PID_EN goto 2 export "soft filtering function enable bit"
register ENA int FAIL goto 4 export "fail signal bit"
register ENA int PEN_0 goto 3 export "PID filter enable bit for PID"
register ENA int DMA_EN goto 1 export "DMA enable bit"
register ENA int ENA goto 0 export "TSSI enable bit"

// 
/* TSSI configure register */
const TSSI_CFG_TRIG_BIT 14
register CFG int TRIG export "fifo trig number"
register CFG int TRIG goto (0x3 << TSSI_CFG_TRIG_BIT)
register CFG int TRIG enum "4" 0
register CFG int TRIG enum "8" 1
register CFG int TRIG enum "16" 2
register CFG int TRIG enum "32" 3
/* FIXME: this register is 16-bit wide ?! Even the datasheet of JZ4780 is wrong */
// #define TSSI_CFG_TRIG_48 	(4 << TSSI_CFG_TRIG_BIT)
// #define TSSI_CFG_TRIG_64 	(5 << TSSI_CFG_TRIG_BIT)
// #define TSSI_CFG_TRIG_80 	(6 << TSSI_CFG_TRIG_BIT)
// #define TSSI_CFG_TRIG_96 	(7 << TSSI_CFG_TRIG_BIT)

// 
/* mode of adding data 0 select bit */
const TSSI_CFG_TRANS_MD_BIT 10
register CFG int TRANS_MD goto (0x3 << TSSI_CFG_TRANS_MD_BIT)
register CFG int TRANS_MD enum "0" 0
register CFG int TRANS_MD enum "1" 1
register CFG int TRANS_MD enum "2" 2

// 
register CFG int END_WD goto 9 export "order of data in word"
register CFG int END_BT goto 8 export "order of data in byte"

// 
register CFG int TSDI_H goto 7 export "data pin polarity"
register CFG int USE_0 goto 6 export "serial mode data pin select: 0 for TSDI7, 1 for TSDI0"
// #define TSSI_CFG_USE_TSDI0 	(1 << 6)      /* TSDI0 as serial mode data pin */
// #define TSSI_CFG_USE_TSDI7 	(0 << 6)      /* TSDI7 as serial mode data pin */
register CFG int TSCLK_CH goto 5 export "clk channel select"
register CFG int PARAL goto 4 export "mode select"
// #define TSSI_CFG_PARAL_MODE 	(1 << 4)      /* parallel select */
// #define TSSI_CFG_SERIAL_MODE 	(0 << 4)      /* serial select */
register CFG int TSCLK_P goto 3 export "clk edge select"
register CFG int TSFRM_H goto 2 export "TSFRM polarity select"
register CFG int TSSTR_H goto 1 export "TSSTR polarity select"
register CFG int TSFAIL_H goto 0 export "TSFAIL polarity select"

// 
/* TSSI control register */
register CTRL int DTRM goto 2 export "FIFO data trigger interrupt mask bit"
register CTRL int OVRNM goto 1 export "FIFO overrun interrupt mask bit"
register CTRL int TRIGM goto 0 export "FIFO trigger interrupt mask bit"

// 
/* TSSI state register */
register STAT int DTR goto 2 export "FIFO data trigger interrupt flag bit"
register STAT int OVRN goto 1 export "FIFO overrun interrupt flag bit"
register STAT int TRIG goto 0 export "FIFO trigger interrupt flag bit"

// 
/* TSSI PID enable register */
register PEN int EN00 goto 0 export "enable PID n"
register PEN int EN10 goto 1
register PEN int EN20 goto 2
register PEN int EN30 goto 3
register PEN int EN40 goto 4
register PEN int EN50 goto 5
register PEN int EN60 goto 6
register PEN int EN70 goto 7
register PEN int EN80 goto 8
register PEN int EN90 goto 9
register PEN int EN100 goto 10
register PEN int EN110 goto 11
register PEN int EN120 goto 12
register PEN int EN130 goto 13
register PEN int EN140 goto 14
register PEN int EN150 goto 15
register PEN int EN01 goto 16
register PEN int EN11 goto 17
register PEN int EN21 goto 18
register PEN int EN31 goto 19
register PEN int EN41 goto 20
register PEN int EN51 goto 21
register PEN int EN61 goto 22
register PEN int EN71 goto 23
register PEN int EN81 goto 24
register PEN int EN91 goto 25
register PEN int EN101 goto 26
register PEN int EN111 goto 27
register PEN int EN121 goto 28
register PEN int EN131 goto 29
register PEN int EN141 goto 30
register PEN int EN151 goto 31
//#define TSSI_PEN_PID0 	(1 << 31) /* PID filter enable PID0 */

// 
/* TSSI Data Number Registers */
const TSSI_DNUM_BIT 0
// #define TSSI_DNUM_MASK	(0x7f << TSSI_DNUM_BIT)

// 
/* TSSI Data Trigger Register */
const TSSI_DTRG_BIT 0
// #define TSSI_DTRG_MASK	(0x7f << TSSI_DTRG_BIT)

// 

// 
/* TSSI PID Filter Registers */
const TSSI_PID_PID1_BIT 16
register PID int PID1 goto (0x1fff<<TSSI_PID_PID1_BIT)
const TSSI_PID_PID0_BIT 0
register PID int PID0 goto (0x1fff<<TSSI_PID_PID0_BIT)

// 
/* TSSI DMA Identifier Registers */
// #define TSSI_DMA_ID_BIT		0
// #define TSSI_DMA_ID_MASK	(0xffff << TSSI_DMA_ID_BIT)

// 
/* TSSI DMA Command Registers */
const TSSI_DCMD_TLEN_BIT 8
register DCMD int TLEN goto (0xff << TSSI_DCMD_TLEN_BIT)
register DCMD int TEFE goto 4
const TSSI_DCMD_TSZ_BIT 2
register DCMD int TSZ goto (0x3 << TSSI_DCMD_TSZ_BIT)
register DCMD int TSZ enum "4" 0
register DCMD int TSZ enum "8" 1
register DCMD int TSZ enum "16" 2
register DCMD int TSZ enum "32" 3
register DCMD int TEIE goto 1
register DCMD int LINK goto 0

// 
/* TSSI DMA Status Registers */
const TSSI_DST_DID_BIT 16
register DST int DID goto (0xffff << 16)
register DST int TEND goto 0

// 
/* TSSI Transfer Control Registers */
const TSSI_TC_OP_BIT 4
register TC int OP goto (0x3 << TSSI_TC_OP_BIT)
//////////////////#define TSSI_TC_OP_0		(
register TC int OPE goto 2
register TC int EME goto 1
register TC int APM goto 0
// #ifndef __MIPS_ASSEMBLER

// 
/*************************************************************************
 * TSSI MPEG 2-TS slave interface operation
 *************************************************************************/
// #define __tssi_enable()                       (REG_TSSI_ENA |= TSSI_ENA_ENA)
// #define __tssi_disable()                      (REG_TSSI_ENA &= ~TSSI_ENA_ENA)
// #define __tssi_soft_reset()                   (REG_TSSI_ENA |= TSSI_ENA_SFT_RST)
// #define __tssi_filter_enable_pid0()	      (REG_TSSI_ENA |= TSSI_ENA_PEN_0)
// #define __tssi_filter_disable_pid0()	      (REG_TSSI_ENA &= ~TSSI_ENA_PEN_0)
// #define __tssi_dma_enable()                   (REG_TSSI_ENA |= TSSI_ENA_DMA_EN)
// #define __tssi_dma_disable()                  (REG_TSSI_ENA &= ~TSSI_ENA_DMA_EN)
// #define __tssi_filter_enable()                (REG_TSSI_ENA |= TSSI_ENA_PID_EN)
// #define __tssi_filter_disable()               (REG_TSSI_ENA &= ~TSSI_ENA_PID_EN)

// 
/* n = 4, 8, 16 */
// #define __tssi_set_tigger_num(n)			\
// 	do {						\
// 		REG_TSSI_CFG &= ~TSSI_CFG_TRIG_MASK;	\
// 		REG_TSSI_CFG |= TSSI_CFG_TRIG_##n;	\
// 	} while (0)

// 
// #define __tssi_set_data0_mode(n)				\
// 	do {							\
// 		REG_TSSI_CFG &= ~ TSSI_CFG_TRANS_MD_MASK;	\
// 		REG_TSSI_CFG |= TSSI_CFG_TRANS_MD_##n;		\
// 	}  while(0)

// 

// 
// #define __tssi_set_wd_1()                     (REG_TSSI_CFG |= TSSI_CFG_END_WD)
// #define __tssi_set_wd_0()                     (REG_TSSI_CFG &= ~TSSI_CFG_END_WD)

// 
// #define __tssi_set_bt_1()                     (REG_TSSI_CFG |= TSSI_CFG_END_BD)
// #define __tssi_set_bt_0()                     (REG_TSSI_CFG &= ~TSSI_CFG_END_BD)

// 
// #define __tssi_set_data_pola_high()           (REG_TSSI_CFG |= TSSI_CFG_TSDI_H)
// #define __tssi_set_data_pola_low()            (REG_TSSI_CFG &= ~TSSI_CFG_TSDI_H)

// 
// #define __tssi_set_data_use_data0()           (REG_TSSI_CFG |= TSSI_CFG_USE_0)
// #define __tssi_set_data_use_data7()           (REG_TSSI_CFG &= ~TSSI_CFG_USE_0)

// 
// #define __tssi_select_clk_fast()              (REG_TSSI_CFG &= ~TSSI_CFG_TSCLK_CH)
// #define __tssi_select_clk_slow()              (REG_TSSI_CFG |= TSSI_CFG_TSCLK_CH)

// 
// #define __tssi_select_serail_mode()           (REG_TSSI_CFG &= ~TSSI_CFG_PARAL)
// #define __tssi_select_paral_mode()            (REG_TSSI_CFG |= TSSI_CFG_PARAL)

// 
// #define __tssi_select_clk_nega_edge()         (REG_TSSI_CFG &= ~TSSI_CFG_TSCLK_P)
// #define __tssi_select_clk_posi_edge()         (REG_TSSI_CFG |= TSSI_CFG_TSCLK_P)

// 
// #define __tssi_select_frm_act_high()          (REG_TSSI_CFG |= TSSI_CFG_TSFRM_H)
// #define __tssi_select_frm_act_low()           (REG_TSSI_CFG &= ~TSSI_CFG_TSFRM_H)

// 
// #define __tssi_select_str_act_high()          (REG_TSSI_CFG |= TSSI_CFG_TSSTR_H)
// #define __tssi_select_str_act_low()           (REG_TSSI_CFG &= ~TSSI_CFG_TSSTR_H)

// 
// #define __tssi_select_fail_act_high()         (REG_TSSI_CFG |= TSSI_CFG_TSFAIL_H)
// #define __tssi_select_fail_act_low()          (REG_TSSI_CFG &= ~TSSI_CFG_TSFAIL_H)

// 
// #define __tssi_enable_data_trigger_irq()      (REG_TSSI_CTRL &= ~TSSI_CTRL_DTRM)
// #define __tssi_disable_data_trigger_irq()     (REG_TSSI_CTRL |= TSSI_CTRL_DTRM)

// 
// #define __tssi_enable_ovrn_irq()              (REG_TSSI_CTRL &= ~TSSI_CTRL_OVRNM)
// #define __tssi_disable_ovrn_irq()             (REG_TSSI_CTRL |= TSSI_CTRL_OVRNM)

// 
// #define __tssi_enable_trig_irq()              (REG_TSSI_CTRL &= ~TSSI_CTRL_TRIGM)
// #define __tssi_disable_trig_irq()             (REG_TSSI_CTRL |= TSSI_CTRL_TRIGM) 

// 
// #define __tssi_state_is_dtr()		      (REG_TSSI_STAT & TSSI_STAT_DTR)
// #define __tssi_state_is_overrun()             (REG_TSSI_STAT & TSSI_STAT_OVRN)
// #define __tssi_state_trigger_meet()           (REG_TSSI_STAT & TSSI_STAT_TRIG)
// #define __tssi_clear_state()                  (REG_TSSI_STAT = 0) /* write 0??? */
// #define __tssi_state_clear_overrun()          (REG_TSSI_STAT = TSSI_STAT_OVRN)   //??????? xyma

// 

// 
//#define __tssi_enable_filte_pid0()            (REG_TSSI_PEN |= TSSI_PEN_PID0)
//#define __tssi_disable_filte_pid0()           (REG_TSSI_PEN &= ~TSSI_PEN_PID0)

// 
/* m = 0, ..., 31 */
////////////////???????????????????????????????????????????????????????????

// 
// #define __tssi_enable_pid_filter(m)				\
// 	do {							\
// 		int n = (m);					\
// 		if (n>=0 && n <(TSSI_PID_MAX*2)) {		\
// 			REG_TSSI_PEN |= (1 << n);		\
// 		}						\
// 	} while (0)

// 
/* m = 0, ..., 31 */
// #define __tssi_disable_pid_filter(m)				       \
// 	do {							       \
// 		int n = (m);					       \
// 		if (n>=0 && n <(TSSI_PID_MAX*2)) {		       \
// 			REG_TSSI_PEN &= ~(1 << n);		       \
// 		}						       \
// 	} while (0)

// 
/* n = 0, ..., 15 */
// #define __tssi_set_pid0(n, pid0)					\
// 	do {								\
// 		REG_TSSI_PID(n) &= ~TSSI_PID_PID0_MASK;			\
// 		REG_TSSI_PID(n) |= ((pid0)<<TSSI_PID_PID0_BIT)&TSSI_PID_PID0_MASK; \
// 	}while (0)
/* n = 0, ..., 15 */
// #define __tssi_set_pid1(n, pid1)					\
// 	do {								\
// 		REG_TSSI_PID(n) &= ~TSSI_PID_PID1_MASK;			\
// 		REG_TSSI_PID(n) |= ((pid1)<<TSSI_PID_PID1_BIT)&TSSI_PID_PID1_MASK; \
// 	}while (0)

// 
/* n = 0, ..., 15 */
// #define __tssi_set_pid(n, pid)						\
// 	do {								\
// 		if (n>=0 && n < TSSI_PID_MAX*2) {			\
// 			if (n < TSSI_PID_MAX)				\
// 				__tssi_set_pid0(n, pid);		\
// 			else						\
// 				__tssi_set_pid1(n-TSSI_PID_MAX, pid);	\
// 		}							\
// 	}while (0)

// 

// 

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4810TSSI_H__ */

// 
