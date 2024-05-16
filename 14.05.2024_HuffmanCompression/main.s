	.file	"main.c"
	.text
	.section	.rodata
.LC0:
	.string	"- %d ; "
	.text
	.globl	fillLetters
	.type	fillLetters, @function
fillLetters:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	cmpq	$0, -24(%rbp)
	je	.L7
	cmpq	$0, -32(%rbp)
	je	.L7
	movl	$0, -4(%rbp)
	jmp	.L5
.L6:
	movl	-4(%rbp), %edx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	subl	$97, %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-4(%rbp), %edx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	leaq	-97(%rax), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	addl	$1, %edx
	movb	%dl, (%rax)
	addl	$1, -4(%rbp)
.L5:
	movl	-4(%rbp), %edx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L6
	jmp	.L1
.L7:
	nop
.L1:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	fillLetters, .-fillLetters
	.globl	createNode
	.type	createNode, @function
createNode:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, %eax
	movl	%esi, -24(%rbp)
	movb	%al, -20(%rbp)
	movl	$24, %esi
	movl	$1, %edi
	call	calloc@PLT
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movzbl	-20(%rbp), %edx
	movb	%dl, (%rax)
	movq	-8(%rbp), %rax
	movl	-24(%rbp), %edx
	movl	%edx, 4(%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	createNode, .-createNode
	.globl	createNodes
	.type	createNodes, @function
createNodes:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	cmpq	$0, -40(%rbp)
	je	.L18
	cmpq	$0, -48(%rbp)
	je	.L18
	movl	$0, -20(%rbp)
	jmp	.L14
.L17:
	movl	-20(%rbp), %edx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L19
	movl	-20(%rbp), %eax
	leaq	0(,%rax,8), %rdx
	movq	-40(%rbp), %rax
	leaq	(%rdx,%rax), %rbx
	movl	$24, %esi
	movl	$1, %edi
	call	calloc@PLT
	movq	%rax, (%rbx)
	movl	-20(%rbp), %eax
	leal	97(%rax), %edx
	movl	-20(%rbp), %eax
	leaq	0(,%rax,8), %rcx
	movq	-40(%rbp), %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	movb	%dl, (%rax)
	movl	-20(%rbp), %edx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movl	-20(%rbp), %eax
	leaq	0(,%rax,8), %rcx
	movq	-40(%rbp), %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	movsbl	%dl, %edx
	movl	%edx, 4(%rax)
	jmp	.L16
.L19:
	nop
.L16:
	addl	$1, -20(%rbp)
.L14:
	cmpl	$31, -20(%rbp)
	jbe	.L17
	jmp	.L10
.L18:
	nop
.L10:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	createNodes, .-createNodes
	.globl	createListNode
	.type	createListNode, @function
createListNode:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$16, %esi
	movl	$1, %edi
	call	calloc@PLT
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	createListNode, .-createListNode
	.globl	pushList
	.type	pushList, @function
pushList:
.LFB10:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	cmpq	$0, -32(%rbp)
	jne	.L23
	movl	$0, %eax
	jmp	.L24
.L23:
	cmpq	$0, -24(%rbp)
	jne	.L25
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	createListNode
	jmp	.L24
.L25:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	4(%rax), %edx
	movq	-32(%rbp), %rax
	movl	4(%rax), %eax
	cmpl	%eax, %edx
	jle	.L26
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	createListNode
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	jmp	.L24
.L26:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	pushList
	movq	-24(%rbp), %rdx
	movq	%rax, 8(%rdx)
	movq	-24(%rbp), %rax
.L24:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	pushList, .-pushList
	.globl	createList
	.type	createList, @function
createList:
.LFB11:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L28
	movl	$0, %eax
	jmp	.L29
.L28:
	movq	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L30
.L32:
	movl	-12(%rbp), %eax
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L31
	movl	-12(%rbp), %eax
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	pushList
	movq	%rax, -8(%rbp)
.L31:
	addl	$1, -12(%rbp)
.L30:
	cmpl	$31, -12(%rbp)
	jbe	.L32
	movq	-8(%rbp), %rax
.L29:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	createList, .-createList
	.globl	createTree
	.type	createTree, @function
createTree:
.LFB12:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L34
	movl	$0, %eax
	jmp	.L35
.L34:
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	jmp	.L36
.L39:
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L40
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movl	4(%rax), %edx
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movq	(%rax), %rax
	movl	4(%rax), %eax
	addl	%edx, %eax
	movl	%eax, %esi
	movl	$42, %edi
	call	createNode
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 16(%rax)
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movq	8(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	pushList
.L36:
	cmpq	$0, -16(%rbp)
	jne	.L39
	jmp	.L38
.L40:
	nop
.L38:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
.L35:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	createTree, .-createTree
	.globl	createCode
	.type	createCode, @function
createCode:
.LFB13:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, %eax
	movq	%rsi, -32(%rbp)
	movb	%al, -20(%rbp)
	cmpq	$0, -32(%rbp)
	jne	.L42
	movl	$-1, %eax
	jmp	.L43
.L42:
	movq	-32(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	%al, -20(%rbp)
	jne	.L44
	movl	$0, %eax
	jmp	.L43
.L44:
	movq	-32(%rbp), %rax
	movq	8(%rax), %rdx
	movsbl	-20(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	createCode
	movl	%eax, -8(%rbp)
	movq	-32(%rbp), %rax
	movq	16(%rax), %rdx
	movsbl	-20(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	createCode
	movl	%eax, -4(%rbp)
	cmpl	$-1, -8(%rbp)
	je	.L45
	movl	-8(%rbp), %eax
	addl	%eax, %eax
	orl	$1, %eax
	jmp	.L43
.L45:
	cmpl	$-1, -4(%rbp)
	je	.L46
	movl	-4(%rbp), %eax
	addl	%eax, %eax
	jmp	.L43
.L46:
	movl	$-1, %eax
.L43:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	createCode, .-createCode
	.globl	compress
	.type	compress, @function
compress:
.LFB14:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	cmpq	$0, -40(%rbp)
	je	.L48
	cmpq	$0, -48(%rbp)
	jne	.L49
.L48:
	movl	$0, %eax
	jmp	.L50
.L49:
	movl	$4, %esi
	movl	$1, %edi
	call	calloc@PLT
	movq	%rax, -24(%rbp)
	movl	$0, -28(%rbp)
	jmp	.L51
.L52:
	movl	-28(%rbp), %edx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	-28(%rbp), %edx
	leaq	0(,%rdx,4), %rcx
	movq	-24(%rbp), %rdx
	leaq	(%rcx,%rdx), %rbx
	movq	-48(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	createCode
	movl	%eax, (%rbx)
	addl	$1, -28(%rbp)
.L51:
	movl	-28(%rbp), %edx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L52
	movl	-28(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	$-1, (%rax)
	movq	-24(%rbp), %rax
.L50:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	compress, .-compress
	.section	.rodata
.LC1:
	.string	"asd"
.LC2:
	.string	"ASJDKl"
	.text
	.globl	huffman
	.type	huffman, @function
huffman:
.LFB15:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	cmpq	$0, -56(%rbp)
	jne	.L54
	movl	$0, %eax
	jmp	.L56
.L54:
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	$0, -48(%rbp)
	movq	$0, -40(%rbp)
	movq	$0, -32(%rbp)
	movq	$0, -24(%rbp)
	movq	-56(%rbp), %rdx
	leaq	-48(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fillLetters
	movl	$0, %eax
.L56:
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L57
	call	__stack_chk_fail@PLT
.L57:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	huffman, .-huffman
	.globl	main
	.type	main, @function
main:
.LFB16:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$144, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movabsq	$8097872770507041889, %rax
	movabsq	$7020093033223058031, %rdx
	movq	%rax, -144(%rbp)
	movq	%rdx, -136(%rbp)
	movq	$0, -128(%rbp)
	movq	$0, -120(%rbp)
	movq	$0, -112(%rbp)
	movq	$0, -104(%rbp)
	movq	$0, -96(%rbp)
	movq	$0, -88(%rbp)
	movq	$0, -80(%rbp)
	movq	$0, -72(%rbp)
	movq	$0, -64(%rbp)
	movq	$0, -56(%rbp)
	movq	$0, -48(%rbp)
	movq	$0, -40(%rbp)
	movq	$0, -32(%rbp)
	movq	$0, -24(%rbp)
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L60
	call	__stack_chk_fail@PLT
.L60:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
