.section .data

.text
.type gen_rand, @function
.globl gen_rand

#   
#   Purpose: Generate 2 random floats between -r, r values
#   Arguments: r -> 8(%ebp)
#   Return: 2 floats
#
#   function with int parameter passes value in %rax
#   function with float parameter passes value in %xmm0

gen_rand:
    push %rbp             
    mov  %rsp, %rbp 

    subq $16, %rsp

    # -4(%rbp)  - r
    # -8(%rbp)  - mnoznik ( 1000 )  
    # -12(%rbp) - dzielnik modulo
    # -16(%rbp) - licznik

generate:
    mov  %eax, -4(%rbp) 
    mov  $10000, %ebx         # -> mult
    mov  %ebx, -8(%rbp)

    addl %ebx, %ebx          # 2 * mult -> x
    imull %ebx, %eax         # x * r    -> dzielnik modulu
    movl %eax, -12(%rbp)

    call  rand
  
    cltd                     # rozszerzenie liczby losowej (wyczysczenie edx)
    divl -12(%rbp)           # dzielenie w liczniku
    mov   %edx, -16(%rbp) 

    # załadowanie wartości do rejestrów xmm*
    # wynik działania w liczniku do xmm0
    # mnoznik do generacji liczby zmiennoprzecinkowej do xmm1
    pxor %xmm0, %xmm0
    cvtsi2ss -16(%rbp), %xmm0
    pxor %xmm1, %xmm1
	cvtsi2ss -8(%rbp), %xmm1

    divss %xmm1, %xmm0       # wynik dzielenia w xmm0

    pxor	 %xmm1, %xmm1
    cvtsi2ss -4(%rbp), %xmm1 # załadowanie r do xmm1

    subss	 %xmm1, %xmm0    # końcowe odejmowanie(ułamek - r), wynik w xmm0

exit:
    movq  %rbp, %rsp
    popq  %rbp
    ret

# rand() % (10000 * 2r)     
# _____________________  -  r
#
#      10000

