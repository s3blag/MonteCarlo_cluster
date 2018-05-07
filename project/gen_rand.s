.code32


.section .data

output:
.asciz "The result (x or y) is %f\n"

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
    movl  $1000000, -4(%ebp)
generate:
    call  rand
    pushl %eax
    xorl  %edx, %edx

    movl  8(%ebp), %ecx
    sal   %ecx
    movl  $1000000, %eax
    mull  %ecx
  
    movl  %eax, %ecx
    popl  %eax
    divl  %ecx
    movl  %edx, -8(%ebp)

    
    fildl  -8(%ebp)
    fidivl -4(%ebp)
    fisubl  8(%ebp)

    #subl   $4, %esp
    #fstpl  (%esp)
    #pushl  $output
    #call   printf 
    #addl   $8, %esp

exit:
    movl  %ebp, %esp
    popl  %ebp
    ret

# rand() % (10000 * 2r)     
# _____________________  -  r
#
#      10000

