#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "p3.h"

// ----------------------------------------------------
// Funcion que muestra un abb con indentacion

void mostrar(Nodo *a, int lvl) {
  int i;
  for (i= 0; i<lvl; i++)
    putchar(' ');

  if (a==NULL) {
    printf("NULL\n");
  }
  else {
    printf("%d\n", a->x);
    mostrar(a->izq, lvl+2);
    mostrar(a->der, lvl+2);
  }
}

// ----------------------------------------------------
// Funcion que construye un arbol binario a partir de otros 2

static Nodo *abb(int x, Nodo *izq, Nodo *der) {
  Nodo *a= malloc(sizeof(*a));
  a->x= x;
  a->izq= izq;
  a->der= der;
  return a;
}

// ----------------------------------------------------
// Funcion que construye un arbol consistente en una sola hoja

static Nodo *hoja(int x) {
  return abb(x, NULL, NULL);
}

// ----------------------------------------------------
// Funcion que verifica que 2 arboles binarios son iguales

static void comparar(Nodo *a, Nodo *b) {
  if (a==NULL) {
    if (b==NULL)
      return;
    fprintf(stderr, "Arboles distintos: a es NULL, b tiene etiqueta %d\n",
                    b->x);
    exit(1);
  }
  else if (b==NULL) {
    fprintf(stderr, "Arboles distintos: b es NULL, a tiene etiqueta %d\n",
                    a->x);
    exit(1);
  }
  else {
    if (a->x!=b->x) {
      fprintf(stderr, "Etiquetas de arboles son distintas: %d != %d\n",
                      a->x, b->x);
      exit(1);
    }
    comparar(a->izq, b->izq);
    comparar(a->der, b->der);
  }
}

// ----------------------------------------------------
// Funcion que termina con un error si un valor es falso

static void verificar(int b, char *msg) {
  if (!b) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
  }
}

// ----------------------------------------------------
// Funcion que verifica que 2 arboles son el mismo

static void identidad(Nodo *a, Nodo *b) {
  verificar(a==b, "Arboles no son identicos (misma direccion)");
}

// ----------------------------------------------------
// Libera un arbol binario

static void liberar(Nodo *a) {
  if (a!=NULL) {
    liberar(a->izq);
    liberar(a->der);
    free(a);
  }
}

// ----------------------------------------------------
// Crea una copia de un arbol binario

static Nodo *copia(Nodo *a) {
  if (a==NULL)
    return NULL;

  Nodo *an= malloc(sizeof(Nodo));
  an->x= a->x;
  an->izq= copia(a->izq);
  an->der= copia(a->der);
  return an;
}

int main() {
  printf("El arbol vacio\n");

  {
    Nodo *a= NULL;
    int r= elimUnicos(&a);
    comparar(a, NULL);
    verificar(r==0, "el valor retornado no es 0");
    printf("Test aprobado\n");
  }

  printf("Arbol con un solo nodo: debe sobrevivir porque no tiene hijos\n");

  {
    Nodo *a= hoja(5);
    Nodo *ref1= a;
    Nodo *ref2= copia(a);
    int r= elimUnicos(&a);
    identidad(a, ref1);
    comparar(a, ref2);
    verificar(r==0, "el valor retornado no es 0");
    liberar(a);
    liberar(ref2);
    printf("Test aprobado\n");
  }

  printf("Arbol con un nodo con un hijo a la izquierda: debe borrar la raiz\n");

  {
    Nodo *h= hoja(5);
    Nodo *ref= copia(h);
    Nodo *a= abb(2, h, NULL);
    int r= elimUnicos(&a);
    identidad(a, h);
    comparar(a, ref);
    verificar(r==1, "el valor retornado no es 1");
    liberar(h);
    liberar(ref);
    printf("Test aprobado\n");
  }

  printf("Arbol con un nodo con un hijo a la derecha: debe borrar la raiz\n");

  {
    Nodo *h= hoja(5);
    Nodo *ref= copia(h);
    Nodo *a= abb(2, NULL, h);
    int r= elimUnicos(&a);
    identidad(a, h);
    comparar(a, ref);
    verificar(r==1, "el valor retornado no es 1");
    liberar(h);
    liberar(ref);
    printf("Test aprobado\n");
  }

  printf("Arbol con un nodo con sus 2 hijos: "
         "el arbol completo debe sobrevivir\n");

  {
    Nodo *izq= hoja(5);
    Nodo *der= hoja(7);
    Nodo *a= abb(2, izq, der);
    Nodo *ref1= a;
    Nodo *ref2= copia(a);
    int r= elimUnicos(&a);
    identidad(a, ref1);
    comparar(a, ref2);
    verificar(r==0, "el valor retornado no es 0");
    liberar(a);
    liberar(ref2);
    printf("Test aprobado\n");
  }

  
  printf("El ejemplo del enunciado\n");

  {
    Nodo *a= abb(5, abb(2, NULL, abb(9, hoja(3), hoja(1))),
                     abb(7, hoja(6), NULL) );
    Nodo *nodo5= a;
    Nodo *nodo9= a->izq->der;
    Nodo *nodo3= nodo9->izq;
    Nodo *nodo1= nodo9->der;
    Nodo *nodo6= a->der->izq;
    Nodo *ref= abb(5, abb(9, hoja(3), hoja(1)), hoja(6));
    int r= elimUnicos(&a);
    comparar(a, ref);
    identidad(a, nodo5);
    identidad(a->izq, nodo9);
    identidad(a->izq->izq, nodo3);
    identidad(a->izq->der, nodo1);
    identidad(a->der, nodo6);
    verificar(r==2, "el valor retornado no es 2");
    liberar(a);
    liberar(ref);
    printf("Test aprobado\n");
  }

  printf("Felicitaciones: paso todos los tests\n");

  return 0;
}
