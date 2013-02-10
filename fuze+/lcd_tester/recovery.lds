ENTRY(start)
OUTPUT_FORMAT(elf32-littlearm)
OUTPUT_ARCH(arm)
STARTUP(crt0.o)

MEMORY
{
    OCRAM : ORIGIN = 0x0, LENGTH = 0x8000
    SDRAM : ORIGIN = 0x40000000, LENGTH = 0x20000000
}

SECTIONS
{
    .vectors :
    {
        *(.vectors*);
        . = ALIGN(0x4);
    } > OCRAM
    
    .octext :
    {
        *(.icode)
        *(.idata)
        *(.irodata)
        *(.ibss)
        *(.init.text)
        . = ALIGN(0x4);
    } > OCRAM

    .sdtext :
    {
        *(.text)
        *(.data*)
        *(.rodata*)
        . = ALIGN(0x4);
    } > SDRAM

    .stack :
    {
       *(.stack)
       stackbegin = .;
       . += 0x2000;
       stackend = .;
    } > OCRAM 

    .bss (NOLOAD) :
    {
        *(.bss)
        . = ALIGN(0x4);
    } > SDRAM

    /DISCARD/ :
    {
        *(.eh_frame)
    } 
}
