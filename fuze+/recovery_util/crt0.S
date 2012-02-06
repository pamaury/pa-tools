.section    .text,"ax",%progbits
.code       32
.align      0x04
.global     start
start:
    cmp     r0, #0
    bne     save_lr
    msr     cpsr_c, #0xd3 /* enter supervisor mode, disable IRQ/FIQ */
    ldr     sp, =stackend
    b       main
save_lr:
    ldr     r0, =call_lr
    str     lr, [r0]
    mov     r0, #0
    bx      lr

.section    .data
.global     call_lr
call_lr:
    .word   0
