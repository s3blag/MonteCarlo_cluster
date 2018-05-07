.code32

.section .data

output:
.asciz "check %f\n"

.text
.type calc, @function
.globl calc

#   Arguments:
#   8(%ebp)  - circle radius
#   12(%ebp) - number of points to generate
#   
#   %-12(%ebp)     - points-in-circle counter
#   %-16(%ebp)     - loop counter 
#
#   -4(%ebp) - x
#   -8(%ebp) - y

calc:
    pushl %ebp              # prepare function
    movl  %esp, %ebp
    
    subl  $16, %esp
    
    movl  $0, -12(%ebp)       # set point counter to 0
    movl  $0, -16(%ebp)       # set loop counter to 0

loop:
    finit
    incl  -16(%ebp)           # increase loop counter   

    # Generate x
    pushl 8(%ebp)
    call  gen_rand
    addl  $4, %esp
    fstp -4(%ebp) 

    # Generate y
    pushl 8(%ebp)
    call  gen_rand
    addl  $4, %esp
    fstp -8(%ebp) 

    flds  -4(%ebp)             # load x
    fmul  %st(0), %st(0)       # square x
    
    flds  -8(%ebp)             # load y
    fmul  %st(0), %st(0)       # square y


    fadd  %st(1), %st(0)       # x^2 + y^2
        

    filds  8(%ebp)             # load radius
    fmul  %st(0)               # square radius

    fcomi                      # check if r^2 >= x^2 + y^2
    jb    check_loop_counter   # jump if r^2 < x^2 + y^2

increment_counter:
    incl  -12(%ebp)               

check_loop_counter:
    movl -16(%ebp), %eax
    cmpl  12(%ebp), %eax
    jl    loop


prepare_result:
    movl  -12(%ebp), %eax

exit:
    movl  %ebp, %esp    
    popl  %ebp

    ret
