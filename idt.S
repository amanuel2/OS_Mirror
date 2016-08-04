.section .text
.global idt_load
.extern idtp
.extern common_interrupt_handler
idt_load:
	lidt 4(%esp)
	sti
	ret

.global common_handler

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
	mov %ds,%ax
	pushl %eax

	mov 0x10,%ax
	mov %ax,%ds
	mov %ax,%es 
	mov %ax,%fs
	mov %ax,%gs

	call common_interrupt_handler

	popl %eax

	mov %ax,%ds 
	mov %ax,%es 
	mov %ax,%fs 
	mov %ax,%gs 

	popa
	add 8,%esp
	sti
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
interrupt 17
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
interrupt 30
no_error_code_interrupt 31
no_error_code_interrupt 32
no_error_code_interrupt 33
no_error_code_interrupt 34