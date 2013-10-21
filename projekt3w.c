#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char **argv) {
  int rank, np, i, pointsSquare, pointsDisk = 0, pointsDiskPartial = 0;
  float *points, *pointsPartial;
  double result;

  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  if (argc < 2) {
    if (rank == 0) {
      printf("\n   Podaj ilość losowanych punktów!\n\n");
    }

    MPI_Finalize();
    return 0;
  }

  pointsSquare = atoi(argv[1]) * 2;

  points = (float*) malloc(pointsSquare * np * sizeof(float));
  pointsPartial = (float*) malloc(pointsSquare * sizeof(float));

  if (rank == 0) {
    srand(time(NULL));

    for (i = 0; i < pointsSquare * np; i++) {
      points[i] = (float) rand() / (float) RAND_MAX;
    }
  }

  MPI_Scatter(points,        pointsSquare, MPI_FLOAT,
              pointsPartial, pointsSquare, MPI_FLOAT,
              0, MPI_COMM_WORLD);

  for (i = 0; i < pointsSquare; i += 2) {
    if (pointsPartial[i] * pointsPartial[i] + pointsPartial[i + 1] * pointsPartial[i + 1] <= 1) {
      pointsDiskPartial++;
    }
  }

  printf("       %i - %i disk\n", rank, pointsDisk);
  printf("       %i - %i diskPartial\n", rank, pointsDiskPartial);
  printf("       %i - %i square\n", rank, pointsSquare * np);

  MPI_Reduce(&pointsDiskPartial, &pointsDisk, np, MPI_INT,
             MPI_SUM, 0, MPI_COMM_WORLD);

  printf("SECOND %i - %i disk\n", rank, pointsDisk);
  printf("SECOND %i - %i diskPartial\n", rank, pointsDiskPartial);
  printf("SECOND %i - %i square\n", rank, pointsSquare * np);

  if (rank == 0) {
    result = (double) 4 * pointsDisk / pointsSquare * np;
///*
    printf("%.12lf\n", result);
//*/
  }

  MPI_Finalize();
  return 0;
}
