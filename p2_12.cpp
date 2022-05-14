#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
 
    // Get number of processes and check that 4 processes are used
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 4)
    {
        printf("This application is meant to be run with 4 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
 
    // Determine root's rank
    int root_rank = 0;
 
    // Get my rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
 
    // Define my value
	char my_value[2];
	my_value[1]='\0';
 
    if(my_rank == root_rank)
    {
        char buffer[4] = {'A', 'B', 'C', 'D'};
        MPI_Scatter(buffer, 1, MPI_CHAR, my_value, 1, MPI_CHAR, root_rank, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Scatter(NULL, 1, MPI_CHAR, my_value, 1, MPI_CHAR, root_rank, MPI_COMM_WORLD);
    }
 
    printf("Process %d received value = \"%s\".\n", my_rank, my_value);
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}


