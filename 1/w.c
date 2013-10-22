#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mpi.h"

#define MLD 1000000000.0

int main(int argc, char **argv) {
  int rank, np, i, j, k,
      *vector, *vectorPartial, *vectorFinal,
      *matrix, *matrixPartial, matrixSize, matrixSizeSafe, matrixSizeSafeHelp;
  struct timespec start, stop;
  double t;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  if (argc < 2) {
    if (rank == 0) {
      printf("\n   Podaj rozmiar macierzy kwadratowej!\n\n");
    }

    MPI_Finalize();
    return 0;
  }

  matrixSize = atoi(argv[1]);
  
  if (matrixSize < np) {
    matrixSizeSafe = np;
  } else {
    matrixSizeSafe = ceil((float) matrixSize / np) * np;
  }

  vector = (int*) malloc(matrixSizeSafe * sizeof(int));
  vectorFinal = (int*) malloc(matrixSizeSafe * sizeof(int));
  vectorPartial = (int*) malloc(matrixSizeSafe / np * sizeof(int));
  matrix = (int*) malloc(matrixSizeSafe * matrixSizeSafe * sizeof(int));
  matrixPartial = (int*) malloc(matrixSizeSafe * matrixSizeSafe / np * sizeof(int));

  if (rank == 0) {
    clock_gettime(CLOCK_MONOTONIC, &start);
    srand(time(NULL));

    for (i = 0; i < matrixSizeSafe; i++) {
      if (i < matrixSize) {
        vector[i] = rand() % 10;
      } else {
        vector[i] = 0;
      }
    }

    for (i = 0; i < matrixSizeSafe * matrixSizeSafe; i++) {
      if (i % matrixSizeSafe < matrixSize && i < matrixSizeSafe * matrixSize) {
        matrix[i] = rand() % 10;
      } else {
        matrix[i] = 0;
      }
    }

    if (!argv[2]) {
      for (i = 0, j = 0; i < matrixSizeSafe * matrixSizeSafe && j < matrixSizeSafe; i++) {
        printf("%i ", matrix[i]);

        if (i % matrixSizeSafe == matrixSizeSafe - 1) {
          printf("   %i\n", vector[j++]);
        }
      }
    }
  }

  MPI_Bcast(vector, matrixSizeSafe, MPI_INT, 0, MPI_COMM_WORLD);

  MPI_Scatter(matrix,        matrixSizeSafe * matrixSizeSafe / np, MPI_INT,
              matrixPartial, matrixSizeSafe * matrixSizeSafe / np, MPI_INT,
              0, MPI_COMM_WORLD);

  for (i = 0, k = 0, matrixSizeSafeHelp = matrixSizeSafe; i < matrixSizeSafe / np; i++, matrixSizeSafeHelp *= 2) {
    vectorPartial[i] = 0;

    for (j = 0; j < matrixSizeSafe && k < matrixSizeSafeHelp; j++, k++) {
      vectorPartial[i] += matrixPartial[k] * vector[j];
    }
  }

  MPI_Gather(vectorPartial, matrixSizeSafe / np,  MPI_INT, 
             vectorFinal,   matrixSizeSafe / np,  MPI_INT, 
             0, MPI_COMM_WORLD);

  if (rank == 0) {
    if (!argv[2]) {
      for (i = 0; i < matrixSizeSafe; i++) {
        printf("%i\n", vectorFinal[i]);
      }
    }

    clock_gettime(CLOCK_MONOTONIC, &stop);

    t = (stop.tv_sec + stop.tv_nsec / MLD) - (start.tv_sec + start.tv_nsec / MLD);

    printf("                              Czas: %lf\n", t);
  }

  MPI_Finalize();
  return 0;
}
