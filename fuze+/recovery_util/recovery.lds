ENTRY(start)
OUTPUT_FORMAT(elf32-littlearm)
OUTPUT_ARCH(arm)
STARTUP(crt0.o)

MEMORY
{
    OCRAM : ORIGIN = 0x0, LENGTH = 0x8000
}

SECTIONS
{
    .octext :
    {
        *(.text*)
        *(.data*)
        *(.rodata*)
    } > OCRAM

    .ocbss :
    {
        *(.bss*)
        . = ALIGN(0x4);
        stackbegin = .;
        . += 0x100;
        stackend = .;
        . = ALIGN(4096);
        buffer = .;
        . += 0x300;
    } > OCRAM

    .symtab :
    {
        KEEP(*(.symtab*));
        *(.symtab*)
    } > OCRAM

    .strtab :
    {
        KEEP(*(.strtab*));
        *(.strtab*)
    } > OCRAM

    /DISCARD/ :
    {
        *(.eh_frame)
    } 
}
