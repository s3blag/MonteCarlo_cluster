all: add substract
add: add.o
	ld add.o -o add
add.o: add.s
	as add.s -gstabs -o add.o
substract: substract.o
	ld substract.o -o substract
substract.o: substract.s
	as substract.s -gstabs -o substract.o
