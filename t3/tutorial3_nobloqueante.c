#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
/* Comunicación no bloqueante */
#define N 200
/* Run with two processes */
int main(int argc, char **argv){
	int rank, size, i, count, M;
	double tiempoPromedio, t1, t2;
	MPI_Request request;

	if(argv[1] != NULL){
		M = atoi(argv[1]);
	}else {
		M = 128;
	}

	int data[M];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank == 0){
		for(i=0; i<N; i++){
			t1 = MPI_Wtime();
			MPI_Isend(data, M, MPI_INT, (rank+1)%size, 8, MPI_COMM_WORLD, &request);
			MPI_Irecv(data, M, MPI_INT,(rank-1)%size, 8, MPI_COMM_WORLD, &request);
			t2 = MPI_Wtime();
			tiempoPromedio += (t2-t1)/2;
		}
		printf("Tiempo promedio no bloqueante: %lf\n", tiempoPromedio);
	}else{
		MPI_Buffer_attach(data, 600);
		for(i=0; i<N; i++){
			MPI_Irecv(data, M, MPI_INT, (rank-1)%size, 8, MPI_COMM_WORLD, &request);
			MPI_Isend(data, M, MPI_INT, (rank+1)%size, 8, MPI_COMM_WORLD, &request);
		}
	}

	MPI_Finalize();
	return 0;
}