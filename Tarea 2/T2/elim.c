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

  while (*p1){
    int match = 1; // bool si hay match o no

    for(int i = 0; i < len; i++){ // Recorremos el pat (puntero_pat) y vemos si hay match
      if (*p2 != *puntero_pat || *p2 == '\0'){
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
      p2 = p1;
      *p3 = '\0';
      puntero_pat = pat;
    }
    // Si no hay match vamos a avanzar el puntero y reiniciar los punteros
    else{
      p1++;
      p2 = p1;
      puntero_pat = pat;
    }
  }
  *p1 = '\0';
}

char *eliminados(char *str, char *pat) {
  int len = strlen(pat); // Guardamos el largo de pat
  char *p1 = str;
  char *p2 = p1;
  char *puntero_pat = pat;
  int count = 0;

  while (*p1){
    int match = 1; // bool si hay match o no

    for(int i = 0; i < len; i++){ // Recorremos el pat (puntero_pat) y vemos si hay match
      if (*p2 != *puntero_pat || *p2 == '\0'){
        match = 0;
        break;
      }
      p2++;
      puntero_pat++;
    }
    
    // Si hay match vamos a saltarnos todo el pat
    if (match) {
      p1 += len;
      p2 = p1;
      puntero_pat = pat;
    } 
    else {
      count++;
      p1++;
      p2 = p1;
      puntero_pat = pat;
    }
  }
  *p1 = '\0';

  char *str2 = malloc(count + 1); // Asigna memoria para la nueva cadena
  p1 = str;
  p2 = str;
  char *p3 = str2;
  char *p4 = str2;
  puntero_pat = pat;

  while(*p1){

    int match = 1;

    for(int i = 0; i < len; i++){
      if (*p2 != *puntero_pat || *p2 == '\0'){
        match = 0;
        break;
      }
      p2++;
      puntero_pat++;

    }

    if(match){
      p1 += len;
      p2 = p1;
      puntero_pat = pat;
    }
    else{
      p2 = p1;
      p4 = p3;
      while(*p2 && *p2 != '\0'){
        *p4 = *p2;
        p2++;
        p4++;
      }
      p1++;
      p2 = p1;
      p3++;
      puntero_pat = pat;
    }
  }
  *p3 = '\0';
  return str2;
}


