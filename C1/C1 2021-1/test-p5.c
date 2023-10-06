#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>

#include "p5.h"

#define P1  8
#define P2  6
#ifdef VALGRIND
#define N 200000
#else
#define N 20000000
#endif

int verbose= 1;

// ----------------------------------------------------
// Funcion que entrega el tiempo transcurrido desde el lanzamiento del
// programa en milisegundos

long long getUSecsOfDay() {
    struct timeval Timeval;
    gettimeofday(&Timeval, NULL);
    return (long long)Timeval.tv_sec*1000000+Timeval.tv_usec;
}

static int time0= 0;

static int getTime0() {
    return getUSecsOfDay()/1000;
}

void resetTime() {
  time0= getTime0();
}

int getTime() {
  return getTime0()-time0;
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
// Libera un arbol binario

static void liberar(Nodo *a) {
  if (a!=NULL) {
    liberar(a->izq);
    liberar(a->der);
    free(a);
  }
}

// ----------------------------------------------------
// Construye arbol equilibrado con etiquetas de i a j

Nodo *equilibrado(int i, int j) {
  if (i>j)
    return NULL;

  int h= (i+j+1)/2;
  return abb(h, equilibrado(i, h-1), equilibrado(h+1, j));
}

// ----------------------------------------------------
// Version secuencial de buscar

static int buscarRec(Nodo *a, int z) {
  if (a==NULL)
    return 0;
  if (a->x==z)
    return 1;
  return buscarRec(a->izq, z) || buscarRec(a->der, z);
}

static int thread_cnt;
static pthread_mutex_t cnt_mtx= PTHREAD_MUTEX_INITIALIZER;

int buscar(Nodo *a, int z) {

  if (verbose) {
    if (a==NULL)
      printf("Buscando secuencialmente %d en arbol vacio\n", z);
    else
      printf("Buscando secuencialmente %d en arbol con raiz %d\n", z, a->x);
  }
  pthread_mutex_lock(&cnt_mtx);
  thread_cnt++;
  pthread_mutex_unlock(&cnt_mtx);
  return buscarRec(a, z);
}

int main() {

  printf("Test: Busqueda paralela en arbol nulo\n");
  verificar(buscarPar(NULL, 10, 1000000)==0,
            "buscarPar en arbol vacio no entrego 0");
  printf("Aprobado\n"); 

  printf("Test: Busqueda secuencial en arbol nulo\n");
  verificar(buscarPar(NULL, 10, 1)==0,
            "buscarPar en arbol vacio no entrego 0");
  printf("Aprobado\n"); 

  {
    Nodo *a= hoja(10);
    printf("Test: Busqueda exitosa paralela en una hoja\n");
    verificar(buscarPar(a, 10, 1000000)==1,
              "buscarPar 10 en arbol 10 no entrego 1");
    printf("Aprobado\n"); 

    printf("Test: Busqueda no exitosa paralela en una hoja\n");
    verificar(buscarPar(a, 0, 1000000)==0,
              "buscarPar 0 en arbol 10 no entrego 0");
    printf("Aprobado\n"); 

    printf("Test: Busqueda exitosa secuencial en una hoja\n");
    verificar(buscarPar(a, 10, 1)==1,
              "buscarPar 10 en arbol 10 no entrego 1");
    printf("Aprobado\n"); 

    printf("Test: Busqueda no exitosa secuencial en una hoja\n");
    verificar(buscarPar(a, 0, 1)==0,
              "buscarPar 0 en arbol 10 no entrego 0");
    printf("Aprobado\n"); 

    liberar(a);
  }

  {
    Nodo *a= abb(5, abb(2, NULL, abb(9, hoja(3), hoja(1))),
                     abb(7, hoja(6), NULL) );
    printf("Test: Busqueda paralela de 1 en arbol del enunciado\n");
    verificar(buscarPar(a, 1, 1000000)==1,
              "buscarPar de 1 en arbol del enunciado no entrego 1");
    printf("Aprobado\n"); 

    printf("Test: Busqueda paralela de 8 en arbol del enunciado\n");
    thread_cnt= 0;
    verificar(buscarPar(a, 8, 1000000)==0,
              "buscarPar de 8 en arbol del enunciado no entrego 0");
    printf("Aprobado\n"); 

    printf("Test: Busqueda secuencial de 1 en arbol del enunciado\n");
    verificar(buscarPar(a, 1, 1)==1,
              "buscarPar de 1 en arbol del enunciado no entrego 1");
    printf("Aprobado\n"); 

    printf("Test: Busqueda secuencial de 8 en arbol del enunciado\n");
    thread_cnt= 0;
    verificar(buscarPar(a, 8, 1)==0,
              "buscarPar de 8 en arbol del enunciado no entrego 0");
    verificar(thread_cnt==1, "No se ejecuto en 1 solo thread");
    printf("Aprobado\n"); 

    liberar(a);
  }

  {
    Nodo *a= equilibrado(0, N/100-1);

    printf("Test: Busqueda paralela no exitosa "
           "en arbol pequeño de %d nodos\n", N/100);
    thread_cnt= 0;
    verificar(buscarPar(a, N, P1)==0, "Buscar debio entregar 0");
    verificar(thread_cnt==P1, "No se ejecuto en los threads requeridos");
    printf("Aprobado\n"); 

    printf("Test: 100 busquedas paralelas exitosas "
           "en arbol pequeño de %d nodos\n", N/100);
    verbose= 0;
    int inc= N/100/100;
    for (int i= 0; i<N/100; i+= inc) {
      verificar(buscarPar(a, i, P2)==1, "buscarPar debio entregar 1");
    }
    thread_cnt= 0;
    verificar(buscarPar(a, N/100-1, P2)==1, "buscarPar debio entregar 1");
    verificar(thread_cnt==P2, "No se ejecuto en los threads requeridos");

    liberar(a);
    printf("Aprobado\n"); 
  }

  printf("\n");
  printf("---------\n");
  printf("Benchmark\n");
  printf("---------\n\n");

  double max_speedup= 0;

  {
    Nodo *a= equilibrado(0, N-1);
    verbose= 0;

#ifdef VALGRIND
#define REP 1
#else
#define REP 10
#endif

    printf("Test: %d busqueda(s) paralela no exitosa "
           "en arbol grande de %d nodos\n", REP, N);

    for (int i= 0; i<REP; i++) {
      resetTime();
      int res= buscar(a, N);
      int tiempo_sec= getTime();
      verificar(res==0, "Asercion fallida\n");
      printf("Tiempo secuencial = %d milisegundos\n", tiempo_sec);
      thread_cnt= 0;
      resetTime();
      res= buscarPar(a, N, P1);
      int tiempo_par= getTime();
      verificar(res==0, "La busqueda no fue fallida\n");
      verificar(thread_cnt==P1, "No se ejecuto en los threads requeridos");
      printf("Tiempo paralelo = %d milisegundos\n", tiempo_par);
      double speedup= (double)tiempo_sec/tiempo_par;
      if (tiempo_par!=0)
        printf("Speed up= %f\n", speedup);
      else
        printf("Tiempo en paralelo fue tan rapido que se midio como 0\n");
      if (speedup>max_speedup)
        max_speedup= speedup;
    }
    liberar(a);
  }

#ifdef VALGRIND
  printf("Felicitaciones: su solucion es correcta\n");
#else
  printf("\nMaximo speedup es %f\n", max_speedup);
  if (max_speedup>=1.7)
    printf("Felicitaciones: su solucion es correcta y eficiente\n");
  else if (max_speedup>=1)
    printf("Conclusion: su solucion es correcta, pero no muy eficiente\n");
  else
    printf("Mmmmmmmm: su solucion es correcta, pero ineficiente\n");
#endif
  
  return 0;
}
