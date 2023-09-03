#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elim.h"

int main(){
  chat str[] = "hola mundo";
  eliminar(str, "o");
  printf("%s\n", str);
  pritf("%s\n", eliminados("hola mundo", "o"));
}


// Elimina todas las ocurrencias de pat en str
void eliminar(char *str, char *pat){
  int len = strlen(pat); // Guardamos el largo de pat
  char *p = str;
  char *p2 = str;

  while (*p2){
    char *p3 = pat;
    int match = 1; // bool si hay match o no

    for (int i = 0; i < len; i++){
      if (*p2 != *p3){
        match = 0;
        break;
      }
      p2++;
      p3++;
    }

    if(match){
      *p = *p2;
    } 
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
char *eliminados(char *str, char *pat){
  int len = strlen(pat); // Guardamos el largo de pat
  char *p = str;
  char *p2 = str;

  while (*p2){
    char *p3 = pat;
    int match = 1; // bool si hay match o no

    for (int i = 0; i < len; i++){
      if (*p2 != *p3){
        match = 0;
        break;
      }
      p2++;
      p3++;
    }

    if(match){
      *p = *p2;
    } 
    else {
      *p = *p2;
      p++;
      p2++;
    }
  }
  *p = '\0';
  char *str2 = malloc(strlen(str) + 1);
  strcpy(str2, str);
  return str2;
}
