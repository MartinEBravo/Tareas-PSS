#include <string.h>

int palabras(char *s){
  char *p = s;
  int count = 0;
  while(*p){
    // we are in a word
    if (*p != ' ')
      continue;
    // first space after a word
    if (*p == ' '){
      count++;
      while(*p && *p == ' ')
        p++;
    }   
  }
  return count;
}

int longer(int x, int y){
  if (x < y)
    return 1;
  else if (x > y)
    return -1;
  else
    return 0;
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

    int t1 = longer(wp1, wp2);

    if (t1 <= 0)
      p++;
    else {
      char *tmp= p[0];
      p[0]= p[1];
      p[1]= tmp;
      p= a;
    }
  }
}
