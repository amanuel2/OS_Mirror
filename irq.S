.section .text

.extern irq_handler
        .macro irq number
        	.global isr\number
        	isr\number:
        		cli
        		pushl $\number
        		jmp common_handler_irq
        .endm

common_handler_irq:
	 # save registers
            
     pusha
     #    mov %ds,%ax
     #    pushl %eax

     # call C++ IRQ Handler
     call irq_handler
            
     #    popl %eax
     #       mov %ds, %ax
           
     mov %eax, %esp # switch the stack

     # restore registers
     popa
     sti
     iret

