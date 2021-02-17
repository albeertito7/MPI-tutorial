#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
/* Comunicación bloqueante síncrona */
#define N 200
/* Run with two processes */
int main(int argc, char **argv){
	int rank, size, i, count, M;
	double tiempoPromedio, t1, t2;
	MPI_Status status;

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
			MPI_Ssend(data, M, MPI_INT, (rank+1)%size, 8, MPI_COMM_WORLD);
			MPI_Recv(data, M, MPI_INT,(rank-1)%size, 8, MPI_COMM_WORLD, &status);
			t2 = MPI_Wtime();
			tiempoPromedio += (t2-t1)/2;		
		}
		printf("Tiempo promedio bloqueante síncrona: %lf\n", tiempoPromedio);
	}else{
		for(i=0; i<N; i++){
			MPI_Recv(data, M, MPI_INT, (rank-1)%size, 8, MPI_COMM_WORLD, &status);
			MPI_Rsend(data, M, MPI_INT, (rank+1)%size, 8, MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();
	return 0;
}
