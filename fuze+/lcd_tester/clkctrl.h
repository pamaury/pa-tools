#ifndef __clocks_h__
#define __clocks_h__

#include "system.h"

#define HW_CLKCTRL_BASE     0x80040000

#define HW_CLKCTRL_XTAL     (*(volatile uint32_t *)(HW_CLKCTRL_BASE + 0x50))
#define HW_CLKCTRL_XTAL__TIMROT_CLK32K_GATE (1 << 26)
#define HW_CLKCTRL_XTAL__PWM_CLK24M_GATE    (1 << 29)

#define HW_CLKCTRL_PIX      (*(volatile uint32_t *)(HW_CLKCTRL_BASE + 0x60))

#define HW_CLKCTRL_CLKSEQ   (*(volatile uint32_t *)(HW_CLKCTRL_BASE + 0x110))
#define HW_CLKCTRL_CLKSEQ__BYPASS_PIX   (1 << 1)

#define HW_CLKCTRL_RESET    (*(volatile uint32_t *)(HW_CLKCTRL_BASE + 0x120))
#define HW_CLKCTRL_RESET_CHIP   0x2
#define HW_CLKCTRL_RESET_DIG    0x1

enum imx233_clock_t
{
    CLK_PIX,
};

void imx233_enable_timrot_xtal_clk32k(bool enable);
void imx233_enable_pwm_xtal_clk24m(bool enable);
void imx233_enable_clock(enum imx233_clock_t clk, bool enable);
void imx233_set_clock_divisor(enum imx233_clock_t clk, int div);
void imx233_set_bypass_pll(enum imx233_clock_t clk, bool bypass);

#endif /* __clocks_h__ */
