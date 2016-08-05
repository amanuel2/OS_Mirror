.section .text
.global idt_load
idt_load:
	lidt 4(%esp)
	sti
	ret

