.section .text
.global inport8
.global outport8
.global inport16
.global outport16
.global inport32
.global outport32

	inport8:
		movl 4(%esp), %edx //Port Number Param
		inb %dx, %al //Since 8bits input the 16bits of edx register
		andl $0xFF, %eax
		ret

	outport8:
		movl 4(%esp), %edx //
		movl 8(%esp), %eax
		andl $0xFF, %eax
		outb %al, %dx
		ret


	inport16:
		movl 4(%esp), %edx
		inw %dx, %ax
		andl $0xFFFF, %eax
		ret

	outport16:
		movl 4(%esp), %edx
		movl 8(%esp), %eax
		andl $0xFFFF, %eax
		outw %ax, %dx
		ret

	inport32:
		movl 4(%esp), %edx
		inl %dx, %eax
		ret

	outport32:
		movl 4(%esp), %edx
		movl 8(%esp), %eax
		outl %eax, %dx
		ret
