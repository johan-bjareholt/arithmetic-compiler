.data

fprinti: .asciz "%i\n"

.text

.global prints
prints:
	call puts
	ret

.global printi
printi:
	push	%rsi
	push	%rax

	movq	%rdi, %rsi
	movq	$fprinti, %rdi
	xor		%rax, %rax
	call	printf

	pop		%rax
	pop		%rsi
	ret

