#include "mpi.h"
#include <stdio.h>

#define N 6
#define M 10

/* Run with 6 processes */
int main(int argc, char *argv[]) {

	int rank, i, sumaParcial, sumaTotal;
	int sum[M/N + M%N], // reservamos el valor máximo necesario
		send[M],
		recvcounts[N] = {0}, 
		matriz[N][M] = {{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10}};

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	//MPI_Comm_size(MPI_COMM_WORLD, &size); // al usar matriz estática en memoria no es necesario ponerlo en función de size, ya que tenemos N fijada

	/* Inicialización datos send a partir de la matriz estática en memoria */
	for(i=0; i<M; i++) send[i] = matriz[rank][i];

    /* Inicialización en función de M y N */
    for(i=0; i<M; i++) recvcounts[i%N] += 1;

	MPI_Reduce_scatter(send, &sum, recvcounts, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	sumaParcial = 0;
	for(i=0; i<recvcounts[rank]; i++) sumaParcial = sumaParcial + sum[i];

	printf("P: %d, Resultado parcial: %d\n", rank, sumaParcial);

	MPI_Reduce(&sumaParcial, &sumaTotal, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(rank == 0) printf("Resultado final: %d\n", sumaTotal);

	MPI_Finalize();
	return 0;
}