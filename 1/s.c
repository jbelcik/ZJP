#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MLD 1000000000.0

int main(int argc, char **argv) {
  int i, j, *vector, *vectorFinal, **matrix, matrixSize;
  struct timespec start, stop;
  double t;

  if (argc < 2) {
    printf("\n   Podaj rozmiar macierzy kwadratowej!\n\n");

    return 0;
  }

  matrixSize = atoi(argv[1]);

  vector = (int*) malloc(matrixSize * sizeof(int));
  vectorFinal = (int*) malloc(matrixSize * sizeof(int));
  matrix = (int**) malloc(matrixSize * sizeof(int*));

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
  srand(time(NULL));

  for (i = 0; i < matrixSize; i++) {
    matrix[i] = (int*) malloc(matrixSize * sizeof(int));

    vector[i] = rand() % 10;

    for (j = 0; j < matrixSize; j++) {
      matrix[i][j] = rand() % 10;

      if (!argv[2]) printf("%i ", matrix[i][j]);
    }

    if (!argv[2]) printf("   %i\n", vector[i]);
  }

  for (i = 0; i < matrixSize; i++) {
    vectorFinal[i] = 0;

    for (j = 0; j < matrixSize; j++) {
      vectorFinal[i] += matrix[i][j] * vector[j];
    }

    if (!argv[2]) printf("   %i\n", vectorFinal[i]);
  }

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);

  t = (stop.tv_sec + stop.tv_nsec / MLD) - (start.tv_sec + start.tv_nsec / MLD);

  printf("                              Czas: %lf us\n", t);

  return 0;
}
