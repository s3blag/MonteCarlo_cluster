#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float sisd_result;

typedef struct
{
    float digits[4];
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
        printf("%d: %f  ", i, vector->digits[i]);
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
                       "* %f\n"
                       "/ %f\n",
                        2048, results[0].times[0], results[1].times[0], results[2].times[0], results[3].times[0]);

    fprintf(destFile, "\nTyp obliczeń: SIMD\n"
                       "Liczba liczb: %d\n"
                       "Sredni czas: \n"
                       "+ %f\n"
                       "- %f\n"
                       "* %f\n"
                       "/ %f\n",
                        4096, results[0].times[1], results[1].times[1], results[2].times[1], results[3].times[1]);
    
    fprintf(destFile, "\nTyp obliczeń: SIMD\n"
                       "Liczba liczb: %d\n"
                       "Sredni czas: \n"
                       "+ %f\n"
                       "- %f\n"
                       "* %f\n"
                       "/ %f\n",
                        8192, results[0].times[2], results[1].times[2], results[2].times[2], results[3].times[2]);




    fprintf(destFile, "\nTyp obliczeń: SISD\n"
                       "Liczba liczb: %d\n"
                       "Sredni czas: \n"
                       "+ %f\n"
                       "- %f\n"
                       "* %f\n"
                       "/ %f\n",
                        2048, results[4].times[0], results[5].times[0], results[6].times[0], results[7].times[0]);

    fprintf(destFile, "\nTyp obliczeń: SISD\n"
                       "Liczba liczb: %d\n"
                       "Sredni czas: \n"
                       "+ %f\n"
                       "- %f\n"
                       "* %f\n"
                       "/ %f\n",
                        4096, results[4].times[1], results[5].times[1], results[6].times[1], results[7].times[1]);

    fprintf(destFile, "\nTyp obliczeń: SISD\n"
                       "Liczba liczb: %d\n"
                       "Sredni czas: \n"
                       "+ %f\n"
                       "- %f\n"
                       "* %f\n"
                       "/ %f\n",
                        8192, results[4].times[2], results[5].times[2], results[6].times[2], results[7].times[2]);

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
    
    for(int i = 0; i < 1; i++)
    {   
        for(int j = 0; j < 1; j++)
        {
            populateSIMD(&vector1);
            populateSIMD(&vector2);

            printVector(&vector1);
            printVector(&vector2);
            
            start = clock();
            asm volatile(
                "movups %1, %%xmm0\n"
                "movups %2, %%xmm1\n"
                "addps %%xmm1, %%xmm0\n"
                "movups %%xmm0, %0\n"
                :"=g"(vector2)
            	:"g"(vector1),"g"(vector2)
            );
            end = clock();

            printVector(&vector2);

            avgTime += (double)(end - start)/CLOCKS_PER_SEC;
        }
    }

    results->times[numberOfDigits/4096] = avgTime/10;
}

void SISD_add(int numberOfDigits, Results *results)
{   
    float digit1,
          digit2;
    double avgTime = 0,
           currentTime = 0;
    clock_t start,
            end;
    
    for(int i = 0; i < 1; i++)
    {   
        for(int j = 0; j < 1; j++)
        {
            digit1 = populateSISD();
            digit2 = populateSISD();

            

            start = clock();
            asm volatile(
                "flds %0\n"
                "fadds %1\n"
                "fsts sisd_result\n"
                :
                :"g"(digit1),"g"(digit2)
            );
            end = clock();

            printf("%f + %f = %f", digit1, digit2, sisd_result);
            
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
    
    for(int i = 0; i < 1; i++)
    {   
        for(int j = 0; j < 1; j++)
        {
            populateSIMD(&vector1);
            populateSIMD(&vector2);

            printVector(&vector1);
            printVector(&vector2);

            start = clock();
            asm volatile(
                "movups %1, %%xmm0\n"
                "movups %2, %%xmm1\n"
                "subps %%xmm1, %%xmm0\n"
                "movups %%xmm0, %0\n"
                :"=g"(vector2)
            	:"g"(vector1),"g"(vector2)
            );
            end = clock();

            printVector(&vector2);

            avgTime += (double)(end - start)/CLOCKS_PER_SEC;
        }
    }

    results->times[numberOfDigits/4096] = avgTime/10;
}

void SISD_substract(int numberOfDigits, Results *results)
{
    float digit1,
        digit2;
    double avgTime = 0,
           currentTime = 0;
    clock_t start,
            end;
    
    for(int i = 0; i < 1; i++)
    {   
        for(int j = 0; j < 1; j++)
        {
            digit1 = populateSISD();
            digit2 = populateSISD();

            start = clock();
            asm volatile(
                "flds %1\n"
                "fsubs %0\n"
                "fsts sisd_result\n"
                :
                :"g"(digit1),"g"(digit2)
            );
            end = clock();

            printf("%f - %f = %f", digit2, digit1, sisd_result);

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
    
    for(int i = 0; i < 1; i++)
    {   
        for(int j = 0; j < 1; j++)
        {
            populateSIMD(&vector1);
            populateSIMD(&vector2);

            printVector(&vector1);
            printVector(&vector2);

            start = clock();
            asm volatile(
                "movups %1, %%xmm0\n"
                "movups %2, %%xmm1\n"
                "mulps %%xmm1, %%xmm0\n"
                "movups %%xmm0, %0\n"
                :"=g"(vector1)
            	:"g"(vector1),"g"(vector2)
            );
            end = clock();

            printVector(&vector1);

            avgTime += (double)(end - start)/CLOCKS_PER_SEC;
        }
    }

    results->times[numberOfDigits/4096] = avgTime/10;
}

void SISD_multiply(int numberOfDigits, Results *results)
{   
    float digit1,
          digit2;
    double avgTime = 0,
           currentTime = 0;
    clock_t start,
            end;
    
    for(int i = 0; i < 1; i++)
    {   
        for(int j = 0; j < 1; j++)
        {
            digit1 = populateSISD();
            digit2 = populateSISD();

            start = clock();
            asm volatile(
                "flds %0\n"
                "fmuls %1\n"
                "fsts sisd_result\n"
                :
                :"g"(digit1),"g"(digit2)
            );
            end = clock();

            printf("%f * %f = %f", digit1, digit2, sisd_result);
            
            avgTime += (double)(end - start)/CLOCKS_PER_SEC;
        }
    }

    results->times[numberOfDigits/4096] = avgTime/10;
}

void SIMD_divide(int numberOfDigits, Results *results)
{   
    Vector vector1,
           vector2;
    double avgTime = 0,
           currentTime = 0;
    clock_t start,
            end;
    
    for(int i = 0; i < 1; i++)
    {   
        for(int j = 0; j < 1; j++)
        {
            populateSIMD(&vector1);
            populateSIMD(&vector2);

            printVector(&vector1);
            printVector(&vector2);

            start = clock();
            asm volatile(
                "movups %1, %%xmm0\n"
                "movups %2, %%xmm1\n"
                "divps %%xmm1, %%xmm0\n"
                "movups %%xmm0, %0\n"
                :"=g"(vector1)
            	:"g"(vector1),"g"(vector2)
            );
            end = clock();

            printVector(&vector1);

            avgTime += (double)(end - start)/CLOCKS_PER_SEC;
        }
    }

    results->times[numberOfDigits/4096] = avgTime/10;
}

void SISD_divide(int numberOfDigits, Results *results)
{   
    float digit1,
        digit2;
    double avgTime = 0,
           currentTime = 0;
    clock_t start,
            end;
    
    for(int i = 0; i < 1; i++)
    {   
        for(int j = 0; j < 1; j++)
        {
            digit1 = populateSISD();
            digit2 = populateSISD();

            start = clock();
            asm volatile(
                "flds %1\n"
                "fdivs %0\n"
                "fsts sisd_result\n"
                :
                :"g"(digit1),"g"(digit2)
            );
            end = clock();

            printf("%f / %f = %f", digit2, digit1, sisd_result);

            avgTime += (double)(end - start)/CLOCKS_PER_SEC;
        }
    }

    results->times[numberOfDigits/4096] = avgTime/10;
}


int main()
{
	srand (time(NULL));

    Results results[8];

    // SIMD
    
    SIMD_add(2048, &results[0]);
    /*SIMD_add(4096, &results[0]);
    SIMD_add(8192, &results[0]);
*/
printf("\n\n");
    SIMD_substract(2048, &results[1]);
    //SIMD_substract(4096, &results[1]);
    //SIMD_substract(8192, &results[1]);
printf("\n\n");
    SIMD_multiply(2048, &results[2]);
    //SIMD_multiply(4096, &results[2]);
    //SIMD_multiply(8192, &results[2]);
printf("\n\n");    
   // SIMD_divide(2048, &results[3]);
    //SIMD_divide(4096, &results[3]);
    SIMD_divide(8192, &results[3]);
  printf("\n\n");  
    // SISD

    //SISD_add(2048, &results[4]);
    //SISD_add(4096, &results[4]);
    SISD_add(8192, &results[4]);
printf("\n\n");
    //SISD_substract(2048, &results[5]);
    //SISD_substract(4096, &results[5]);
    SISD_substract(8192, &results[5]);
printf("\n\n");
    //SISD_multiply(2048, &results[6]);
    //SISD_multiply(4096, &results[6]);
    SISD_multiply(8192, &results[6]);
printf("\n\n");
    SISD_divide(2048, &results[7]);
    //SISD_divide(4096, &results[7]);
    //SISD_divide(8192, &results[7]);
printf("\n\n");
    writeToFile(results);

    return 0;
}