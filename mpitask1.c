#include <stdio.h>
#include "mpi.h"
#include<malloc.h>
main(int argc, char** argv) {
	int my_rank; 
	int p; 
	int source; 
	int dest; 
	int tag = 50; 
	char message[100]; 
	
	int data1;
	int data2;
	MPI_Status status; 
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	if (my_rank != 0) {
		sprintf(message, "hellow from process %d!",
			my_rank);
		data1 = my_rank + 2;
		data2 = my_rank + 3;
		dest = 0;
		
		MPI_Send(message, strlen(message) + 1, MPI_CHAR, dest,
			tag, MPI_COMM_WORLD);
		MPI_Send(&data1, 2, MPI_INT, dest, tag, MPI_COMM_WORLD);
		MPI_Send(&data2, 2, MPI_INT, dest, tag, MPI_COMM_WORLD);

	}
	
	

	if (my_rank == 0) {
		int(*a)[2] = (int(*)[2])malloc(sizeof(int) * 4 * 2);
		for (source = 1; source < p; source++) {
			
				MPI_Recv(message, 100, MPI_CHAR, source, tag,
					MPI_COMM_WORLD, &status);
				MPI_Recv(&data1, 2, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
				MPI_Recv(&data2, 2, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
				a[source][0] = data1;
				a[source][1] = data2;
			printf("%s\n", message);
			printf("%d,%d\n",a[source][0], a[source][1]);
		}

		
		
		
	}
	MPI_Finalize();
}
