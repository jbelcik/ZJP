#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
  int i, j, *vector, *vectorFinal, **matrix, matrixSize;

  if (argc < 2) {
    printf("\n   Podaj rozmiar macierzy kwadratowej!\n\n");

    return 0;
  }

  matrixSize = atoi(argv[1]);

  vector = vectorFinal = (int*) malloc(matrixSize * sizeof(int));
  matrix = (int**) malloc(matrixSize * sizeof(int*));

  srand(time(NULL));

  for (i = 0; i < matrixSize; i++) {
    matrix[i] = (int*) malloc(matrixSize * sizeof(int));

    vector[i] = rand() % 10;

    for (j = 0; j < matrixSize; j++) {
      matrix[i][j] = rand() % 10;
///*
      printf("%i ", matrix[i][j]);
//*/
    }
///*
    printf("   %i\n", vector[i]);
//*/
  }

  for (i = 0; i < matrixSize; i++) {
    vectorFinal[i] = 0;

    for (j = 0; j < matrixSize; j++) {
      vectorFinal[i] += matrix[i][j] * vector[j];
    }
///*
    printf("%i\n", vectorFinal[i]);
//*/
  }

  return 0;
}
