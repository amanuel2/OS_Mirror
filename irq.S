.section .text
.extern irq_handler

        .macro irq number
        	.global irq\number
        	irq\number:
        		cli
                pushl $0
        		pushl $\number
        		jmp common_handler_irq
        .endm

common_handler_irq:
	  # save registers
            
            
            pusha

            # call C++ Handler
            call irq_handler

            # restore registers
            popa
            iret


#TODO FOR LOOP
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

