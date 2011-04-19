#ifndef __system_h__
#define __system_h__

#include "config.h"
#include "stdint.h"
#include "imx233.h"

#define INT_SRC_TIMER0      28
#define INT_SRC_NR_SOURCES  66

void imx233_enable_interrupt(int src, int enable);
void imx233_softirq(int src, int enable);
void system_init(void);

#endif /* __system_h__ */
