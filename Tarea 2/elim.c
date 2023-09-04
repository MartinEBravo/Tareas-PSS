#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elim.h"

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

char *eliminados(char *str, char *pat) {
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

  int len2 = strlen(str);

  char *str2 = malloc(len2 + 1); // Asigna memoria para la nueva cadena
  char *p4 = str;
  char *p5 = str2;

  while (*p4){
    *p5 = *p4;
    p4++;
    p5++;
  }
  *p5 = '\0';
  return str2;
}


