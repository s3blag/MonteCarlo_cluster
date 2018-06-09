.section .data

.text
.type calculate, @function
.globl calculate

#   Argumenty:
#   - pierwszy argument - edi (r)
#   - drugi argument    - esi (liczba punktów do wygenerowania)

#   Zmienne:
#   - -4(%rbp) - licznik punktów spełniających równanie
#   - -8(%rbp) - licznik iteracji
#   - -12(%rbp)- promień okręgu
#   - -16(%rbp)- liczba punktów do wygenerowania
#   - -20(%rbp)- wynik x^2 + y^2

calculate:
    push     %rbp              # prepare function
    mov      %rsp, %rbp
    
    subq     $20, %rsp
    
    movl     $0, -4(%rbp)       # wyzerowanie licznika punktów
    movl     $0, -8(%rbp)       # wyzerowanie licznika iteracji
    movl     %edi, -12(%rbp)    # r
    movl     %esi, -16(%rbp)    # arg: 2 - liczba punktów
                                #          do wygenerowania
loop:
    incl     -8(%rbp)

    # Generate x
    movl     -12(%rbp), %eax
    call     gen_rand

    pxor     %xmm4, %xmm4
    movups 	 %xmm0, %xmm4       # x - xmm4

    # Generate y
    movl     -12(%rbp), %eax
    call     gen_rand  

    pxor     %xmm3, %xmm3
    movups   %xmm0, %xmm3       # y - xmm3

    mulss    %xmm3, %xmm3       # y^2

    mulss    %xmm4, %xmm4       # x^2

    addss    %xmm4, %xmm3       # x^2 + y^2 - wynik w xmm1
    movss    %xmm3, -20(%rbp)
    
    movl     -12(%rbp), %eax
    imull    %eax, %eax
    pxor     %xmm0, %xmm0
    cvtsi2ss %eax, %xmm0        # r^2

    ucomiss	 -20(%rbp), %xmm0
    jb       check_loop_counter

increment_points_counter:
    incl     -4(%rbp) 

check_loop_counter:
    movl     -8(%rbp), %eax
    cmpl     -16(%rbp), %eax
    jl       loop

prepare_result:
    movl     -4(%rbp), %eax
exit:
    movq     %rbp, %rsp    
    popq     %rbp

    ret
