#include "stdio.h"

extern int square(int n);
extern int calc(float x, float y, float r, int counter);

int global_in_C= 777;

int main()
{
    int i = calc(6, 5, 8, 4);
    printf("%d \n", i);
    return 0;
}

int multiply(int a, int b)
{
    return a*b;
}