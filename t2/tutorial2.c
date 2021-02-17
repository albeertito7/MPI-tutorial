#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 200
/* Run with two processes */
int main(int argc, char **argv){
	int rank, i, count, M;
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
	if(rank == 0){
		for(i=0; i<M; i++) data[i] = 1; /* llenamos el array (en este tutorial 2 he optado por llenarlo, en cambio en los siguientes no lo lleno (no sabia exactamente si se debia llenar o no)*/

		for(i=0; i<N; i++){
			t1 = MPI_Wtime();
			MPI_Send(data, M, MPI_INT, 1, 7, MPI_COMM_WORLD);
			MPI_Recv(data, M, MPI_INT, 1, 8, MPI_COMM_WORLD, &status);
			t2 = MPI_Wtime();
			tiempoPromedio += (t2-t1)/2;
		}
		printf("Tamaño mensaje: %d, Tiempo promedio: %lf\n", M, tiempoPromedio);
	}else{
		for(i=0;i<N;i++){
			MPI_Recv(data, M, MPI_INT, 0, 7, MPI_COMM_WORLD, &status);
			MPI_Send(data, M, MPI_INT, 0, 8, MPI_COMM_WORLD);
		}
	}
	MPI_Finalize();
	return 0;
}