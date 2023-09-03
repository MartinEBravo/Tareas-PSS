#include <stdio.h>
#include "suma.h"

Bcd sumaBcd(Bcd x, Bcd y) {
  // carry
  Bcd carry = 0;
  Bcd result = 0;
  Bcd mask = 0xF;

  // a cada dígito hacemos su suma
  for (int i = 0; i < 64; i+=4) {
    // Extraemos los últimos 4 bits de cada número
    Bcd digitoX = x & mask;
    Bcd digitoY = y & mask;

    Bcd suma = digitoX + digitoY + carry;

    if (suma > 9){
      carry = 1;
      suma -= 10;
    }
    else
      carry = 0;
    
    result |= (Bcd)(suma & mask) << i;

    x >>= 4;
    y >>= 4;

    if (x == 0 && y == 0 && carry == 0) break;
  }
  // tiene hasta 16 cifras
  if (carry == 0) 
    return result;

  // tiene más de 16 cifras
  return (Bcd)0xffffffffffffffff;
}