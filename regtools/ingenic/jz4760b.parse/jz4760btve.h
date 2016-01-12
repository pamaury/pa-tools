/*
 * linux/include/asm-mips/mach-jz4760b/jz4760btve.h
 *
 * JZ4760B TVE register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

// 
// #ifndef __JZ4760BTVE_H__
// #define __JZ4760BTVE_H__

// 
/* TVE (TV Encoder Controller) */
this class TVE goto 0xB3050100 export "TVE (TV Encoder Controller)"

// 

// 
register CTRL goto 0x40 export "TV Encoder Control register"
register FRCFG goto 0x44 export "Frame configure register"
register SLCFG1 goto 0x50 export "TV signal level configure register 1"
register SLCFG2 goto 0x54 export "TV signal level configure register 2"
register SLCFG3 goto 0x58 export "TV signal level configure register 3"
register LTCFG1 goto 0x60 export "Line timing configure register 1"
register LTCFG2 goto 0x64 export "Line timing configure register 2"
register CFREQ goto 0x70 export "Chrominance sub-carrier frequency configure register"
register CPHASE goto 0x74 export "Chrominance sub-carrier phase configure register"
register CBCRCFG goto 0x78 export "Chrominance filter configure register"
register WSSCR goto 0x80 export "Wide screen signal control register"
register WSSCFG1 goto 0x84 export "Wide screen signal configure register 1"
register WSSCFG2 goto 0x88 export "Wide screen signal configure register 2"
register WSSCFG3 goto 0x8c export "Wide screen signal configure register 3"

// 
register CTRL sizeof 32
register FRCFG sizeof 32
register SLCFG1 sizeof 32
register SLCFG2 sizeof 32
register SLCFG3 sizeof 32
register LTCFG1 sizeof 32
register LTCFG2 sizeof 32
register CFREQ sizeof 32
register CPHASE sizeof 32
register CBCRCFG sizeof 32
register WSSCR sizeof 32
register WSSCFG1 sizeof 32
register WSSCFG2 sizeof 32
register WSSCFG3 sizeof 32

// 
/* TV Encoder Control register */
register CTRL int EYCBCR goto 25 export "YCbCr_enable"
register CTRL int ECVBS goto 24 export "1: cvbs_enable 0: s-video"
register CTRL int DAPD3 goto 23 export "DAC 3 power down"
register CTRL int DAPD2 goto 22 export "DAC 2 power down"
register CTRL int DAPD1 goto 21 export "DAC 1 power down"
register CTRL int DAPD goto 20 export "power down all DACs"
const TVE_CTRL_YCDLY_BIT 16
register CTRL int YCDLY goto (0x7 << TVE_CTRL_YCDLY_BIT)
const TVE_CTRL_CGAIN_BIT 14
register CTRL int CGAIN goto (0x3 << TVE_CTRL_CGAIN_BIT)
register CTRL int CGAIN enum FULL 0 export "gain = 1"
register CTRL int CGAIN enum QUTR 1 export "gain = 1/4"
register CTRL int CGAIN enum HALF 2 export "gain = 1/2"
register CTRL int CGAIN enum THREE_QURT 3 export "gain = 3/4"
const TVE_CTRL_CBW_BIT 12
register CTRL int CBW goto (0x3 << TVE_CTRL_CBW_BIT)
register CTRL int CBW enum NARROW 0 export "Narrow band"
register CTRL int CBW enum WIDE 1 export "Wide band"
register CTRL int CBW enum EXTRA 2 export "Extra wide band"
register CTRL int CBW enum ULTRA 3 export "Ultra wide band"
register CTRL int SYNCT goto 9
register CTRL int PAL goto 8 export "1: PAL, 0: NTSC"
register CTRL int FINV goto 7 export "invert_top:1-invert top and bottom fields."
register CTRL int ZBLACK goto 6 export "bypass_yclamp:1-Black of luminance (Y) input is 0."
register CTRL int CR1ST goto 5 export "uv_order:0-Cb before Cr,1-Cr before Cb"
register CTRL int CLBAR goto 4 export "Color bar mode:0-Output input video to TV,1-Output color bar to TV"
register CTRL int SWRST goto 0 export "Software reset:1-TVE is reset"

// 
/* Signal level configure register 1 */
const TVE_SLCFG1_BLACKL_BIT 0
register SLCFG1 int BLACKL goto (0x3ff << TVE_SLCFG1_BLACKL_BIT)
const TVE_SLCFG1_WHITEL_BIT 16
register SLCFG1 int WHITEL goto (0x3ff << TVE_SLCFG1_WHITEL_BIT)

// 
/* Signal level configure register 2 */
const TVE_SLCFG2_BLANKL_BIT 0
register SLCFG2 int BLANKL goto (0x3ff << TVE_SLCFG2_BLANKL_BIT)
const TVE_SLCFG2_VBLANKL_BIT 16
register SLCFG2 int VBLANKL goto (0x3ff << TVE_SLCFG2_VBLANKL_BIT)

// 
/* Signal level configure register 3 */
const TVE_SLCFG3_SYNCL_BIT 0
register SLCFG3 int SYNCL goto (0xff << TVE_SLCFG3_SYNCL_BIT)

// 
/* Line timing configure register 1 */
const TVE_LTCFG1_BACKP_BIT 0
register LTCFG1 int BACKP goto (0x7f << TVE_LTCFG1_BACKP_BIT)
const TVE_LTCFG1_HSYNCW_BIT 8
register LTCFG1 int HSYNCW goto (0x7f << TVE_LTCFG1_HSYNCW_BIT)
const TVE_LTCFG1_FRONTP_BIT 16
register LTCFG1 int FRONTP goto (0x1f << TVE_LTCFG1_FRONTP_BIT)

// 
/* Line timing configure register 2 */
const TVE_LTCFG2_BURSTW_BIT 0
register LTCFG2 int BURSTW goto (0x3f << TVE_LTCFG2_BURSTW_BIT)
const TVE_LTCFG2_PREBW_BIT 8
register LTCFG2 int PREBW goto (0x1f << TVE_LTCFG2_PREBW_BIT)
const TVE_LTCFG2_ACTLIN_BIT 16
register LTCFG2 int ACTLIN goto (0x7ff << TVE_LTCFG2_ACTLIN_BIT)

// 
/* Chrominance sub-carrier phase configure register */
const TVE_CPHASE_CCRSTP_BIT 0
register CPHASE int CCRSTP goto (0x3 << TVE_CPHASE_CCRSTP_BIT)
register CPHASE int CCRSTP enum "8" 0 export "Every 8 field"
register CPHASE int CCRSTP enum "4" 1 export "Every 4 field"
register CPHASE int CCRSTP enum "2" 2 export "Every 2 lines"
register CPHASE int CCRSTP enum "0" 3 export "Never"
const TVE_CPHASE_ACTPH_BIT 16
register CPHASE int ACTPH goto (0xff << TVE_CPHASE_ACTPH_BIT)
const TVE_CPHASE_INITPH_BIT 24
register CPHASE int INITPH goto (0xff << TVE_CPHASE_INITPH_BIT)

// 
/* Chrominance filter configure register */
const TVE_CBCRCFG_CRGAIN_BIT 0
register CBCRCFG int CRGAIN goto (0xff << TVE_CBCRCFG_CRGAIN_BIT)
const TVE_CBCRCFG_CBGAIN_BIT 8
register CBCRCFG int CBGAIN goto (0xff << TVE_CBCRCFG_CBGAIN_BIT)
const TVE_CBCRCFG_CRBA_BIT 16
register CBCRCFG int CRBA goto (0xff << TVE_CBCRCFG_CRBA_BIT)
const TVE_CBCRCFG_CBBA_BIT 24
register CBCRCFG int CBBA goto (0xff << TVE_CBCRCFG_CBBA_BIT)

// 
/* Frame configure register */
const TVE_FRCFG_NLINE_BIT 0
register FRCFG int NLINE goto (0x3ff << TVE_FRCFG_NLINE_BIT)
const TVE_FRCFG_L1ST_BIT 16
register FRCFG int L1ST goto (0xff << TVE_FRCFG_L1ST_BIT)

// 
/* Wide screen signal control register */
const TVE_WSSCR_EWSS0_BIT 0
const TVE_WSSCR_EWSS1_BIT 1
const TVE_WSSCR_WSSTP_BIT 2
const TVE_WSSCR_WSSCKBP_BIT 3
const TVE_WSSCR_WSSEDGE_BIT 4
register WSSCR int WSSEDGE goto (0x7 << TVE_WSSCR_WSSEDGE_BIT)
const TVE_WSSCR_ENCH_BIT 8
const TVE_WSSCR_NCHW_BIT 9
const TVE_WSSCR_NCHFREQ_BIT 12
register WSSCR int NCHFREQ goto (0x7 << TVE_WSSCR_NCHFREQ_BIT)

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 
/*************************************************************************
 * TVE (TV Encoder Controller) ops
 *************************************************************************/
/* TV Encoder Control register ops */
// #define __tve_soft_reset()		(REG_TVE_CTRL |= TVE_CTRL_SWRST)

// 
// #define __tve_output_colorbar()		(REG_TVE_CTRL |= TVE_CTRL_CLBAR)
// #define __tve_output_video()		(REG_TVE_CTRL &= ~TVE_CTRL_CLBAR)

// 
// #define __tve_input_cr_first()		(REG_TVE_CTRL |= TVE_CTRL_CR1ST)
// #define __tve_input_cb_first()		(REG_TVE_CTRL &= ~TVE_CTRL_CR1ST)

// 
// #define __tve_set_0_as_black()		(REG_TVE_CTRL |= TVE_CTRL_ZBLACK)
// #define __tve_set_16_as_black()		(REG_TVE_CTRL &= ~TVE_CTRL_ZBLACK)

// 
// #define __tve_ena_invert_top_bottom()	(REG_TVE_CTRL |= TVE_CTRL_FINV)
// #define __tve_dis_invert_top_bottom()	(REG_TVE_CTRL &= ~TVE_CTRL_FINV)

// 
// #define __tve_set_pal_mode()		(REG_TVE_CTRL |= TVE_CTRL_PAL)
// #define __tve_set_ntsc_mode()		(REG_TVE_CTRL &= ~TVE_CTRL_PAL)

// 
// #define __tve_set_pal_dura()		(REG_TVE_CTRL |= TVE_CTRL_SYNCT)
// #define __tve_set_ntsc_dura()		(REG_TVE_CTRL &= ~TVE_CTRL_SYNCT)

// 
/* n = 0 ~ 3 */
// #define __tve_set_c_bandwidth(n) \
// do {\
// 	REG_TVE_CTRL &= ~TVE_CTRL_CBW_MASK;\
// 	REG_TVE_CTRL |= (n) << TVE_CTRL_CBW_BIT;	\
// }while(0)

// 
/* n = 0 ~ 3 */
// #define __tve_set_c_gain(n) \
// do {\
// 	REG_TVE_CTRL &= ~TVE_CTRL_CGAIN_MASK;\
// 	(REG_TVE_CTRL |= (n) << TVE_CTRL_CGAIN_BIT;	\
// }while(0)

// 
/* n = 0 ~ 7 */
// #define __tve_set_yc_delay(n)				\
// do {							\
// 	REG_TVE_CTRL &= ~TVE_CTRL_YCDLY_MASK		\
// 	REG_TVE_CTRL |= ((n) << TVE_CTRL_YCDLY_BIT);	\
// } while(0)

// 
// #define __tve_disable_all_dacs()	(REG_TVE_CTRL |= TVE_CTRL_DAPD)
// #define __tve_disable_dac1()		(REG_TVE_CTRL |= TVE_CTRL_DAPD1)
// #define __tve_enable_dac1()		(REG_TVE_CTRL &= ~TVE_CTRL_DAPD1)
// #define __tve_disable_dac2()		(REG_TVE_CTRL |= TVE_CTRL_DAPD2)
// #define __tve_enable_dac2()		(REG_TVE_CTRL &= ~TVE_CTRL_DAPD2)
// #define __tve_disable_dac3()		(REG_TVE_CTRL |= TVE_CTRL_DAPD3)
// #define __tve_enable_dac3()		(REG_TVE_CTRL &= ~TVE_CTRL_DAPD3)

// 
// #define __tve_enable_svideo_fmt()	(REG_TVE_CTRL |= TVE_CTRL_ECVBS)
// #define __tve_enable_cvbs_fmt()		(REG_TVE_CTRL &= ~TVE_CTRL_ECVBS)

// 
/* TV Encoder Frame Configure register ops */
/* n = 0 ~ 255 */
// #define __tve_set_first_video_line(n)		\
// do {\
// 		REG_TVE_FRCFG &= ~TVE_FRCFG_L1ST_MASK;\
// 		REG_TVE_FRCFG |= (n) << TVE_FRCFG_L1ST_BIT;\
// } while(0)
/* n = 0 ~ 1023 */
// #define __tve_set_line_num_per_frm(n)		\
// do {\
// 		REG_TVE_FRCFG &= ~TVE_FRCFG_NLINE_MASK;\
// 		REG_TVE_CFG |= (n) << TVE_FRCFG_NLINE_BIT;\
// } while(0)
// #define __tve_get_video_line_num()\
// 	(((REG_TVE_FRCFG & TVE_FRCFG_NLINE_MASK) >> TVE_FRCFG_NLINE_BIT) - 1 - 2 * ((REG_TVE_FRCFG & TVE_FRCFG_L1ST_MASK) >> TVE_FRCFG_L1ST_BIT))

// 
/* TV Encoder Signal Level Configure register ops */
/* n = 0 ~ 1023 */
// #define __tve_set_white_level(n)		\
// do {\
// 		REG_TVE_SLCFG1 &= ~TVE_SLCFG1_WHITEL_MASK;\
// 		REG_TVE_SLCFG1 |= (n) << TVE_SLCFG1_WHITEL_BIT;\
// } while(0)
/* n = 0 ~ 1023 */
// #define __tve_set_black_level(n)		\
// do {\
// 		REG_TVE_SLCFG1 &= ~TVE_SLCFG1_BLACKL_MASK;\
// 		REG_TVE_SLCFG1 |= (n) << TVE_SLCFG1_BLACKL_BIT;\
// } while(0)
/* n = 0 ~ 1023 */
// #define __tve_set_blank_level(n)		\
// do {\
// 		REG_TVE_SLCFG2 &= ~TVE_SLCFG2_BLANKL_MASK;\
// 		REG_TVE_SLCFG2 |= (n) << TVE_SLCFG2_BLANKL_BIT;\
// } while(0)
/* n = 0 ~ 1023 */
// #define __tve_set_vbi_blank_level(n)		\
// do {\
// 		REG_TVE_SLCFG2 &= ~TVE_SLCFG2_VBLANKL_MASK;\
// 		REG_TVE_SLCFG2 |= (n) << TVE_SLCFG2_VBLANKL_BIT;\
// } while(0)
/* n = 0 ~ 1023 */
// #define __tve_set_sync_level(n)		\
// do {\
// 		REG_TVE_SLCFG3 &= ~TVE_SLCFG3_SYNCL_MASK;\
// 		REG_TVE_SLCFG3 |= (n) << TVE_SLCFG3_SYNCL_BIT;\
// } while(0)

// 
/* TV Encoder Signal Level Configure register ops */
/* n = 0 ~ 31 */
// #define __tve_set_front_porch(n)		\
// do {\
// 		REG_TVE_LTCFG1 &= ~TVE_LTCFG1_FRONTP_MASK;\
// 		REG_TVE_LTCFG1 |= (n) << TVE_LTCFG1_FRONTP_BIT;	\
// } while(0)
/* n = 0 ~ 127 */
// #define __tve_set_hsync_width(n)		\
// do {\
// 		REG_TVE_LTCFG1 &= ~TVE_LTCFG1_HSYNCW_MASK;\
// 		REG_TVE_LTCFG1 |= (n) << TVE_LTCFG1_HSYNCW_BIT;	\
// } while(0)
/* n = 0 ~ 127 */
// #define __tve_set_back_porch(n)		\
// do {\
// 		REG_TVE_LTCFG1 &= ~TVE_LTCFG1_BACKP_MASK;\
// 		REG_TVE_LTCFG1 |= (n) << TVE_LTCFG1_BACKP_BIT;	\
// } while(0)
/* n = 0 ~ 2047 */
// #define __tve_set_active_linec(n)		\
// do {\
// 		REG_TVE_LTCFG2 &= ~TVE_LTCFG2_ACTLIN_MASK;\
// 		REG_TVE_LTCFG2 |= (n) << TVE_LTCFG2_ACTLIN_BIT;	\
// } while(0)
/* n = 0 ~ 31 */
// #define __tve_set_breezy_way(n)		\
// do {\
// 		REG_TVE_LTCFG2 &= ~TVE_LTCFG2_PREBW_MASK;\
// 		REG_TVE_LTCFG2 |= (n) << TVE_LTCFG2_PREBW_BIT;	\
// } while(0)

// 
/* n = 0 ~ 127 */
// #define __tve_set_burst_width(n)		\
// do {\
// 		REG_TVE_LTCFG2 &= ~TVE_LTCFG2_BURSTW_MASK;\
// 		REG_TVE_LTCFG2 |= (n) << TVE_LTCFG2_BURSTW_BIT;	\
// } while(0)

// 
/* TV Encoder Chrominance filter and Modulation register ops */
/* n = 0 ~ (2^32-1) */
// #define __tve_set_c_sub_carrier_freq(n)  REG_TVE_CFREQ = (n)
/* n = 0 ~ 255 */
// #define __tve_set_c_sub_carrier_init_phase(n) \
// do {   \
// 	REG_TVE_CPHASE &= ~TVE_CPHASE_INITPH_MASK;	\
// 	REG_TVE_CPHASE |= (n) << TVE_CPHASE_INITPH_BIT;	\
// } while(0)
/* n = 0 ~ 255 */
// #define __tve_set_c_sub_carrier_act_phase(n) \
// do {   \
// 	REG_TVE_CPHASE &= ~TVE_CPHASE_ACTPH_MASK;	\
// 	REG_TVE_CPHASE |= (n) << TVE_CPHASE_ACTPH_BIT;	\
// } while(0)
/* n = 0 ~ 255 */
// #define __tve_set_c_phase_rst_period(n) \
// do {   \
// 	REG_TVE_CPHASE &= ~TVE_CPHASE_CCRSTP_MASK;	\
// 	REG_TVE_CPHASE |= (n) << TVE_CPHASE_CCRSTP_BIT;	\
// } while(0)
/* n = 0 ~ 255 */
// #define __tve_set_cb_burst_amp(n) \
// do {   \
// 	REG_TVE_CBCRCFG &= ~TVE_CBCRCFG_CBBA_MASK;	\
// 	REG_TVE_CBCRCFG |= (n) << TVE_CBCRCFG_CBBA_BIT;	\
// } while(0)
/* n = 0 ~ 255 */
// #define __tve_set_cr_burst_amp(n) \
// do {   \
// 	REG_TVE_CBCRCFG &= ~TVE_CBCRCFG_CRBA_MASK;	\
// 	REG_TVE_CBCRCFG |= (n) << TVE_CBCRCFG_CRBA_BIT;	\
// } while(0)
/* n = 0 ~ 255 */
// #define __tve_set_cb_gain_amp(n) \
// do {   \
// 	REG_TVE_CBCRCFG &= ~TVE_CBCRCFG_CBGAIN_MASK;	\
// 	REG_TVE_CBCRCFG |= (n) << TVE_CBCRCFG_CBGAIN_BIT;	\
// } while(0)
/* n = 0 ~ 255 */
// #define __tve_set_cr_gain_amp(n) \
// do {   \
// 	REG_TVE_CBCRCFG &= ~TVE_CBCRCFG_CRGAIN_MASK;	\
// 	REG_TVE_CBCRCFG |= (n) << TVE_CBCRCFG_CRGAIN_BIT;	\
// } while(0)

// 
/* TV Encoder Wide Screen Signal Control register ops */
/* n = 0 ~ 7 */
// #define __tve_set_notch_freq(n) \
// do {   \
// 	REG_TVE_WSSCR &= ~TVE_WSSCR_NCHFREQ_MASK;	\
// 	REG_TVE_WSSCR |= (n) << TVE_WSSCR_NCHFREQ_BIT;	\
// } while(0)
/* n = 0 ~ 7 */
// #define __tve_set_notch_width()	(REG_TVE_WSSCR |= TVE_WSSCR_NCHW_BIT)
// #define __tve_clear_notch_width()	(REG_TVE_WSSCR &= ~TVE_WSSCR_NCHW_BIT)
// #define __tve_enable_notch()		(REG_TVE_WSSCR |= TVE_WSSCR_ENCH_BIT)
// #define __tve_disable_notch()		(REG_TVE_WSSCR &= ~TVE_WSSCR_ENCH_BIT)
/* n = 0 ~ 7 */
// #define __tve_set_wss_edge(n) \
// do {   \
// 	REG_TVE_WSSCR &= ~TVE_WSSCR_WSSEDGE_MASK;	\
// 	REG_TVE_WSSCR |= (n) << TVE_WSSCR_WSSEDGE_BIT;	\
// } while(0)
// #define __tve_set_wss_clkbyp()		(REG_TVE_WSSCR |= TVE_WSSCR_WSSCKBP_BIT)
// #define __tve_set_wss_type()		(REG_TVE_WSSCR |= TVE_WSSCR_WSSTP_BIT)
// #define __tve_enable_wssf1()		(REG_TVE_WSSCR |= TVE_WSSCR_EWSS1_BIT)
// #define __tve_enable_wssf0()		(REG_TVE_WSSCR |= TVE_WSSCR_EWSS0_BIT)

// 
/* TV Encoder Wide Screen Signal Configure register 1, 2 and 3 ops */
/* n = 0 ~ 1023 */
// #define __tve_set_wss_level(n) \
// do {   \
// 	REG_TVE_WSSCFG1 &= ~TVE_WSSCFG1_WSSL_MASK;	\
// 	REG_TVE_WSSCFG1 |= (n) << TVE_WSSCFG1_WSSL_BIT;	\
// } while(0)
/* n = 0 ~ 4095 */
// #define __tve_set_wss_freq(n) \
// do {   \
// 	REG_TVE_WSSCFG1 &= ~TVE_WSSCFG1_WSSFREQ_MASK;	\
// 	REG_TVE_WSSCFG1 |= (n) << TVE_WSSCFG1_WSSFREQ_BIT;	\
// } while(0)
/* n = 0, 1; l = 0 ~ 255 */
// #define __tve_set_wss_line(n,v)			\
// do {   \
// 	REG_TVE_WSSCFG##n &= ~TVE_WSSCFG_WSSLINE_MASK;	\
// 	REG_TVE_WSSCFG##n |= (v) << TVE_WSSCFG_WSSLINE_BIT;	\
// } while(0)
/* n = 0, 1; d = 0 ~ (2^20-1) */
// #define __tve_set_wss_data(n, v)			\
// do {   \
// 	REG_TVE_WSSCFG##n &= ~TVE_WSSCFG_WSSLINE_MASK;	\
// 	REG_TVE_WSSCFG##n |= (v) << TVE_WSSCFG_WSSLINE_BIT;	\
// } while(0)

// 

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BTVE_H__ */

// 
