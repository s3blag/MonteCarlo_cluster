.code32

SYSEXIT = 1
EXIT_SUCCESS = 0

.section .data
number1:
        .long 0xF0304008, 0x701100FF, 0x45100020, 0x08570030
position = ((. - number1)/4)
number2:
        .long 0xE040500C, 0x00220026, 0x321000CB, 0x04520031

.section .text
.globl _start
_start:
    # przenies iterator do %ecx
    # oraz wyczysc flage przeniesienia
    movl  $position, %ecx
    clc
    pushf
substract_loop:
    popf
    movl  number1(-4,%ecx,4), %eax
    movl  number2(-4,%ecx,4), %ebx
    sbbl  %ebx, %eax
    pushl %eax
    pushf
    loop  substract_loop   

check_carry:
    popf
    jnc   exit
create_carry:
    pushl $0xFFFFFFFF
exit:
    movl  $SYSEXIT, %eax
    movl  $EXIT_SUCCESS, %ebx
    int   $0x80
    