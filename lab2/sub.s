.code32

SYSEXIT = 1
EXIT_SUCCESS = 0

.section .data

number1: .long 0x45454545, 0xD5555555, 0x88888888, 0x22222222
index = ((. - number1)/4)-1
number2: .long 0x52222222, 0x55555555, 0x22222222, 0x31111111

.section .text
.global _start

_start:
	movl	$index,%ecx
	clc
	pushf
	
substract_loop:
	popf
	movl	number1(,%ecx,4),%eax
	movl	number2(,%ecx,4),%ebx
	sbbl	%ebx,%eax
	pushl	%eax
	pushf
	subl	$1,%ecx
	cmpl	$0,%ecx
	jge		substract_loop

check_overflow:
	popf
	jnc		exit

make_overflow:
	pushl	$0xFFFFFFFF

exit:
	movl	$SYSEXIT,%eax
	movl	$EXIT_SUCCESS,%ebx
	int		$0x80
