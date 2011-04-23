#include "clkctrl.h"
#include "logf.h"

#define __CLK_CLKGATE   (1 << 31)
#define __CLK_BUSY      (1 << 29)

void imx233_enable_timrot_xtal_clk32k(bool enable)
{
    if(enable)
        __REG_CLR(HW_CLKCTRL_XTAL) = HW_CLKCTRL_XTAL__TIMROT_CLK32K_GATE;
    else
        __REG_SET(HW_CLKCTRL_XTAL) = HW_CLKCTRL_XTAL__TIMROT_CLK32K_GATE;
}

void imx233_enable_clock(enum imx233_clock_t clk, bool enable)
{
    logf("imx233_enable_clock\n");
    volatile uint32_t *REG;
    switch(clk)
    {
        case CLK_PIX: REG = &HW_CLKCTRL_PIX; break;
        default: return;
    }

    /* warning: some registers like HW_CLKCTRL_PIX don't have a CLR/SET variant ! */
    if(enable)
    {
        *REG = (*REG) & ~__CLK_CLKGATE;
        while((*REG) & __CLK_CLKGATE);
        while((*REG) & __CLK_BUSY);
    }
    else
    {
        *REG |= __CLK_CLKGATE;
        while(!((*REG) & __CLK_CLKGATE));
    }
}

void imx233_set_clock_divisor(enum imx233_clock_t clk, int div)
{
    logf("imx233_set_clock_divisor\n");
    switch(clk)
    {
        case CLK_PIX:
            __REG_CLR(HW_CLKCTRL_PIX) = (1 << 12) - 1;
            __REG_SET(HW_CLKCTRL_PIX) = div;
            while(HW_CLKCTRL_PIX & __CLK_BUSY);
            break;
        default: return;
    }
}

void imx233_set_bypass_pll(enum imx233_clock_t clk, bool bypass)
{
    uint32_t msk;
    switch(clk)
    {
        case CLK_PIX: msk = HW_CLKCTRL_CLKSEQ__BYPASS_PIX; break;
        default: return;
    }

    if(bypass)
        __REG_SET(HW_CLKCTRL_CLKSEQ) = msk;
    else
        __REG_CLR(HW_CLKCTRL_CLKSEQ) = msk;
}
