GPPARAMS =  -m32 -g -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings -Wno-unused-label -ffreestanding -Wall -Werror
LDPARAMS =  -melf_i386
objects = stdio.o kernel.o idt.o mem.o string.o serial.o gdt.o port.o  gdt_flush.o port_a.o boot.o idt_a.o
i686 = i686-elf-
ASPARAMS = --32 
all: run_vb

compile:
	$(i686)g++ $(GPPARAMS) -o stdio.o -c stdio.c++ -ffreestanding 
	$(i686)g++ $(GPPARAMS) -o kernel.o -c kernel.c++ -ffreestanding
	$(i686)g++ $(GPPARAMS) -o gdt.o -c gdt.c++ -ffreestanding
	$(i686)g++ $(GPPARAMS) -o port.o -c port.c++ -ffreestanding
	$(i686)g++ $(GPPARAMS) -o serial.o -c serial.c++ -ffreestanding
	$(i686)g++ $(GPPARAMS) -o mem.o -c mem.c++ -ffreestanding
	$(i686)g++ $(GPPARAMS) -o string.o -c string.c++ -ffreestanding
	$(i686)g++ $(GPPARAMS) -o idt.o -c idt.c++ -ffreestanding
	$(i686)as $(ASPARAMS) -g -o boot.o boot.S
	$(i686)as $(ASPARAMS) -g -o port_a.o port.S
	$(i686)as $(ASPARAMS) -g -o idt_a.o idt.S
	$(i686)as $(ASPARAMS) -g -o gdt_flush.o gdt_flush.S
	
BoneOS.bin : linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)
	
install: BoneOS.bin
	sudo cp $< /boot/BoneOS.bin

clean:
	  rm $(objects)
	  rm -rf iso
	  rm BoneOS.*

qemu_compile: compile BoneOS.bin qemu
	

qemu:
	qemu-system-i386 -kernel BoneOS.bin

qemu_debug:
	qemu-system-i386 -kernel BoneOS.bin -d in_asm,cpu_reset,exec,int,guest_errors,pcall -no-reboot &>qemu.log

BoneOS.iso: BoneOS.bin 
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp BoneOS.bin iso/boot/BoneOS.bin
	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "My Operating System" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/BoneOS.bin'    >> iso/boot/grub/grub.cfg
		echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=BoneOS.iso iso
	rm -rf iso

start-debug:
	qemu-system-i386 -S -s -kernel BoneOS.bin -m 1G -serial file:qemu-serial.log 
	

run_vb: compile BoneOS.bin BoneOS.iso
	(killall VirtualBox && sleep 1)||true
	VirtualBox --startvm "BoneOS" &

compile_iso: compile BoneOS.bin BoneOS.iso
