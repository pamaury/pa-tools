/*
 * linux/include/asm-mips/mach-jz4810/jz4810i2c.h
 *
 * JZ4810 I2C register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

#ifndef __JZ4810I2C_H__
#define __JZ4810I2C_H__

#define JZ_I2C_NUM	3

/* I2C */
#define	I2C_BASE(0)	0xB0050000
#define	I2C_BASE(1)	0xB0051000
#define I2C_BASE(2)	0xB0055000


/*************************************************************************
 * I2C
 *************************************************************************/
/* n is the block index (0-2) */
#define	I2C_CTRL		(I2C_BASE  + 0x00)
#define	I2C_TAR     		(I2C_BASE  + 0x04)
#define	I2C_SAR     		(I2C_BASE  + 0x08)
#define	I2C_DC      		(I2C_BASE  + 0x10)
#define	I2C_SHCNT		(I2C_BASE  + 0x14)
#define	I2C_SLCNT		(I2C_BASE  + 0x18)
#define	I2C_FHCNT		(I2C_BASE  + 0x1C)
#define	I2C_FLCNT		(I2C_BASE  + 0x20)
#define	I2C_INTST		(I2C_BASE  + 0x2C)
#define	I2C_INTM		(I2C_BASE  + 0x30)
#define I2C_RXTL		(I2C_BASE  + 0x38)
#define I2C_TXTL		(I2C_BASE  + 0x3c)
#define	I2C_CINTR		(I2C_BASE  + 0x40)
#define	I2C_CRXUF		(I2C_BASE  + 0x44)
#define	I2C_CRXOF		(I2C_BASE  + 0x48)
#define	I2C_CTXOF		(I2C_BASE  + 0x4C)
#define	I2C_CRXREQ		(I2C_BASE  + 0x50)
#define	I2C_CTXABRT		(I2C_BASE  + 0x54)
#define	I2C_CRXDONE		(I2C_BASE  + 0x58)
#define	I2C_CACT		(I2C_BASE  + 0x5C)
#define	I2C_CSTP		(I2C_BASE  + 0x60)
#define	I2C_CSTT		(I2C_BASE  + 0x64)
#define	I2C_CGC    		(I2C_BASE  + 0x68)
#define	I2C_ENB     		(I2C_BASE  + 0x6C)
#define	I2C_STA     		(I2C_BASE  + 0x70)
#define I2C_TXFLR		(I2C_BASE  + 0x74)
#define I2C_RXFLR		(I2C_BASE  + 0x78)
#define	I2C_TXABRT		(I2C_BASE  + 0x80)
#define I2C_DMACR            (I2C_BASE  + 0x88)
#define I2C_DMATDLR          (I2C_BASE  + 0x8c)
#define I2C_DMARDLR          (I2C_BASE  + 0x90)
#define	I2C_SDASU		(I2C_BASE  + 0x94)
#define	I2C_ACKGC		(I2C_BASE  + 0x98)
#define	I2C_ENSTA		(I2C_BASE  + 0x9C)
#define I2C_SDAHD		(I2C_BASE  + 0xD0)

#define	REG_I2C_CTRL		REG8(I2C_CTRL) /* I2C Control Register (I2C_CTRL) */
#define	REG_I2C_TAR		REG16(I2C_TAR) /* I2C target address (I2C_TAR) */
#define REG_I2C_SAR		REG16(I2C_SAR)
#define REG_I2C_DC		REG16(I2C_DC)
#define REG_I2C_SHCNT       	REG16(I2C_SHCNT)
#define REG_I2C_SLCNT       	REG16(I2C_SLCNT)
#define REG_I2C_FHCNT       	REG16(I2C_FHCNT)
#define REG_I2C_FLCNT       	REG16(I2C_FLCNT)
#define REG_I2C_INTST       	REG16(I2C_INTST) /* i2c interrupt status (I2C_INTST) */
#define REG_I2C_INTM		REG16(I2C_INTM) /* i2c interrupt mask status (I2C_INTM) */
#define REG_I2C_RXTL		REG8(I2C_RXTL)
#define REG_I2C_TXTL		REG8(I2C_TXTL)
#define REG_I2C_CINTR       	REG8(I2C_CINTR)
#define REG_I2C_CRXUF       	REG8(I2C_CRXUF)
#define REG_I2C_CRXOF       	REG8(I2C_CRXOF)
#define REG_I2C_CTXOF       	REG8(I2C_CTXOF)
#define REG_I2C_CRXREQ      	REG8(I2C_CRXREQ)
#define REG_I2C_CTXABRT     	REG8(I2C_CTXABRT)
#define REG_I2C_CRXDONE     	REG8(I2C_CRXDONE)
#define REG_I2C_CACT		REG8(I2C_CACT)
#define REG_I2C_CSTP		REG8(I2C_CSTP)
#define REG_I2C_CSTT		REG16(I2C_CSTT)
#define REG_I2C_CGC		REG8(I2C_CGC)
#define REG_I2C_ENB		REG8(I2C_ENB)
#define REG_I2C_STA		REG8(I2C_STA)
#define REG_I2C_TXFLR	REG8(I2C_TXFLR)
#define REG_I2C_RXFLR	REG8(I2C_RXFLR)
#define REG_I2C_TXABRT      	REG16(I2C_TXABRT)
#define REG_I2C_DMACR        REG8(I2C_DMACR)
#define REG_I2C_DMATDLR      REG8(I2C_DMATDLR)
#define REG_I2C_DMARDLR      REG8(I2C_DMARDLR)
#define REG_I2C_SDASU       	REG8(I2C_SDASU)
#define REG_I2C_ACKGC       	REG8(I2C_ACKGC)
#define REG_I2C_ENSTA       	REG8(I2C_ENSTA)
#define REG_I2C_SDAHD	REG16(I2C_SDAHD)

/* I2C Control Register (CTRL) */

#define I2C_CTRL_STPHLD		(1 << 7)
#define I2C_CTRL_SLVDIS		(1 << 6) /* after reset slave is disabled*/
#define I2C_CTRL_REST		(1 << 5)
#define I2C_CTRL_MATP		(1 << 4) /* 1: 10bit address 0: 7bit addressing*/
#define I2C_CTRL_SATP		(1 << 3) /* standard mode 100kbps */
#define I2C_CTRL_SPD_BIT	1 /* speed */
#define I2C_CTRL_SPD_MASK	(0x3 << I2C_CTRL_SPD_BIT) /* speed */
#define I2C_CTRL_SPD_SPDF		(2 << I2C_CTRL_SPD_BIT) /* fast mode 400kbps */
#define I2C_CTRL_SPD_SPDS		(1 << I2C_CTRL_SPD_BIT) /* standard mode 100kbps */
#define I2C_CTRL_MD		(1 << 0) /* master enabled*/

/* I2C target address (TAR) */

#define I2C_TAR_MATP		(1 << 12)
#define I2C_TAR_SPECIAL		(1 << 11)
#define I2C_TAR_GC_OR_START	(1 << 10)

/* I2C slave address  */
/* I2C data buffer and command (DC) */

#define I2C_DC_CMD			(1 << 8) /* 1 read 0  write*/

/* i2c interrupt status (INTST) */

#define I2C_INTST_IGC			(1 << 11) /* */
#define I2C_INTST_ISTT			(1 << 10)
#define I2C_INTST_ISTP			(1 << 9)
#define I2C_INTST_IACT			(1 << 8)
#define I2C_INTST_RXDN			(1 << 7)
#define I2C_INTST_TXABT			(1 << 6)
#define I2C_INTST_RDREQ			(1 << 5)
#define I2C_INTST_TXEMP			(1 << 4)
#define I2C_INTST_TXOF			(1 << 3)
#define I2C_INTST_RXFL			(1 << 2)
#define I2C_INTST_RXOF			(1 << 1)
#define I2C_INTST_RXUF			(1 << 0)

/* i2c interrupt mask status (INTM) */

#define I2C_INTM_MIGC			(1 << 11) /* */
#define I2C_INTM_MISTT			(1 << 10)
#define I2C_INTM_MISTP			(1 << 9)
#define I2C_INTM_MIACT			(1 << 8)
#define I2C_INTM_MRXDN			(1 << 7)
#define I2C_INTM_MTXABT			(1 << 6)
#define I2C_INTM_MRDREQ			(1 << 5)
#define I2C_INTM_MTXEMP			(1 << 4)
#define I2C_INTM_MTXOF			(1 << 3)
#define I2C_INTM_MRXFL			(1 << 2)
#define I2C_INTM_MRXOF			(1 << 1)
#define I2C_INTM_MRXUF			(1 << 0)

/* I2C Clear Combined and Individual Interrupts (CINTR) */

#define I2C_CINTR_CINT

/* I2C Clear TX_OVER Interrupt */
/* I2C Clear RDREQ Interrupt */
/* I2C Clear TX_ABRT Interrupt */
/* I2C Clear RX_DONE Interrupt */
/* I2C Clear ACTIVITY Interrupt */
/* I2C Clear STOP Interrupts */
/* I2C Clear START Interrupts */
/* I2C Clear GEN_CALL Interrupts */

/* I2C Enable (ENB) */

#define I2C_ENB_I2CENB 		(1 << 0) /* Enable the i2c */

/* I2C Status Register (STA) */

#define I2C_STA_SLVACT		(1 << 6) /* Slave FSM is not in IDLE state */
#define I2C_STA_MSTACT		(1 << 5) /* Master FSM is not in IDLE state */
#define I2C_STA_RFF		(1 << 4) /* RFIFO if full */
#define I2C_STA_RFNE		(1 << 3) /* RFIFO is not empty */
#define I2C_STA_TFE		(1 << 2) /* TFIFO is empty */
#define I2C_STA_TFNF		(1 << 1) /* TFIFO is not full  */
#define I2C_STA_ACT		(1 << 0) /* I2C Activity Status */

/* I2C Transmit Abort Status Register (TXABRT) */

#define I2C_TXABRT_SLVRD_INTX		(1 << 15)
#define I2C_TXABRT_SLV_ARBLOST		(1 << 14)
#define I2C_TXABRT_SLVFLUSH_TXFIFO	(1 << 13)
#define I2C_TXABRT_ARB_LOST		(1 << 12)
#define I2C_TXABRT_ABRT_MASTER_DIS	(1 << 11)
#define I2C_TXABRT_ABRT_10B_RD_NORSTRT	(1 << 10)
#define I2C_TXABRT_SBYTE_NORSTRT	(1 << 9)
#define I2C_TXABRT_ABRT_HS_NORSTRT	(1 << 8)
#define I2C_TXABRT_SBYTE_ACKDET		(1 << 7)
#define I2C_TXABRT_ABRT_HS_ACKD		(1 << 6)
#define I2C_TXABRT_ABRT_GCALL_READ	(1 << 5)
#define I2C_TXABRT_ABRT_GCALL_NOACK	(1 << 4)
#define I2C_TXABRT_ABRT_XDATA_NOACK	(1 << 3)
#define I2C_TXABRT_ABRT_10ADDR2_NOACK	(1 << 2)
#define I2C_TXABRT_ABRT_10ADDR1_NOACK	(1 << 1)
#define I2C_TXABRT_ABRT_7B_ADDR_NOACK	(1 << 0)

/* I2C Enable Status Register (ENSTA) */

#define I2C_ENSTA_SLVRDLST		(1 << 2)
#define I2C_ENSTA_SLVDISB 		(1 << 1)
#define I2C_ENSTA_I2CEN 		(1 << 0) /* when read as 1, i2c is deemed to be in an enabled state, when read as 0, i2c is deemed completely inactive. The cpu can, safely read this bit anytime .When this bit is read as 0 ,the cpu can, safely read SLVRDLST and SLVDISB */

#define I2C_SDASU_SETUP_TIME_BASE	0
#define I2C_SDASU_SETUP_TIME_MASK	0xff

#define I2C_SDAHD_HOLD_TIME_BASE	0
#define I2C_SDAHD_HOLD_TIME_MASK	0xff
#define I2C_SDAHD_HOLD_TIME_EN		(1 << 8)

#ifndef __MIPS_ASSEMBLER

/***************************************************************************
 * I2C
 ***************************************************************************/

#define __i2c_enable(n)		( REG_I2C_ENB(n) = 1 )
#define __i2c_disable(n)       	( REG_I2C_ENB(n) = 0 )

#define __i2c_is_enable(n)       ( REG_I2C_ENSTA(n) & I2C_ENB_I2CENB )
#define __i2c_is_disable(n)      ( !(REG_I2C_ENSTA(n) & I2C_ENB_I2CENB) )

#define __i2c_abrt(n)            ( REG_I2C_TXABRT(n) != 0 )
#define __i2c_master_active(n)   ( REG_I2C_STA(n) & I2C_STA_MSTACT )
#define __i2c_abrt_7b_addr_nack(n)  ( REG_I2C_TXABRT(n) & I2C_TXABRT_ABRT_7B_ADDR_NOACK )
#define __i2c_txfifo_is_empty(n)     ( REG_I2C_STA(n) & I2C_STA_TFE )
#define __i2c_txfifo_not_full(n)     ( REG_I2C_STA(n) & I2C_STA_TFNF )
#define __i2c_clear_interrupts(ret,n)    ( ret = REG_I2C_CINTR(n) )

#define __i2c_dma_rd_enable(n)        SETREG8(I2C_DMACR(n),1 << 0)
#define __i2c_dma_rd_disable(n)       CLRREG8(I2C_DMACR(n),1 << 0)
#define __i2c_dma_td_enable(n)        SETREG8(I2C_DMACR(n),1 << 1)
#define __i2c_dma_td_disable(n)       CLRREG8(I2C_DMACR(n),1 << 1)

#define __i2c_send_stop(n)           CLRREG8(I2C_SHCNT(n), I2C_CTRL_STPHLD)
#define __i2c_nsend_stop(n)          SETREG8(I2C_SHCNT(n), I2C_CTRL_STPHLD)

#define __i2c_set_dma_td_level(n,data) OUTREG8(I2C_DMATDLR(n),data)
#define __i2c_set_dma_rd_level(n,data) OUTREG8(I2C_DMARDLR(n),data)

#define __i2c_hold_time_enable(n) SETREG16(I2C_SDAHD(n), I2C_SDAHD_HOLD_TIME_EN)
#define __i2c_hold_time_disable(n) CLRREG16(I2C_SDAHD(n), I2C_SDAHD_HOLD_TIME_EN)
#define __i2c_set_hold_time(n, ht)					\
	do {								\
		CLRREG16(I2C_SDAHD(n), I2C_SDAHD_HOLD_TIME_MASK);	\
		SETREG16(I2C_SDAHD(n), ((ht) & I2C_SDAHD_HOLD_TIME_MASK)); \
	} while(0)

#define __i2c_set_setup_time(n, su)					\
	do {								\
		CLRREG16(I2C_SDASU(n), I2C_SDASU_SETUP_TIME_MASK);	\
		SETREG16(I2C_SDASU(n), ((su) & I2C_SDASU_SETUP_TIME_MASK)); \
	} while(0) 

/* I2C standard mode high count register(SHCNT) */
#define I2C_SHCNT_ADJUST(n)      (((n) - 8) < 6 ? 6 : ((n) - 8))

/* I2C standard mode low count register(SLCNT) */
#define I2C_SLCNT_ADJUST(n)      (((n) - 1) < 8 ? 8 : ((n) - 1))

/* I2C fast mode high count register(FHCNT) */
#define I2C_FHCNT_ADJUST(n)      (((n) - 8) < 6 ? 6 : ((n) - 8))

/* I2C fast mode low count register(FLCNT) */
#define I2C_FLCNT_ADJUST(n)      (((n) - 1) < 8 ? 8 : ((n) - 1))

/*
#define __i2c_set_clk(dev_clk, i2c_clk) \
  ( REG_I2C_GR = (dev_clk) / (16*(i2c_clk)) - 1 )
*/

#define __i2c_read(n)		( REG_I2C_DC(n) & 0xff )
#define __i2c_write(val,n)	( REG_I2C_DC(n) = (val) )


#endif /* __MIPS_ASSEMBLER */

#endif /* __JZ4810I2C_H__ */

