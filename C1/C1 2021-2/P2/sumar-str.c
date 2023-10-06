#include <stdio.h>
#include <string.h>

#include "sumar-str.h"

char sumarStr(char *a, char *b) {
  char n = strlen(a), carry = 0;
  char *pa = a + n - 1;
  char *pb = b + n - 1;
  for (int i = 0; i < n; i++){
    char digitoA = *pa - '0', digitoB = *pb - '0';
    char suma = digitoA + digitoB + carry;
    if (suma>9){
      suma-=10;
      carry=1;
    }
    else{
      carry = 0;
    }
    *pa = suma+'0';
    pa--;
    pb--;
  }
  return carry+'0';
}
