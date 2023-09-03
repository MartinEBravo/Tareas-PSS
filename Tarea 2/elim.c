#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elim.h"

// Elimina todas las ocurrencias de pat en str
void eliminar(char *str, char *pat){
  int len = strlen(pat); // Guardamos el largo de pat
  char *p = str;
  char *p2 = str;

  while (*p2){
    char *p3 = pat;
    int match = 1; // bool si hay match o no

    for (int i = 0; i < len; i++){
      if (*p2 != *p3){ // Si no hay match
        match = 0;
        break;
      }
      p2++;
      p3++;
    }

    // Si hay match vamos a saltarnos todo el pat
    if(match){
      *p = *p2;
    } 
    // Si no avanzamos
    else {
      *p = *p2;
      p++;
      p2++;
    }
  }
  *p = '\0';
}

// Entrega un nuevo string en donde
// se han eliminado todas las ocurrencias de pat en str
char *eliminados(char *str, char *pat) {
  int len = strlen(pat); // Guardamos el largo de pat
  char *p2 = str;
  int count = 0; // Primero contaremos la cantidad de caracteres para hacer el malloc

  while (*p2) {
    char *p3 = pat;
    int match = 1; // Booleano que indica si hay match o no

    for (int i = 0; i < len; i++) {
      if (*p2 != *p3) {
        match = 0;
        break;
      }
      p2++;
      p3++;
    }

    if (!match) {
      count++;
      }  
    else{
      p2 -= len;
    }

    p2++;
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
