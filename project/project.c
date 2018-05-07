#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern int calc(int r, int numberOfPoints);

int main()
{   
    int seed = time(NULL);
    srand(seed);
    //int i = calc(4, 4, 5, 4);
    for( int j = 0; j < 10; j++)
    {
       float i = calc(10, 2);
       printf("%f \n", i);
    }
    
    return 0;
}
