/*
 * chip-pcm.h
 * JZ4760 PCM register definition
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 *
 * Author: whxu@ingenic.cn
 */

// 
// #ifndef __CHIP_PCM_H__
// #define __CHIP_PCM_H__

// 

// 
//#define	PCM_BASE        0xb0071000
/* Pulse-code modulation module(PCM) address definition */
this class PCM goto (0, 0xb0071000) export "Pulse-code modulation module(PCM) address definition"
this class PCM goto (1, 0xb0074000)
for n 0 1

// 

// 
/*
 * PCM registers offset address definition
 */
const PCM_PCTL_OFFSET 0x00
const PCM_PCFG_OFFSET 0x04
const PCM_PDP_OFFSET 0x08
const PCM_PINTC_OFFSET 0x0c
const PCM_PINTS_OFFSET 0x10
const PCM_PDIV_OFFSET 0x14

// 

// 
/*
 * PCM registers address definition
 */
register PCTL goto<n> "0x3000 * (n) + PCM_PCTL_OFFSET" export ""
register PCFG goto<n> "0x3000 * (n) + PCM_PCFG_OFFSET" export ""
register PDP goto<n> "0x3000 * (n) + PCM_PDP_OFFSET" export ""
register PINTC goto<n> "0x3000 * (n) + PCM_PINTC_OFFSET" export ""
register PINTS goto<n> "0x3000 * (n) + PCM_PINTS_OFFSET" export ""
register PDIV goto<n> "0x3000 * (n) + PCM_PDIV_OFFSET" export ""

// 

// 
/*
 * CPM registers common define
 */

// 
register PCTL export "PCM controller control register"
register PCTL int ERDMA goto 9
register PCTL int ETDMA goto 8
register PCTL int LSMP goto 7
register PCTL int ERPL goto 6
register PCTL int EREC goto 5
register PCTL int FLUSH goto 4
register PCTL int RST goto 3
register PCTL int CLKEN goto 1
register PCTL int PCMEN goto 0

// 
register PCFG export "PCM controller configure register"
const PCM_PCFG_SLOT_BIT 13
register PCFG int SLOT goto (14, PCM_PCFG_SLOT_BIT)
// #define PCM_PCFG_SLOT(n)		((n) << PCM_PCFG_SLOT_BIT)

// 
register PCFG int ISS_16BIT goto 12
register PCFG int OSS_16BIT goto 11
register PCFG int IMSBPOS goto 10
register PCFG int OMSBPOS goto 9

// 
const PCM_PCFG_RFTH_BIT 5
register PCFG int RFTH goto (8, PCM_PCFG_RFTH_BIT)

// 
const PCM_PCFG_TFTH_BIT 1
register PCFG int TFTH goto (4, PCM_PCFG_TFTH_BIT)

// 
register PCFG int MODE_SLAVE goto 0

// 
register PINTC export "PCM controller interrupt control register"
register PINTC int ETFS goto 3
register PINTC int ETUR goto 2
register PINTC int ERFS goto 1
register PINTC int EROR goto 0

// 
register PINTS export "PCM controller interrupt status register"
register PINTS int RSTS goto 14

// 
const PCM_PINTS_TFL_BIT 9
register PINTS int TFL goto (13, PCM_PINTS_TFL_BIT)

// 
register PINTS int TFS goto 8
register PINTS int TUR goto 7

// 
const PCM_PINTS_RFL_BIT 2
register PINTS int RFL goto (6, PCM_PINTS_RFL_BIT)

// 
register PINTS int RFS goto 1
register PINTS int ROR goto 0

// 
register PDIV export "PCM controller clock division register"
const PCM_PDIV_SYNL_BIT 11
register PDIV int SYNL goto (16, PCM_PDIV_SYNL_BIT)

// 
const PCM_PDIV_SYNDIV_BIT 6
register PDIV int SYNDIV goto (10, PCM_PDIV_SYNDIV_BIT)

// 
const PCM_PDIV_CLKDIV_BIT 0
register PDIV int CLKDIV goto (5, PCM_PDIV_CLKDIV_BIT)

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 

// 
register PCTL sizeof 32
register PCFG sizeof 32
register PDP sizeof 32
register PINTC sizeof 32
register PINTS sizeof 32
register PDIV sizeof 32

// 
/*
 * PCM_DIN, PCM_DOUT, PCM_CLK, PCM_SYN
 */
// #define __gpio_as_pcm0()				\
// 	do {						\
// 		unsigned int bits = BITS_H2L(3, 0);	\
// 		REG_GPIO_PXFUNS(3) = bits;		\
// 		REG_GPIO_PXSELC(3) = bits;		\
// 		REG_GPIO_PXTRGC(3) = bits; 		\
// 		REG_GPIO_PXPES(3)  = bits; 		\
// 	} while (0)

// 
// #define __gpio_as_pcm1()			\
// 	do {					\
// 		__gpio_as_func2(GPD(12));	\
// 		__gpio_as_func3(GPE(5));	\
// 		__gpio_as_func1(GPE(8));	\
// 		__gpio_as_func1(GPE(9));	\
// 	} while(0)

// 
// #define __pcm_enable(n)          (REG_PCM_PCTL(n) |= PCM_PCTL_PCMEN)
// #define __pcm_disable(n)         (REG_PCM_PCTL(n) &= ~PCTL_PCMEN)

// 
// #define __pcm_clk_enable(n)      (REG_PCM_PCTL(n) |= PCM_PCTL_CLKEN)
// #define __pcm_clk_disable(n)     (REG_PCM_PCTL(n) &= ~PCTL_CLKEN)

// 
// #define __pcm_reset(n)           (REG_PCM_PCTL(n) |= PCM_PCTL_RST)
// #define __pcm_flush_fifo(n)	(REG_PCM_PCTL(n) |= PCM_PCTL_FLUSH)

// 
// #define __pcm_enable_record(n)		(REG_PCM_PCTL(n) |= PCM_PCTL_EREC)
// #define __pcm_disable_record(n)		(REG_PCM_PCTL(n) &= ~PCTL_EREC)
// #define __pcm_enable_playback(n)		(REG_PCM_PCTL(n) |= PCM_PCTL_ERPL)
// #define __pcm_disable_playback(n)	(REG_PCM_PCTL(n) &= ~PCTL_ERPL)

// 
// #define __pcm_enable_rxfifo(n)           __pcm_enable_record(n)
// #define __pcm_disable_rxfifo(n)          __pcm_disable_record(n)
// #define __pcm_enable_txfifo(n)           __pcm_enable_playback(n)
// #define __pcm_disable_txfifo(n)          __pcm_disable_playback(n)

// 
// #define __pcm_last_sample(n)     (REG_PCM_PCTL(n) |= PCM_PCTL_LSMP)
// #define __pcm_zero_sample(n)     (REG_PCM_PCTL(n) &= ~PCTL_LSMP)

// 
// #define __pcm_enable_transmit_dma(n)    (REG_PCM_PCTL(n) |= PCM_PCTL_ETDMA)
// #define __pcm_disable_transmit_dma(n)   (REG_PCM_PCTL(n) &= ~PCTL_ETDMA)
// #define __pcm_enable_receive_dma(n)     (REG_PCM_PCTL(n) |= PCM_PCTL_ERDMA)
// #define __pcm_disable_receive_dma(n)    (REG_PCM_PCTL(n) &= ~PCTL_ERDMA)

// 
// #define __pcm_as_master(n)     (REG_PCM_PCFG(n) &= ~PCFG_MODE_SLAVE)
// #define __pcm_as_slave(n)      (REG_PCM_PCFG(n) |= PCM_PCFG_MODE_SLAVE)

// 
// #define __pcm_set_transmit_trigger(idx, n)		\
// 	do {						\
// 		REG_PCM_PCFG(idx) &= ~PCFG_TFTH_MASK;	\
// 		REG_PCM_PCFG(idx) |= ((n) << PCM_PCFG_TFTH_BIT);	\
// 	} while(0)

// 
// #define __pcm_set_receive_trigger(idx, n)		\
// 	do {						\
// 		REG_PCM_PCFG(idx) &= ~PCFG_RFTH_MASK;	\
// 		REG_PCM_PCFG(idx) |= ((n) << PCM_PCFG_RFTH_BIT);	\
// 	} while(0)

// 
// #define __pcm_omsb_same_sync(n)   (REG_PCM_PCFG(n) &= ~PCFG_OMSBPOS)
// #define __pcm_omsb_next_sync(n)   (REG_PCM_PCFG(n) |= PCM_PCFG_OMSBPOS)

// 
// #define __pcm_imsb_same_sync(n)   (REG_PCM_PCFG(n) &= ~PCFG_IMSBPOS)
// #define __pcm_imsb_next_sync(n)   (REG_PCM_PCFG(n) |= PCM_PCFG_IMSBPOS)

// 
// #define __pcm_set_iss(idx,n)					\
// 	do {							\
// 		if (n == 16)					\
// 			REG_PCM_PCFG(idx) |= PCM_PCFG_ISS_16BIT;	\
// 		else						\
// 			REG_PCM_PCFG(idx) &= ~PCFG_ISS_16BIT;	\
// 	} while(0)

// 

// 
// #define __pcm_set_oss(idx, n)					\
// 	do {							\
// 		if (n == 16)					\
// 			REG_PCM_PCFG(idx) |= PCM_PCFG_OSS_16BIT;	\
// 		else						\
// 			REG_PCM_PCFG(idx) &= ~PCFG_OSS_16BIT;	\
// 	} while(0)

// 
// #define __pcm_set_valid_slot(idx, n)					\
// 	do {								\
// 		REG_PCM_PCFG((idx)) = (REG_PCM_PCFG((idx)) & ~PCFG_SLOT_MASK) | ((n) << PCM_PCFG_SLOT_BIT); \
// 	} while(0)							\

// 
// #define __pcm_write_data(idx, v)	(REG_PCM_PDP(idx) = (v))
// #define __pcm_read_data(idx)	(REG_PCM_PDP(idx))

// 
// #define __pcm_enable_tfs_intr(n)	(REG_PCM_PINTC(n) |= PCM_PINTC_ETFS)
// #define __pcm_disable_tfs_intr(n)	(REG_PCM_PINTC(n) &= ~PINTC_ETFS)

// 
// #define __pcm_enable_tur_intr(n)	(REG_PCM_PINTC(n) |= PCM_PINTC_ETUR)
// #define __pcm_disable_tur_intr(n)	(REG_PCM_PINTC(n) &= ~PINTC_ETUR)

// 
// #define __pcm_enable_rfs_intr(n)	(REG_PCM_PINTC(n) |= PCM_PINTC_ERFS)
// #define __pcm_disable_rfs_intr(n)	(REG_PCM_PINTC(n) &= ~PINTC_ERFS)

// 
// #define __pcm_enable_ror_intr(n)	(REG_PCM_PINTC(n) |= PCM_PINTC_EROR)
// #define __pcm_disable_ror_intr(n)	(REG_PCM_PINTC(n) &= ~PINTC_EROR)

// 
// #define __pcm_ints_valid_tx(n)	(((REG_PCM_PINTS(n) & PCM_PINTSTFL_MASK) >> PCM_PINTSTFL_BIT))
// #define __pcm_ints_valid_rx(n)	(((REG_PCM_PINTS(n) & PCM_PINTSRFL_MASK) >> PCM_PINTSRFL_BIT))

// 
// #define __pcm_set_clk_div(idx, n)					\
// 	(REG_PCM_PDIV(idx) = (REG_PCM_PDIV(idx) & ~PDIV_CLKDIV_MASK) | ((n) << PCM_PDIV_CLKDIV_BIT))

// 
// #define __pcm_set_clk_rate(idx, sysclk, pcmclk)		\
// 	__pcm_set_clk_div(idx, ((sysclk) / (pcmclk) - 1))

// 
// #define __pcm_set_sync_div(idx, n)					\
// 	do {								\
// 		REG_PCM_PDIV(idx) = (REG_PCM_PDIV(idx) & ~PDIV_SYNDIV_MASK) | ((n) << PCM_PDIV_SYNDIV_BIT);	\
// 	} while(0)

// 
// #define __pcm_set_sync_rate(idx, pcmclk, sync)			\
// 	__pcm_set_sync_div(idx, ((pcmclk) / (8 * (sync)) - 1))

// 
// #define __pcm_set_sync_len(idx, n)					\
// 	do {								\
// 		REG_PCM_PDIV(idx) = (REG_PCM_PDIV(idx) & (~PDIV_SYNL_MASK)) | ((n) << PCM_PDIV_SYNL_BIT); \
// 	} while(0)

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __CHIP_PCM_H__ */