
SYSEXIT = 1
EXIT_SUCCESS = 0

.section .data
zero:       .float 0.00

single1:    .float 1.234
single2:    .float 2.345
single3:    .float -2.345

double1:    .double 3.333
double2:    .double 4.123
double3:    .double -5.111

mask:		.short 0x003f

precision:		
			#.short 0x000	        # single
			.short 0x200			# double

rounding:		
			.short 0x000			# to nearest
			#.short 0x400			# toward -inf
			#.short 0x800			# toward +inf
			#.short 0xc00			# toward 0 - obciecie

control:	.short 0x0000

.section .text
.global _start
_start:

    mov     precision, %ax
    mov     rounding, %bx
    mov     mask, %cx
    mov     control, %dx
    
    add     %ax, %dx
    add     %bx, %dx
    add     %cx, %dx

    mov     %dx, control

    fldcw   control

    #jmp     generate_exceptions

    #działania double
    jmp     add_d

# SINGLE
add_s:
    flds    single1
    fadds   single2

sub_s:
    flds    single2
    fsubs   single1

mul_s:
    flds    single1
    fmuls   single2

div_s:
    flds    single1
    fdivs   single2
    jmp     exit

# DOUBLE
add_d:
    fldl    double1
    faddl   double2

sub_d:
    fldl    double2
    fsubl   double1

mul_d:
    fldl    double1
    fmull   double2

div_d:
    fldl    double1
    fdivl   double2
    jmp     exit

generate_exceptions:

    #NaN
    fldz
    fdivs   zero

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
    movl  $SYSEXIT, %eax
    movl  $EXIT_SUCCESS, %ebx
    int   $0x80
