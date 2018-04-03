SYS_EXIT = 1
EXIT_SUCCESS = 0

.data

zero:		.float 0.0

single1:	.float 1.34
single2:	.float 11.23
single3:	.float -3.14

double1:	.double 3.1
double2:	.double 0.6
double3:	.double -2.17

masks:		.short 0x003f

prec:		
			#.short 0x000			# single
			.short 0x200			# double

round:		
			#.short 0x000			# to nearest
			.short 0x400			# toward -inf
			#.short 0x800			# toward +inf
			#.short 0xc00			# toward 0 - uciecie

c_word:	.short 0x0000

.text
.global _start

_start:
	mov		round, %ax
	mov		prec, %bx
	mov		masks, %cx
	mov		c_word,%dx

	add		%ax, %dx
	add		%bx, %dx
	add		%cx, %dx
	mov		%dx, c_word
	# ustaw control register
	fldcw	c_word

	mov		$0x000, %ax

	jmp		addition

addition:
	cmp		%bx, %ax
	jne		double_add

single_add:
	flds	single1
	fadds	single2
	jmp		exit

double_add:
	fldl	double1
	faddl	double2
	jmp		exit

substraction:
	cmp		%bx, %ax
	jne		double_sub

single_sub:
	flds	single1
	fsubs	single2
	jmp		exit

double_sub:
	fldl	double1
	fsubl	double2
	jmp		exit

multiplication:
	cmp		%bx, %ax
	jne		double_mul

single_mul:
	flds	single1
	fmuls	single2
	jmp		exit

double_mul:
	fldl	double1
	fmull	double2
	jmp		exit

division:
	cmp		%bx, %ax
	jne		double_div

single_div:
	flds	single1
	fdivs	single2
	jmp		exit

double_div:
	fldl	double1
	fdivl	double2
	jmp		exit

generate_exceptions:
	
	#NaN
	fldz					
	fdivs	zero

	#+inf
	flds	single1			
	fdivs	zero

	#-inf
	flds	single3
	fdivs	zero

	#+0
	fldz					
	fdivs	single1

	#-0
	fldz					
	fdivs	single3
 
exit:
	mov	$SYS_EXIT, %eax
	mov	$EXIT_SUCCESS, %ebx
	int	$0x80
