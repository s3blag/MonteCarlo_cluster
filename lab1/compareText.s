SYSEXIT = 1
EXIT_SUCCESS = 0
SYSREAD = 3
STDIN = 0
SYSWRITE = 4
STDOUT = 1

.text
	# wiadomosc, do ktorej porownujemy
	msg: .ascii "message"
	msg_len = . - msg

	# wiadomosc, jesli wiadomosci
	# sa takie same
	msg2: .ascii "Equal \n"
	msg2_len = . - msg2

	# wiadomosc, jesli wiadomosci
	# nie sa takie same
	msg3: .ascii "Not Equal \n"
	msg3_len = . - msg3

.data
	# wiadomosc wczytana z klawiatury
	buf: .ascii "       "
	buf_len = . - buf

.global _start
_start:
	# wczytaj z klawiatury
	mov $SYSREAD, %eax
	mov $STDIN, %ebx
	mov $buf, %ecx
	mov $buf_len, %edx
	int $0x80

	cmp $msg_len, %eax
	jne not_equal
	
reset_counter:
	mov $0, %ecx

compare_byte:
	cmp $msg_len, %ecx
	je  equal
	mov buf(,%ecx,1), %al
	mov msg(,%ecx,1), %ah
	inc %ecx
	cmp %al, %ah
	je compare_byte

not_equal:
	# drukuj wynik na ekran
	mov $SYSWRITE, %eax
	mov $STDOUT, %ebx
	mov $msg3, %ecx
	mov $msg3_len, %edx
	int $0x80
	jmp exit

equal:
	# drukuj wynik na ekran
	mov $SYSWRITE, %eax
	mov $STDOUT, %ebx
	mov $msg2, %ecx
	mov $msg2_len, %edx
	int $0x80

exit:
	mov $SYSEXIT, %eax
	mov $EXIT_SUCCESS, %ebx
	int $0x80
