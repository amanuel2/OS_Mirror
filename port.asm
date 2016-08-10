section .text
global inport8
global outport8
global inport16
global outport16
global inport32
global outport32

	inport8:
		mov edx, [esp + 4]
		in al, dx
		ret

	outport8:
		mov   edx, [esp + 4]
		mov   al, [esp + 4 + 4]
		out   dx, al
		ret



	inport16:
		mov edx, [esp + 4]
		in ax, dx
		ret

	outport16:
		mov   edx, [esp + 4]
		mov   ax, [esp + 4 + 4]
		out   dx, ax
		ret

	inport32:
		mov edx, [esp + 4]
		in eax, dx
		ret

	outport32:
		mov   edx, [esp + 4]
		mov   eax, [esp + 4 + 4]
		out   dx, eax
		ret