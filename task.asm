section .text
global switch_task_a
switch_task_a:
    pusha
    pushf
    mov eax,cr3 ;Push CR3
    push eax
    mov eax,[esp+44] ;The first argument, where to save
    mov [eax+4],ebx
    mov [eax+8],ecx
    mov [eax+12],edx
    mov [eax+16],esi
    mov [eax+20],edi
    mov ebx, [esp+36] ;EAX
    mov ecx, [esp+40] ;IP
    mov edx,[esp+20] ;ESP
    add edx,4 ;Remove the return value ;)
    mov esi,[esp+16] ;EBP
    mov edi,[esp+4] ;EFLAGS
    mov [eax],ebx
    mov [eax+24],edx
    mov [eax+28],esi
    mov [eax+32],ecx
    mov [eax+36],edi
    pop ebx ;CR3
    mov [eax+40],ebx
    push ebx ;Goodbye again ;)
    mov eax,[esp+48] ;Now it is the new object
    mov ebx,[eax+4] ;EBX
    mov ecx, [eax+8] ;ECX
    mov edx, [eax+12] ;EDX
    mov esi, [eax+16] ;ESI
    mov edi,[eax+20] ;EDI
    mov ebp, [eax+28] ;EBP
    push eax
    mov eax, [eax+36] ;EFLAGS
    push eax
    popf
    pop eax
    mov esp,[eax+24] ;ESP
    push eax
    mov eax, [eax+40] ;CR3
    mov cr3,eax
    pop eax
    push eax
    mov eax, [eax+32] ;EIP
    xchg eax,[esp] ;We do not have any more registers to use as tmp storage
    mov eax, [eax] ;EAX
    ret ;This ends all!
