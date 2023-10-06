#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "p2.h"

int main() {
  char *hola= "hola";
  char *s= malloc(2*strlen(hola)+1);
  strcpy(s, hola);
  espaciar(s);
  if (strcmp(s, "h o l a ")!=0) {
    fprintf(stderr, "resultado \"%s\" es incorrecto\n", s);
    exit(1);
  }
  printf("Felicitaciones, el resultado es correcto: \"%s\"\n", s);
  free(s);
  return 0;
}
