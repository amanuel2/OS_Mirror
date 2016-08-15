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
    extern page_directory
	extern pages_init
    global loader

        loader:
                mov esp,kernel_stack
                call callConstructors

                ;Enable Paging START

	                call pages_init
					mov eax, page_directory


					mov cr3, eax ; Load Page Directory to the cr3 Register

					;TODO SET UP PSE (4MB Page Frame)

					;Enable Paging
					mov ebx, cr0
					or ebx, 0x80000000 ; Set 31'th bit to 1
					mov cr0, ebx ; Update the cr0 register

                ;Enable Paging END
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
