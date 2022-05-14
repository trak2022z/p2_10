/**
 * Original source code at https://www.rookiehpc.com/mpi/docs/mpi_char.php
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
 

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
 
    // Check that 3 MPI processes are used.
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 3)
    {
        printf("This application is meant to be run with 3 MPI processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
 
    // Get my rank and do the corresponding job.
    enum role_ranks { SENDER, RECEIVER, R };
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    switch(my_rank)
    {
        case SENDER:
        {
            // Sends the string
            char stringToSend[] = "Hello world";
	    char stringR[13];
	    stringR[12]='\0';
	    char stringR2[13];
	    stringR2[12]='\0';

            printf("[MPI process %d] I send string: \"%s\".\n", my_rank, stringToSend);

	    for(int i = 1; i<3; i++)
                MPI_Ssend(stringToSend, strlen(stringToSend), MPI_CHAR, i, 0, MPI_COMM_WORLD);

		MPI_Recv(stringR,12,MPI_CHAR,RECEIVER,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(stringR2,12,MPI_CHAR,R,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("Proces: %d. Returned string1: \"%s\".\n", my_rank,stringR);
		printf("Proces: %d. Returned string2: \"%s\".\n", my_rank,stringR2);
            break;
        }
        case RECEIVER:
        {
            // Receives the string
            char stringReceived[13];
	    stringReceived[11]='X';
            stringReceived[12] = '\0';
            
	    MPI_Recv(stringReceived, 11, MPI_CHAR, SENDER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("[MPI process %d] I received string and add X: \"%s\".\n", my_rank, stringReceived);
            MPI_Ssend(stringReceived, strlen(stringReceived),MPI_CHAR,SENDER,0,MPI_COMM_WORLD);
            break;
        }

	case R:
	{
		char sR[13];
		sR[11]='Y';
		sR[12]='\0';

		MPI_Recv(sR, 11, MPI_CHAR, SENDER, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("[MPI process %d] I received string and add Y: \"%s\".\n", my_rank,sR);
		MPI_Ssend(sR, strlen(sR),MPI_CHAR,SENDER,0,MPI_COMM_WORLD);
		break;
	}

    }
    MPI_Finalize();
    return EXIT_SUCCESS;
}
