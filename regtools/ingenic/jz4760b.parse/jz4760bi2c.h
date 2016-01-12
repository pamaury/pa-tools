/*
 * linux/include/asm-mips/mach-jz4810/jz4810i2c.h
 *
 * JZ4810 I2C register definition.
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

// 
// #ifndef __JZ4810I2C_H__
// #define __JZ4810I2C_H__

// 
const JZ_I2C_NUM 3

// 
/* I2C */
this class I2C goto (0, 0xB0050000) export "I2C"
this class I2C goto (1, 0xB0051000)
this class I2C goto (2, 0xB0055000)

// 

// 
/*************************************************************************
 * I2C
 *************************************************************************/
for n 0 2
register CTRL goto<n> "(n)*0x1000 + 0x00" export ""
register TAR goto<n> "(n)*0x1000 + 0x04" export ""
register SAR goto<n> "(n)*0x1000 + 0x08" export ""
register DC goto<n> "(n)*0x1000 + 0x10" export ""
register SHCNT goto<n> "(n)*0x1000 + 0x14" export ""
register SLCNT goto<n> "(n)*0x1000 + 0x18" export ""
register FHCNT goto<n> "(n)*0x1000 + 0x1C" export ""
register FLCNT goto<n> "(n)*0x1000 + 0x20" export ""
register INTST goto<n> "(n)*0x1000 + 0x2C" export ""
register INTM goto<n> "(n)*0x1000 + 0x30" export ""
register RXTL goto<n> "(n)*0x1000 + 0x38" export ""
register TXTL goto<n> "(n)*0x1000 + 0x3c" export ""
register CINTR goto<n> "(n)*0x1000 + 0x40" export ""
register CRXUF goto<n> "(n)*0x1000 + 0x44" export ""
register CRXOF goto<n> "(n)*0x1000 + 0x48" export ""
register CTXOF goto<n> "(n)*0x1000 + 0x4C" export ""
register CRXREQ goto<n> "(n)*0x1000 + 0x50" export ""
register CTXABRT goto<n> "(n)*0x1000 + 0x54" export ""
register CRXDONE goto<n> "(n)*0x1000 + 0x58" export ""
register CACT goto<n> "(n)*0x1000 + 0x5C" export ""
register CSTP goto<n> "(n)*0x1000 + 0x60" export ""
register CSTT goto<n> "(n)*0x1000 + 0x64" export ""
register CGC goto<n> "(n)*0x1000 + 0x68" export ""
register ENB goto<n> "(n)*0x1000 + 0x6C" export ""
register STA goto<n> "(n)*0x1000 + 0x70" export ""
register TXFLR goto<n> "(n)*0x1000 + 0x74" export ""
register RXFLR goto<n> "(n)*0x1000 + 0x78" export ""
register TXABRT goto<n> "(n)*0x1000 + 0x80" export ""
register DMACR goto<n> "(n)*0x1000 + 0x88" export ""
register DMATDLR goto<n> "(n)*0x1000 + 0x8c" export ""
register DMARDLR goto<n> "(n)*0x1000 + 0x90" export ""
register SDASU goto<n> "(n)*0x1000 + 0x94" export ""
register ACKGC goto<n> "(n)*0x1000 + 0x98" export ""
register ENSTA goto<n> "(n)*0x1000 + 0x9C" export ""
register SDAHD goto<n> "(n)*0x1000 + 0xD0" export ""

// 
register CTRL sizeof 8
register TAR sizeof 16
register SAR sizeof 16
register DC sizeof 16
register SHCNT sizeof 16
register SLCNT sizeof 16
register FHCNT sizeof 16
register FLCNT sizeof 16
register INTST sizeof 16
register INTM sizeof 16
register RXTL sizeof 8
register TXTL sizeof 8
register CINTR sizeof 8
register CRXUF sizeof 8
register CRXOF sizeof 8
register CTXOF sizeof 8
register CRXREQ sizeof 8
register CTXABRT sizeof 8
register CRXDONE sizeof 8
register CACT sizeof 8
register CSTP sizeof 8
register CSTT sizeof 16
register CGC sizeof 8
register ENB sizeof 8
register STA sizeof 8
register TXFLR sizeof 8
register RXFLR sizeof 8
register TXABRT sizeof 16
register DMACR sizeof 8
register DMATDLR sizeof 8
register DMARDLR sizeof 8
register SDASU sizeof 8
register ACKGC sizeof 8
register ENSTA sizeof 8
register SDAHD sizeof 16

// 
register CTRL export "I2C Control Register"

// 
register CTRL int STPHLD goto 7
register CTRL int SLVDIS goto 6 export "after reset slave is disabled"
register CTRL int REST goto 5
register CTRL int MATP goto 4 export "1: 10bit address 0: 7bit addressing"
register CTRL int SATP goto 3 export "standard mode 100kbps"
// #define I2C_CTRL_SPDF		(2 << 1) /* fast mode 400kbps */
register CTRL int SPDS goto 1 export "standard mode 100kbps"
register CTRL int MD goto 0 export "master enabled"

// 
register TAR export "I2C target address"

// 
register TAR int MATP goto 12
register TAR int SPECIAL goto 11
register TAR int GC_OR_START goto 10

// 
/* I2C slave address  */
register DC export "I2C data buffer and command"

// 
register DC int CMD goto 8 export "1 read 0  write"

// 
register INTST export "i2c interrupt status"

// 
register INTST int IGC goto 11 export ""
register INTST int ISTT goto 10
register INTST int ISTP goto 9
register INTST int IACT goto 8
register INTST int RXDN goto 7
register INTST int TXABT goto 6
register INTST int RDREQ goto 5
register INTST int TXEMP goto 4
register INTST int TXOF goto 3
register INTST int RXFL goto 2
register INTST int RXOF goto 1
register INTST int RXUF goto 0

// 
register INTM export "i2c interrupt mask status"

// 
register INTM int MIGC goto 11 export ""
register INTM int MISTT goto 10
register INTM int MISTP goto 9
register INTM int MIACT goto 8
register INTM int MRXDN goto 7
register INTM int MTXABT goto 6
register INTM int MRDREQ goto 5
register INTM int MTXEMP goto 4
register INTM int MTXOF goto 3
register INTM int MRXFL goto 2
register INTM int MRXOF goto 1
register INTM int MRXUF goto 0

// 
register CINTR export "I2C Clear Combined and Individual Interrupts"

// 
// #define I2C_CINTR_CINT

// 
/* I2C Clear TX_OVER Interrupt */
/* I2C Clear RDREQ Interrupt */
/* I2C Clear TX_ABRT Interrupt */
/* I2C Clear RX_DONE Interrupt */
/* I2C Clear ACTIVITY Interrupt */
/* I2C Clear STOP Interrupts */
/* I2C Clear START Interrupts */
/* I2C Clear GEN_CALL Interrupts */

// 
register ENB export "I2C Enable"

// 
register ENB int I2CENB goto 0 export "Enable the i2c"

// 
register STA export "I2C Status Register"

// 
register STA int SLVACT goto 6 export "Slave FSM is not in IDLE state"
register STA int MSTACT goto 5 export "Master FSM is not in IDLE state"
register STA int RFF goto 4 export "RFIFO if full"
register STA int RFNE goto 3 export "RFIFO is not empty"
register STA int TFE goto 2 export "TFIFO is empty"
register STA int TFNF goto 1 export "TFIFO is not full"
register STA int ACT goto 0 export "I2C Activity Status"

// 
register TXABRT export "I2C Transmit Abort Status Register"

// 
register TXABRT int SLVRD_INTX goto 15
register TXABRT int SLV_ARBLOST goto 14
register TXABRT int SLVFLUSH_TXFIFO goto 13
register TXABRT int ARB_LOST goto 12
register TXABRT int ABRT_MASTER_DIS goto 11
register TXABRT int ABRT_10B_RD_NORSTRT goto 10
register TXABRT int SBYTE_NORSTRT goto 9
register TXABRT int ABRT_HS_NORSTRT goto 8
register TXABRT int SBYTE_ACKDET goto 7
register TXABRT int ABRT_HS_ACKD goto 6
register TXABRT int ABRT_GCALL_READ goto 5
register TXABRT int ABRT_GCALL_NOACK goto 4
register TXABRT int ABRT_XDATA_NOACK goto 3
register TXABRT int ABRT_10ADDR2_NOACK goto 2
register TXABRT int ABRT_10ADDR1_NOACK goto 1
register TXABRT int ABRT_7B_ADDR_NOACK goto 0

// 
register ENSTA export "I2C Enable Status Register"

// 
register ENSTA int SLVRDLST goto 2
register ENSTA int SLVDISB goto 1
register ENSTA int I2CEN goto 0 export "when read as 1, i2c is deemed to be in an enabled state, when read as 0, i2c is deemed completely inactive. The cpu can, safely read this bit anytime .When this bit is read as 0 ,the cpu can, safely read SLVRDLST and SLVDISB"

// 
const I2C_SDASU_SETUP_TIME_BASE 0
const I2C_SDASU_SETUP_TIME_MASK 0xff

// 
const I2C_SDAHD_HOLD_TIME_BASE 0
const I2C_SDAHD_HOLD_TIME_MASK 0xff
register SDAHD int HOLD_TIME_EN goto 8

// 
// #ifndef __MIPS_ASSEMBLER

// 
/***************************************************************************
 * I2C
 ***************************************************************************/

// 
// #define __i2c_enable(n)		( REG_I2C_ENB(n) = 1 )
// #define __i2c_disable(n)       	( REG_I2C_ENB(n) = 0 )

// 
// #define __i2c_is_enable(n)       ( REG_I2C_ENSTA(n) & I2C_ENB_I2CENB )
// #define __i2c_is_disable(n)      ( !(REG_I2C_ENSTA(n) & I2C_ENB_I2CENB) )

// 
// #define __i2c_abrt(n)            ( REG_I2C_TXABRT(n) != 0 )
// #define __i2c_master_active(n)   ( REG_I2C_STA(n) & I2C_STA_MSTACT )
// #define __i2c_abrt_7b_addr_nack(n)  ( REG_I2C_TXABRT(n) & I2C_TXABRT_ABRT_7B_ADDR_NOACK )
// #define __i2c_txfifo_is_empty(n)     ( REG_I2C_STA(n) & I2C_STA_TFE )
// #define __i2c_txfifo_not_full(n)     ( REG_I2C_STA(n) & I2C_STA_TFNF )
// #define __i2c_clear_interrupts(ret,n)    ( ret = REG_I2C_CINTR(n) )

// 
// #define __i2c_dma_rd_enable(n)        SETREG8(I2C_DMACR(n),1 << 0)
// #define __i2c_dma_rd_disable(n)       CLRREG8(I2C_DMACR(n),1 << 0)
// #define __i2c_dma_td_enable(n)        SETREG8(I2C_DMACR(n),1 << 1)
// #define __i2c_dma_td_disable(n)       CLRREG8(I2C_DMACR(n),1 << 1)

// 
// #define __i2c_send_stop(n)           CLRREG8(I2C_SHCNT(n), I2C_CTRL_STPHLD)
// #define __i2c_nsend_stop(n)          SETREG8(I2C_SHCNT(n), I2C_CTRL_STPHLD)

// 
// #define __i2c_set_dma_td_level(n,data) OUTREG8(I2C_DMATDLR(n),data)
// #define __i2c_set_dma_rd_level(n,data) OUTREG8(I2C_DMARDLR(n),data)

// 
// #define __i2c_hold_time_enable(n) SETREG16(I2C_SDAHD(n), I2C_SDAHD_HOLD_TIME_EN)
// #define __i2c_hold_time_disable(n) CLRREG16(I2C_SDAHD(n), I2C_SDAHD_HOLD_TIME_EN)
// #define __i2c_set_hold_time(n, ht)					\
// 	do {								\
// 		CLRREG16(I2C_SDAHD(n), I2C_SDAHD_HOLD_TIME_MASK);	\
// 		SETREG16(I2C_SDAHD(n), ((ht) & I2C_SDAHD_HOLD_TIME_MASK)); \
// 	} while(0)

// 
// #define __i2c_set_setup_time(n, su)					\
// 	do {								\
// 		CLRREG16(I2C_SDASU(n), I2C_SDASU_SETUP_TIME_MASK);	\
// 		SETREG16(I2C_SDASU(n), ((su) & I2C_SDASU_SETUP_TIME_MASK)); \
// 	} while(0) 

// 
register SHCNT export "I2C standard mode high count register"
// #define I2C_SHCNT_ADJUST(n)      (((n) - 8) < 6 ? 6 : ((n) - 8))

// 
register SLCNT export "I2C standard mode low count register"
// #define I2C_SLCNT_ADJUST(n)      (((n) - 1) < 8 ? 8 : ((n) - 1))

// 
register FHCNT export "I2C fast mode high count register"
// #define I2C_FHCNT_ADJUST(n)      (((n) - 8) < 6 ? 6 : ((n) - 8))

// 
register FLCNT export "I2C fast mode low count register"
// #define I2C_FLCNT_ADJUST(n)      (((n) - 1) < 8 ? 8 : ((n) - 1))

// 
/*
#define __i2c_set_clk(dev_clk, i2c_clk) \
  ( REG_I2C_GR = (dev_clk) / (16*(i2c_clk)) - 1 )
*/

// 
// #define __i2c_read(n)		( REG_I2C_DC(n) & 0xff )
// #define __i2c_write(val,n)	( REG_I2C_DC(n) = (val) )

// 

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4810I2C_H__ */

// 
