section .text
    global gdt_flush
    global invalidate_page_vm
    extern gp
    gdt_flush:
        lgdt [esp+4]
        mov ax,0x10
        mov ds,ax
        mov es,ax
        mov fs,ax
        mov gs,ax
        mov ss,ax
        jmp 0x08:flush2
    flush2:
        ret

    invalidate_page_vm:
        mov eax, [esp+4]
        invlpg [eax]
        ret
