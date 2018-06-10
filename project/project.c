#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <unistd.h>

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
    int numberOfPoints = 100000000;

    int result =0;
	
    int *arr = malloc (sizeof(int) * world_size);
    for (int i = 0; i < world_size; i++)
        arr[i] = 0;
    
    clock_t start,
            end;

    start = clock();
    result = calculate(r, numberOfPoints);
    end = clock();
            
    double timeResult = (double)(end - start)/CLOCKS_PER_SEC;
    
    printf("\nComputer: _%s_ Core: %d/%d [time:[%f]]\n",
            processor_name, world_rank+1, world_size, timeResult);

    MPI_Gather(&result, 1, MPI_INT, arr, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    if (world_rank == 0)
    {
        long long int totalSum = 0;
        for (int i = 0; i < world_size; i++)
        {
            totalSum += arr[i];
        }

        double result = ((double)totalSum/(numberOfPoints*world_size))*(double)(2*r*2*r);
        printf("\n\nResult: [%lf]\n\n", result);
    }

    free(arr);
    MPI_Finalize();
    
    return 0;

}
