/*
 * chip-pcm.h
 * JZ4760 PCM register definition
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 *
 * Author: whxu@ingenic.cn
 */

#ifndef __CHIP_PCM_H__
#define __CHIP_PCM_H__


//#define	PCM_BASE        0xb0071000
/* Pulse-code modulation module(PCM) address definition */
#define PCM_BASE(0)	0xb0071000
#define PCM_BASE(1)	0xb0074000
/* n is block index (0-1) */


/*
 * PCM registers offset address definition
 */
#define PCM_PCTL_OFFSET		(0x00)	/* rw, 32, 0x00000000 */
#define PCM_PCFG_OFFSET		(0x04)  /* rw, 32, 0x00000110 */
#define PCM_PDP_OFFSET		(0x08)  /* rw, 32, 0x00000000 */
#define PCM_PINTC_OFFSET	(0x0c)  /* rw, 32, 0x00000000 */
#define PCM_PINTS_OFFSET	(0x10)  /* rw, 32, 0x00000100 */
#define PCM_PDIV_OFFSET		(0x14)  /* rw, 32, 0x00000001 */


/*
 * PCM registers address definition
 */
#define PCM_PCTL	(PCM_BASE  + PCM_PCTL_OFFSET)
#define PCM_PCFG	(PCM_BASE  + PCM_PCFG_OFFSET)
#define PCM_PDP	(PCM_BASE  + PCM_PDP_OFFSET)
#define PCM_PINTC	(PCM_BASE  + PCM_PINTC_OFFSET)
#define PCM_PINTS	(PCM_BASE  + PCM_PINTS_OFFSET)
#define PCM_PDIV	(PCM_BASE  + PCM_PDIV_OFFSET)


/*
 * CPM registers common define
 */

/* PCM controller control register (PCTL) */
#define PCM_PCTL_ERDMA	BIT9
#define PCM_PCTL_ETDMA	BIT8
#define PCM_PCTL_LSMP	BIT7
#define PCM_PCTL_ERPL	BIT6
#define PCM_PCTL_EREC	BIT5
#define PCM_PCTL_FLUSH	BIT4
#define PCM_PCTL_RST	BIT3
#define PCM_PCTL_CLKEN	BIT1
#define PCM_PCTL_PCMEN	BIT0

/* PCM controller configure register (PCFG) */
#define PCM_PCFG_SLOT_BIT		13
#define PCM_PCFG_SLOT_MASK		BITS_H2L(14, PCM_PCFG_SLOT_BIT)
#define PCM_PCFG_SLOT(n)		((n) << PCM_PCFG_SLOT_BIT)

#define PCM_PCFG_ISS_16BIT		BIT12
#define PCM_PCFG_OSS_16BIT		BIT11
#define PCM_PCFG_IMSBPOS		BIT10
#define PCM_PCFG_OMSBPOS		BIT9

#define PCM_PCFG_RFTH_BIT		5
#define PCM_PCFG_RFTH_MASK		BITS_H2L(8, PCM_PCFG_RFTH_BIT)

#define PCM_PCFG_TFTH_BIT		1
#define PCM_PCFG_TFTH_MASK		BITS_H2L(4, PCM_PCFG_TFTH_BIT)

#define PCM_PCFG_MODE_SLAVE		BIT0

/* PCM controller interrupt control register(PINTC) */
#define PCM_PINTC_ETFS	BIT3
#define PCM_PINTC_ETUR	BIT2
#define PCM_PINTC_ERFS	BIT1
#define PCM_PINTC_EROR	BIT0

/* PCM controller interrupt status register(PINTS) */
#define PCM_PINTS_RSTS	BIT14

#define PCM_PINTS_TFL_BIT		9
#define PCM_PINTS_TFL_MASK		BITS_H2L(13, PCM_PINTS_TFL_BIT)

#define PCM_PINTS_TFS	BIT8
#define PCM_PINTS_TUR	BIT7

#define PCM_PINTS_RFL_BIT		2
#define PCM_PINTS_RFL_MASK		BITS_H2L(6, PCM_PINTS_RFL_BIT)

#define PCM_PINTS_RFS	BIT1
#define PCM_PINTS_ROR	BIT0

/* PCM controller clock division register(PDIV) */
#define PCM_PDIV_SYNL_BIT		11
#define PCM_PDIV_SYNL_MASK		BITS_H2L(16, PCM_PDIV_SYNL_BIT)

#define PCM_PDIV_SYNDIV_BIT		6
#define PCM_PDIV_SYNDIV_MASK	BITS_H2L(10, PCM_PDIV_SYNDIV_BIT)

#define PCM_PDIV_CLKDIV_BIT		0
#define PCM_PDIV_CLKDIV_MASK	BITS_H2L(5, PCM_PDIV_CLKDIV_BIT)


#ifndef __MIPS_ASSEMBLER


#define REG_PCM_PCTL(n)		REG32(PCM_PCTL(n))
#define REG_PCM_PCFG(n)		REG32(PCM_PCFG(n))
#define REG_PCM_PDP(n)		REG32(PCM_PDP(n))
#define REG_PCM_PINTC(n)	REG32(PCM_PINTC(n))
#define REG_PCM_PINTS(n)	REG32(PCM_PINTS(n))
#define REG_PCM_PDIV(n)		REG32(PCM_PDIV(n))

/*
 * PCM_DIN, PCM_DOUT, PCM_CLK, PCM_SYN
 */
#define __gpio_as_pcm0()				\
	do {						\
		unsigned int bits = BITS_H2L(3, 0);	\
		REG_GPIO_PXFUNS(3) = bits;		\
		REG_GPIO_PXSELC(3) = bits;		\
		REG_GPIO_PXTRGC(3) = bits; 		\
		REG_GPIO_PXPES(3)  = bits; 		\
	} while (0)

#define __gpio_as_pcm1()			\
	do {					\
		__gpio_as_func2(GPD(12));	\
		__gpio_as_func3(GPE(5));	\
		__gpio_as_func1(GPE(8));	\
		__gpio_as_func1(GPE(9));	\
	} while(0)

#define __pcm_enable(n)          (REG_PCM_PCTL(n) |= PCM_PCTL_PCMEN)
#define __pcm_disable(n)         (REG_PCM_PCTL(n) &= ~PCTL_PCMEN)

#define __pcm_clk_enable(n)      (REG_PCM_PCTL(n) |= PCM_PCTL_CLKEN)
#define __pcm_clk_disable(n)     (REG_PCM_PCTL(n) &= ~PCTL_CLKEN)

#define __pcm_reset(n)           (REG_PCM_PCTL(n) |= PCM_PCTL_RST)
#define __pcm_flush_fifo(n)	(REG_PCM_PCTL(n) |= PCM_PCTL_FLUSH)

#define __pcm_enable_record(n)		(REG_PCM_PCTL(n) |= PCM_PCTL_EREC)
#define __pcm_disable_record(n)		(REG_PCM_PCTL(n) &= ~PCTL_EREC)
#define __pcm_enable_playback(n)		(REG_PCM_PCTL(n) |= PCM_PCTL_ERPL)
#define __pcm_disable_playback(n)	(REG_PCM_PCTL(n) &= ~PCTL_ERPL)

#define __pcm_enable_rxfifo(n)           __pcm_enable_record(n)
#define __pcm_disable_rxfifo(n)          __pcm_disable_record(n)
#define __pcm_enable_txfifo(n)           __pcm_enable_playback(n)
#define __pcm_disable_txfifo(n)          __pcm_disable_playback(n)

#define __pcm_last_sample(n)     (REG_PCM_PCTL(n) |= PCM_PCTL_LSMP)
#define __pcm_zero_sample(n)     (REG_PCM_PCTL(n) &= ~PCTL_LSMP)

#define __pcm_enable_transmit_dma(n)    (REG_PCM_PCTL(n) |= PCM_PCTL_ETDMA)
#define __pcm_disable_transmit_dma(n)   (REG_PCM_PCTL(n) &= ~PCTL_ETDMA)
#define __pcm_enable_receive_dma(n)     (REG_PCM_PCTL(n) |= PCM_PCTL_ERDMA)
#define __pcm_disable_receive_dma(n)    (REG_PCM_PCTL(n) &= ~PCTL_ERDMA)

#define __pcm_as_master(n)     (REG_PCM_PCFG(n) &= ~PCFG_MODE_SLAVE)
#define __pcm_as_slave(n)      (REG_PCM_PCFG(n) |= PCM_PCFG_MODE_SLAVE)

#define __pcm_set_transmit_trigger(idx, n)		\
	do {						\
		REG_PCM_PCFG(idx) &= ~PCFG_TFTH_MASK;	\
		REG_PCM_PCFG(idx) |= ((n) << PCM_PCFG_TFTH_BIT);	\
	} while(0)

#define __pcm_set_receive_trigger(idx, n)		\
	do {						\
		REG_PCM_PCFG(idx) &= ~PCFG_RFTH_MASK;	\
		REG_PCM_PCFG(idx) |= ((n) << PCM_PCFG_RFTH_BIT);	\
	} while(0)

#define __pcm_omsb_same_sync(n)   (REG_PCM_PCFG(n) &= ~PCFG_OMSBPOS)
#define __pcm_omsb_next_sync(n)   (REG_PCM_PCFG(n) |= PCM_PCFG_OMSBPOS)

#define __pcm_imsb_same_sync(n)   (REG_PCM_PCFG(n) &= ~PCFG_IMSBPOS)
#define __pcm_imsb_next_sync(n)   (REG_PCM_PCFG(n) |= PCM_PCFG_IMSBPOS)

#define __pcm_set_iss(idx,n)					\
	do {							\
		if (n == 16)					\
			REG_PCM_PCFG(idx) |= PCM_PCFG_ISS_16BIT;	\
		else						\
			REG_PCM_PCFG(idx) &= ~PCFG_ISS_16BIT;	\
	} while(0)


#define __pcm_set_oss(idx, n)					\
	do {							\
		if (n == 16)					\
			REG_PCM_PCFG(idx) |= PCM_PCFG_OSS_16BIT;	\
		else						\
			REG_PCM_PCFG(idx) &= ~PCFG_OSS_16BIT;	\
	} while(0)

#define __pcm_set_valid_slot(idx, n)					\
	do {								\
		REG_PCM_PCFG((idx)) = (REG_PCM_PCFG((idx)) & ~PCFG_SLOT_MASK) | ((n) << PCM_PCFG_SLOT_BIT); \
	} while(0)							\

#define __pcm_write_data(idx, v)	(REG_PCM_PDP(idx) = (v))
#define __pcm_read_data(idx)	(REG_PCM_PDP(idx))

#define __pcm_enable_tfs_intr(n)	(REG_PCM_PINTC(n) |= PCM_PINTC_ETFS)
#define __pcm_disable_tfs_intr(n)	(REG_PCM_PINTC(n) &= ~PINTC_ETFS)

#define __pcm_enable_tur_intr(n)	(REG_PCM_PINTC(n) |= PCM_PINTC_ETUR)
#define __pcm_disable_tur_intr(n)	(REG_PCM_PINTC(n) &= ~PINTC_ETUR)

#define __pcm_enable_rfs_intr(n)	(REG_PCM_PINTC(n) |= PCM_PINTC_ERFS)
#define __pcm_disable_rfs_intr(n)	(REG_PCM_PINTC(n) &= ~PINTC_ERFS)

#define __pcm_enable_ror_intr(n)	(REG_PCM_PINTC(n) |= PCM_PINTC_EROR)
#define __pcm_disable_ror_intr(n)	(REG_PCM_PINTC(n) &= ~PINTC_EROR)

#define __pcm_ints_valid_tx(n)	(((REG_PCM_PINTS(n) & PCM_PINTSTFL_MASK) >> PCM_PINTSTFL_BIT))
#define __pcm_ints_valid_rx(n)	(((REG_PCM_PINTS(n) & PCM_PINTSRFL_MASK) >> PCM_PINTSRFL_BIT))

#define __pcm_set_clk_div(idx, n)					\
	(REG_PCM_PDIV(idx) = (REG_PCM_PDIV(idx) & ~PDIV_CLKDIV_MASK) | ((n) << PCM_PDIV_CLKDIV_BIT))

#define __pcm_set_clk_rate(idx, sysclk, pcmclk)		\
	__pcm_set_clk_div(idx, ((sysclk) / (pcmclk) - 1))

#define __pcm_set_sync_div(idx, n)					\
	do {								\
		REG_PCM_PDIV(idx) = (REG_PCM_PDIV(idx) & ~PDIV_SYNDIV_MASK) | ((n) << PCM_PDIV_SYNDIV_BIT);	\
	} while(0)

#define __pcm_set_sync_rate(idx, pcmclk, sync)			\
	__pcm_set_sync_div(idx, ((pcmclk) / (8 * (sync)) - 1))

#define __pcm_set_sync_len(idx, n)					\
	do {								\
		REG_PCM_PDIV(idx) = (REG_PCM_PDIV(idx) & (~PDIV_SYNL_MASK)) | ((n) << PCM_PDIV_SYNL_BIT); \
	} while(0)

#endif /* __MIPS_ASSEMBLER */

#endif /* __CHIP_PCM_H__ */
