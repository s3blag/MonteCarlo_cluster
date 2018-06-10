#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

extern int calculate(int r, int numberOfPoints);

int main(int argc, char** argv)
{   
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int nameLength;
    MPI_Get_processor_name(processor_name, &nameLength);

    int seed = time(NULL);
    srand(seed);

    int r = 1;
    int numberOfPoints = 2000000000;

    clock_t start,
            end;

    start = clock();
    int points = calculate(r, numberOfPoints);
    end = clock();
            
    double timeResult = (double)(end - start)/CLOCKS_PER_SEC;

    float result = ((float)points/numberOfPoints)*(float)(2*r*2*r);
    
    printf("Computer: _%s_ Core: %d/%d\n"
           "   result: %f time:[%f]\n",
            processor_name, world_rank, world_size, result, timeResult);

    MPI_Finalize();
    
    return 0;

}
