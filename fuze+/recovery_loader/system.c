#include "system.h"

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

default_interrupt(INT_TIMER0);
default_interrupt(INT_USB_CTRL);

typedef void (*isr_t)(void);

static isr_t isr_table[INT_SRC_NR_SOURCES] =
{
    [INT_SRC_TIMER0] = INT_TIMER0,
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
    /* FIXME: this seems to be needed to correctly shutdown the chip */
    __REG_CLR(HW_ICOLL_CTRL) = HW_ICOLL_CTRL__IRQ_FINAL_ENABLE;
    /* power down */
    HW_POWER_RESET = HW_POWER_RESET__UNLOCK;
    HW_POWER_RESET = HW_POWER_RESET__UNLOCK | HW_POWER_RESET__PWD;
    while(1);
}
