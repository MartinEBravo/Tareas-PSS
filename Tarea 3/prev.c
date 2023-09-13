#include <stddef.h>

#include "prev.h"

void asignarPrev(Nodo *t, Nodo **pprev) {
  
  // Abordamos caso árbol vacio
  if (t == NULL) 
    return;
  // Recorremos árbol izquierdo
  if (t->izq != NULL) 
    asignarPrev(t->izq, pprev);

  // Asignamos previo y prox
  t->prox = NULL;
  if (*pprev != NULL) 
    (*pprev)->prox = t;
  t->prev = *pprev;
  *pprev = t;

  // Recorremos árbol derecho
  if (t->der != NULL) 
    asignarPrev(t->der, pprev);
}