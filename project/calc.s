.code32

.text
.type calc, @function
.globl calc

#
#   %edi     - points-in-circle counter
#   %ecx     - loop counter 
#

calc:
    pushl %ebp              # prepare function
    movl  %esp, %ebp
    
    pushl %ecx              # save registers state
    pushl %edi

    #subl  $8, %esp

    
    movl  $0, %edi             # set point counter to 0
    movl  $0, %ecx             # set loop counter to 0

loop:
    finit
    incl  %ecx                 # increase loop counter    
    flds  8(%ebp)              # load x
    fmul  %st(0)               # square x
    flds  12(%ebp)             # load y
    fmul  %st(0)               # square y
    fadd  %st(1), %st(0)       # x^2 + y^2
    flds  16(%ebp)             # load radius
    fmul  %st(0)               # square radius
    fcomi                      # check if r^2 >= x^2 + y^2
    jb    check_loop_counter   # jump if r^2 < x^2 + y^2

increment_counter:
    incl  %edi               

check_loop_counter:
    cmpl  20(%ebp), %ecx
    jl    loop

prepare_result:
    movl  %edi, %eax

restore_registers:
    popl %edi              
    popl %ecx

exit:
    movl  %ebp, %esp
    popl  %ebp
    ret
