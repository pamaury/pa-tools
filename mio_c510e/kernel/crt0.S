#define ASM_ONLY
#include "rom.h"
#include "config.h"
#include "s3c2440.h"

.section    .init.text,"ax",%progbits
.code       32
.align      0x04
.global     start
start:
    b       boot /* branch to actual starting point */

.section    .text,"ax",%progbits
.code       32
.align      0x04 
boot:
    /* setup a new stack */
    ldr     r0, =(LCD_FRAME_ADDR - 0x4)
    mov     sp, r0
    /* kill the MMU, ICache and DCache */
    mrc     p15, 0, r0, c1, c0, 0
    ldr     r1, =0x1005
    bic     r0, r1
    mcr     p15, 0, r0, c1, c0, 0
    nop
    nop
    nop
    nop
    /* zero out BSS */
    ldr     r2, =_bss_start
    ldr     r3, =_bss_end
    mov     r4, #0
1:
    cmp     r3, r2
    strhi   r4, [r2], #4
    bhi     1b
    /* random things */
    bl      main
1:
    b       1b

.global     arm_clock_select
arm_clock_select:
    mrc     p15, 0, r0, c1, c0
    orr     r0, #0xC0000000
    mcr     p15, 0, r0, c1, c0
    bx      lr

.global     arm_clock_wait
arm_clock_wait:
    mov     r0, #0x2000
0:
    subs    r0, #1
    bne     0b
    bx      lr

.global     wait
wait:
    movs    r0, r0
0:
    bxeq    lr
    ldr     r2, =0x4D2
1:
    subs    r2, #1
    bne     1b
    subs    r0, #1
    b       0b
