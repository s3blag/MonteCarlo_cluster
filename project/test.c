#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//extern int calc(int r, int numberOfPoints);

//extern double gen_rand(int r);

float gen_rand(int r)
{
    int divisor = 1000;
    int modulus = 2 * divisor * r;
    int random = rand();
    int upper = random % modulus;
    float doubleTheResult = (float)upper / (float)divisor;
    float result = doubleTheResult - r;

    return result;
}

int main()
{   
    //int seed = time(NULL);
    srand(time(NULL));

    int r = 1;
    //int numberOfPoints = 1000000;

   // double i = gen_rand(r);

    float i = gen_rand(r);

    printf("rand: [%f]\n", i );
    //int i = calc(r, numberOfPoints);
    //printf("%f\n", ((float)i/numberOfPoints)*(float)(2*r*2*r) );
    return 0;
}
