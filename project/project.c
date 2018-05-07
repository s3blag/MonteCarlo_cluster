#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern int calc(float x, float y, float r, int counter);
extern float gen_rand(int r);
int main()
{   
    int seed = time(NULL);
    srand(seed);
    //int i = calc(4, 4, 5, 4);
    for( int j = 0; j < 20; j++)
    {
       float i = gen_rand(20);
       printf("%f \n", i);
    }
    
    return 0;
}

int multiply(int a, int b)
{
    return a*b;
}