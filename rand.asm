section .text

	global randomnumber

	randomnumber:

		mov ax, dx
		xor dx, dx
		mov cx, 10
		div cx

		add dl, '0'
		mov al,dl

