.code32


.section .data

value:    .float 10000.00
value1:   .long 1
output:
.asciz "The result is %f\n"

.text
.type gen_rand, @function
.globl gen_rand



#   
#   Purpose: Generate 2 random floats between -r, r values
#   Arguments: r -> 8(%ebp)
#   Return: 2 floats
#


gen_rand:
    pushl %ebp              # prepare function
    movl  %esp, %ebp
    subl  $8, %esp
    movl  $10000, -4(%ebp)
generate:
    call  rand
    pushl %eax
    xorl  %edx, %edx

    movl  8(%ebp), %ecx
    sal   %ecx
    movl  $10000, %eax
    mull %ecx
  
    movl  %eax, %ecx
    popl  %eax
    divl  %ecx
    movl  %edx, -8(%ebp)
    
    fildl  -8(%ebp)
    fidivl -4(%ebp)
    fisubl  8(%ebp)

exit:
    movl  %ebp, %esp
    popl  %ebp
    ret

# rand() % (10000 * 2r)     
# _____________________  -  r
#
#      10000

