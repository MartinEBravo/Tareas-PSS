#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pss.h"

typedef struct {
  char var[80];
  char newLine;
} Linea;

// linea desocupada
char lineaVacia[80] = "\n";


int main(int argc, char *argv[]) {

  // Verificar argumentos
  if (argc != 4){
    fprintf(stderr, "Uso: %s <diccionario> <llave> <definicion>\n", argv[0]);
    exit(1);
  }

  // Obtener argumentos
  char *nomArch = argv[1];
  char *llave = argv[2];
  char *definicion = argv[3];
  int tamLlave = strlen(llave);
  int tamDefinicion = strlen(definicion);

  // Abrir archivo del diccionario 
  FILE *fileDicc = fopen(nomArch, "r+");
  if (fileDicc == NULL){
    perror(nomArch);
    exit(2);
  }

  // Calcular tamaño del archivo
  fseek(fileDicc, 0, SEEK_END);
  int tamArchivo = ftell(fileDicc);
  
  // Calcular número de líneas
  int numDef = tamArchivo / sizeof(Linea);

  // numero de linea donde se encuentra la llave
  int numLinea = hash_string(llave) % numDef;
  int numLineaInicial = numLinea;
  Linea linea;


  // Mientras quede archivo por leer
  while (numLinea < numDef){

    // NO se puede mover a la posición numLinea
    if (fseek(fileDicc, numLinea * sizeof(Linea), SEEK_SET) != 0){
      perror(nomArch);
      exit(3);
    }
    // No se puede leer la línea
    if (fread(&linea, sizeof(Linea), 1, fileDicc) != 1){
      perror(nomArch);
      exit(4);
    }
    // Si la llave ya existe
    if (strncmp(linea.var, llave, tamLlave) == 0){
      perror(nomArch);
      exit(5);
    }

    // Si la línea está vacía
    if (strncmp(linea.var, lineaVacia, 80) == 0){
      // Entonces escribimos
      fprintf(fileDicc, "%s:%s\n", llave, definicion);
      fclose(fileDicc);
      return 0;
    }

    // Si la línea está ocupada
    numLinea++;
  }
  // Si llegamos al final del archivo
  numLinea = 0;

  // repetimos el proceso
  while (numLinea < numLineaInicial){

   // NO se puede mover a la posición numLinea
    if (fseek(fileDicc, numLinea * sizeof(Linea), SEEK_SET) != 0){
      perror(nomArch);
      exit(3);
    }
    // No se puede leer la línea
    if (fread(&linea, sizeof(Linea), 1, fileDicc) != 1){
      perror(nomArch);
      exit(4);
    }
    // Si la llave ya existe
    if (strncmp(linea.var, llave, tamLlave) == 0){
      perror(nomArch);
      exit(5);
    }

    // Si la línea está vacía
    if (strncmp(linea.var, lineaVacia, 80) == 0){
      // Entonces escribimos
      fprintf(fileDicc, "%s:%s\n", llave, definicion);
      fclose(fileDicc);
      return 0;
    }

    // Si la línea está ocupada
    numLinea++;
  }

  // El archivo está lleno
  perror(nomArch);
  exit(6);
  return 0;
}
