ENTRY(start)
OUTPUT_FORMAT(elf32-littlearm)
OUTPUT_ARCH(arm)
/*STARTUP(crt0.o)*/

MEMORY
{
    DRAM : ORIGIN = 0x30000000, LENGTH = 0x4000000
}

SECTIONS
{
    .text :
    {
        _start = .;
        *(.init.text)
        *(.text)
        *(.data*)
        *(.rodata*)
        . = ALIGN(0x4);
        _end = .;
    } > DRAM

    .bss (NOLOAD) :
    {
        _bss_start = .;
        *(.bss)
        . = ALIGN(0x4);
        _bss_end = .;
    } > DRAM

    _image_size = _end - _start;

    _ramstart = .;

    /DISCARD/ :
    {
        *(.eh_frame)
    } 
}
