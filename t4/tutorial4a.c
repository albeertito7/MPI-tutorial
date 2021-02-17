#include "mpi.h"
#include <stdio.h>

#define N 6
#define M 10

int main(int argc, char *argv[]) {

	int rank, i, j, sum,
		send[N*M], recv[M], recvR[N], 
		matriz[N][M] = {{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10}};

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank == 0) {
		for(i=0; i<N; i++) for(j=0; j<M; j++) send[i*M+j] = matriz[i][j];
	}

	MPI_Scatter(&send,M,MPI_INT,&recv,M,MPI_INT,0,MPI_COMM_WORLD);

	sum=0;
	for(i = 0; i<M; i++) sum += recv[i];
	printf("P: %d, Resultado parcial: %d\n", rank, sum);

	MPI_Gather(&sum, 1, MPI_INT, &recvR, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == 0) {
		sum=0;
		for(i=0; i<N; i++) sum += recvR[i];
		printf("Resultado final: %d\n", sum);
	}

	MPI_Finalize();
	return 0;
}