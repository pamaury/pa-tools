#include "system.h"
#include "clkctrl.h"

#define HW_POWER_BASE           0x80044000

#define HW_POWER_RESET          (*(volatile uint32_t *)(HW_POWER_BASE + 0x100))
#define HW_POWER_RESET__UNLOCK  0x3E770000
#define HW_POWER_RESET__PWD     0x1

#define HW_ICOLL_BASE           0x80000000

#define HW_ICOLL_VECTOR         (*(volatile uint32_t *)(HW_ICOLL_BASE + 0x0))

#define HW_ICOLL_LEVELACK       (*(volatile uint32_t *)(HW_ICOLL_BASE + 0x10))
#define HW_ICOLL_LEVELACK__LEVEL0   0x1

#define HW_ICOLL_CTRL           (*(volatile uint32_t *)(HW_ICOLL_BASE + 0x20))
#define HW_ICOLL_CTRL__IRQ_FINAL_ENABLE (1 << 16)
#define HW_ICOLL_CTRL__ARM_RSE_MODE     (1 << 18)

#define HW_ICOLL_VBASE          (*(volatile uint32_t *)(HW_ICOLL_BASE + 0x40))
#define HW_ICOLL_INTERRUPT(i)   (*(volatile uint32_t *)(HW_ICOLL_BASE + 0x120 + (i) * 0x10))
#define HW_ICOLL_INTERRUPT__PRIORITY_BM 0x3
#define HW_ICOLL_INTERRUPT__ENABLE      0x4
#define HW_ICOLL_INTERRUPT__SOFTIRQ     0x8
#define HW_ICOLL_INTERRUPT__ENFIQ       0x10

#define default_interrupt(name) \
    extern __attribute__((weak ,alias("UIRQ"))) void name(void)

void irq_handler(void) __attribute__((interrupt("IRQ"))) ICODE_ATTR;
void fiq_handler(void) __attribute__((interrupt("FIQ"))) ICODE_ATTR;

void UIRQ(void)
{
}

default_interrupt(INT_USB_CTRL);
default_interrupt(INT_TIMER0);
default_interrupt(INT_LCDIF_DMA);
default_interrupt(INT_LCDIF_ERROR);

typedef void (*isr_t)(void);

static isr_t isr_table[INT_SRC_NR_SOURCES] =
{
    [INT_SRC_USB_CTRL] = INT_USB_CTRL,
    [INT_SRC_TIMER0] = INT_TIMER0,
    [INT_SRC_LCDIF_DMA] = INT_LCDIF_DMA,
    [INT_SRC_LCDIF_ERROR] = INT_LCDIF_ERROR,
};

void irq_handler(void)
{
    HW_ICOLL_VECTOR = HW_ICOLL_VECTOR; /* notify icoll that we entered ISR */
    (*(isr_t *)HW_ICOLL_VECTOR)();
    /* acknowledge completion of IRQ (all use the same priority 0 */
    HW_ICOLL_LEVELACK = HW_ICOLL_LEVELACK__LEVEL0;
}

void fiq_handler(void)
{
}

void imx233_enable_interrupt(int src, bool enable)
{
    if(enable)
        __REG_SET(HW_ICOLL_INTERRUPT(src)) = HW_ICOLL_INTERRUPT__ENABLE;
    else
        __REG_CLR(HW_ICOLL_INTERRUPT(src)) = HW_ICOLL_INTERRUPT__ENABLE;
}

void imx233_softirq(int src, bool enable)
{
    if(enable)
        __REG_SET(HW_ICOLL_INTERRUPT(src)) = HW_ICOLL_INTERRUPT__SOFTIRQ;
    else
        __REG_CLR(HW_ICOLL_INTERRUPT(src)) = HW_ICOLL_INTERRUPT__SOFTIRQ;
}

void system_init(void)
{
    /* disable all interrupts */
    for(int i = 0; i < INT_SRC_NR_SOURCES; i++)
    {
        /* priority = 0, disable, disable fiq */
        HW_ICOLL_INTERRUPT(i) = 0;
    }
    /* setup vbase as isr_table */
    HW_ICOLL_VBASE = (uint32_t)&isr_table;
    /* enable final irq bit */
    __REG_SET(HW_ICOLL_CTRL) = HW_ICOLL_CTRL__IRQ_FINAL_ENABLE; 
}

void power_off(void)
{
    /* power down */
    HW_POWER_RESET = HW_POWER_RESET__UNLOCK | HW_POWER_RESET__PWD;
    while(1);
}

void system_reset(void)
{
    HW_CLKCTRL_RESET = HW_CLKCTRL_RESET_DIG;
}

bool imx233_tick_elapsed(uint32_t ref, unsigned us_delay)
{
    uint32_t cur = HW_DIGCTL_MICROSECONDS;
    if(ref + us_delay <= ref)
        return !(cur > ref) && !(cur < (ref + us_delay));
    else
        return (cur < ref) || cur >= (ref + us_delay);
}

void imx233_reset_block(volatile uint32_t *block_reg)
{
    __REG_CLR(*block_reg) = __BLOCK_SFTRST;
    while(*block_reg & __BLOCK_SFTRST);
    __REG_CLR(*block_reg) = __BLOCK_CLKGATE;
    __REG_SET(*block_reg) = __BLOCK_SFTRST;
    while(!(*block_reg & __BLOCK_CLKGATE));
    __REG_CLR(*block_reg) = __BLOCK_SFTRST;
    while(*block_reg & __BLOCK_SFTRST);
    __REG_CLR(*block_reg) = __BLOCK_CLKGATE;
    while(*block_reg & __BLOCK_CLKGATE);
}

void udelay(unsigned us)
{
    uint32_t ref = HW_DIGCTL_MICROSECONDS;
    while(!imx233_tick_elapsed(ref, us));
}
