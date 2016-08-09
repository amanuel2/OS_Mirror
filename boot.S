#Global MultiBoot Kernel Recongnzation
.set MAGIC,0x1badb002
.set FLAGS , (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

#Putting in object file
.section .multiboot
	.long MAGIC
	.long FLAGS
	.long CHECKSUM


.section .text

    .extern kernelMain
    .extern callConstructors
    .globl loader
    
        loader:
                mov $kernel_stack , %esp
                call callConstructors
                push %eax
                push %ebx
                call kernelMain
                
        _eof:
             cli
             hlt 
             jmp _eof
                
                
.section .bss
.space 16*1024 #16 KiB
kernel_stack:
            
