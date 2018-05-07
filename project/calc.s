.code32

.text
.type calc, @function
.globl calc

calc:
    pushl %ebp              # prepare function
    movl %esp, %ebp
    subl $8, %esp

    movl $0, -4(%ebp)       # set point counter to 0
    movl $0, -8(%ebp)       # set loop counter to 0

loop:
    finit
    incl -8(%ebp)           # increase loop counter    
    flds 8(%ebp)            # load x
    fmul %st(0)             # square x
    flds 12(%ebp)           # load y
    fmul %st(0)             # square y
    fadd %st(1), %st(0)     # x^2 + y^2
    flds 16(%ebp)           # load radius
    fmul %st(0)             # square radius
    fcomi                   # check if x^2 + y^2 <= r^2
    jbe continue

count:
    incl -4(%ebp)           # increase point counter

continue:
    movl -8(%ebp), %eax     # check loop counter
    cmp 20(%ebp), %eax
    jl loop

exit:
    movl -4(%ebp), %eax
    movl %ebp, %esp
    popl %ebp
    ret
