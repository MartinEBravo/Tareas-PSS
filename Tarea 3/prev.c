#include <stddef.h>

#include "prev.h"

void asignarPrev(Nodo *t, Nodo **pprev) {
  t->prox = NULL;
  if (*pprev != NULL) (*pprev)->prox = t;
  t->prev = *pprev;
  *pprev = t;
  if (t->izq != NULL) asignarPrev(t->izq, pprev);
  if (t->der != NULL) asignarPrev(t->der, pprev);
}