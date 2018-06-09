#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern int calculate(int r, int numberOfPoints);

int main()
{   
    srand(time(NULL));
    int r = 1,
        numberOfPoints = 2000000000;

    int result = calculate(r, numberOfPoints);

    printf("%f\n", ((float)result/numberOfPoints)*(float)(2*r*2*r) );
    return 0;
}
