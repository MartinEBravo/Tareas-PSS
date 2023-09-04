#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elim.h"

void eliminar(char *str, char *pat);
char *eliminados(char *str, char *pat);

// Elimina todas las ocurrencias de pat en str
void eliminar(char *str, char *pat){
  int len = strlen(pat); // Guardamos el largo de pat
  char *p1 = str;
  char *p2 = p1;
  char *p3 = p1;
  char *puntero_pat = pat;

  while (*p2){
    int match = 1; // bool si hay match o no

    for(int i = 0; i < len; i++){ // Recorremos el pat (puntero_pat) y vemos si hay match
      if (*p2 != *puntero_pat){ // Si no hay match
        match = 0;
        break;
      }
      p2++;
      puntero_pat++;
    }
    
    // Si hay match vamos a saltarnos todo el pat
    if(match){
      p2 = p1 + len;
      p3 = p1;
      while(*p2){
        *p3 = *p2;
        p3++;
        p2++;
      }
      *p3 = '\0';
    }


    p1++;
    p2 = p1;
    puntero_pat = pat;
  }
  *p1 = '\0';
}

// Entrega un nuevo string en donde
// se han eliminado todas las ocurrencias de pat en str
char *eliminados(char *str, char *pat) {
  int len = strlen(pat); // Guardamos el largo de pat
  char *p1 = str;
  char *p2 = p1;
  char *p3 = p1;
  char *puntero_pat = pat;
  int count = 0; // Primero contaremos la cantidad de caracteres para hacer el malloc

  while (*p2) {
    int match = 1; // Booleano que indica si hay match o no

    puntero_pat = pat;
    for (int i = 0; i < len; i++) {
      if (*p2 != *puntero_pat) {
        match = 0;
        break;
      }
      p2++;
      puntero_pat++;
    }

    // Si hay match vamos a saltarnos todo el pat
    if(match){
      count++;
      p2 = p1 + len;
      *p1 = *p2;
      p1++;
    }
    p2 = p1;
    puntero_pat = pat;

    p1++;
  }

  char *str2 = malloc(count + 1); // Alojamos la memoria

  p2 = str;
  char *p4 = str2;

  while (*p2) {
    char *p3 = pat;
    int match = 1;

    for (int i = 0; i < len; i++) {
      if (*p2 != *p3) {
        match = 0;
        break;
      }
      p2++;
      p3++;
    }
    if (!match){
      *p4 = *p2;
      p2++;
      p4++;
    }
  }
  *p4 = '\0';
  return str2;
}

