.section .text

        .global common_handler
        .extern common_interrupt_exception_handler

        .macro interrupt number
            .global isr\number
            isr\number:
                cli
                pushl $\number
                jmp common_handler
        .endm

        .macro no_error_code_interrupt number
            .global isr\number
            isr\number:
                cli
                pushl $0
                pushl $\number
                jmp common_handler
        .endm


        common_handler:
            pusha
            pushl %ds
            pushl %esp
       # call C++ Handler
           call common_interrupt_exception_handler
            addl $4,%esp
       # restore registers
            popl %ds
            popa
            addl $8,%esp
            iret


no_error_code_interrupt 0
no_error_code_interrupt 1
no_error_code_interrupt 2
no_error_code_interrupt 3
no_error_code_interrupt 4
no_error_code_interrupt 5
no_error_code_interrupt 6
no_error_code_interrupt 7
interrupt 8
no_error_code_interrupt 9
interrupt 10
interrupt 11
interrupt 12
interrupt 13
interrupt 14
no_error_code_interrupt 15
no_error_code_interrupt 16
no_error_code_interrupt 17
no_error_code_interrupt 18
no_error_code_interrupt 19
no_error_code_interrupt 20
no_error_code_interrupt 21
no_error_code_interrupt 22
no_error_code_interrupt 23
no_error_code_interrupt 24
no_error_code_interrupt 25
no_error_code_interrupt 26
no_error_code_interrupt 27
no_error_code_interrupt 28
no_error_code_interrupt 29
no_error_code_interrupt 30
no_error_code_interrupt 31