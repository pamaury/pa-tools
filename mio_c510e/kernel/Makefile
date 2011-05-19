CC=arm-elf-eabi-gcc
#LD=arm-elf-eabi-ar
LD=arm-elf-eabi-gcc
#AS=arm-elf-eabi-as
AS=arm-elf-eabi-gcc
OC=arm-elf-eabi-objcopy
CFLAGS=-Wall -O2 -std=c99 -nostdlib -ffreestanding -mcpu=arm920t -fomit-frame-pointer
ASFLAGS=$(CFLAGS) -D__ASSEMBLER__
OCFLAGS=
LINKER_FILE=kernel.lds
LDFLAGS=-lgcc -Os -nostdlib -T$(LINKER_FILE) -Wl,-Map,kernel.map
SRC_C=$(wildcard *.c)
SRC_S=$(wildcard *.S)
OBJ_C=$(SRC_C:.c=.o)
OBJ_S=$(SRC_S:.S=.o)
OBJ=$(OBJ_C) $(OBJ_S)
SCRAMBLE=./scramble

all: kernel.s3c

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< 

%.o: %.S
	$(AS) $(ASFLAGS) -c -o $@ $< 
	
kernel.elf: $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

kernel.bin: kernel.elf
	$(OC) $(OCFLAGS) -S -x -O binary $< $@

kernel.s3c: kernel.bin
	$(SCRAMBLE) -add=m244 $< $@

clean:
	rm -rf $(OBJ)
