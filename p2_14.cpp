
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
    char my_value[3];
    my_value[1]='X';
    my_value[2]='\0';
 
    if(my_rank == root_rank)
    {
        char buffer[4] = {'A', 'B', 'C', 'D'};
        MPI_Scatter(buffer, 1, MPI_CHAR, my_value, 1, MPI_CHAR, root_rank, MPI_COMM_WORLD);
    
        char b[9];
        MPI_Gather(my_value, 2, MPI_CHAR, b, 2, MPI_CHAR, root_rank, MPI_COMM_WORLD);
        printf("Values collected: \"%s\".\n",  b);

}
    else
    {
        MPI_Scatter(NULL, 1, MPI_CHAR, my_value, 1, MPI_CHAR, root_rank, MPI_COMM_WORLD);
        MPI_Gather(my_value, 2, MPI_CHAR, NULL, 0, MPI_CHAR, root_rank, MPI_COMM_WORLD);
    }
 
    printf("Process %d received value and add X= \"%s\".\n", my_rank, my_value);
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}


