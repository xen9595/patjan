# Build i386 kernel -> ISO -> run in QEMU as CD-ROM (cd0), kernel at /boot/kernel.elf

CC      := gcc
CFLAGS  := -m32 -ffreestanding -O2 -Wall -Wextra -fno-stack-protector -fno-pic -fno-pie
LDFLAGS := -m32 -nostdlib -T undefined/linker.ld -no-pie
INCLUDES:= -I headers

OBJS := \
  src/idt.o src/idt_flush.o src/video.o src/keyboard.o src/keyboard_stub.o \
  src/kernel.o src/mm.o src/sched.o src/ramfs.o

all: myos.iso

kernel.elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

src/%.o: src/%.s
	$(CC) -m32 -c -o $@ $<

# automatyczne generowanie grub/grub.cfg jeśli go nie ma
grub/grub.cfg:
	mkdir -p grub
	echo 'set default=0'        >  grub/grub.cfg
	echo 'set timeout=0'        >> grub/grub.cfg
	echo ''                     >> grub/grub.cfg
	echo 'menuentry "miniOS (CD-ROM, /boot/kernel.elf)" {' >> grub/grub.cfg
	echo '    multiboot /boot/kernel.elf' >> grub/grub.cfg
	echo '    boot'             >> grub/grub.cfg
	echo '}'                    >> grub/grub.cfg

myos.iso: kernel.elf grub/grub.cfg
	mkdir -p iso/boot/grub
	cp kernel.elf iso/boot/kernel.elf
	cp grub/grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso iso

run: myos.iso
	qemu-system-i386 -m 128M -cdrom myos.iso -serial stdio -no-reboot -no-shutdown

clean:
	rm -rf src/*.o kernel.elf iso myos.iso grub/grub.cfg
