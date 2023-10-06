#include "p1.h"

unsigned int max01(unsigned int x) {
  // 1s consecutivos
  int count1 = 0;
  unsigned int aux = x;
  unsigned int aux2 = aux;
  while(aux != 0){
    aux2 <<= 1;
    aux = aux & aux2; // Uso de '&'
    count1++;
  }
  
  // 0s consecutivos
  int count0 = 0;
  aux = x;
  aux2 = x;
  while (aux != 0xFFFFFFFF) { // Detener cuando el resultado sea -1
    aux2 = (aux2 << 1) | 1; // Agregar 1 a la derecha
    aux = aux | aux2;
    count0++;
  }
  
  unsigned int result = (count1 << 6) | count0;
  return result;
}
