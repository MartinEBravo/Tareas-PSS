#include <stdio.h>
#include <stdlib.h>

#include "p3.h"

int elimUnicos(Nodo **pa) {
  Nodo *a = *pa;
  if (a == NULL) return 0;
  if (a->izq != NULL && a->der != NULL)
    return elimUnicos(&a->izq)+elimUnicos(&a->der);
  else if (a->izq == NULL && a->der == NULL) return 0;
  else if (a->izq == NULL){
    *pa = a->der;
      free(a);
      return 1+elimUnicos(&a->izq);
  }
  else{
    *pa = a->izq;
      free(a);
    return 1+elimUnicos(&a->der);
  }
}
