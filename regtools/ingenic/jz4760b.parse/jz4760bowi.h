/*
 * jz4760bowi.h
 * JZ4760B OWI register definition
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 *
 * Author: whxu@ingenic.cn
 */

// 
// #ifndef __JZ4760BOWI_H__
// #define __JZ4760BOWI_H__

// 

// 
/*
 * One wire bus interface(OWI) address definition
 */
this class OWI goto 0xb0072000

// 

// 
/*
 * OWI registers offset address definition
 */
const OWI_OWICFG_OFFSET 0x00
const OWI_OWICTL_OFFSET 0x04
const OWI_OWISTS_OFFSET 0x08
const OWI_OWIDAT_OFFSET 0x0c
const OWI_OWIDIV_OFFSET 0x10

// 

// 
/*
 * OWI registers address definition
 */
register OWICFG goto OWI_OWICFG_OFFSET export ""
register OWICTL goto OWI_OWICTL_OFFSET export ""
register OWISTS goto OWI_OWISTS_OFFSET export ""
register OWIDAT goto OWI_OWIDAT_OFFSET export ""
register OWIDIV goto OWI_OWIDIV_OFFSET export ""

// 

// 
/*
 * OWI registers common define
 */

// 
register OWICFG export "OWI configure register"
register OWICFG int MODE goto 7
register OWICFG int RDDATA goto 6
register OWICFG int WRDATA goto 5
register OWICFG int RDST goto 4
register OWICFG int WR1RD goto 3
register OWICFG int WR0 goto 2
register OWICFG int RST goto 1
register OWICFG int ENA goto 0

// 
register OWICTL export "OWI control register"
// #define OWICTL_EBYTE	BIT2
// #define OWICTL_EBIT	BIT1
// #define OWICTL_ERST	BIT0

// 
register OWISTS export "OWI status register"
register OWISTS int PST goto 7
register OWISTS int BYTE_RDY goto 2
register OWISTS int BIT_RDY goto 1
register OWISTS int PST_RDY goto 0

// 
register OWIDIV export "OWI clock divide register"
const OWI_OWIDIV_CLKDIV_LSB 0
register OWIDIV int CLKDIV goto (5, OWI_OWIDIV_CLKDIV_LSB)

// 

// 
// #ifndef __MIPS_ASSEMBLER

// 
/* Basic ops */
register OWICFG sizeof 8
register OWICTL sizeof 8
register OWISTS sizeof 8
register OWIDAT sizeof 8
register OWIDIV sizeof 8

// 

// 
// #endif /* __MIPS_ASSEMBLER */

// 
// #endif /* __JZ4760BOWI_H__ */

// 
