all: add sub

add: add.o
	ld add.o -o add

add.o: add.s
	as add.s -gstabs -o add.o

sub: sub.o
	ld sub.o -o sub

sub.o: sub.s
	as sub.s -gstabs -o sub.o
