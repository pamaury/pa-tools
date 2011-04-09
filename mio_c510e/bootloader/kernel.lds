ENTRY(start)
OUTPUT_FORMAT(elf32-littlearm)
OUTPUT_ARCH(arm)
/*STARTUP(crt0.o)*/

MEMORY
{
    DRAM : ORIGIN = 0x30000000, LENGTH = 0x4000000
    BOOTLOADER : ORIGIN = 0x32000000, LENGTH = 0x1000000
}

SECTIONS
{
    .ram (NOLOAD) :
    {
        _ramstart = .;
    } > DRAM
    
    .text :
    {
        _start = .;
        *(.romhdr)
        *(.text)
        *(.text)
        *(.data*)
        *(.rodata*)
        . = ALIGN(0x4);
        _end = .;
    } > BOOTLOADER

    .bss (NOLOAD) :
    {
        _bss_start = .;
        *(.bss)
        . = ALIGN(0x4);
        _bss_end = .;
    } > BOOTLOADER

    _image_size = _end - _start;

    /DISCARD/ :
    {
        *(.eh_frame)
    } 
}
