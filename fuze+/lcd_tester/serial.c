#include "serial.h"
#include "pinctrl.h"
#include "clkctrl.h"

void serial_init(void)
{
    imx233_set_pin_function(1, 26, PINCTRL_FUNCTION_ALT2); /* duart_rx */
    imx233_set_pin_function(1, 27, PINCTRL_FUNCTION_ALT2); /* duart_tx */

    /* disable uart, mask interrupts */
    HW_UARTDBGCR = 0;
    HW_UARTDBGIMSC = 0;
    /* set baudrate: 115200 */
    unsigned divisor = 24000000 * 4 / 115200;
    HW_UARTDBGFBRD = divisor & 0x3f;
    HW_UARTDBGIBRD = divisor >> 6;

    /* 8-bit mode, fifo enable */
    HW_UARTDBGLCR_H = HW_UARTDBGLCR_H__WLEN8 /*| HW_UARTDBGLCR_H__FEN*/;

    /* enable */
    HW_UARTDBGCR = HW_UARTDBGCR__TXE | HW_UARTDBGCR__UARTEN;

    serial_send("hello\n");
}

void serial_flush()
{
    while(!(HW_UARTDBGFR & HW_UARTDBGFR__TXFE));
}

void serial_put(char c)
{
    /* wait for fifo */
    while(HW_UARTDBGFR & HW_UARTDBGFR__TXFF);

    /* write data */
    HW_UARTDBGDR = c;

    if(c == '\n')
        serial_put('\r');
}

void serial_send(const char *s)
{
    while(*s)
        serial_put(*s++);
}
