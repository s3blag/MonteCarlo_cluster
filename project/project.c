#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//extern int calc(int r, int numberOfPoints);

extern float gen_rand(int r);

int main()
{   
    int seed = time(NULL);
    srand(seed);

    int r = 1;
    int numberOfPoints = 1000000;

    float i = gen_rand(r);

    printf("rand: [%f]\n", i );
    //int i = calc(r, numberOfPoints);
    //printf("%f\n", ((float)i/numberOfPoints)*(float)(2*r*2*r) );
    return 0;
}
