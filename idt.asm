section .text
global idt_load
;global load
;load:
;	call test_func
;	ret

idt_load:
	lidt [esp+4]
	ret

