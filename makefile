FLOPPY = bin/floppy.img
BOOTLOADER = bin/bootloader.bin
KERNEL = bin/kernel.bin

prepare:
	mkdir -p bin
	dd if=/dev/zero of=$(FLOPPY) bs=512 count=2880

bootloader:
	nasm -f bin src/bootloader.asm -o $(BOOTLOADER)
	dd if=bin/bootloader.bin of=bin/floppy.img bs=512 count=1 conv=notrunc

stdlib:
	bcc -ansi -Iinclude -c src/std_lib.c -o bin/std_lib.o

shell:
	bcc -ansi -Iinclude -c src/shell.c -o bin/shell.o

kernel:
	bcc -ansi -Iinclude -c src/kernel.c -o bin/kernel.o
	nasm -f as86 src/kernel.asm -o bin/kernel-asm.o

link:
	ld86 -d bin/kernel.o bin/kernel-asm.o bin/shell.o bin/std_lib.o -o bin/kernel.bin
	dd if=$(KERNEL) of=$(FLOPPY) bs=512 seek=1 conv=notrunc

build: prepare bootloader stdlib shell kernel link

clean:
	rm -rf bin/

run: build
	bochs -f bochsrc.txt -q

.PHONY: all prepare bootloader stdlib shell kernel link build clean run
