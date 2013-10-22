#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MLD 1000000000.0

int main(int argc, char **argv) {
  int i, vectorSize, *vectorX, *vectorY, dotProduct = 0;
  struct timespec start, stop;
  double t;

  if (argc < 2) {
    printf("\n   Podaj rozmiar wektora!\n\n");

    return 0;
  }

  vectorSize = atoi(argv[1]);

  vectorX = (int*) malloc(vectorSize * sizeof(int));
  vectorY = (int*) malloc(vectorSize * sizeof(int));

  srand(time(NULL));
  clock_gettime(CLOCK_MONOTONIC, &start);

  for (i = 0; i < vectorSize; i++) {
    vectorX[i] = rand() % 10;
    vectorY[i] = rand() % 10;

    dotProduct += vectorX[i] * vectorY[i];
  }

  if (!argv[2]) printf("%i\n", dotProduct);

  clock_gettime(CLOCK_MONOTONIC, &stop);

  t = (stop.tv_sec + stop.tv_nsec / MLD) - (start.tv_sec + start.tv_nsec / MLD);

  printf("                              Czas: %lf\n", t);

  return 0;
}
