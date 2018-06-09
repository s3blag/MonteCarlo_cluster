	.file	"test.c"
	.text
	.globl	gen_rand
	.type	gen_rand, @function
gen_rand:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6


	subq	 $48, %rsp
	movl	 %edi, -36(%rbp)     #    r    #

	movl	 $1000, -24(%rbp)	###########
	movl	 -24(%rbp), %eax
	addl	 %eax, %eax			# 2 * 1000# - a
	imull	 -36(%rbp), %eax     # a*r#  ## modulus
	movl	 %eax, -20(%rbp)

	call	 rand
	movl	 %eax, -16(%rbp)
	movl	 -16(%rbp), %eax    # rand res#
	cltd                        # edx:eax #
	idivl	 -20(%rbp)			#rand / modulus #
	movl	 %edx, -12(%rbp)    # reszta #

	# -12(%rbp) - licznik
	# -24(%rbp) - mianownik
	# -36(%rbp) - r

	pxor	 %xmm0, %xmm0
	cvtsi2ss -12(%rbp), %xmm0
	pxor	 %xmm1, %xmm1
	cvtsi2ss -24(%rbp), %xmm1

	divss	 %xmm1, %xmm0
	movss	 %xmm0, -8(%rbp)

	# lewa strona w -8(%rbp)

	pxor	 %xmm0, %xmm0
	cvtsi2ss -36(%rbp), %xmm0
	movss	 -8(%rbp), %xmm1
	subss	 %xmm0, %xmm1

	movaps 	 %xmm1, %xmm0
	movss	 %xmm0, -4(%rbp)
	movss    -4(%rbp), %xmm0


	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	gen_rand, .-gen_rand
	.section	.rodata
.LC0:
	.string	"rand: [%f]\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, %edi
	call	time

	movl	%eax, %edi
	call	srand

	movl	$1, -8(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, %edi
	call	gen_rand

	movd	%xmm0, %eax
	movl	%eax, -4(%rbp)
	cvtss2sd	-4(%rbp), %xmm0
	movl	$.LC0, %edi
	movl	$1, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
