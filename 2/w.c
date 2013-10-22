#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mpi.h"

#define MLD 1000000000.0

int main(int argc, char **argv) {
  int rank, np, i,
  	  vectorSize, vectorSizeSafe,
	    *vectorX, *vectorXPartial,
	    *vectorY, *vectorYPartial,
	    dotProduct = 0, dotProductPartial = 0;
  struct timespec start, stop;
  double t;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  if (argc < 2) {
	  if (rank == 0) {
      printf("\n   Podaj rozmiar wektora!\n\n");
    }

	  MPI_Finalize();
    return 0;
  }

  vectorSize = atoi(argv[1]);

  if (vectorSize < np) {
    vectorSizeSafe = np;
  } else {
    vectorSizeSafe = ceil((float) vectorSize / np) * np;
  }

  vectorX = (int*) malloc(vectorSizeSafe * sizeof(int));
  vectorY = (int*) malloc(vectorSizeSafe * sizeof(int));
  vectorXPartial = (int*) malloc(vectorSizeSafe / np * sizeof(int));
  vectorYPartial = (int*) malloc(vectorSizeSafe / np * sizeof(int));

  if (rank == 0) {
    clock_gettime(CLOCK_MONOTONIC, &start);
    srand(time(NULL));
  
    for (i = 0; i < vectorSizeSafe; i++) {
      if (i < vectorSize) {
        vectorX[i] = rand() % 10;
        vectorY[i] = rand() % 10;
      } else {
        vectorX[i] = 0;
        vectorY[i] = 0;
      }
    }
  }

  MPI_Scatter(vectorX,        vectorSizeSafe / np, MPI_INT,
              vectorXPartial, vectorSizeSafe / np, MPI_INT,
              0, MPI_COMM_WORLD);

  MPI_Scatter(vectorY,        vectorSizeSafe / np, MPI_INT,
              vectorYPartial, vectorSizeSafe / np, MPI_INT,
              0, MPI_COMM_WORLD);

  for (i = 0; i < vectorSizeSafe / np; i++) {
    dotProductPartial += vectorXPartial[i] * vectorYPartial[i];
  }

  MPI_Reduce(&dotProductPartial, &dotProduct, 1, MPI_INT,
			       MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    if (!argv[2]) printf("%i\n", dotProduct);

    clock_gettime(CLOCK_MONOTONIC, &stop);

    t = (stop.tv_sec + stop.tv_nsec / MLD) - (start.tv_sec + start.tv_nsec / MLD);

    printf("                              Czas: %lf\n", t);
  }

  MPI_Finalize();
  return 0;
}
