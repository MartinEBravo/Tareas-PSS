#include <stdio.h>
#include <stdlib.h>

#include "p1.h"

int main() {
  unsigned int r= max01(0b00110011000011001111100011110001);
  int max0s=r&0b111111, max1s=r>> 6; // max0s=4 y max1s=5
  if (max0s!=4) {
    fprintf(stderr, "max0s=%d, es incorrecto, debio ser 4\n", max0s);
    exit(1);
  }
  if (max1s!=5) {
    fprintf(stderr, "max1s=%d, es incorrecto, debio ser 5\n", max1s);
    exit(1);
  }

  printf("Felicitaciones, los resultados son correctos: max0s= %d, max1s= %d\n",
         max0s, max1s);
  return 0;
}
