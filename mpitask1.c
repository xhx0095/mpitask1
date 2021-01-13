#include <stdio.h>
#include "mpi.h"
#include<malloc.h>
#include <math.h>
main(int argc, char** argv) {
	int my_rank;
	int p;
	int source;
	int dest;
	int tag = 50;
	char message[100];
	int count;
	int data1;
	int i;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	if (my_rank != 0) {
		int data1=pow(10,my_rank);
		sprintf(message, " hello from  %d!",data1);
		dest = 0;
		MPI_Send(message, strlen(message)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);

	}
	if (my_rank == 0) {
		for (source = 1; source < p; source++) {
			MPI_Probe(MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
			MPI_Get_count(&status, MPI_CHAR, &count);
			MPI_Recv(message, 1000, MPI_CHAR, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
			char(*a)[100] = (char(*)[100])malloc(sizeof(char) * count * 100);
			for (i = 0; i < strlen(message)+1; i++) {
				a[source][i] = message[i];
			}
			printf(" %s\n", a[source]);
		}
	}
	MPI_Finalize();
}
