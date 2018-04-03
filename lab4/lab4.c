#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int digits[4];
} Vector;

typedef struct
{
    double times[3];
} Results;


void populateSIMD(Vector *vector)
{   
    for(int i = 0; i < 4; i++)
        vector->digits[i] = rand()%1000 + 1;
}

int populateSISD()
{   
    return rand()%1000 + 1;
}

void printVector(Vector *vector)
{   
    for(int i = 0; i < 4; i++)
        printf("%d: %d  ", i, vector->digits[i]);
    printf("\n");
}

void writeToFile(Results results[])
{
    FILE *destFile = fopen("wyniki.txt", "w");
    
    if (destFile == NULL)
    {
        printf("Nie udalo sie otworzyc pliku");
        return;
    }

    fprintf(destFile, "\nTyp obliczeń: SIMD\n"
                       "Liczba liczb: %d\n"
                       "Sredni czas: \n"
                       "+ %f\n"
                       "- %f\n"
                       "* \n"
                       "/ \n",
                        2048, results[0].times[0], results[1].times[0]);

    fprintf(destFile, "\nTyp obliczeń: SIMD\n"
                       "Liczba liczb: %d\n"
                       "Sredni czas: \n"
                       "+ %f\n"
                       "- %f\n"
                       "* \n"
                       "/ \n",
                        4096, results[0].times[1], results[1].times[1]);
    
    fprintf(destFile, "\nTyp obliczeń: SIMD\n"
                       "Liczba liczb: %d\n"
                       "Sredni czas: \n"
                       "+ %f\n"
                       "- %f\n"
                       "* \n"
                       "/ \n",
                        8192, results[0].times[2], results[1].times[2]);


    fprintf(destFile, "\nTyp obliczeń: SISD\n"
                       "Liczba liczb: %d\n"
                       "Sredni czas: \n"
                       "+ %f\n"
                       "- %f\n"
                       "* \n"
                       "/ \n",
                        2048, results[4].times[0], results[5].times[0]);

    

    fprintf(destFile, "\nTyp obliczeń: SISD\n"
                       "Liczba liczb: %d\n"
                       "Sredni czas: \n"
                       "+ %f\n"
                       "- %f\n"
                       "* \n"
                       "/ \n",
                        4096, results[4].times[1], results[5].times[1]);

    
    fprintf(destFile, "\nTyp obliczeń: SISD\n"
                       "Liczba liczb: %d\n"
                       "Sredni czas: \n"
                       "+ %f\n"
                       "- %f\n"
                       "* \n"
                       "/ \n",
                        8192, results[4].times[2], results[5].times[2]);

    fclose(destFile);
}

void SIMD_add(int numberOfDigits, Results *results)
{   
    Vector vector1,
           vector2;
    double avgTime = 0,
           currentTime = 0;
    clock_t start,
            end;
    
    for(int i = 0; i < 10; i++)
    {   
        for(int j = 0; j < numberOfDigits/4; j++)
        {
            populateSIMD(&vector1);
            populateSIMD(&vector2);
            start = clock();
            asm(
                "movups %1, %%xmm0\n"
                "movups %2, %%xmm1\n"
                "addps %%xmm1, %%xmm0\n"
                "movups %%xmm0, %0\n"
                :"=g"(vector2)
            	:"g"(vector1),"g"(vector2)
            );
            end = clock();

            avgTime += (double)(end - start)/CLOCKS_PER_SEC;
        }
    }

    results->times[numberOfDigits/4096] = avgTime/10;
}

void SISD_add(int numberOfDigits, Results *results)
{   
    int digit1,
        digit2;
    double avgTime = 0,
           currentTime = 0;
    clock_t start,
            end;
    
    for(int i = 0; i < 10; i++)
    {   
        for(int j = 0; j < numberOfDigits; j++)
        {
            digit1 = populateSISD();
            digit2 = populateSISD();

            start = clock();
            asm(
                "movl %1, %%eax\n"
                "movl %2, %%ebx\n"
                "addl %%eax, %%ebx\n"
                "movl %%ebx, %0\n"
                :"=g"(digit2)
                :"g"(digit1),"g"(digit2)
            );
            end = clock();

            avgTime += (double)(end - start)/CLOCKS_PER_SEC;
        }
    }

    results->times[numberOfDigits/4096] = avgTime/10;
}

void SIMD_substract(int numberOfDigits, Results *results)
{
    Vector vector1,
           vector2;
    double avgTime = 0,
           currentTime = 0;
    clock_t start,
            end;
    
    for(int i = 0; i < 10; i++)
    {   
        for(int j = 0; j < numberOfDigits/4; j++)
        {
            populateSIMD(&vector1);
            populateSIMD(&vector2);
            start = clock();
            asm(
                "movups %1, %%xmm0\n"
                "movups %2, %%xmm1\n"
                "subps %%xmm1, %%xmm0\n"
                "movups %%xmm0, %0\n"
                :"=g"(vector2)
            	:"g"(vector1),"g"(vector2)
            );
            end = clock();

            avgTime += (double)(end - start)/CLOCKS_PER_SEC;
        }
    }

    results->times[numberOfDigits/4096] = avgTime/10;
}

void SISD_substract(int numberOfDigits, Results *results)
{
    int digit1,
        digit2;
    double avgTime = 0,
           currentTime = 0;
    clock_t start,
            end;
    
    for(int i = 0; i < 10; i++)
    {   
        for(int j = 0; j < numberOfDigits; j++)
        {
            digit1 = populateSISD();
            digit2 = populateSISD();

            start = clock();
            asm(
                "movl %1, %%eax\n"
                "movl %2, %%ebx\n"
                "subl %%eax, %%ebx\n"
                "movl %%ebx, %0\n"
                :"=g"(digit2)
                :"g"(digit1),"g"(digit2)
            );
            end = clock();

            avgTime += (double)(end - start)/CLOCKS_PER_SEC;
        }
    }

    results->times[numberOfDigits/4096] = avgTime/10;
}

void SIMD_multiply(int numberOfDigits, Results *results)
{   
    Vector vector1,
           vector2;
    double avgTime = 0,
           currentTime = 0;
    clock_t start,
            end;
    
    for(int i = 0; i < 10; i++)
    {   
        for(int j = 0; j < numberOfDigits/4; j++)
        {
            populateSIMD(&vector1);
            populateSIMD(&vector2);
            start = clock();
            asm(
                "movups %1, %%xmm0\n"
                "movups %2, %%xmm1\n"
                "addps %%xmm1, %%xmm0\n"
                "movups %%xmm0, %0\n"
                :"=g"(vector2)
            	:"g"(vector1),"g"(vector2)
            );
            end = clock();

            avgTime += (double)(end - start)/CLOCKS_PER_SEC;
        }
    }

    results->times[numberOfDigits/4096] = avgTime/10;
}

void SISD_multiply(int numberOfDigits, Results *results)
{   
    int digit1,
        digit2;
    double avgTime = 0,
           currentTime = 0;
    clock_t start,
            end;
    
    for(int i = 0; i < 10; i++)
    {   
        for(int j = 0; j < numberOfDigits; j++)
        {
            digit1 = populateSISD();
            digit2 = populateSISD();

            start = clock();
            asm(
                "movl %1, %%eax\n"
                "movl %2, %%ebx\n"
                "addl %%eax, %%ebx\n"
                "movl %%ebx, %0\n"
                :"=g"(digit2)
                :"g"(digit1),"g"(digit2)
            );
            end = clock();

            avgTime += (double)(end - start)/CLOCKS_PER_SEC;
        }
    }

    results->times[numberOfDigits/4096] = avgTime/10;
}


int main()
{
	srand (time(NULL));

    Results addResults_SIMD;
    Results addResults_SISD;
    Results subResults_SIMD;
    Results subResults_SISD;
    Results mulResults_SIMD;
    Results mulResults_SISD;
    Results divResults_SIMD;
    Results divResults_SISD;

    Results results[8];

    // SIMD

    SIMD_add(2048, &results[0]);
    SIMD_add(4096, &results[0]);
    SIMD_add(8192, &results[0]);

    SIMD_substract(2048, &results[1]);
    SIMD_substract(4096, &results[1]);
    SIMD_substract(8192, &results[1]);

    /*SIMD_multiply(2048, &results[2]);
    SIMD_multiply(4096, &results[2]);
    SIMD_multiply(8192, &results[2]);

    SIMD_divide(2048, &results[3]);
    SIMD_divide(4096, &results[3]);
    SIMD_divide(8192, &results[3]);*/
    
    // SISD

    SISD_add(2048, &results[4]);
    SISD_add(4096, &results[4]);
    SISD_add(8192, &results[4]);

    SISD_substract(2048, &results[5]);
    SISD_substract(4096, &results[5]);
    SISD_substract(8192, &results[5]);

    /*SISD_multiply(2048, &results[6]);
    SISD_multiply(4096, &results[6]);
    SISD_multiply(8192, &results[6]);

    SISD_divide(2048, &results[7]);
    SISD_divide(4096, &results[7]);
    SISD_divide(8192, &results[7]);*/

    writeToFile(results);

    return 0;
}