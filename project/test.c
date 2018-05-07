
#include <stdio.h>
void eeezy(float i)
{
    i=0;
}

int main()
{   
    int a = 10000,
        b = 31,
        c = 17,
        d = 19;
    float i = ((a * b) % d) / (float)c;
    
    printf("%f\n", i);
    eeezy(i);

    return i;
}

