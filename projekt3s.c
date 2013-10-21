#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
  int i, pointsSquare, pointsDisk = 0;
  float x, y;

  if (argc < 2) {
    printf("\n   Podaj ilość losowanych punktów!\n\n");

    return 0;
  }

  pointsSquare = atoi(argv[1]);

  srand(time(NULL));

  for (i = 0; i < pointsSquare; i++) {
    x = (float) rand() / (float) RAND_MAX;
    y = (float) rand() / (float) RAND_MAX;

    if (x * x + y * y <= 1) {
      pointsDisk++;
    }
  }

  printf("%.12f\n", (double) 4 * pointsDisk / pointsSquare);

  return 0;
}
