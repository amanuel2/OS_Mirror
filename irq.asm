section .text
extern irq_handler


        %macro irq 1
                global irq%1
                irq%1:
                    cli
                    push 0
                    push %1
                    jmp common_handler_irq
            %endmacro

common_handler_irq:
    ; save registers
            pusha
           ; push ds
            push ebp
		     push edi
		     push esi

		     push edx
		     push ecx
		     push ebx
		     push eax
            push esp
    ; call C++ Handler
           call irq_handler
           add esp,4
    ; restore registers
           ; pop ds
           pop eax
 		   pop ebx
     	   pop ecx
           pop edx

           pop esi
           pop edi
           pop ebp
            ;popa
            add esp,8
            iret

;TODO FOR LOOP
irq 0
irq 1
irq 2
irq 3
irq 4
irq 5
irq 6
irq 7
irq 8
irq 9
irq 10
irq 11
irq 12
irq 13
irq 14
irq 15
