#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/*
	MPI_Type_vector se usa para la matriz de enteros
	MPI_Type_struct se usa para la estructura de datos Particula
	Pack & Unpack se usan para empaquetar/desempaquetar los datos, así agrupamos los datos en un mismo mensaje
 */

/* Run with two processes */
int main(int argc, char **argv) {

	int rank, i, j, position, M;
	char buff[1000];
	MPI_Status status;

	struct Particula { float x; float y; float massa; char Nombre[50]; } data;

	if(argv[1] != NULL) {
		M =  atoi(argv[1]);
	}else {
		M = 2;
	}

	int vector[M][M];

	int blocklengths[4] = {1,1,1,60};
	MPI_Datatype restype, coltype, types[4] = {MPI_FLOAT, MPI_FLOAT, MPI_FLOAT, MPI_CHAR};
	MPI_Aint displacements[4], floatex;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Type_extent(MPI_FLOAT, &floatex);

	displacements[0] = (MPI_Aint) 0;
	displacements[1] = displacements[2] = displacements[3] = floatex;

	MPI_Type_struct(4, blocklengths, displacements, types, &restype);
	MPI_Type_commit(&restype);

	MPI_Type_vector(M, M, M, MPI_INT, &coltype);
	MPI_Type_commit(&coltype);

	if(rank == 0) {

		/* Inicialización de los datos */
		data.x = 1.2; data.y= 2.3; data.massa = 72.5; for(i=0; i<50; i++) data.Nombre[i] = (char) 'a';
		for(i=0; i<M; i++) for(j=0; j<M; j++) vector[i][j] = 1;

		position = 0;
		MPI_Pack(&data,1, restype, buff, 1000, &position, MPI_COMM_WORLD);
		MPI_Pack(&vector,1, coltype, buff, 1000, &position, MPI_COMM_WORLD);

		MPI_Send(buff, position, MPI_PACKED, 1, 7, MPI_COMM_WORLD);
	}
	else {

		MPI_Recv(buff, 1000, MPI_PACKED, 0, 7, MPI_COMM_WORLD, &status);
		
		position = 0;
		MPI_Unpack(buff, 1000, &position, &data, 1, restype, MPI_COMM_WORLD);
		MPI_Unpack(buff, 1000, &position, &vector, 1, coltype, MPI_COMM_WORLD);

		/* Imprimir Resultados */
		printf("P: %d:\n x: %f\n y: %f\n massa: %f\n Nombre: %c", rank, data.x, data.y, data.massa, data.Nombre[0]);
		for(i=1; i<49; i++) printf("%c", data.Nombre[i]);
		printf("%c\n", data.Nombre[49]);

		printf(" Vector:\n");
		for(i=0; i<M; i++) for(j=0; j<M; j++) printf("  vector[%d][%d] = %d\n", i, j, vector[i][j]);
	}

	MPI_Finalize();
	return 0;
}