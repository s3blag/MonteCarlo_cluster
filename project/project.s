	.file	"project.c"
	.section	.rodata
.LC0:
	.string	"%f \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
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
	subl	$36, %esp
	subl	$12, %esp
	pushl	$0
	call	time
	addl	$16, %esp
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	subl	$12, %esp
	pushl	%eax
	call	srand
	addl	$16, %esp
	subl	$12, %esp
	pushl	$20
	call	gen_rand
	addl	$16, %esp
	fstps	-28(%ebp)
	movl	-28(%ebp), %eax
	movl	%eax, -12(%ebp)
	flds	-12(%ebp)
	subl	$4, %esp
	leal	-8(%esp), %esp
	fstpl	(%esp)
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
