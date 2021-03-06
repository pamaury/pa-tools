#define ASM_ONLY
#include "rom.h"
#include "config.h"
#include "s3c2440.h"

.section    .romhdr,"ax",%progbits
.code       32
.align      0x04
.global     start
start:
    b       boot /* branch to actual starting point */

rom_ecec:
    .org        ROM_SIGNATURE_OFFSET
    .word       ROM_SIGNATURE
    .org        ROM_TOC_POINTER_OFFSET
    .word       romhdr
    .org        ROM_TOC_OFFSET_OFFSET
    .word       0

.global romhdr
romhdr:
    .org        (romhdr + ROMHDR_dllfirst)
    .word       0
    .org        (romhdr + ROMHDR_dlllast)
    .word       0
    .org        (romhdr + ROMHDR_physfirst)
    .global     _start
    .word       _start
    .org        (romhdr + ROMHDR_physlast)
    .global     _end
    .word       _end
    .org        (romhdr + ROMHDR_nummods)
    .word       1
    .org        (romhdr + ROMHDR_ulRAMStart)
    .word       _start
    .org        (romhdr + ROMHDR_ulRAMFree)
    .word       _end
    .org        (romhdr + ROMHDR_ulRAMEnd)
    .word       _end
    .org        (romhdr + ROMHDR_ulCopyEntries)
    .word       0
    .org        (romhdr + ROMHDR_ulCopyOffset)
    .word       0
    .org        (romhdr + ROMHDR_ulProfileLen)
    .word       0
    .org        (romhdr + ROMHDR_ulProfileOffset)
    .word       0
    .org        (romhdr  + ROMHDR_numfiles)
    .word       0
    .org        (romhdr + ROMHDR_ulObjstoreStart)
    .word       0
    .org        (romhdr + ROMHDR_ulObjstoreLen)
    .word       0
    .org        (romhdr + ROMHDR_ulDrivglobStart)
    .word       0
    .org        (romhdr + ROMHDR_ulDrivglobLen)
    .word       0
    .org        (romhdr + ROMHDR_usCPUType)
    .hword      IMAGE_FILE_MACHINE_ARM
    .org        (romhdr + ROMHDR_usMiscFlags)
    .hword      0
    .org        (romhdr + ROMHDR_pExtensions)
    .word       rom_ext
    .org        (romhdr + ROMHDR_ulTrackingStart)
    .word       0
    .org        (romhdr + ROMHDR_ulTrackingLen)
    .word       0
.global nk_exe_module
nk_exe_module:
    .org        (nk_exe_module + TOCentry_dwFileAttributes)
    .word       (FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM)
    .org        (nk_exe_module + TOCentry_ftTime)
    .word       0 /* created three centuries ago ;) */
    .word       0
    .org        (nk_exe_module + TOCentry_lpszFileSize)
    .word       _image_size
    .org        (nk_exe_module + TOCentry_lpszFileName)
    .word       nk_exe_module_string
    .org        (nk_exe_module + TOCentry_ulE32Offset)
    .word       0
    .org        (nk_exe_module + TOCentry_ulO32Offset)
    .word       0
    .org        (nk_exe_module + TOCentry_ulLoadOffset)
    .word       _start
.global nk_exe_module_string
nk_exe_module_string:
    .asciz      "nk.exe"
.global rom_ext
rom_ext:
    .org        (rom_ext + ROMPID_dwPID)
    .fill       PID_LENGTH, 4, 0
    .org        (rom_ext + ROMPID_pNextExt)
    .word       rom_second_ext
.global rom_second_ext
rom_second_ext:
    .org        (rom_second_ext + ROMPID_name)
    .asciz      "chain information"
    .org        (rom_second_ext + ROMPID_type)
    .word       0
    .org        (rom_second_ext + ROMPID_pdata)
    .word       rom_ext_chain_info
    .org        (rom_second_ext + ROMPID_length)
    .word       (rom_ext_chain_info_end - rom_ext_chain_info)
    .org        (rom_second_ext + ROMPID_reserved)
    .word       0
    .org        (rom_second_ext + ROMPID_pNextExt)
    .word       0
.global rom_ext_chain_info
rom_ext_chain_info:
    .org        (rom_ext_chain_info + XIPCHAIN_SUMMARY_pvAddr)
    .word       0x8c200000
    .org        (rom_ext_chain_info + XIPCHAIN_SUMMARY_dwMaxLength)
    .word       0x1000
    .org        (rom_ext_chain_info + XIPCHAIN_SUMMARY_usOrder)
    .hword      0
    .org        (rom_ext_chain_info + XIPCHAIN_SUMMARY_usFlags)
    .hword      0
    .org        (rom_ext_chain_info + XIPCHAIN_SUMMARY_reserved)
    .word       0
rom_ext_chain_info_entry:
    .org        (rom_ext_chain_info_entry + XIPCHAIN_SUMMARY_pvAddr)
    .word       _start
    .org        (rom_ext_chain_info_entry + XIPCHAIN_SUMMARY_dwMaxLength)
    .word       _image_size
    .org        (rom_ext_chain_info_entry + XIPCHAIN_SUMMARY_usOrder)
    .hword      0
    .org        (rom_ext_chain_info_entry + XIPCHAIN_SUMMARY_usFlags)
    .hword      ROMXIP_OK_TO_LOAD
    .org        (rom_ext_chain_info_entry + XIPCHAIN_SUMMARY_reserved)
    .word       0
.global rom_ext_chain_info_end
rom_ext_chain_info_end:

.section    .text,"ax",%progbits
.code       32
.align      0x04 
boot:
    /* copy itself at the real location because it is loaded at _ramstart but
     * linked at _start */
    ldr     r3, =_start
    ldr     r2, =_ramstart
    ldr     r1, =_image_size
copy_loop:
    subs    r1, r1, #0x04
    ldrge   r0, [r2], #4
    strge   r0, [r3], #4
    bgt     copy_loop
    /* jump at real location */
    ldr     r0, =jump
    mov     pc, r0
    nop
    nop
jump:
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
