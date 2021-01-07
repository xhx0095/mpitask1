#include <stdio.h>
#include "mpi.h"
#include<malloc.h>
main(int argc, char** argv) {
	int my_rank;
	int p;
	int source;
	int dest;
	int tag = 50;
	char message[1000];
	int count;
	int data1;
	
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	if (my_rank != 0) {
		sprintf(message,"is %d!",
			my_rank);
		data1 = my_rank;
		
		dest = 0;

		
		MPI_Send(&data1, 2, MPI_INT, dest, tag, MPI_COMM_WORLD);
		

	}



	if (my_rank == 0) {
		int(*a)[2] = (int(*)[2])malloc(sizeof(int) * 6 * 2);
		
		    
		for (source = 1; source < p; source++) {
			MPI_Probe(MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
			MPI_Get_count(&status, MPI_INT, &count);
			
			MPI_Recv(&data1, 2, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
			
			a[source][0] = data1;
			
			
			printf(" help from %d\n", a[source][0]);
			


		}
