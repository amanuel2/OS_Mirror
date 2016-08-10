;Global MultiBoot Kernel Recongnzation
MAGIC equ 0x1badb002
FLAGS equ (1<<0 | 1<<1)
CHECKSUM equ -(MAGIC + FLAGS)


;Putting in object file
section .multiboot
	dd MAGIC
	dd FLAGS
	dd CHECKSUM


section .text

    extern kernelMain
    extern callConstructors
    global loader
    
        loader:
                mov esp,kernel_stack
                call callConstructors
                push eax
                push ebx
                call kernelMain
                
        _eof:
             cli
             hlt 
             jmp _eof
                
                
section .bss
resb 16*1024 ;16 KiB
kernel_stack:
