#ifndef __serial_h__
#define __serial_h__

#include "system.h"

#define HW_DBGUART_BASE 0x80070000

#define HW_UARTDBGDR        (*(volatile uint32_t *)(HW_DBGUART_BASE + 0x0))

#define HW_UARTDBGRSR_ECR   (*(volatile uint32_t *)(HW_DBGUART_BASE + 0x4))

#define HW_UARTDBGFR        (*(volatile uint32_t *)(HW_DBGUART_BASE + 0x18))
#define HW_UARTDBGFR__CTS   0x0001
#define HW_UARTDBGFR__DSR   0x0002
#define HW_UARTDBGFR__DCD   0x0004
#define HW_UARTDBGFR__BUSY  0x0008
#define HW_UARTDBGFR__RXFE  0x0010
#define HW_UARTDBGFR__TXFF  0x0020
#define HW_UARTDBGFR__RXFF  0x0040
#define HW_UARTDBGFR__TXFE  0x0080
#define HW_UARTDBGFR__RI    0x0100

#define HW_UARTDBGILPR      (*(volatile uint32_t *)(HW_DBGUART_BASE + 0x20))

#define HW_UARTDBGIBRD      (*(volatile uint32_t *)(HW_DBGUART_BASE + 0x24))

#define HW_UARTDBGFBRD      (*(volatile uint32_t *)(HW_DBGUART_BASE + 0x28))

#define HW_UARTDBGLCR_H     (*(volatile uint32_t *)(HW_DBGUART_BASE + 0x2c))
#define HW_UARTDBGLCR_H__BRK    x0001
#define HW_UARTDBGLCR_H__PEN    0x0002
#define HW_UARTDBGLCR_H__EPS    0x0004
#define HW_UARTDBGLCR_H__STP2   0x0008
#define HW_UARTDBGLCR_H__FEN    0x0010
#define HW_UARTDBGLCR_H__WLEN5  0x0000
#define HW_UARTDBGLCR_H__WLEN6  0x0020
#define HW_UARTDBGLCR_H__WLEN7  0x0040
#define HW_UARTDBGLCR_H__WLEN8  0x0060
#define HW_UARTDBGLCR_H__SPS    0x0080

#define HW_UARTDBGCR        (*(volatile uint32_t *)(HW_DBGUART_BASE + 0x30))
/* UARTDBGCR - Control Register bits */
#define HW_UARTDBGCR__UARTEN    0x0001
#define HW_UARTDBGCR__LBE       0x0080
#define HW_UARTDBGCR__TXE       0x0100
#define HW_UARTDBGCR__RXE       0x0200
#define HW_UARTDBGCR__DTR       0x0400
#define HW_UARTDBGCR__RTS       0x0800
#define HW_UARTDBGCR__OUT1      0x1000
#define HW_UARTDBGCR__OUT2      0x2000
#define HW_UARTDBGCR__RTSEN     0x4000
#define HW_UARTDBGCR__CTSEN     0x8000

#define HW_UARTDBGIFLS      (*(volatile uint32_t *)(HW_DBGUART_BASE + 0x34))

#define HW_UARTDBGIMSC      (*(volatile uint32_t *)(HW_DBGUART_BASE + 0x38))

#define HW_UARTDBGRIS       (*(volatile uint32_t *)(HW_DBGUART_BASE + 0x3c))

#define HW_UARTDBGMIS       (*(volatile uint32_t *)(HW_DBGUART_BASE + 0x40))

#define HW_UARTDBGICR       (*(volatile uint32_t *)(HW_DBGUART_BASE + 0x44))

#define HW_UARTDBGDMACR     (*(volatile uint32_t *)(HW_DBGUART_BASE + 0x48))

void serial_init(void);
void serial_put(char c);
void serial_send(const char *s);
void serial_flush(void);

#endif /* __serial_h__ */
