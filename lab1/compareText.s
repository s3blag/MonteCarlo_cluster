SYSEXIT = 1
EXIT_SUCCESS = 0
SYSREAD = 3
STDIN = 0
SYSWRITE = 4
STDOUT = 1

.text
#sample message
msg: .ascii "message"
msg_len = . - msg

#return message not equal
msg2: .ascii "     "
msg2_len = . - msg

#return message equal
msg3: .ascii "     "
msg3_len = . - msg

.data
#buffer for keyboard message
buf: .ascii "     "
buf_len = . - buf



.global _start
_start:
	#make counter 0
	mov $0, %ecx

	#wczytaj z klawiatury
	mov $SYSREAD, %eax
	mov $STDIN, %ebx
	mov $buf, %ecx
	mov $buf_len, %edx
	int $0x80

# %ecx - bytes counter	
compare_byte:
	cmp $7, %ecx
	je equal
	mov buf(,%ecx,1), %al
	mov msg(,%ecx,1), %ah
	inc %ecx
	cmp %al, %ah
	je compare_byte

not_equal:
	
	#print result
	mov $SYSWRITE, %eax
	mov $STDOUT, %ebx
	mov $msg2, %ecx
	mov $msg2_len, %edx
	int $0x80
	jmp exit

equal:
	#print result
	mov $SYSWRITE, %eax
	mov $STDOUT, %ebx
	mov $msg3, %ecx
	mov $msg3_len, %edx
	int $0x80

exit:
	mov $SYSEXIT, %eax
	mov $EXIT_SUCCESS, %ebx
	int $0x80


