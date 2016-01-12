/*
 * chip-aic.h
 * JZ4760B AIC register definition
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 *
 * Author: whxu@ingenic.cn
 */

// 
// #ifndef __CHIP_AIC_H__
// #define __CHIP_AIC_H__

// 

// 
/* AC97 and I2S controller module */
this class AIC goto 0xb0020000 export "AC97 and I2S controller module"

// 

// 
/*
 * AIC registers offset address definition
 */
const AIC_FR_OFFSET 0x00
const AIC_CR_OFFSET 0x04
const AIC_ACCR1_OFFSET 0x08
const AIC_ACCR2_OFFSET 0x0c
const AIC_I2SCR_OFFSET 0x10
const AIC_SR_OFFSET 0x14
const AIC_ACSR_OFFSET 0x18
const AIC_I2SSR_OFFSET 0x1c
const AIC_ACCAR_OFFSET 0x20
const AIC_ACCDR_OFFSET 0x24
const AIC_ACSAR_OFFSET 0x28
const AIC_ACSDR_OFFSET 0x2c
const AIC_I2SDIV_OFFSET 0x30
const AIC_DR_OFFSET 0x34

// 
const AIC_SPENA_OFFSET 0x80
const AIC_SPCTRL_OFFSET 0x84
const AIC_SPSTATE_OFFSET 0x88
const AIC_SPCFG1_OFFSET 0x8c
const AIC_SPCFG2_OFFSET 0x90
const AIC_SPFIFO_OFFSET 0x94

// 
const AIC_RGADW_OFFSET 0xa4
const AIC_RGDATA_OFFSET 0xa8

// 

// 
/*
 * AIC registers address definition
 */
register FR goto AIC_FR_OFFSET export ""
register CR goto AIC_CR_OFFSET export ""
register ACCR1 goto AIC_ACCR1_OFFSET export ""
register ACCR2 goto AIC_ACCR2_OFFSET export ""
register I2SCR goto AIC_I2SCR_OFFSET export ""
register SR goto AIC_SR_OFFSET export ""
register ACSR goto AIC_ACSR_OFFSET export ""
register I2SSR goto AIC_I2SSR_OFFSET export ""
register ACCAR goto AIC_ACCAR_OFFSET export ""
register ACCDR goto AIC_ACCDR_OFFSET export ""
register ACSAR goto AIC_ACSAR_OFFSET export ""
register ACSDR goto AIC_ACSDR_OFFSET export ""
register I2SDIV goto AIC_I2SDIV_OFFSET export ""
register DR goto AIC_DR_OFFSET export ""

// 
register SPENA goto AIC_SPENA_OFFSET export ""
register SPCTRL goto AIC_SPCTRL_OFFSET export ""
register SPSTATE goto AIC_SPSTATE_OFFSET export ""
register SPCFG1 goto AIC_SPCFG1_OFFSET export ""
register SPCFG2 goto AIC_SPCFG2_OFFSET export ""
register SPFIFO goto AIC_SPFIFO_OFFSET export ""

// 
register RGADW goto AIC_RGADW_OFFSET export ""
register RGDATA goto AIC_RGDATA_OFFSET export ""

// 

// 
/*
 * AIC registers common define
 */

// 
register FR export "AIC controller configuration register"
register FR int LSMP goto 6
register FR int ICDC goto 5
register FR int AUSEL goto 4
register FR int RST goto 3
register FR int BCKD goto 2
register FR int SYNCD goto 1
register FR int ENB goto 0

// 
const AIC_FR_RFTH_LSB 24
register FR int RFTH goto (27, AIC_FR_RFTH_LSB)

// 
const AIC_FR_TFTH_LSB 16
register FR int TFTH goto (20, AIC_FR_TFTH_LSB)

// 
register CR export "AIC controller common control register"
register CR int PACK16 goto 28
register CR int RDMS goto 15
register CR int TDMS goto 14
register CR int M2S goto 11
register CR int ENDSW goto 10
register CR int AVSTSU goto 9
register CR int TFLUSH goto 8
register CR int RFLUSH goto 7
register CR int EROR goto 6
register CR int ETUR goto 5
register CR int ERFS goto 4
register CR int ETFS goto 3
register CR int ENLBF goto 2
register CR int ERPL goto 1
register CR int EREC goto 0

// 
const AIC_CR_CHANNEL_LSB 24
register CR int CHANNEL goto (26, AIC_CR_CHANNEL_LSB)

// 
const AIC_CR_OSS_LSB 19
register CR int OSS goto (21, AIC_CR_OSS_LSB)
//  #define AIC_CR_OSS(n)		(((n) > 18 ? (n)/6 : (n)/9) << AIC_CR_OSS_LSB)	/* n = 8, 16, 18, 20, 24 */

// 
const AIC_CR_ISS_LSB 16
register CR int ISS goto (18, AIC_CR_ISS_LSB)
//  #define AIC_CR_ISS(n)		(((n) > 18 ? (n)/6 : (n)/9) << AIC_CR_ISS_LSB)	/* n = 8, 16, 18, 20, 24 */

// 
register ACCR1 export "AIC controller AC-link control register 1"
const AIC_ACCR1_RS_LSB 16
register ACCR1 int RS goto (25, AIC_ACCR1_RS_LSB)
//  #define AIC_ACCR1_RS_SLOT(n)	((1 << ((n) - 3)) << AIC_ACCR1_RS_LSB)	/* n = 3 .. 12 */

// 
const AIC_ACCR1_XS_LSB 0
register ACCR1 int XS goto (9, AIC_ACCR1_XS_LSB)
//  #define AIC_ACCR1_XS_SLOT(n)	((1 << ((n) - 3)) << AIC_ACCR1_XS_LSB)	/* n = 3 .. 12 */

// 
register ACCR2 export "AIC controller AC-link control register 2"
register ACCR2 int ERSTO goto 18
register ACCR2 int ESADR goto 17
register ACCR2 int ECADT goto 16
register ACCR2 int SO goto 3
register ACCR2 int SR goto 2
register ACCR2 int SS goto 1
register ACCR2 int SA goto 0

// 
register I2SCR export "AIC controller i2s/msb-justified control register"
register I2SCR int RFIRST goto 17
register I2SCR int SWLH goto 16
register I2SCR int STPBK goto 12
register I2SCR int ESCLK goto 4
register I2SCR int AMSL goto 0

// 
register SR export "AIC controller FIFO status register"
register SR int ROR goto 6
register SR int TUR goto 5
register SR int RFS goto 4
register SR int TFS goto 3

// 
const AIC_SR_RFL_LSB 24
register SR int RFL goto (29, AIC_SR_RFL_LSB)

// 
const AIC_SR_TFL_LSB 8
register SR int TFL goto (13, AIC_SR_TFL_LSB)

// 
register ACSR export "AIC controller AC-link status register"
register ACSR int SLTERR goto 21
register ACSR int CRDY goto 20
register ACSR int CLPM goto 19
register ACSR int RSTO goto 18
register ACSR int SADR goto 17
register ACSR int CADT goto 16

// 
register I2SSR export "AIC controller I2S/MSB-justified status register"
register I2SSR int CHBSY goto 5
register I2SSR int TBSY goto 4
register I2SSR int RBSY goto 3
register I2SSR int BSY goto 2

// 
register ACCAR export "AIC controller AC97 codec command address register"
const AIC_ACCAR_CAR_LSB 0
register ACCAR int CAR goto (19, AIC_ACCAR_CAR_LSB)

// 

// 
register ACCDR export "AIC controller AC97 codec command data register"
const AIC_ACCDR_CDR_LSB 0
register ACCDR int CDR goto (19, AIC_ACCDR_CDR_LSB)

// 
/* AC97 read and write macro based on ACCAR and ACCDR */
// #define AC97_READ_CMD		BIT19
// #define AC97_WRITE_CMD		(BIT19 & ~BIT19)

// 
const AC97_INDEX_LSB 12
// #define AC97_INDEX_MASK		BITS_H2L(18, AC97_INDEX_LSB)

// 
const AC97_DATA_LSB 4
// #define AC97_DATA_MASK		BITS_H2L(19, AC97_DATA_LSB)

// 
register ACSAR export "AIC controller AC97 codec status address register"
const AIC_ACSAR_SAR_LSB 0
register ACSAR int SAR goto (19, AIC_ACSAR_SAR_LSB)

// 
register ACSDR export "AIC controller AC97 codec status data register"
const AIC_ACSDR_SDR_LSB 0
register ACSDR int SDR goto (19, AIC_ACSDR_SDR_LSB)

// 
register I2SDIV export "AIC controller I2S/MSB-justified clock divider register"
const AIC_I2SDIV_DIV_LSB 0
register I2SDIV int DIV goto (3, AIC_I2SDIV_DIV_LSB)

// 
register SPENA export "SPDIF enable register"
register SPENA int SPEN goto 0

// 
register SPCTRL export "SPDIF control register"
register SPCTRL int DMAEN goto 15
register SPCTRL int DTYPE goto 14
register SPCTRL int SIGN goto 13
register SPCTRL int INVALID goto 12
register SPCTRL int RST goto 11
register SPCTRL int SPDIFI2S goto 10
register SPCTRL int MTRIG goto 1
register SPCTRL int MFFUR goto 0

// 
register SPSTATE export "SPDIF state register"
register SPSTATE int BUSY goto 7
register SPSTATE int FTRIG goto 1
register SPSTATE int FUR goto 0

// 
const AIC_SPSTATE_FLVL_LSB 8
register SPSTATE int FLVL goto (14, AIC_SPSTATE_FLVL_LSB)

// 
register SPCFG1 export "SPDIF configure 1 register"
register SPCFG1 int INITLVL goto 17
register SPCFG1 int ZROVLD goto 16

// 
const AIC_SPCFG1_TRIG_LSB 12
register SPCFG1 int TRIG goto (13, AIC_SPCFG1_TRIG_LSB)
// #define AIC_SPCFG1_TRIG(n)	(((n) > 16 ? 3 : (n)/8) << AIC_SPCFG1_TRIG_LSB)	/* n = 4, 8, 16, 32 */

// 
const AIC_SPCFG1_SRCNUM_LSB 8
register SPCFG1 int SRCNUM goto (11, AIC_SPCFG1_SRCNUM_LSB)

// 
const AIC_SPCFG1_CH1NUM_LSB 4
register SPCFG1 int CH1NUM goto (7, AIC_SPCFG1_CH1NUM_LSB)

// 
const AIC_SPCFG1_CH2NUM_LSB 0
register SPCFG1 int CH2NUM goto (3, AIC_SPCFG1_CH2NUM_LSB)

// 
register SPCFG2 export "SPDIF configure 2 register"
register SPCFG2 int MAXWL goto 18
register SPCFG2 int PRE goto 3
register SPCFG2 int COPYN goto 2
register SPCFG2 int AUDION goto 1
register SPCFG2 int CONPRO goto 0

// 
const AIC_SPCFG2_FS_LSB 26
register SPCFG2 int FS goto (29, AIC_SPCFG2_FS_LSB)

// 
const AIC_SPCFG2_ORGFRQ_LSB 22
register SPCFG2 int ORGFRQ goto (25, AIC_SPCFG2_ORGFRQ_LSB)

// 
const AIC_SPCFG2_SAMWL_LSB 19
register SPCFG2 int SAMWL goto (21, AIC_SPCFG2_SAMWL_LSB)

// 
const AIC_SPCFG2_CLKACU_LSB 16
register SPCFG2 int CLKACU goto (17, AIC_SPCFG2_CLKACU_LSB)

// 
const AIC_SPCFG2_CATCODE_LSB 8
register SPCFG2 int CATCODE goto (15, AIC_SPCFG2_CATCODE_LSB)

// 
const AIC_SPCFG2_CHMD_LSB 6
register SPCFG2 int CHMD goto (7, AIC_SPCFG2_CHMD_LSB)

// 
register RGADW export "ICDC internal register access control register"
register RGADW int RGWR goto 16

// 
const AIC_RGADW_RGADDR_LSB 8
register RGADW int RGADDR goto (14, AIC_RGADW_RGADDR_LSB)

// 
const AIC_RGADW_RGDIN_LSB 0
register RGADW int RGDIN goto (7, AIC_RGADW_RGDIN_LSB)

// 
register RGDATA export "ICDC internal register data output register"
register RGDATA int IRQ goto 8

// 
const AIC_RGDATA_RGDOUT_LSB 0
register RGDATA int RGDOUT goto (7, AIC_RGDATA_RGDOUT_LSB)

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 

// 
register FR sizeof 32
register CR sizeof 32
register ACCR1 sizeof 32
register ACCR2 sizeof 32
register I2SCR sizeof 32
register SR sizeof 32
register ACSR sizeof 32
register I2SSR sizeof 32
register ACCAR sizeof 32
register ACCDR sizeof 32
register ACSAR sizeof 32
register ACSDR sizeof 32
register I2SDIV sizeof 32
register DR sizeof 32

// 
register SPENA sizeof 32
register SPCTRL sizeof 32
register SPSTATE sizeof 32
register SPCFG1 sizeof 32
register SPCFG2 sizeof 32
register SPFIFO sizeof 32

// 
register RGADW sizeof 32
register RGDATA sizeof 32

// 

// 
// #define __aic_enable()		( REG_AIC_FR |= AIC_FR_ENB )
// #define __aic_disable()		( REG_AIC_FR &= ~AIC_FR_ENB )

// 
// #define __aic_select_ac97()	( REG_AIC_FR &= ~AIC_FR_AUSEL )
// #define __aic_select_i2s()	( REG_AIC_FR |= AIC_FR_AUSEL )

// 
// #define __aic_play_zero()	( REG_AIC_FR &= ~AIC_FR_LSMP )
// #define __aic_play_lastsample()	( REG_AIC_FR |= AIC_FR_LSMP )

// 
// #define __i2s_as_master()	( REG_AIC_FR |= AIC_FR_BCKD | AIC_FR_SYNCD )
// #define __i2s_as_slave()	( REG_AIC_FR &= ~(AIC_FR_BCKD | AIC_FR_SYNCD) )
// #define __aic_reset_status()          ( REG_AIC_FR & AIC_FR_RST )

// 
// #define __aic_reset()                                   \
// do {                                                    \
//         REG_AIC_FR |= AIC_FR_RST;                       \
// } while(0)

// 

// 
// #define __aic_set_transmit_trigger(n) 			\
// do {							\
// 	REG_AIC_FR &= ~AIC_FR_TFTH_MASK;		\
// 	REG_AIC_FR |= ((n) << AIC_FR_TFTH_LSB);		\
// } while(0)

// 
// #define __aic_set_receive_trigger(n) 			\
// do {							\
// 	REG_AIC_FR &= ~AIC_FR_RFTH_MASK;		\
// 	REG_AIC_FR |= ((n) << AIC_FR_RFTH_LSB);		\
// } while(0)

// 
// #define __aic_enable_oldstyle()
// #define __aic_enable_newstyle()
// #define __aic_enable_pack16()   ( REG_AIC_CR |= AIC_CR_PACK16 )
// #define __aic_enable_unpack16() ( REG_AIC_CR &= ~AIC_CR_PACK16)

// 
/* n = AIC_CR_CHANNEL_MONO,AIC_CR_CHANNEL_STEREO ... */
// #define __aic_out_channel_select(n)                    \
// do {                                                   \
// 	REG_AIC_CR &= ~AIC_CR_CHANNEL_MASK;            \
//         REG_AIC_CR |= ((n) << AIC_CR_CHANNEL_LSB );			       \
// } while(0)

// 
// #define __aic_enable_record()	( REG_AIC_CR |= AIC_CR_EREC )
// #define __aic_disable_record()	( REG_AIC_CR &= ~AIC_CR_EREC )
// #define __aic_enable_replay()	( REG_AIC_CR |= AIC_CR_ERPL )
// #define __aic_disable_replay()	( REG_AIC_CR &= ~AIC_CR_ERPL )
// #define __aic_enable_loopback()	( REG_AIC_CR |= AIC_CR_ENLBF )
// #define __aic_disable_loopback() ( REG_AIC_CR &= ~AIC_CR_ENLBF )

// 
// #define __aic_flush_tfifo()	( REG_AIC_CR |= AIC_CR_TFLUSH )
// #define __aic_unflush_tfifo()	( REG_AIC_CR &= ~AIC_CR_TFLUSH )
// #define __aic_flush_rfifo()	( REG_AIC_CR |= AIC_CR_RFLUSH )
// #define __aic_unflush_rfifo()	( REG_AIC_CR &= ~AIC_CR_RFLUSH )

// 
// #define __aic_enable_transmit_intr() \
//   ( REG_AIC_CR |= (AIC_CR_ETFS | AIC_CR_ETUR) )
// #define __aic_disable_transmit_intr() \
//   ( REG_AIC_CR &= ~(AIC_CR_ETFS | AIC_CR_ETUR) )
// #define __aic_enable_receive_intr() \
//   ( REG_AIC_CR |= (AIC_CR_ERFS | AIC_CR_EROR) )
// #define __aic_disable_receive_intr() \
//   ( REG_AIC_CR &= ~(AIC_CR_ERFS | AIC_CR_EROR) )

// 
// #define __aic_enable_transmit_dma()  ( REG_AIC_CR |= AIC_CR_TDMS )
// #define __aic_disable_transmit_dma() ( REG_AIC_CR &= ~AIC_CR_TDMS )
// #define __aic_enable_receive_dma()   ( REG_AIC_CR |= AIC_CR_RDMS )
// #define __aic_disable_receive_dma()  ( REG_AIC_CR &= ~AIC_CR_RDMS )

// 
// #define __aic_enable_mono2stereo()   ( REG_AIC_CR |= AIC_CR_M2S )
// #define __aic_disable_mono2stereo()  ( REG_AIC_CR &= ~AIC_CR_M2S )
// #define __aic_enable_byteswap()      ( REG_AIC_CR |= AIC_CR_ENDSW )
// #define __aic_disable_byteswap()     ( REG_AIC_CR &= ~AIC_CR_ENDSW )
// #define __aic_enable_unsignadj()     ( REG_AIC_CR |= AIC_CR_AVSTSU )
// #define __aic_disable_unsignadj()    ( REG_AIC_CR &= ~AIC_CR_AVSTSU )

// 
// #define AC97_PCM_XS_L_FRONT   	AIC_ACCR1_XS_SLOT(3)
// #define AC97_PCM_XS_R_FRONT   	AIC_ACCR1_XS_SLOT(4)
// #define AC97_PCM_XS_CENTER    	AIC_ACCR1_XS_SLOT(6)
// #define AC97_PCM_XS_L_SURR    	AIC_ACCR1_XS_SLOT(7)
// #define AC97_PCM_XS_R_SURR    	AIC_ACCR1_XS_SLOT(8)
// #define AC97_PCM_XS_LFE       	AIC_ACCR1_XS_SLOT(9)

// 
// #define AC97_PCM_RS_L_FRONT   	AIC_ACCR1_RS_SLOT(3)
// #define AC97_PCM_RS_R_FRONT   	AIC_ACCR1_RS_SLOT(4)
// #define AC97_PCM_RS_CENTER    	AIC_ACCR1_RS_SLOT(6)
// #define AC97_PCM_RS_L_SURR    	AIC_ACCR1_RS_SLOT(7)
// #define AC97_PCM_RS_R_SURR    	AIC_ACCR1_RS_SLOT(8)
// #define AC97_PCM_RS_LFE       	AIC_ACCR1_RS_SLOT(9)

// 
// #define __ac97_set_xs_none()	( REG_AIC_ACCR1 &= ~AIC_ACCR1_XS_MASK )
// #define __ac97_set_xs_mono() 						\
// do {									\
// 	REG_AIC_ACCR1 &= ~AIC_ACCR1_XS_MASK;				\
// 	REG_AIC_ACCR1 |= AC97_PCM_XS_R_FRONT;				\
// } while(0)
// #define __ac97_set_xs_stereo() 						\
// do {									\
// 	REG_AIC_ACCR1 &= ~AIC_ACCR1_XS_MASK;				\
// 	REG_AIC_ACCR1 |= AC97_PCM_XS_L_FRONT | AC97_PCM_XS_R_FRONT;	\
// } while(0)

// 
/* In fact, only stereo is support now. */
// #define __ac97_set_rs_none()	( REG_AIC_ACCR1 &= ~AIC_ACCR1_RS_MASK )
// #define __ac97_set_rs_mono() 						\
// do {									\
// 	REG_AIC_ACCR1 &= ~AIC_ACCR1_RS_MASK;				\
// 	REG_AIC_ACCR1 |= AC97_PCM_RS_R_FRONT;				\
// } while(0)
// #define __ac97_set_rs_stereo() 						\
// do {									\
// 	REG_AIC_ACCR1 &= ~AIC_ACCR1_RS_MASK;				\
// 	REG_AIC_ACCR1 |= AC97_PCM_RS_L_FRONT | AC97_PCM_RS_R_FRONT;	\
// } while(0)

// 
// #define __ac97_warm_reset_codec()		\
//  do {						\
// 	REG_AIC_ACCR2 |= AIC_ACCR2_SA;		\
// 	REG_AIC_ACCR2 |= AIC_ACCR2_SS;		\
// 	udelay(2);				\
// 	REG_AIC_ACCR2 &= ~AIC_ACCR2_SS;		\
// 	REG_AIC_ACCR2 &= ~AIC_ACCR2_SA;		\
//  } while (0)

// 
// #define __ac97_cold_reset_codec()		\
//  do {						\
// 	REG_AIC_ACCR2 |=  AIC_ACCR2_SR;		\
// 	udelay(2);				\
// 	REG_AIC_ACCR2 &= ~AIC_ACCR2_SR;		\
//  } while (0)

// 
/* n=8,16,18,20 */
// #define __ac97_set_iass(n) \
//  ( REG_AIC_ACCR2 = (REG_AIC_ACCR2 & ~AIC_ACCR2_IASS_MASK) | AIC_ACCR2_IASS_##n##BIT )
// #define __ac97_set_oass(n) \
//  ( REG_AIC_ACCR2 = (REG_AIC_ACCR2 & ~AIC_ACCR2_OASS_MASK) | AIC_ACCR2_OASS_##n##BIT )

// 
/* This bit should only be set in 2 channels configuration */
// #define __i2s_send_rfirst()   ( REG_AIC_I2SCR |= AIC_I2SCR_RFIRST )  /* RL */
// #define __i2s_send_lfirst()   ( REG_AIC_I2SCR &= ~AIC_I2SCR_RFIRST ) /* LR */

// 
/* This bit should only be set in 2 channels configuration and 16bit-packed mode */
// #define __i2s_switch_lr()     ( REG_AIC_I2SCR |= AIC_I2SCR_SWLH )
// #define __i2s_unswitch_lr()   ( REG_AIC_I2SCR &= ~AIC_I2SCR_SWLH )

// 
// #define __i2s_select_i2s()            ( REG_AIC_I2SCR &= ~AIC_I2SCR_AMSL )
// #define __i2s_select_msbjustified()   ( REG_AIC_I2SCR |= AIC_I2SCR_AMSL )

// 
/* n=8,16,18,20,24 */
/*#define __i2s_set_sample_size(n) \
 ( REG_AIC_I2SCR |= (REG_AIC_I2SCR & ~AIC_I2SCR_WL_MASK) | AIC_I2SCR_WL_##n##BIT )*/

// 
// #define __i2s_out_channel_select(n) __aic_out_channel_select(n)

// 
// #define __i2s_set_oss_sample_size(n) \
//  ( REG_AIC_CR = (REG_AIC_CR & ~AIC_CR_OSS_MASK) | AIC_CR_OSS(n))
// #define __i2s_set_iss_sample_size(n) \
//  ( REG_AIC_CR = (REG_AIC_CR & ~AIC_CR_ISS_MASK) | AIC_CR_ISS(n))

// 
// #define __i2s_stop_bitclk()   ( REG_AIC_I2SCR |= AIC_I2SCR_STPBK )
// #define __i2s_start_bitclk()  ( REG_AIC_I2SCR &= ~AIC_I2SCR_STPBK )

// 
// #define __aic_transmit_request()  ( REG_AIC_SR & AIC_SR_TFS )
// #define __aic_receive_request()   ( REG_AIC_SR & AIC_SR_RFS )
// #define __aic_transmit_underrun() ( REG_AIC_SR & AIC_SR_TUR )
// #define __aic_receive_overrun()   ( REG_AIC_SR & AIC_SR_ROR )

// 
// #define __aic_clear_errors()      ( REG_AIC_SR &= ~(AIC_SR_TUR | AIC_SR_ROR) )

// 
// #define __aic_get_transmit_resident() \
//   ( (REG_AIC_SR & AIC_SR_TFL_MASK) >> AIC_SR_TFL_LSB )
// #define __aic_get_receive_count() \
//   ( (REG_AIC_SR & AIC_SR_RFL_MASK) >> AIC_SR_RFL_LSB )

// 
// #define __ac97_command_transmitted()     ( REG_AIC_ACSR & AIC_ACSR_CADT )
// #define __ac97_status_received()         ( REG_AIC_ACSR & AIC_ACSR_SADR )
// #define __ac97_status_receive_timeout()  ( REG_AIC_ACSR & AIC_ACSR_RSTO )
// #define __ac97_codec_is_low_power_mode() ( REG_AIC_ACSR & AIC_ACSR_CLPM )
// #define __ac97_codec_is_ready()          ( REG_AIC_ACSR & AIC_ACSR_CRDY )
// #define __ac97_slot_error_detected()     ( REG_AIC_ACSR & AIC_ACSR_SLTERR )
// #define __ac97_clear_slot_error()        ( REG_AIC_ACSR &= ~AIC_ACSR_SLTERR )

// 
// #define __i2s_is_busy()         ( REG_AIC_I2SSR & AIC_I2SSR_BSY )

// 
// #define __ac97_out_rcmd_addr(reg) 					\
// do { 									\
//     REG_AIC_ACCAR = AC97_READ_CMD | ((reg) << AC97_INDEX_LSB); 	\
// } while (0)

// 
// #define __ac97_out_wcmd_addr(reg) 					\
// do { 									\
//     REG_AIC_ACCAR = AC97_WRITE_CMD | ((reg) << AC97_INDEX_LSB); 	\
// } while (0)

// 
// #define __ac97_out_data(value) 						\
// do { 									\
//     REG_AIC_ACCDR = ((value) << AC97_DATA_LSB); 			\
// } while (0)

// 
// #define __ac97_in_data() \
//  ( (REG_AIC_ACSDR & CODEC_REG_DATA_MASK) >> AC97_DATA_LSB )

// 
// #define __ac97_in_status_addr() \
//  ( (REG_AIC_ACSAR & AC97_INDEX_MASK) >> AC97_INDEX_LSB )

// 
// #define __i2s_set_sample_rate(i2sclk, sync) \
//   ( REG_AIC_I2SDIV = ((i2sclk) / (4*64)) / (sync) )

// 
// #define __aic_write_tfifo(v)  ( REG_AIC_DR = (v) )
// #define __aic_read_rfifo()    ( REG_AIC_DR )

// 
// #define __aic_internal_codec()  ( REG_AIC_FR |= AIC_FR_ICDC )
// #define __aic_external_codec()  ( REG_AIC_FR &= ~AIC_FR_ICDC )

// 
//
// Define next ops for AC97 compatible
//

// 
// #define AC97_ACSR	AIC_ACSR

// 
// #define __ac97_enable()		__aic_enable(); __aic_select_ac97()
// #define __ac97_disable()	__aic_disable()
// #define __ac97_reset()		__aic_reset()

// 
// #define __ac97_set_transmit_trigger(n)	__aic_set_transmit_trigger(n)
// #define __ac97_set_receive_trigger(n)	__aic_set_receive_trigger(n)

// 
// #define __ac97_enable_record()		__aic_enable_record()
// #define __ac97_disable_record()		__aic_disable_record()
// #define __ac97_enable_replay()		__aic_enable_replay()
// #define __ac97_disable_replay()		__aic_disable_replay()
// #define __ac97_enable_loopback()	__aic_enable_loopback()
// #define __ac97_disable_loopback()	__aic_disable_loopback()

// 
// #define __ac97_enable_transmit_dma()	__aic_enable_transmit_dma()
// #define __ac97_disable_transmit_dma()	__aic_disable_transmit_dma()
// #define __ac97_enable_receive_dma()	__aic_enable_receive_dma()
// #define __ac97_disable_receive_dma()	__aic_disable_receive_dma()

// 
// #define __ac97_transmit_request()	__aic_transmit_request()
// #define __ac97_receive_request()	__aic_receive_request()
// #define __ac97_transmit_underrun()	__aic_transmit_underrun()
// #define __ac97_receive_overrun()	__aic_receive_overrun()

// 
// #define __ac97_clear_errors()		__aic_clear_errors()

// 
// #define __ac97_get_transmit_resident()	__aic_get_transmit_resident()
// #define __ac97_get_receive_count()	__aic_get_receive_count()

// 
// #define __ac97_enable_transmit_intr()	__aic_enable_transmit_intr()
// #define __ac97_disable_transmit_intr()	__aic_disable_transmit_intr()
// #define __ac97_enable_receive_intr()	__aic_enable_receive_intr()
// #define __ac97_disable_receive_intr()	__aic_disable_receive_intr()

// 
// #define __ac97_write_tfifo(v)		__aic_write_tfifo(v)
// #define __ac97_read_rfifo()		__aic_read_rfifo()

// 
//
// Define next ops for I2S compatible
//

// 
// #define I2S_ACSR	AIC_I2SSR

// 
// #define __i2s_enable()		 __aic_enable(); __aic_select_i2s()
// #define __i2s_disable()		__aic_disable()
// #define __i2s_reset()		__aic_reset()

// 
// #define __i2s_set_transmit_trigger(n)	__aic_set_transmit_trigger(n)
// #define __i2s_set_receive_trigger(n)	__aic_set_receive_trigger(n)

// 
// #define __i2s_enable_record()		__aic_enable_record()
// #define __i2s_disable_record()		__aic_disable_record()
// #define __i2s_enable_replay()		__aic_enable_replay()
// #define __i2s_disable_replay()		__aic_disable_replay()
// #define __i2s_enable_loopback()		__aic_enable_loopback()
// #define __i2s_disable_loopback()	__aic_disable_loopback()

// 
// #define __i2s_enable_transmit_dma()	__aic_enable_transmit_dma()
// #define __i2s_disable_transmit_dma()	__aic_disable_transmit_dma()
// #define __i2s_enable_receive_dma()	__aic_enable_receive_dma()
// #define __i2s_disable_receive_dma()	__aic_disable_receive_dma()

// 
// #define __i2s_transmit_request()	__aic_transmit_request()
// #define __i2s_receive_request()		__aic_receive_request()
// #define __i2s_transmit_underrun()	__aic_transmit_underrun()
// #define __i2s_receive_overrun()		__aic_receive_overrun()

// 
// #define __i2s_clear_errors()		__aic_clear_errors()

// 
// #define __i2s_get_transmit_resident()	__aic_get_transmit_resident()
// #define __i2s_get_receive_count()	__aic_get_receive_count()

// 
// #define __i2s_enable_transmit_intr()	__aic_enable_transmit_intr()
// #define __i2s_disable_transmit_intr()	__aic_disable_transmit_intr()
// #define __i2s_enable_receive_intr()	__aic_enable_receive_intr()
// #define __i2s_disable_receive_intr()	__aic_disable_receive_intr()

// 
// #define __i2s_write_tfifo(v)		__aic_write_tfifo(v)
// #define __i2s_read_rfifo()		__aic_read_rfifo()

// 
// #define __i2s_reset_codec()			\
//  do {						\
//  } while (0)

// 

// 
/*************************************************************************
 * SPDIF INTERFACE in AIC Controller
 *************************************************************************/

// 
// #define __spdif_enable()        ( REG_AIC_SPENA |= AIC_SPENA_SPEN )
// #define __spdif_disable()       ( REG_AIC_SPENA &= ~AIC_SPENA_SPEN )

// 
// #define __spdif_enable_transmit_dma()     ( REG_AIC_SPCTRL |= AIC_SPCTRL_DMAEN )
// #define __spdif_disable_transmit_dma()    ( REG_AIC_SPCTRL &= ~AIC_SPCTRL_DMAEN )
// #define __spdif_enable_dtype()            ( REG_AIC_SPCTRL |= AIC_SPCTRL_DTYPE )
// #define __spdif_disable_dtype()           ( REG_AIC_SPCTRL &= ~AIC_SPCTRL_DTYPE )
// #define __spdif_enable_sign()             ( REG_AIC_SPCTRL |= AIC_SPCTRL_SIGN )
// #define __spdif_disable_sign()            ( REG_AIC_SPCTRL &= ~AIC_SPCTRL_SIGN )
// #define __spdif_enable_invalid()          ( REG_AIC_SPCTRL |= AIC_SPCTRL_INVALID )
// #define __spdif_disable_invalid()         ( REG_AIC_SPCTRL &= ~AIC_SPCTRL_INVALID )
// #define __spdif_enable_reset()            ( REG_AIC_SPCTRL |= AIC_SPCTRL_RST )
// #define __spdif_select_spdif()            ( REG_AIC_SPCTRL |= AIC_SPCTRL_SPDIFI2S )
// #define __spdif_select_i2s()              ( REG_AIC_SPCTRL &= ~AIC_SPCTRL_SPDIFI2S )
// #define __spdif_enable_MTRIGmask()        ( REG_AIC_SPCTRL |= AIC_SPCTRL_MTRIG )
// #define __spdif_disable_MTRIGmask()       ( REG_AIC_SPCTRL &= ~AIC_SPCTRL_MTRIG )
// #define __spdif_enable_MFFURmask()        ( REG_AIC_SPCTRL |= AIC_SPCTRL_MFFUR )
// #define __spdif_disable_MFFURmask()       ( REG_AIC_SPCTRL &= ~AIC_SPCTRL_MFFUR )

// 
// #define __spdif_enable_initlvl_high()     ( REG_AIC_SPCFG1 |=  AIC_SPCFG1_INITLVL )
// #define __spdif_enable_initlvl_low()      ( REG_AIC_SPCFG1 &=  ~AIC_SPCFG1_INITLVL )
// #define __spdif_enable_zrovld_invald()    ( REG_AIC_SPCFG1 |=  AIC_SPCFG1_ZROVLD )
// #define __spdif_enable_zrovld_vald()      ( REG_AIC_SPCFG1 &=  ~AIC_SPCFG1_ZROVLD )

// 
/* 0, 1, 2, 3 */
// #define __spdif_set_transmit_trigger(n)			\
// do {							\
// 	REG_AIC_SPCFG1 &= ~AIC_SPCFG1_TRIG_MASK;	\
// 	REG_AIC_SPCFG1 |= AIC_SPCFG1_TRIG(n);	\
// } while(0)

// 
/* 1 ~ 15 */
// #define __spdif_set_srcnum(n)    			\
// do {							\
// 	REG_AIC_SPCFG1 &= ~AIC_SPCFG1_SRCNUM_MASK;	\
// 	REG_AIC_SPCFG1 |= ((n) << AIC_SPCFG1_SRCNUM_LSB);	\
// } while(0)

// 
/* 1 ~ 15 */
// #define __spdif_set_ch1num(n)    			\
// do {							\
// 	REG_AIC_SPCFG1 &= ~AIC_SPCFG1_CH1NUM_MASK;	\
// 	REG_AIC_SPCFG1 |= ((n) << AIC_SPCFG1_CH1NUM_LSB);	\
// } while(0)

// 
/* 1 ~ 15 */
// #define __spdif_set_ch2num(n)    			\
// do {							\
// 	REG_AIC_SPCFG1 &= ~AIC_SPCFG1_CH2NUM_MASK;	\
// 	REG_AIC_SPCFG1 |= ((n) << AIC_SPCFG1_CH2NUM_LSB);	\
// } while(0)

// 
/* 0x0, 0x2, 0x3, 0xa, 0xe */
// #define __spdif_set_fs(n)				\
// do {							\
// 	REG_AIC_SPCFG2 &= ~AIC_SPCFG2_FS_MASK;   	\
// 	REG_AIC_SPCFG2 |= ((n) << AIC_SPCFG2_FS_LSB);	\
// } while(0)

// 
/* 0xd, 0xc, 0x5, 0x1 */
// #define __spdif_set_orgfrq(n)				\
// do {							\
// 	REG_AIC_SPCFG2 &= ~AIC_SPCFG2_ORGFRQ_MASK;   	\
// 	REG_AIC_SPCFG2 |= ((n) << AIC_SPCFG2_ORGFRQ_LSB);	\
// } while(0)

// 
/* 0x1, 0x6, 0x2, 0x4, 0x5 */
// #define __spdif_set_samwl(n)				\
// do {							\
// 	REG_AIC_SPCFG2 &= ~AIC_SPCFG2_SAMWL_MASK;   	\
// 	REG_AIC_SPCFG2 |= ((n) << AIC_SPCFG2_SAMWL_LSB);	\
// } while(0)

// 
// #define __spdif_enable_samwl_24()    ( REG_AIC_SPCFG2 |= AIC_SPCFG2_MAXWL )
// #define __spdif_enable_samwl_20()    ( REG_AIC_SPCFG1 &= ~AIC_SPCFG2_MAXWL )

// 
/* 0x1, 0x1, 0x2, 0x3 */
// #define __spdif_set_clkacu(n)				\
// do {							\
// 	REG_AIC_SPCFG2 &= ~AIC_SPCFG2_CLKACU_MASK;   	\
// 	REG_AIC_SPCFG2 |= ((n) << AIC_SPCFG2_CLKACU_LSB);	\
// } while(0)

// 
/* see IEC60958-3 */
// #define __spdif_set_catcode(n)				\
// do {							\
// 	REG_AIC_SPCFG2 &= ~AIC_SPCFG2_CATCODE_MASK;   	\
// 	REG_AIC_SPCFG2 |= ((n) << AIC_SPCFG2_CATCODE_LSB);	\
// } while(0)

// 
/* n = 0x0, */
// #define __spdif_set_chmode(n)				\
// do {							\
// 	REG_AIC_SPCFG2 &= ~AIC_SPCFG2_CHMD_MASK;   	\
// 	REG_AIC_SPCFG2 |= ((n) << AIC_SPCFG2_CHMD_LSB);	\
// } while(0)

// 
// #define __spdif_enable_pre()       ( REG_AIC_SPCFG2 |= AIC_SPCFG2_PRE )
// #define __spdif_disable_pre()      ( REG_AIC_SPCFG2 &= ~AIC_SPCFG2_PRE )
// #define __spdif_enable_copyn()     ( REG_AIC_SPCFG2 |= AIC_SPCFG2_COPYN )
// #define __spdif_disable_copyn()    ( REG_AIC_SPCFG2 &= ~AIC_SPCFG2_COPYN )
/* audio sample word represents linear PCM samples */
// #define __spdif_enable_audion()    ( REG_AIC_SPCFG2 &= ~AIC_SPCFG2_AUDION )
/* udio sample word used for other purpose */
// #define __spdif_disable_audion()   ( REG_AIC_SPCFG2 |= AIC_SPCFG2_AUDION )
// #define __spdif_enable_conpro()    ( REG_AIC_SPCFG2 &= ~AIC_SPCFG2_CONPRO )
// #define __spdif_disable_conpro()   ( REG_AIC_SPCFG2 |= AIC_SPCFG2_CONPRO )

// 
/***************************************************************************
 * ICDC
 ***************************************************************************/
// #define __i2s_internal_codec()         __aic_internal_codec()
// #define __i2s_external_codec()         __aic_external_codec()

// 
// #define __icdc_clk_ready()             ( REG_AIC_CKCFG & AIC_CKCFG_CKRDY )
// #define __icdc_sel_adc()               ( REG_AIC_CKCFG |= AIC_CKCFG_SELAD )
// #define __icdc_sel_dac()               ( REG_AIC_CKCFG &= ~AIC_CKCFG_SELAD )

// 
// #define __icdc_set_rgwr()              ( REG_AIC_RGADW |= AIC_RGADW_RGWR )
// #define __icdc_clear_rgwr()            ( REG_AIC_RGADW &= ~AIC_RGADW_RGWR )
// #define __icdc_rgwr_ready()            ( REG_AIC_RGADW & AIC_RGADW_RGWR )

// 
// #define __icdc_set_addr(n)				\
// do {          						\
// 	REG_AIC_RGADW &= ~AIC_RGADW_RGADDR_MASK;	\
// 	REG_AIC_RGADW |= (n) << AIC_RGADW_RGADDR_LSB;	\
// } while(0)

// 
// #define __icdc_set_cmd(n)				\
// do {          						\
// 	REG_AIC_RGADW &= ~AIC_RGADW_RGDIN_MASK;	\
// 	REG_AIC_RGADW |= (n) << AIC_RGADW_RGDIN_LSB;	\
// } while(0)

// 
// #define __icdc_irq_pending()            ( REG_AIC_RGDATA & AIC_RGDATA_IRQ )
// #define __icdc_get_value()              ( REG_AIC_RGDATA & AIC_RGDATA_RGDOUT_MASK )

// 

// 

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __CHIP_AIC_H__ */
