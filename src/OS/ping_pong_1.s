	.file	"ping_pong_1.c"
	.globl	g_flag
	.bss
	.align 4
	.type	g_flag, @object
	.size	g_flag, 4
g_flag:
	.zero	4
	.section	.rodata
.LC0:
	.string	"in child id = %d\n"
.LC1:
	.string	"pong"
.LC2:
	.string	"in parent id = %d\n"
.LC3:
	.string	"ping"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$336, %rsp
	movl	$0, -324(%rbp)
	movl	$0, -328(%rbp)
	leaq	-320(%rbp), %rsi
	movl	$0, %eax
	movl	$19, %edx
	movq	%rsi, %rdi
	movq	%rdx, %rcx
	rep stosq
	leaq	-160(%rbp), %rsi
	movl	$0, %eax
	movl	$19, %edx
	movq	%rsi, %rdi
	movq	%rdx, %rcx
	rep stosq
	call	fork
	movl	%eax, -324(%rbp)
	cmpl	$0, -324(%rbp)
	jns	.L2
	movl	$1, %eax
	jmp	.L11
.L2:
	cmpl	$0, -324(%rbp)
	jne	.L4
	movq	$Handler2, -160(%rbp)
	leaq	-160(%rbp), %rax
	movl	$0, %edx
	movq	%rax, %rsi
	movl	$12, %edi
	call	sigaction
	call	getpid
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
.L7:
	movl	$1, %edi
	call	sleep
	call	getppid
	movl	$10, %esi
	movl	%eax, %edi
	call	kill
	call	pause
	movl	g_flag(%rip), %eax
	cmpl	$2, %eax
	jne	.L5
	movl	$.LC1, %edi
	call	puts
	movl	$0, g_flag(%rip)
	jmp	.L7
.L5:
	movl	$1, %eax
	jmp	.L11
.L4:
	call	getpid
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movq	$Handler, -320(%rbp)
	leaq	-320(%rbp), %rax
	movl	$0, %edx
	movq	%rax, %rsi
	movl	$10, %edi
	call	sigaction
.L10:
	call	pause
	movl	g_flag(%rip), %eax
	cmpl	$1, %eax
	jne	.L8
	movl	$.LC3, %edi
	call	puts
	movl	$0, g_flag(%rip)
	movl	$1, %edi
	call	sleep
	movl	-324(%rbp), %eax
	movl	$12, %esi
	movl	%eax, %edi
	call	kill
	jmp	.L10
.L8:
	movl	$1, %eax
.L11:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.globl	Handler
	.type	Handler, @function
Handler:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	$1, g_flag(%rip)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	Handler, .-Handler
	.globl	Handler2
	.type	Handler2, @function
Handler2:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	$2, g_flag(%rip)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	Handler2, .-Handler2
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
