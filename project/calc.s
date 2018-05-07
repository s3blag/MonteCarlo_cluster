.code32

.text
.type calc, @function
.globl calc

#   Arguments:
#   8(%ebp)  - circle radius
#   12(%ebp) - number of points to generate
#   
#   %edx     - points-in-circle counter
#   %ecx     - loop counter 
#
#   -4(%ebp) - x
#   -8(%ebp) - y

calc:
    pushl %ebp              # prepare function
    movl  %esp, %ebp
    
    pushl %ecx              # save registers state
    pushl %edx

    subl  $8, %esp
    
    movl  $0, %edx             # set point counter to 0
    movl  $0, %ecx             # set loop counter to 0

loop:
    finit
    incl  %ecx                 # increase loop counter   

    # Generate x
    pushl 8(%ebp)
    call  gen_rand
    addl  $4, %esp
    fstpl -4(%ebp) 

    # Generate y
    pushl 8(%ebp)
    call  gen_rand
    addl  $4, %esp
    fstpl -8(%ebp) 

    flds  -4(%ebp)             # load x
    fmul  %st(0)               # square x
    
    # Generate y
    pushl 8(%ebp)
    call  gen_rand
    addl  $4, %esp
    fstpl -8(%ebp) 
    
    flds  -8(%ebp)             # load y
    fmul  %st(0)               # square y
    fadd  %st(1), %st(0)       # x^2 + y^2


    flds  8(%ebp)              # load radius
    fmul  %st(0)               # square radius
    fcomi                      # check if r^2 >= x^2 + y^2
    jb    check_loop_counter   # jump if r^2 < x^2 + y^2

increment_counter:
    incl  %edx               

check_loop_counter:
    cmpl  12(%ebp), %ecx
    jl    loop

prepare_result:
    movl  %edx, %eax

restore_registers:
    popl %edx            
    popl %ecx

exit:
    movl  %ebp, %esp
    popl  %ebp
    ret
