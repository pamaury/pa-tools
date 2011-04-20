#ifndef __system_h__
#define __system_h__

#include "config.h"
#include "stdint.h"
#include "imx233.h"
#include "system-arm.h"

#define INT_SRC_TIMER0      28
#define INT_SRC_NR_SOURCES  66

#define HZ  100

extern volatile long current_tick;

#define HW_DIGCTL_BASE          0x8001C000
#define HW_DIGCTL_MICROSECONDS  (*(volatile uint32_t *)(HW_DIGCTL_BASE + 0xC0))

void imx233_enable_interrupt(int src, bool enable);
void imx233_softirq(int src, bool enable);
void system_init(void);

#endif /* __system_h__ */
