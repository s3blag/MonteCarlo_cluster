SYSEXIT = 1
EXIT_SUCCESS = 0
SYSREAD = 3
STDIN = 0
SYSWRITE = 4
STDOUT = 1

.text
msg: .ascii "Write text (5): \n"
msg_len = . - msg

msg2: .ascii "Written text: "
msg2_len = . - msg2

newline: .ascii "\n"
newline_len = . - newline

.data
buf: .ascii "     "
buf_len = . - buf

.global _start
_start:
	
	mov $SYSWRITE, %eax
	mov $STDOUT, %ebx
	mov $msg, %ecx
	mov $msg_len, %edx
	int $0x80
	
	#wczytaj z klawiatury
	mov $SYSREAD, %eax
	mov $STDIN, %ebx
	mov $buf, %ecx
	mov $buf_len, %edx
	int $0x80
    
	#wypisz msg2
	mov $SYSWRITE, %eax
	mov $STDOUT, %ebx
	mov $msg2, %ecx
	mov $msg2_len, %edx
	int $0x80
	
	#wypisz wczytany tekst
	mov $SYSWRITE, %eax
	mov $STDOUT, %ebx
	mov $buf, %ecx
	mov $buf_len, %edx
	int $0x80
	
	#wypisz /n
	mov $SYSWRITE, %eax
	mov $STDOUT, %ebx
	mov $newline, %ecx
	mov $newline_len, %edx
	
	int $0x80
	mov $SYSEXIT, %eax
    mov $EXIT_SUCCESS, %ebx
    int $0x80
