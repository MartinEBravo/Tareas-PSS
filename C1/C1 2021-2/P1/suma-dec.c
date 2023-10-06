#include <stdio.h>

#include "suma-dec.h"

Decimal sumaDecimal(Decimal x, Decimal y) {

  Decimal carry = 0, result = 0, mask = 0xF;

  for (int i = 0; i < 64; i+=4){
    Decimal digitoX = x & mask, digitoY = y & mask;
    Decimal suma = digitoX + digitoY + carry;
    if (suma > 9) {
      carry = 1;
      suma -= 10;
    } else {
      carry = 0;
    }
    result |= (suma&mask)<<i;
    x >>= 4;
    y >>= 4;
  }
  return result;
}
