#ifndef __timer_h__
#define __timer_h__

#include "system.h"

#define HW_TIMROT_BASE          0x80068000

#define HW_TIMROT_ROTCTRL       (*(volatile uint32_t *)(HW_TIMROT_BASE + 0x0))

#define HW_TIMROT_ROTCOUNT      (*(volatile uint32_t *)(HW_TIMROT_BASE + 0x10))

#define HW_TIMROT_TIMCTRL(i)    (*(volatile uint32_t *)(HW_TIMROT_BASE + 0x20 + (i) * 0x20))
#define HW_TIMROT_TIMCTRL__IRQ      (1 << 15)
#define HW_TIMROT_TIMCTRL__IRQ_EN   (1 << 14)
#define HW_TIMROT_TIMCTRL__UPDATE   (1 << 7)
#define HW_TIMROT_TIMCTRL__RELOAD   (1 << 6)
#define HW_TIMROT_TIMCTRL__PRESCALE_1   (0 << 4)
#define HW_TIMROT_TIMCTRL__PRESCALE_2   (1 << 4)
#define HW_TIMROT_TIMCTRL__PRESCALE_4   (2 << 4)
#define HW_TIMROT_TIMCTRL__PRESCALE_8   (3 << 4)
#define HW_TIMROT_TIMCTRL__SELECT_32KHZ_XTAL    8
#define HW_TIMROT_TIMCTRL__SELECT_8KHZ_XTAL     9
#define HW_TIMROT_TIMCTRL__SELECT_4KHZ_XTAL     10
#define HW_TIMROT_TIMCTRL__SELECT_1KHZ_XTAL     11
#define HW_TIMROT_TIMCTRL__SELECT_TICK_ALWAYS   12


#define HW_TIMROT_TIMCOUNT(i)   (*(volatile uint32_t *)(HW_TIMROT_BASE + 0x30 + (i) * 0x20))

typedef void (*timer_fn_t)(void);

void timer_init(void);
void register_timer_function(timer_fn_t fn);

#endif /* __timer_h__ */
