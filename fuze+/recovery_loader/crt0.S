.section .vectors,"ax",%progbits
.code 32
.global vectors
vectors:
    b   start
    b   undef_instr_handler
    b   software_int_handler
    b   prefetch_abort_handler
    b   data_abort_handler
    b   reserved_handler
    b   irq_handler
    b   fiq_handler

.section    .init.text,"ax",%progbits
.code       32
.align      0x04
.global     start
start:
    msr     cpsr_c, #0xd3 /* enter supervisor mode, disable IRQ/FIQ */
    /* Set up some stack and munge it with 0xdeadbeef */
    ldr     sp, =stackend
    ldr     r2, =stackbegin
    ldr     r3, =0xdeadbeef
1:
    cmp     sp, r2
    strhi   r3, [r2], #4
    bhi     1b
    /* Set up stack for IRQ mode */ 
    msr     cpsr_c, #0xd2
    ldr     sp, =irq_stack
    /* Set up stack for FIQ mode */ 
    msr     cpsr_c, #0xd1
    ldr     sp, =fiq_stack
    /* Let abort and undefined modes use IRQ stack */
    msr     cpsr_c, #0xd7
    ldr     sp, =irq_stack
    msr     cpsr_c, #0xdb
    ldr     sp, =irq_stack
    /* Switch back to supervisor mode */
    msr     cpsr_c, #0xd3
    /* Disable MMU, disable caching and buffering;
     * use low exception range address (the core uses high range by default) */
    mrc     p15, 0, r0, c1, c0, 0
    ldr     r1, =0x3005
    bic     r0, r1
    mcr     p15, 0, r0, c1, c0, 0
    /* Go to main */
    bl      main
loop:
    b       loop

undef_instr_handler:
software_int_handler:
prefetch_abort_handler:
data_abort_handler:
reserved_handler:
    b       reserved_handler

.weak       irq_handler, fiq_handler

irq_handler:
fiq_handler:
dead_loop:
    b       dead_loop

/* 256 words of IRQ stack */
    .space 256*4
irq_stack:

/* 256 words of FIQ stack */
    .space 256*4
fiq_stack:
