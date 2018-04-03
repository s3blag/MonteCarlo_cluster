all: fpu
fpu: fpu.o
	ld fpu.o -o fpu
fpu.o: fpu.s
	as fpu.s -gstabs -o fpu.o
	
