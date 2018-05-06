.code32

.text
.type square, @function
.globl square
square:
    pushl %ebp
    movl  %esp, %ebp
    movl  8(%ebp), %eax   # get function argument

    xorl  %ecx, %ecx

loop:
    cmpl  %eax, %ecx
    incl  %ecx
    jle   loop

exit:
    pushl %ecx

    movl  %ebp, %esp
    popl  %ebp
    ret
