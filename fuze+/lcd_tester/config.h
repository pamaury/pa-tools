#ifndef __config_h__
#define __config_h__

#define MEMORYSIZE  128

#define CPU_ARM

#define ARM_ARCH 5 /* ARMv5 */

#define ICODE_ATTR      __attribute__ ((section(".icode")))
#define ICONST_ATTR     __attribute__ ((section(".irodata")))
#define IDATA_ATTR      __attribute__ ((section(".idata")))
#define IBSS_ATTR       __attribute__ ((section(".ibss")))

#define UNLIKELY(a) a

#if defined(CPU_ARM) && defined(__ASSEMBLER__)
/* ARMv4T doesn't switch the T bit when popping pc directly, we must use BX */
.macro ldmpc cond="", order="ia", regs
#if ARM_ARCH == 4 && defined(USE_THUMB)
    ldm\cond\order sp!, { \regs, lr }
    bx\cond lr
#else
    ldm\cond\order sp!, { \regs, pc }
#endif
.endm
.macro ldrpc cond=""
#if ARM_ARCH == 4 && defined(USE_THUMB)
    ldr\cond lr, [sp], #4
    bx\cond  lr
#else
    ldr\cond pc, [sp], #4
#endif
.endm
#endif

#endif /* __config_h__ */
