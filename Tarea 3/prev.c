#include <stddef.h>

#include "prev.h"

typedef struct nodo {
  int x;
  struct nodo *izq, *der, *prev, *prox;
} Nodo;

void asignarPrev(Nodo *t, Nodo **pprev) {
  t->prev = *pprev;
  t->prox = NULL;
  if (t->izq != NULL) {
    t->prox = t->izq;
    t = *pprev;
    asignarPrev(t->izq, &t);
  }
  if (t->der != NULL) {
    t->prox = t->der;
    t = *pprev;
    asignarPrev(t->der, pprev);
  }
  
}