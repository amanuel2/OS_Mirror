;Global MultiBoot Kernel Recongnzation
MAGIC equ 0x1badb002
FLAGS equ (1<<0 | 1<<1)
CHECKSUM equ -(MAGIC + FLAGS)


;Putting in object file
section .multiboot
	dd MAGIC
	dd FLAGS
	dd CHECKSUM




section .data

KERNEL_VIRTUAL_BASE equ 0xC0000000                  ; 3GB
KERNEL_PAGE_NUMBER equ (KERNEL_VIRTUAL_BASE >> 22)  ; Page directory index of kernel's 4MB PTE.

align 0x1000
BootPageDirectory:
    ; This page directory entry identity-maps the first 4MB of the 32-bit physical address space.
    ; All bits are clear except the following:
    ; bit 7: PS The kernel page is 4MB.
    ; bit 1: RW The kernel page is read/write.
    ; bit 0: P  The kernel page is present.
    ; This entry must be here -- otherwise the kernel will crash immediately after paging is
    ; enabled because it can't fetch the next instruction! It's ok to unmap this page later.
    dd 0x00000083
    times (KERNEL_PAGE_NUMBER - 1) dd 0                 ; Pages before kernel space.
    ; This page directory entry defines a 4MB page containing the kernel.
    dd 0x00000083
    times (1024 - KERNEL_PAGE_NUMBER - 1) dd 0  ; Pages after the kernel image.


section .text
    extern kernelMain
    extern callConstructors
    extern page_directory
	extern pages_init
	; reserve initial kernel stack space -- that's 16k.
	STACKSIZE equ 0x4000
	; setting up entry point for linker
	loader equ (_loader - 0xC0000000)
	global loader

        _loader:
                ;Enable Paging START

	                call pages_init


					mov eax, (BootPageDirectory - KERNEL_VIRTUAL_BASE)
					mov cr3, eax ; Load Page Directory to the cr3 Register

					;TODO SET UP PSE (4MB Page Frame)

					;Enable Paging
					mov ebx, cr0
					or ebx, 0x80000000 ; Set 31'th bit to 1
					mov cr0, ebx ; Update the cr0 register

                 ;Enable Paging END
				lea ebx, [higherhalf]
				jmp ebx

		higherhalf:
		   		; Unmap the identity-mapped first 4MB of physical address space. It should not be needed
			    ; anymore.
			    mov dword [BootPageDirectory], 0
			    invlpg [0]

		       	mov esp, stack           ; set up the stack
                call callConstructors

                push eax
                push ebx
                call kernelMain
                
        _eof:
             cli
             hlt 
             jmp _eof
                
                
section .bss
align 32
stack:
    resb STACKSIZE      ; reserve 16k stack on a uint64_t boundary
