	.file	"thread.c"
	.globl	array
	.bss
	.align 32
	.type	array, @object
	.size	array, 400000
array:
	.zero	400000
	.section	.rodata
.LC0:
	.string	"%d\n"
.LC1:
	.string	"error"
.LC2:
	.string	"Success"
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
	subq	$48, %rsp
	movl	$0, -44(%rbp)
	movl	$0, -40(%rbp)
	movl	$0, -36(%rbp)
	call	clock
	movl	%eax, -36(%rbp)
	movl	$0, %edx
	movl	$0, %esi
	movl	$main._omp_fn.0, %edi
	call	GOMP_parallel_start
	movl	$0, %edi
	call	main._omp_fn.0
	call	GOMP_parallel_end
	call	clock
	movl	%eax, %edx
	movl	-36(%rbp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -36(%rbp)
	movl	-36(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$1, -44(%rbp)
	jmp	.L2
.L5:
	movl	-44(%rbp), %eax
	cltq
	movl	array(,%rax,4), %edx
	movl	-44(%rbp), %eax
	subl	$1, %eax
	cltq
	movl	array(,%rax,4), %eax
	addl	$1, %eax
	cmpl	%eax, %edx
	je	.L3
	movl	$.LC1, %edi
	call	puts
	movl	$1, %eax
	jmp	.L6
.L3:
	addl	$1, -44(%rbp)
.L2:
	cmpl	$99999, -44(%rbp)
	jle	.L5
	movl	$.LC2, %edi
	call	puts
	movl	$0, %eax
.L6:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.type	main._omp_fn.0, @function
main._omp_fn.0:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	call	omp_get_num_threads
	movl	%eax, %ebx
	call	omp_get_thread_num
	movl	%eax, %esi
	movl	$100000, %eax
	cltd
	idivl	%ebx
	movl	%eax, %ecx
	movl	$100000, %eax
	cltd
	idivl	%ebx
	movl	%edx, %eax
	cmpl	%eax, %esi
	jl	.L8
.L11:
	imull	%ecx, %esi
	movl	%esi, %edx
	addl	%edx, %eax
	leal	(%rax,%rcx), %edx
	cmpl	%edx, %eax
	jge	.L7
	movl	%eax, -20(%rbp)
.L10:
	movl	-20(%rbp), %eax
	cltq
	movl	-20(%rbp), %ecx
	movl	%ecx, array(,%rax,4)
	addl	$1, -20(%rbp)
	cmpl	%edx, -20(%rbp)
	jl	.L10
	jmp	.L7
.L8:
	movl	$0, %eax
	addl	$1, %ecx
	jmp	.L11
.L7:
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main._omp_fn.0, .-main._omp_fn.0
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
