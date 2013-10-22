#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MLD 1000000000.0

int main(int argc, char **argv) {
  int i, pointsSquare, pointsDisk = 0;
  float x, y;
  struct timespec start, stop;
  double t;

  if (argc < 2) {
    printf("\n   Podaj ilość losowanych punktów!\n\n");

    return 0;
  }

  pointsSquare = atoi(argv[1]);

  clock_gettime(CLOCK_MONOTONIC, &start);
  srand(time(NULL));

  for (i = 0; i < pointsSquare; i++) {
    x = (float) rand() / (float) RAND_MAX;
    y = (float) rand() / (float) RAND_MAX;

    if (x * x + y * y <= 1) {
      pointsDisk++;
    }
  }

  if (!argv[2]) printf("%.12f\n", (double) 4 * pointsDisk / pointsSquare);

  clock_gettime(CLOCK_MONOTONIC, &stop);

  t = (stop.tv_sec + stop.tv_nsec / MLD) - (start.tv_sec + start.tv_nsec / MLD);

  printf("                              Czas: %lf\n", t);

  return 0;
}
