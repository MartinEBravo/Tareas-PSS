#include <string.h>

int palabras(char *s) {
  int count = 0;
  while (*s) {
    while (*s == ' ')
      s++;
    if (*s) {
      count++;
      while (*s != ' ' && *s != 0)
        s++;
    }
  }
  return count;
}



void sort(char **a, int n) {
  char **ult= &a[n-1];
  char **p= a;
  while (p<ult) {
    // first word
    char *p1 = p[0];
    // second word
    char *p2 = p[1];

    int wp1 = palabras(p1);
    int wp2 = palabras(p2);

    int rc = wp1 - wp2;

    // Correct order or equal
    if (rc <= 0)
      p++;
    // Incorrect order, we have to swap
    else {
      char *tmp= p[0];
      p[0]= p[1];
      p[1]= tmp;
      p= a;
    }
  }
}
