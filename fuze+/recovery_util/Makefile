CC=arm-elf-eabi-gcc
LD=arm-elf-eabi-gcc
AS=arm-elf-eabi-gcc
OC=arm-elf-eabi-objcopy
DD=dd
REAL_KEY="6F393BD9E3940558F4FF418BF976A5B7"
IV="85708CC00C67ACDB6BAB0324FAE57FB0"
#ELF2SB=./elftosb -d --real-key $(REAL_KEY) --crypto-iv $(IV)
ELF2SB=./elftosb -d
ELF2SB_CMD=-c recovery.db
#ELF2SB_KEY=-a 00000000000000000000000000000000
ELF2SB_KEY=-z
CFLAGS=-W -Wall -Wundef -O -nostdlib -ffreestanding -Wstrict-prototypes -pipe -std=gnu99 -mcpu=arm926ej-s -fomit-frame-pointer -Wno-pointer-sign -Wno-override-init
ASFLAGS=$(CFLAGS) -D__ASSEMBLER__
OCFLAGS=
LINKER_FILE=recovery.lds
LDFLAGS=-lgcc -Os -nostdlib -T$(LINKER_FILE) -Wl,-Map,kernel.map
SRC_C=$(wildcard *.c)
SRC_S=$(wildcard *.S)
OBJ_C=$(SRC_C:.c=.o)
OBJ_S=$(SRC_S:.S=.o)
OBJ=$(OBJ_C) $(OBJ_S)
OBJ_EXCEPT_CRT0=$(filter-out crt0.o,$(OBJ))

all: recovery.sb

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< 

%.o: %.S
	$(AS) $(ASFLAGS) -c -o $@ $< 
	
recovery.elf: $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $(OBJ_EXCEPT_CRT0)

recovery.sb: recovery.elf
	$(ELF2SB) $(ELF2SB_CMD) $(ELF2SB_KEY) -o $@
#	cp $@ recovery-hack.sb
#	$(DD) if=hdr.bin conv=notrunc of=recovery-hack.sb

clean:
	rm -rf $(OBJ)
