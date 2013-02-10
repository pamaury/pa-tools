CC=arm-elf-eabi-gcc
LD=arm-elf-eabi-gcc
AS=arm-elf-eabi-gcc
OC=arm-elf-eabi-objcopy
ELF2SB=./elftosb
#ELF2SB=~/Téléchargements/elftosb_2.6.1/linux_x86_64/elftosb
ELF2SB_CMD=-c recovery.db
ELF2SB_KEY=-z
#ELF2SB_KEY=
#PLATFORM=-DSANSA_FUZEPLUS
#PLATFORM=-DCREATIVE_ZENXFI2
#PLATFORM=-DSONY_NWZE360
PLATFORM=-DCREATIVE_ZENXFI3
#PLATFORM=-DINSIGNIA_INFOCAST35
CFLAGS=$(PLATFORM) -W -Wall -Wundef -O -nostdlib -ffreestanding -Wstrict-prototypes -pipe -std=gnu99 -mcpu=arm926ej-s -fomit-frame-pointer -Wno-pointer-sign -Wno-override-init
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

clean:
	rm -rf $(OBJ)
