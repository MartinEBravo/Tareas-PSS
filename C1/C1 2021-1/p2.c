#include <string.h>

#include "p2.h"

void espaciar(char *str) {
  int n = strlen(str);
  char *p1 = str+n-1;
  char *p2 = str+2*n;
  *p2 = 0;
  p2--;
  for (int i = 0; i < n; i++){
    *p2 = ' ';
    p2--;
    *p2 = *p1;
    p1--;
    p2--;
  }
}
