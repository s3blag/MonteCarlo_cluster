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
    mul   %ecx
    movl  %eax, %ecx
    popl  %eax
    divl  %ecx
    movl  %edx, (value1)
    
    
    finit
    flds  value1
    fidivs  value
    fisubs  8(%ebp)
    #subl $8, %esp
    #fstpl (%esp)
    #pushl $output
    #call printf 
    #addl $8, %esp
    #fld  -8(%ebp)
    #filds  -4(%ebp)
    #filds  value1
    
    #fdiv
    #fsubs  8(%ebp)

prepare_result:
    #movl  %edx, %eax
    movl  value1, %eax
exit:
    movl  %ebp, %esp
    popl  %ebp
    ret

# rand() % (10000 * 2r)     
# _____________________  -  r
#
#      10000

