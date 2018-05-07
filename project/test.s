	.file	"test.c"
	.text
	.globl	eeezy
	.type	eeezy, @function
eeezy:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	fldz
	fstps	8(%ebp)
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	eeezy, .-eeezy
	.section	.rodata
.LC2:
	.string	"%f\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$52, %esp
	movl	$10000, -28(%ebp)
	movl	$31, -24(%ebp)
	movl	$17, -20(%ebp)
	movl	$19, -16(%ebp)
	movl	-28(%ebp), %eax
	imull	-24(%ebp), %eax
	cltd
	idivl	-16(%ebp)
	movl	%edx, -52(%ebp)
	fildl	-52(%ebp)
	fildl	-20(%ebp)
	fdivrp	%st, %st(1)
	fstps	-12(%ebp)
	flds	-12(%ebp)
	subl	$4, %esp
	leal	-8(%esp), %esp
	fstpl	(%esp)
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	subl	$12, %esp
	pushl	-12(%ebp)
	call	eeezy
	addl	$16, %esp
	flds	-12(%ebp)
	fnstcw	-42(%ebp)
	movzwl	-42(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -44(%ebp)
	fldcw	-44(%ebp)
	fistpl	-48(%ebp)
	fldcw	-42(%ebp)
	movl	-48(%ebp), %eax
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
