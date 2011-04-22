#include "clkctrl.h"

#define __CLK_CLKGATE   (1 << 31)
#define __CLK_BUSY      (1 << 29)

void imx233_enable_clock(enum imx233_clock_t clk, bool enable)
{
    volatile uint32_t *REG;
    switch(clk)
    {
        case CLK_PIX: REG = &HW_CLKCTRL_PIX; break;
        default: return;
    }

    if(enable)
    {
        __REG_CLR(*REG) = __CLK_CLKGATE;
        while((*REG) & __CLK_CLKGATE);
        while((*REG) & __CLK_BUSY);
    }
    else
    {
        __REG_SET(*REG) = __CLK_CLKGATE;
        while(!((*REG) & __CLK_CLKGATE));
    }
}

void imx233_set_clock_divisor(enum imx233_clock_t clk, int div)
{
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
