GPPARAMS =  -m32 -g -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -std=c++11 -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings -Wno-unused-label -ffreestanding -Wall -Werror
LDPARAMS =  -melf_i386
objects = stdlib.o stdio.o kernel.o isr.o irq.o idt.o mem.o string.o serial.o timer.o gdt.o port.o paging.o gdt_flush.o port_a.o boot.o idt_a.o isr_a.o  irq_a.o kbd.o mouse.o
i686 = i686-elf-
Asm_files =  idt boot isr port gdt_flush irq
C++_FILES = stdio kernel gdt port serial mem string isr idt stdlib irq timer kbd mouse paging
ASPARAMS = 	
VB=virtualbox
VBM=VBoxManage


all: run_vb

compile:
	$(i686)g++ $(GPPARAMS) -o stdio.o -c stdio.c++ -ffreestanding 
	$(i686)g++ $(GPPARAMS) -o kernel.o -c kernel.c++ -ffreestanding
	$(i686)g++ $(GPPARAMS) -o gdt.o -c gdt.c++ -ffreestanding
	$(i686)g++ $(GPPARAMS) -o port.o -c port.c++ -ffreestanding
	$(i686)g++ $(GPPARAMS) -o serial.o -c serial.c++ -ffreestanding
	$(i686)g++ $(GPPARAMS) -o mem.o -c mem.c++ -ffreestanding
	$(i686)g++ $(GPPARAMS) -o string.o -c string.c++ -ffreestanding
	$(i686)g++ $(GPPARAMS) -o isr.o -c isr.c++ -ffreestanding
	$(i686)g++ $(GPPARAMS) -o idt.o -c idt.c++ -ffreestanding
	$(i686)g++ $(GPPARAMS) -o irq.o -c irq.c++ -ffreestanding
	$(i686)g++ $(GPPARAMS) -o stdlib.o -c stdlib.c++ -ffreestanding
	$(i686)g++ $(GPPARAMS) -o timer.o -c timer.c++ -ffreestanding
	$(i686)g++ $(GPPARAMS) -o kbd.o -c kbd.c++ -ffreestanding
	$(i686)g++ $(GPPARAMS) -o mouse.o -c mouse.c++ -ffreestanding
	$(i686)g++ $(GPPARAMS) -o paging.o -c paging.c++ -ffreestanding
	nasm -f elf32 boot.asm -o boot.o
	nasm -f elf32 isr.asm -o isr_a.o
	nasm -f elf32 port.asm -o port_a.o
	nasm -f elf32 idt.asm -o idt_a.o
	nasm -f elf32 irq.asm -o irq_a.o
	nasm -f elf32 gdt_flush.asm -o gdt_flush.o

#IN TEST  START	
compile_c++: $(C++_FILES)
	$(i686)g++ $(GPPARAMS) -o $<.o -c $<.c++ -ffreestanding 
compile_asm: $(Asm_files)
	$(i686)as $(ASPARAMS) -g -o $<_a.o $<.S	
#IN TEST END

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
	qemu-system-i386 -s -kernel  BoneOS.bin

qemu_debug:
	qemu-system-i386 -kernel BoneOS.bin -d -s in_asm,cpu_reset,exec,int,guest_errors,pcall -no-reboot &>qemu.log

BoneOS.iso: BoneOS.bin 
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp BoneOS.bin iso/boot/BoneOS.bin
#	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
#	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
#	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "My Operating System" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/BoneOS.bin'    >> iso/boot/grub/grub.cfg
#	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=BoneOS.iso iso
	rm -rf iso

start-debug:
	qemu-system-i386 -S -s -kernel BoneOS.bin -m 1G -serial file:qemu-serial.log  -serial stdio -usb -device usb-host,hostbus=2,hostaddr=1
	

run_vb: compile BoneOS.bin BoneOS.iso
	-${VBM} unregistervm BoneOS --delete;
	echo "Creating VM"
	${VBM} createvm --name BoneOS --register
	${VBM} modifyvm BoneOS --memory 1024
	${VBM} modifyvm BoneOS --vram 64
	${VBM} modifyvm BoneOS --nic1 nat
	${VBM} modifyvm BoneOS --nictype1 82540EM
	${VBM} modifyvm BoneOS --nictrace1 on
	${VBM} modifyvm BoneOS --uart1 0x3F8 4
	${VBM} storagectl BoneOS --name "IDE Controller" --add ide
	${VBM} storageattach BoneOS --storagectl "IDE Controller" --port 0 \
	--device 0 --type dvddrive --medium BoneOS.iso
	echo "Run VM"
	${VB} --startvm BoneOS --dbg

compile_iso: compile BoneOS.bin BoneOS.iso
