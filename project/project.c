#include "stdio.h"

extern int square(int n);

int global_in_C= 777;

int main()
{
    int i = square(25);
    printf("%d \n", i);
    return 0;
}

int multiply(int a, int b)
{
    return a*b;
}