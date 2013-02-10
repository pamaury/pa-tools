#ifndef __imx233_h__
#define __imx233_h__

#include "config.h"

#define __REG_SET(reg)  (*((volatile uint32_t *)(&reg + 1)))
#define __REG_CLR(reg)  (*((volatile uint32_t *)(&reg + 2)))
#define __REG_TOG(reg)  (*((volatile uint32_t *)(&reg + 3)))

#define __BLOCK_SFTRST  (1 << 31)
#define __BLOCK_CLKGATE (1 << 30)

#define __XTRACT(reg, field)    ((reg & reg##__##field##_BM) >> reg##__##field##_BP)
#define __XTRACT_EX(val, field)    (((val) & field##_BM) >> field##_BP)

#define imx233_soft_reset_block(reg) __imx233_soft_reset_block(&reg)

#if 0
inline uint32_t __imx233_get_microseconds(void)
{
}

void __imx233_soft_reset_block(volatile uint32_t *reg)
{
    /* clear soft reset */
    __REG_CLR(reg) = __BLOCK_SFTRST;
    /* wait a microsecond for soft reset to deassert */
    uint32_t ms = __imx233_get_microseconds();
    while(*reg & __BLOCK_SFTRST || (__imx233_get_microseconds() - ms) < 1);
    /* clear gate */
    __REG_CLR(reg) = __BLOCK_CLKGATE;
    /* soft-reset */
    __REG_SET(reg) = __BLOCK_SFTRST;
    /* wait for clock to be gated */
    while(!(*reg & __BLOCK_CLKGATE));
    /* clear soft-reset */
    __REG_CLR(reg) = __BLOCK_SFTRST;
    /* wait a microsecond for soft reset to deassert */
    uint32_t ms = __imx233_get_microseconds();
    while(*reg & __BLOCK_SFTRST || (__imx233_get_microseconds() - ms) < 1);
    /* clear clkgate */
    __REG_CLR(reg) = __BLOCK_CLKGATE;
    /* wait for clock to be non-gated */
    while(*reg & __BLOCK_CLKGATE);
}
#endif

#endif /* __imx233_h__ */
