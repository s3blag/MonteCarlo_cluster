#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern int calc(int r, int numberOfPoints);

int main()
{   
    int seed = time(NULL);
    srand(seed);
    //int i = calc(4, 4, 5, 4);

    int i = calc(10, 1);

    
    return 0;
}
