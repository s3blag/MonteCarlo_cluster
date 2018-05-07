#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern int calc(int r, int numberOfPoints);

int main()
{   
    int seed = time(NULL);
    srand(seed);

    int r = 1;
    int numberOfPoints = 1000000;


    int i = calc(r, numberOfPoints);

    printf("%f\n", ((float)i/numberOfPoints)*(float)(2*r*2*r) );
    return 0;
}
