#ifndef __clocks_h__
#define __clocks_h__

#include "system.h"

#define HW_CLKCTRL_BASE     0x80040000
#define HW_CLKCTRL_XTAL     (*(volatile uint32_t *)(HW_CLKCTRL_BASE + 0x50))
#define HW_CLKCTRL_XTAL__TIMROT_CLK32K_GATE (1 << 26)

static inline void imx233_enable_timrot_xtal_clk32k(bool enable)
{
    if(enable)
        __REG_CLR(HW_CLKCTRL_XTAL) = HW_CLKCTRL_XTAL__TIMROT_CLK32K_GATE;
    else
        __REG_SET(HW_CLKCTRL_XTAL) = HW_CLKCTRL_XTAL__TIMROT_CLK32K_GATE;
}

#endif /* __clocks_h__ */
