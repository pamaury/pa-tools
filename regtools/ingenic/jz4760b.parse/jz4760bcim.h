/*
 * linux/include/asm-mips/mach-jz4760b/jz4760bcim.h
 *
 * JZ4760B CIM register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

// 
// #ifndef __JZ4760BCIM_H__
// #define __JZ4760BCIM_H__

// 

// 
this class CIM goto 0xB3060000

// 
/*************************************************************************
 * CIM
 *************************************************************************/
register CFG goto 0x0000 export ""
register CTRL goto 0x0004 export ""
register STATE goto 0x0008 export ""
register IID goto 0x000C export ""
register RXFIFO goto 0x0010 export ""
register DA goto 0x0020 export ""
register FA goto 0x0024 export ""
register FID goto 0x0028 export ""
register CMD goto 0x002C export ""
register SIZE goto 0x0030 export ""
register OFFSET goto 0x0034 export ""
register YFA goto 0x0038 export ""
register YCMD goto 0x003C export ""
register CBFA goto 0x0040 export ""
register CBCMD goto 0x0044 export ""
register CRFA goto 0x0048 export ""
register CRCMD goto 0x004C export ""
register CTRL2 goto 0x0050 export ""
register RAM_ADDR goto 0x1000 export ""

// 
register CFG sizeof 32
register CTRL sizeof 32
register CTRL2 sizeof 32
register STATE sizeof 32
register IID sizeof 32
register RXFIFO sizeof 32
register DA sizeof 32
register FA sizeof 32
register FID sizeof 32
register CMD sizeof 32
register SIZE sizeof 32
register OFFSET sizeof 32
register YFA sizeof 32
register YCMD sizeof 32
register CBFA sizeof 32
register CBCMD sizeof 32
register CRFA sizeof 32
register CRCMD sizeof 32

// 
const CIM_CFG_RXF_TRIG_BIT 24
register CFG int RXF_TRIG goto (0x3f << CIM_CFG_RXF_TRIG_BIT)
register CFG int SEP goto 20
const CIM_CFG_ORDER_BIT 18
register CFG int ORDER goto (0x3 << CIM_CFG_ORDER_BIT)
register CFG int ORDER enum "0" 0x0 export "Y0CbY1Cr; YCbCr"
register CFG int ORDER enum "1" 0x1 export "Y0CrY1Cb; YCrCb"
register CFG int ORDER enum "2" 0x2 export "CbY0CrY1; CbCrY"
register CFG int ORDER enum "3" 0x3 export "CrY0CbY1; CrCbY"
const CIM_CFG_DF_BIT 16
register CFG int DF goto (0x3 << CIM_CFG_DF_BIT)
register CFG int DF enum YUV444 0x1 export "YCbCr444"
register CFG int DF enum YUV422 0x2 export "YCbCr422"
register CFG int DF enum ITU656 0x3 export "ITU656 YCbCr422"
register CFG int INV_DAT goto 15
register CFG int VSP goto 14 export "VSYNC Polarity:0-rising edge active,1-falling edge active"
register CFG int HSP goto 13 export "HSYNC Polarity:0-rising edge active,1-falling edge active"
register CFG int PCP goto 12 export "PCLK working edge: 0-rising, 1-falling"
const CIM_CFG_DMA_BURST_TYPE_BIT 10
register CFG int DMA goto (0x3 << CIM_CFG_DMA_BURST_TYPE_BIT)
register CFG int DMA enum BURST_INCR4 0
register CFG int DMA enum BURST_INCR8 1 export "Suggested"
register CFG int DMA enum BURST_INCR16 2 export "Suggested High speed AHB"
register CFG int DMA enum BURST_INCR32 3 export "Suggested High speed AHB"
register CFG int DUMMY_ZERO goto 9
register CFG int EXT_VSYNC goto 8 export "Only for ITU656 Progressive mode"
const CIM_CFG_PACK_BIT 4
register CFG int PACK goto (0x7 << CIM_CFG_PACK_BIT)
register CFG int PACK enum "0" 0 export "11 22 33 44 0xY0CbY1Cr"
register CFG int PACK enum "1" 1 export "22 33 44 11 0xCbY1CrY0"
register CFG int PACK enum "2" 2 export "33 44 11 22 0xY1CrY0Cb"
register CFG int PACK enum "3" 3 export "44 11 22 33 0xCrY0CbY1"
register CFG int PACK enum "4" 4 export "44 33 22 11 0xCrY1CbY0"
register CFG int PACK enum "5" 5 export "33 22 11 44 0xY1CbY0Cr"
register CFG int PACK enum "6" 6 export "22 11 44 33 0xCbY0CrY1"
register CFG int PACK enum "7" 7 export "11 44 33 22 0xY0CrY1Cb"
const CIM_CFG_BYPASS_BIT 2
register CFG int BYPASS goto (1 << CIM_CFG_BYPASS_BIT)
//   #define CIM_CFG_BYPASS	  (1 << CIM_CFG_BYPASS_BIT)
const CIM_CFG_DSM_BIT 0
register CFG int DSM goto (0x3 << CIM_CFG_DSM_BIT)
register CFG int DSM enum CPM 0 export "CCIR656 Progressive Mode"
register CFG int DSM enum CIM 1 export "CCIR656 Interlace Mode"
register CFG int DSM enum GCM 2 export "Gated Clock Mode"

// 
/* CIM Control Register  (CIM_CTRL) */
const CIM_CTRL_EEOF_LINE_BIT 20
register CTRL int EEOF_LINE goto (0xfff << CIM_CTRL_EEOF_LINE_BIT)
const CIM_CTRL_FRC_BIT 16
register CTRL int FRC goto (0xf << CIM_CTRL_FRC_BIT)
register CTRL int FRC enum "1" 0x0 export "Sample every frame"
register CTRL int FRC enum "2" 0x1 export "Sample 1/2 frame"
register CTRL int FRC enum "3" 0x2 export "Sample 1/3 frame"
register CTRL int FRC enum "4" 0x3 export "Sample 1/4 frame"
register CTRL int FRC enum "5" 0x4 export "Sample 1/5 frame"
register CTRL int FRC enum "6" 0x5 export "Sample 1/6 frame"
register CTRL int FRC enum "7" 0x6 export "Sample 1/7 frame"
register CTRL int FRC enum "8" 0x7 export "Sample 1/8 frame"
register CTRL int FRC enum "9" 0x8 export "Sample 1/9 frame"
register CTRL int FRC enum "10" 0x9 export "Sample 1/10 frame"
register CTRL int FRC enum "11" 0xA export "Sample 1/11 frame"
register CTRL int FRC enum "12" 0xB export "Sample 1/12 frame"
register CTRL int FRC enum "13" 0xC export "Sample 1/13 frame"
register CTRL int FRC enum "14" 0xD export "Sample 1/14 frame"
register CTRL int FRC enum "15" 0xE export "Sample 1/15 frame"
register CTRL int FRC enum "16" 0xF export "Sample 1/16 frame"

// 
register CTRL int DMA_EEOFM goto 15 export "Enable EEOF interrupt"
register CTRL int WIN_EN goto 14
register CTRL int VDDM goto 13 export "VDD interrupt enable"
register CTRL int DMA_SOFM goto 12
register CTRL int DMA_EOFM goto 11
register CTRL int DMA_STOPM goto 10
register CTRL int RXF_TRIGM goto 9
register CTRL int RXF_OFM goto 8
register CTRL int DMA_SYNC goto 7 export "when change DA, do frame sync"
const CIM_CTRL_RXF_TRIG_BIT 3
register CTRL int RXF_TRIG goto (0xf << CIM_CTRL_RXF_TRIG_BIT) export "trigger value = (n+1)*burst_type"

// 
register CTRL int DMA_EN goto 2 export "Enable DMA"
register CTRL int RXF_RST goto 1 export "RxFIFO reset"
register CTRL int ENA goto 0 export "Enable CIM"

// 

// 
/* cim control2 */
const CIM_CTRL2_OPG_BIT 4
register CTRL2 int OPG goto (0x3 << CIM_CTRL2_OPG_BIT)
register CTRL2 int OPE goto 2
register CTRL2 int EME goto 1
register CTRL2 int APM goto 0

// 
/* CIM State Register  (CIM_STATE) */
register STATE int CR_RF_OF goto 27
register STATE int CR_RF_TRIG goto 26
register STATE int CR_RF_EMPTY goto 25

// 
register STATE int CB_RF_OF goto 19
register STATE int CB_RF_TRIG goto 18
register STATE int CB_RF_EMPTY goto 17

// 
register STATE int Y_RF_OF goto 11
register STATE int Y_RF_TRIG goto 10
register STATE int Y_RF_EMPTY goto 9

// 
register STATE int DMA_EEOF goto 7 export "DMA Line EEOf irq"
register STATE int DMA_SOF goto 6 export "DMA start irq"
register STATE int DMA_EOF goto 5 export "DMA end irq"
register STATE int DMA_STOP goto 4 export "DMA stop irq"
register STATE int RXF_OF goto 3 export "RXFIFO over flow irq"
register STATE int RXF_TRIG goto 2 export "RXFIFO triger meet irq"
register STATE int RXF_EMPTY goto 1 export "RXFIFO empty irq"
register STATE int VDD goto 0 export "CIM disabled irq"

// 
/* CIM DMA Command Register (CIM_CMD) */

// 
register CMD int SOFINT goto 31 export "enable DMA start irq"
register CMD int EOFINT goto 30 export "enable DMA end irq"
register CMD int EEOFINT goto 29 export "enable DMA EEOF irq"
register CMD int STOP goto 28 export "enable DMA stop irq"
register CMD int OFRCV goto 27 export "enable recovery when TXFiFo overflow"
const CIM_CMD_LEN_BIT 0
register CMD int LEN goto (0xffffff << CIM_CMD_LEN_BIT)

// 
/* CIM Window-Image Size Register  (CIM_SIZE) */
const CIM_SIZE_LPF_BIT 16
register SIZE int LPF export "Lines per freame for csc output image"
register SIZE int LPF goto (0x1fff << CIM_SIZE_LPF_BIT)
const CIM_SIZE_PPL_BIT 0
register SIZE int PPL export "Pixels per line for csc output image, should be an even number"
register SIZE int PPL goto (0x1fff << CIM_SIZE_PPL_BIT)

// 
/* CIM Image Offset Register  (CIM_OFFSET) */
const CIM_OFFSET_V_BIT 16
register OFFSET int V export "Vertical offset"
register OFFSET int V goto (0xfff << CIM_OFFSET_V_BIT)
const CIM_OFFSET_H_BIT 0
register OFFSET int H export "Horizontal offset, should be an enen number"
register OFFSET int H goto (0xfff << CIM_OFFSET_H_BIT) export "OFFSET_H should be even number"

// 
// #ifndef __MIPS_ASSEMBLER

// 
/***************************************************************************
 * CIM
 ***************************************************************************/

// 
// #define __cim_enable()	( REG_CIM_CTRL |= CIM_CTRL_ENA )
// #define __cim_disable()	( REG_CIM_CTRL &= ~CIM_CTRL_ENA )

// 
// #define __cim_enable_sep() (REG_CIM_CFG |= CIM_CFG_SEP)
// #define __cim_disable_sep() (REG_CIM_CFG &= ~CIM_CFG_SEP)

// 
/* n = 0, 1, 2, 3 */
// #define __cim_set_input_data_stream_order(n)				\
// 	do {								\
// 		REG_CIM_CFG &= ~CIM_CFG_ORDER_MASK;			\
// 		REG_CIM_CFG |= ((n)<<CIM_CFG_ORDER_BIT)&CIM_CFG_ORDER_MASK; \
// 	} while (0)

// 
// #define __cim_input_data_format_select_RGB()	\
// 	do {					\
// 		REG_CIM_CFG &= ~CIM_CFG_DF_MASK;	\
// 		REG_CIM_CFG |= CIM_CFG_DF_RGB;	\
// 	} while (0)

// 
// #define __cim_input_data_format_select_YUV444()		\
// 	do {						\
// 		REG_CIM_CFG &= ~CIM_CFG_DF_MASK;		\
// 		REG_CIM_CFG |= CIM_CFG_DF_YUV444;	\
// 	} while (0)

// 
// #define __cim_input_data_format_select_YUV422()		\
// 	do {						\
// 		REG_CIM_CFG &= ~CIM_CFG_DF_MASK;		\
// 		REG_CIM_CFG |= CIM_CFG_DF_YUV422;	\
// 	} while (0)

// 
// #define __cim_input_data_format_select_ITU656()		\
// 	do {						\
// 		REG_CIM_CFG &= ~CIM_CFG_DF_MASK;		\
// 		REG_CIM_CFG |= CIM_CFG_DF_ITU656;	\
// 	} while (0)

// 
// #define __cim_input_data_inverse()	( REG_CIM_CFG |= CIM_CFG_INV_DAT )
// #define __cim_input_data_normal()	( REG_CIM_CFG &= ~CIM_CFG_INV_DAT )

// 
// #define __cim_vsync_active_low()	( REG_CIM_CFG |= CIM_CFG_VSP )
// #define __cim_vsync_active_high()	( REG_CIM_CFG &= ~CIM_CFG_VSP )

// 
// #define __cim_hsync_active_low()	( REG_CIM_CFG |= CIM_CFG_HSP )
// #define __cim_hsync_active_high()	( REG_CIM_CFG &= ~CIM_CFG_HSP )

// 
// #define __cim_sample_data_at_pclk_falling_edge() \
// 	( REG_CIM_CFG |= CIM_CFG_PCP )
// #define __cim_sample_data_at_pclk_rising_edge() \
// 	( REG_CIM_CFG &= ~CIM_CFG_PCP )

// 
// #define __cim_enable_dummy_zero()	( REG_CIM_CFG |= CIM_CFG_DUMMY_ZERO )
// #define __cim_disable_dummy_zero()	( REG_CIM_CFG &= ~CIM_CFG_DUMMY_ZERO )

// 
// #define __cim_select_external_vsync()	( REG_CIM_CFG |= CIM_CFG_EXT_VSYNC )
// #define __cim_select_internal_vsync()	( REG_CIM_CFG &= ~CIM_CFG_EXT_VSYNC )

// 
/* n=0-7 */
// #define __cim_set_data_packing_mode(n) 		\
// do {						\
// 	REG_CIM_CFG &= ~CIM_CFG_PACK_MASK;	\
// 	REG_CIM_CFG |= (CIM_CFG_PACK_##n);	\
// } while (0)

// 
// #define __cim_enable_bypass_func() 	(REG_CIM_CFG |= CIM_CFG_BYPASS)
// #define __cim_disable_bypass_func() 	(REG_CIM_CFG &= ~CIM_CFG_BYPASS_MASK)

// 
// #define __cim_enable_ccir656_progressive_mode()	\
// do {						\
// 	REG_CIM_CFG &= ~CIM_CFG_DSM_MASK;	\
// 	REG_CIM_CFG |= CIM_CFG_DSM_CPM;		\
// } while (0)

// 
// #define __cim_enable_ccir656_interlace_mode()	\
// do {						\
// 	REG_CIM_CFG &= ~CIM_CFG_DSM_MASK;	\
// 	REG_CIM_CFG |= CIM_CFG_DSM_CIM;		\
// } while (0)

// 
// #define __cim_enable_gated_clock_mode()		\
// do {						\
// 	REG_CIM_CFG &= ~CIM_CFG_DSM_MASK;	\
// 	REG_CIM_CFG |= CIM_CFG_DSM_GCM;		\
// } while (0)

// 
// #define __cim_enable_nongated_clock_mode()	\
// do {						\
// 	REG_CIM_CFG &= ~CIM_CFG_DSM_MASK;	\
// 	REG_CIM_CFG |= CIM_CFG_DSM_NGCM;	\
// } while (0)

// 
/* sclk:system bus clock
 * mclk: CIM master clock
 */
// #define __cim_set_master_clk(sclk, mclk)			\
// do {								\
// 	REG_CIM_CTRL &= ~CIM_CTRL_MCLKDIV_MASK;				\
// 	REG_CIM_CTRL |= (((sclk)/(mclk) - 1) << CIM_CTRL_MCLKDIV_BIT);	\
// } while (0)
/* n=1-16 */
// #define __cim_set_frame_rate(n) 		\
// do {						\
// 	REG_CIM_CTRL &= ~CIM_CTRL_FRC_MASK; 	\
// 	REG_CIM_CTRL |= CIM_CTRL_FRC_##n;	\
// } while (0)

// 
// #define __cim_enable_size_func() \
// 	( REG_CIM_CTRL |= CIM_CTRL_WIN_EN)
// #define __cim_disable_size_func() \
// 	( REG_CIM_CTRL &= ~CIM_CTRL_WIN_EN )

// 
// #define __cim_enable_vdd_intr() \
// 	( REG_CIM_CTRL |= CIM_CTRL_VDDM )
// #define __cim_disable_vdd_intr() \
// 	( REG_CIM_CTRL &= ~CIM_CTRL_VDDM )

// 
// #define __cim_enable_sof_intr() \
// 	( REG_CIM_CTRL |= CIM_CTRL_DMA_SOFM )
// #define __cim_disable_sof_intr() \
// 	( REG_CIM_CTRL &= ~CIM_CTRL_DMA_SOFM )

// 
// #define __cim_enable_eof_intr() \
// 	( REG_CIM_CTRL |= CIM_CTRL_DMA_EOFM )
// #define __cim_disable_eof_intr() \
// 	( REG_CIM_CTRL &= ~CIM_CTRL_DMA_EOFM )

// 
// #define __cim_enable_eeof_intr() \
// 	( REG_CIM_CTRL |= CIM_CTRL_DMA_EEOFM )
// #define __cim_disable_eeof_intr() \
// 	( REG_CIM_CTRL &= ~CIM_CTRL_DMA_EEOFM )

// 
// #define __cim_enable_stop_intr() \
// 	( REG_CIM_CTRL |= CIM_CTRL_DMA_STOPM )
// #define __cim_disable_stop_intr() \
// 	( REG_CIM_CTRL &= ~CIM_CTRL_DMA_STOPM )

// 
// #define __cim_enable_trig_intr() \
// 	( REG_CIM_CTRL |= CIM_CTRL_RXF_TRIGM )
// #define __cim_disable_trig_intr() \
// 	( REG_CIM_CTRL &= ~CIM_CTRL_RXF_TRIGM )

// 
// #define __cim_enable_rxfifo_overflow_intr()	\
// 	( REG_CIM_CTRL |= CIM_CTRL_RXF_OFM )
// #define __cim_disable_rxfifo_overflow_intr()	\
// 	( REG_CIM_CTRL &= ~CIM_CTRL_RXF_OFM )

// 
/* n=4,8,12,16,20,24,28,32 */
// #define __cim_set_rxfifo_trigger(n)				\
// 	do {							\
// 		REG_CIM_CTRL &= ~CIM_CTRL_RXF_TRIG_MASK; 	\
// 		REG_CIM_CTRL |= CIM_CTRL_RXF_TRIG_##n;		\
// 	} while (0)

// 

// 
// #define __cim_set_eeof_line(n)						\
// 	do {								\
// 		REG_CIM_CTRL &= ~CIM_CTRL_EEOF_LINE_MASK;		\
// 		REG_CIM_CTRL |= ( ((n) << CIM_CTRL_EEOF_LINE_BIT) & CIM_CTRL_EEOF_LINE_MASK ); \
// 	} while (0)

// 
// #define __cim_enable_fast_mode() 	( REG_CIM_CTRL |= CIM_CTRL_FAST_MODE )
// #define __cim_disable_fast_mode() 	( REG_CIM_CTRL &= ~CIM_CTRL_FAST_MODE )
// #define __cim_use_normal_mode() 	__cim_disable_fast_mode()
// #define __cim_enable_dma()   ( REG_CIM_CTRL |= CIM_CTRL_DMA_EN )
// #define __cim_disable_dma()  ( REG_CIM_CTRL &= ~CIM_CTRL_DMA_EN )
// #define __cim_reset_rxfifo() ( REG_CIM_CTRL |= CIM_CTRL_RXF_RST )
// #define __cim_unreset_rxfifo() ( REG_CIM_CTRL &= ~CIM_CTRL_RXF_RST )

// 
/* cim control2 */
// #define __cim_enable_priority_control()		( REG_CIM_CTRL2 |= CIM_CTRL2_APM)
// #define __cim_disable_priority_control()	( REG_CIM_CTRL2 &= ~CIM_CTRL2_APM)
// #define __cim_enable_auto_priority()		( REG_CIM_CTRL2 |= CIM_CTRL2_OPE)
// #define __cim_disable_auto_priority()		( REG_CIM_CTRL2 &= ~CIM_CTRL2_OPE)
// #define __cim_enable_emergency()		( REG_CIM_CTRL2 |= CIM_CTRL2_EME)
// #define __cim_disable_emergency()		( REG_CIM_CTRL2 &= ~CIM_CTRL2_EME);
/* 0, 1, 2, 3
 * 0: highest priority
 * 3: lowest priority
 * 1 maybe best for SEP=1
 * 3 maybe best for SEP=0
 */
// #define __cim_set_opg(n)				\
// 	do {								\
// 		REG_CIM_CTRL2 &= ~CIM_CTRL2_OPG_MASK;			\
// 		REG_CIM_CTRL2 |= ((n) << CIM_CTRL2_OPG_BIT) & CIM_CTRL2_OPG_MASK; \
// 	} while (0)

// 
// #define __cim_clear_state()   	     ( REG_CIM_STATE = 0 )

// 
// #define __cim_disable_done()   	     ( REG_CIM_STATE & CIM_STATE_VDD )
// #define __cim_rxfifo_empty()   	     ( REG_CIM_STATE & CIM_STATE_RXF_EMPTY )
// #define __cim_rxfifo_reach_trigger() ( REG_CIM_STATE & CIM_STATE_RXF_TRIG )
// #define __cim_rxfifo_overflow()      ( REG_CIM_STATE & CIM_STATE_RXF_OF )
// #define __cim_clear_rxfifo_overflow() ( REG_CIM_STATE &= ~CIM_STATE_RXF_OF )
// #define __cim_dma_stop()   	     ( REG_CIM_STATE & CIM_STATE_DMA_STOP )
// #define __cim_dma_eof()   	     ( REG_CIM_STATE & CIM_STATE_DMA_EOF )
// #define __cim_dma_sof()   	     ( REG_CIM_STATE & CIM_STATE_DMA_SOF )

// 
// #define __cim_get_iid()   	     ( REG_CIM_IID )
// #define __cim_get_fid()   	     ( REG_CIM_FID )
// #define __cim_get_image_data()       ( REG_CIM_RXFIFO )
// #define __cim_get_dma_cmd()          ( REG_CIM_CMD )

// 
// #define __cim_set_da(a)              ( REG_CIM_DA = (a) )

// 
// #define __cim_set_line(a) 	( REG_CIM_SIZE = (REG_CIM_SIZE&(~CIM_SIZE_LPF_MASK))|((a)<<CIM_SIZE_LPF_BIT) )
// #define __cim_set_pixel(a) 	( REG_CIM_SIZE = (REG_CIM_SIZE&(~CIM_SIZE_PPL_MASK))|((a)<<CIM_SIZE_PPL_BIT) )
// #define __cim_get_line() 	((REG_CIM_SIZE&CIM_SIZE_LPF_MASK)>>CIM_SIZE_LPF_BIT)
// #define __cim_get_pixel() 	((REG_CIM_SIZE&CIM_SIZE_PPL_MASK)>>CIM_SIZE_PPL_BIT)

// 
// #define __cim_set_v_offset(a) 	( REG_CIM_OFFSET = (REG_CIM_OFFSET&(~CIM_OFFSET_V_MASK)) | ((a)<<CIM_OFFSET_V_BIT) )
// #define __cim_set_h_offset(a) 	( REG_CIM_OFFSET = (REG_CIM_OFFSET&(~CIM_OFFSET_H_MASK)) | ((a)<<CIM_OFFSET_H_BIT) )
// #define __cim_get_v_offset() 	((REG_CIM_OFFSET&CIM_OFFSET_V_MASK)>>CIM_OFFSET_V_BIT)
// #define __cim_get_h_offset() 	((REG_CIM_OFFSET&CIM_OFFSET_H_MASK)>>CIM_OFFSET_H_BIT)

// 

// 

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BCIM_H__ */
