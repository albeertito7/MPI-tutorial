 
#include "mpi.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {

	int rank, size, len;
	char nombre[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank == 0) {
		printf("Numero de procesos arrancados: %d\n", size );
	} else {
		MPI_Get_processor_name(nombre, &len);
		printf("Hola Mundo Paralelo! Ejecutable: %s, Pid: %d, Rango: %d, Maquina: %s\n", argv[0], getpid(), rank, nombre);
	}
	
	MPI_Finalize();
	return 0;
}