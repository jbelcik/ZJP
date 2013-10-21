#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
  int i, vectorSize, *vectorX, *vectorY, dotProduct = 0;

  if (argc < 2) {
    printf("\n   Podaj rozmiar wektora!\n\n");

    return 0;
  }

  vectorSize = atoi(argv[1]);

  vectorX = (int*) malloc(vectorSize * sizeof(int));
  vectorY = (int*) malloc(vectorSize * sizeof(int));

  srand(time(NULL));

  for (i = 0; i < vectorSize; i++) {
    vectorX[i] = rand() % 10;
    vectorY[i] = rand() % 10;

    dotProduct += vectorX[i] * vectorY[i];
  }

  printf("%i\n", dotProduct);

  return 0;
}
