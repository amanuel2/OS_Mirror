;Global MultiBoot Kernel Recongnzatio

; setting up the Multiboot header - see GRUB docs for details
MODULEALIGN equ  1<<0             ; align loaded modules on page boundaries
MEMINFO     equ  1<<1             ; provide memory map
FLAGS       equ  MODULEALIGN | MEMINFO  ; this is the Multiboot 'flag' field
MAGIC       equ    0x1BADB002     ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)  ; checksum required


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
	; reserve initial kernel stack space -- that's 16k.
	STACKSIZE equ 0x4000
	global loader
	global BootPageDirectory

        loader:
                	;Enable Paging START

				    ; NOTE: Until paging is set up, the code must be position-independent and use physical
				    ; addresses, not virtual ones!
				    mov ecx, (BootPageDirectory - KERNEL_VIRTUAL_BASE)
				    mov cr3, ecx                                        ; Load Page Directory Base Register.

				    mov ecx, cr4
				    or ecx, 0x00000010                          ; Set PSE bit in CR4 to enable 4MB pages.
				    mov cr4, ecx

				    mov ecx, cr0
				    or ecx, 0x80000000                          ; Set PG bit in CR0 to enable paging.
				    mov cr0, ecx


					lea ebx, [higherhalf]
				    jmp ebx ; Absolute Jump

		higherhalf:
		    extern kernelMain
   		    extern callConstructors

		   		; Unmap the identity-mapped first 4MB of physical address space. It should not be needed
			    ; anymore.
			    mov dword [BootPageDirectory], 0
			    invlpg [0]

		       	mov esp, stack            ; set up the stack
                call callConstructors



              extern kernel_virtual_start
    		  extern kernel_virtual_end
    		  extern kernel_physical_start
		      extern kernel_physical_end


	    		push kernel_virtual_end ; 2
	    		push 5
	    		push kernel_virtual_start ; 1
	    		push kernel_physical_start ; 3
	    		push kernel_physical_end ; 4
				push eax ; 5
				push ebx ; 6
                call kernelMain


                jmp _eof
                
        _eof:
             cli
             hlt 
             jmp _eof
                
                
section .bss
align 32
stack:
    resb STACKSIZE      ; reserve 16k stack on a uint64_t boundary
