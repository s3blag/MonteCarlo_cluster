#include <stdio.h>
#include <stdlib.h>

//Mateusz Ligus 209939

//Wektor czteroelementowy
typedef struct vector4 {   
    float x, y, z, w;       
} vector4;

float detM(vector4 op_a, vector4 op_b, vector4 op_c, vector4 op_d)
{
	//wektor wynikowy
	vector4 ret_vector;
	
	/*
	Wzór na wyznacznik:
	detM = (a0*b1-a1*b0)*(c2*d3-c3*d2) +
           (a2*b0-a0*b2)*(c1*d3-c3*d1) +
           (a0*b3-a3*b0)*(c1*d2-c2*d1) +
           (a1*b2-a2*b1)*(c0*d3-c3*d0) +
           (a2*b3-a3*b2)*(c0*d1-c1*d0) +
           (a3*b1-a1*b3)*(c0*d2-c2*d0)
           
     Jako działania wymagają wektórów czteroelementowych
     do swobodnego liczenia można uzupełnić wzór o 2 puste sumy:
     detM = (a0*b1-a1*b0)*(c2*d3-c3*d2) +
            (a2*b0-a0*b2)*(c1*d3-c3*d1) +
            (a0*b3-a3*b0)*(c1*d2-c2*d1) +
            (a1*b2-a2*b1)*(c0*d3-c3*d0) +
            
            (a2*b3-a3*b2)*(c0*d1-c1*d0) +
            (a3*b1-a1*b3)*(c0*d2-c2*d0) +
            (a0*b0-a0*b0)*(c0*d0-c0*d0) + -> 0 * 0
            (a0*b0-a0*b0)*(c0*d0-c0*d0)   -> 0 * 0
	*/
	
	__asm__(
	/*
	 Obliczamy pierwszą część działania
	 (a0*b1-a1*b0)
     (a2*b0-a0*b2)
     (a0*b3-a3*b0)
     (a1*b2-a2*b1)
	*/
	//Obliczenia dla lewej strony
	"movups %1, %%xmm0 \n\t"
	"movups %2, %%xmm1 \n\t"
	"shufps $0x48, %%xmm0, %%xmm0 \n\t" // A` = (01, 00, 10, 00)
	"shufps $0xb1, %%xmm1, %%xmm1 \n\t" // B` = (10, 11, 00, 01)
	"mulps %%xmm0, %%xmm1 \n\t"         // A` * B`
	
	//Obliczenia dla prawej strony
	"movups %1, %%xmm0 \n\t"
	"movups %2, %%xmm2 \n\t"
	"shufps $0xb1, %%xmm0, %%xmm0 \n\t" // A`` = (10, 11, 00, 01)
	"shufps $0x48, %%xmm2, %%xmm2 \n\t" // B`` = (01, 00, 10, 00)
	"mulps %%xmm0, %%xmm2 \n\t"         // A`` * B``
	
	//Wynik czesci 1
	"subps %%xmm1, %%xmm2 \n\t"
	
	/*
	 Obliczamy drugą część działania
	 (c2*d3-c3*d2) 
     (c1*d3-c3*d1) 
     (c1*d2-c2*d1) 
     (c0*d3-c3*d0) 
	*/
	
	//Obliczenia dla lewej strony
	"movups %3, %%xmm0 \n\t"
	"movups %4, %%xmm1 \n\t"
	"shufps $0x16, %%xmm0, %%xmm0 \n\t" // C` = (00, 01, 01, 10)
	"shufps $0xef, %%xmm1, %%xmm1 \n\t" // D` = (11, 10, 11, 11)
	"mulps %%xmm0, %%xmm1 \n\t"         // C` * D`
	
	//Obliczenia dla prawej strony
	"movups %3, %%xmm0 \n\t"
	"movups %4, %%xmm3 \n\t"
	"shufps $0xef, %%xmm0, %%xmm0 \n\t" // C`` = (11, 10, 11, 11)
	"shufps $0x16, %%xmm3, %%xmm3 \n\t" // D`` = (00, 01, 01, 10)
	"mulps %%xmm0, %%xmm3 \n\t"         // C`` * D``
	
	//Wynik czesci 2
	"subps %%xmm1, %%xmm3 \n\t"
	
	/*
	 Obliczamy trzecią część działania
	 (a2*b3-a3*b2)
     (a3*b1-a1*b3)
     (a0*b0-a0*b0)
     (a0*b0-a0*b0)
	*/
	
	//Obliczenia dla lewej strony
	"movups %1, %%xmm0 \n\t"
	"movups %2, %%xmm1 \n\t"
	"shufps $0xe, %%xmm0, %%xmm0 \n\t" // A` = (00, 00, 11, 10)
	"shufps $0x7, %%xmm1, %%xmm1 \n\t" // B` = (00, 00, 01, 11)
	"mulps %%xmm0, %%xmm1 \n\t"         // A` * B`
	
	//Obliczenia dla prawej strony
	"movups %1, %%xmm0 \n\t"
	"movups %2, %%xmm4 \n\t"
	"shufps $0x7, %%xmm0, %%xmm0 \n\t" // A`` = (00, 00, 01, 11)
	"shufps $0xe, %%xmm4, %%xmm4 \n\t" // B`` = (00, 00, 11, 10)
	"mulps %%xmm0, %%xmm4 \n\t"         // A`` * B``
	
	//Wynik czesci 3
	"subps %%xmm1, %%xmm4 \n\t"
	
	/*
	 Obliczamy czwartą część działania
	 (c0*d1-c1*d0)
     (c0*d2-c2*d0) 
     (c0*d0-c0*d0) 
     (c0*d0-c0*d0)
	*/
	
	//Obliczenia dla lewej strony
	"movups %3, %%xmm0 \n\t"
	"movups %4, %%xmm1 \n\t"
	"shufps $0x0, %%xmm0, %%xmm0 \n\t" // C` = (00, 00, 00, 00)
	"shufps $0x9, %%xmm1, %%xmm1 \n\t" // D` = (00, 00, 10, 01)
	"mulps %%xmm0, %%xmm1 \n\t"         // C` * D`
	
	//Obliczenia dla prawej strony
	"movups %3, %%xmm0 \n\t"
	"movups %4, %%xmm5 \n\t"
	"shufps $0x9, %%xmm0, %%xmm0 \n\t" // C`` = (00, 00, 10, 01)
	"shufps $0x0, %%xmm5, %%xmm5 \n\t" // D`` = (00, 00, 00, 00)
	"mulps %%xmm0, %%xmm5 \n\t"         // C`` * D``
	
	//Wynik czesci 4
	"subps %%xmm1, %%xmm5 \n\t"
	
	//Mnożymy odpowiednie części wynikowe
	"mulps %%xmm2, %%xmm3 \n\t"
	"mulps %%xmm4, %%xmm5 \n\t"
	
	//Dodajemy aby otrzymać wektor końcowy, który zwracamy
	"addps %%xmm3, %%xmm5 \n\t"
	"movups %%xmm5, %0 \n\t"
	
	:"=g" (ret_vector)
	:"g"(op_a),"g"(op_b),"g"(op_c),"g"(op_d) //wektor a, b, c, d
	);
	
	return ret_vector.x + ret_vector.y + ret_vector.z + ret_vector.w;
}

int main()
{
	vector4 matrix[4];
	float wyznacznik;
	
	float m_test[4][4]=
	{{22,13,23,76},
	 {34,5,34,12},
	 {44,12,35,21},
	 {34,12,34,51}};
	 
	 int i;
	 
	 for(i = 0; i < 4; i++)
	 {
	 	matrix[i].x = m_test[i][0];
	 	matrix[i].y = m_test[i][1];
	 	matrix[i].z = m_test[i][2];
	 	matrix[i].w = m_test[i][3];
	 }
	 
	wyznacznik = detM(matrix[0], matrix[1], matrix[2], matrix[3]);
	printf("Wyznacznik to: %f\n", wyznacznik);
	
	
	return 0;	
}
