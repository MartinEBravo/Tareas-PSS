#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pss.h"

int main(int argc, char *argv[]) {

  // Buffer para leer una línea
  char linea[81];

  // Verificar argumentos
  if (argc != 4){
    fprintf(stderr, "Uso: ./definir <diccionario> <llave> <definicion>\n");
    exit(1);
  }


  // Obtener argumentos
  char *nomArch = argv[1];
  char *llave = argv[2];
  char *definicion = argv[3];

  // Obtener tamaño de la llave y la definición
  int tamLlave = strlen(llave);
  // int tamDefinicion = strlen(definicion);

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
  int numDef = tamArchivo / 81;

  // numero de linea donde se encuentra la llave
  int numLinea = hash_string(llave) % numDef;
  int numLineaInicial = numLinea;

  // Mientras quede archivo por leer
  while (numLinea < numDef){

   // NO se puede mover a la posición numLinea
    if (fseek(fileDicc, numLinea * 81, SEEK_SET) != 0){
      fprintf(stderr, "No se puede mover a la posición numLinea");
      exit(3);
    }
    // No se puede leer la línea
    if (fread(linea, 1, 81, fileDicc) != 81){
      fprintf(stderr, "No se puede leer la linea");
      exit(4);
    }
    // Si la llave ya existe
    if (strncmp(linea, llave, tamLlave) == 0){
      fprintf(stderr, "La llave %s ya se encuentra en el diccionario\n", llave);
      exit(5);
    }

    // Si la línea está vacía
    if (linea[0] == ' '){
      char correct[81];
      char *ptr = correct;

      // Copiar llave y definición a correct
      while(*llave != 0){
        *ptr = *llave;
        ptr++;
        llave++;
      }
      *ptr = ':';
      ptr++;
      while(*definicion != 0){
        *ptr = *definicion;
        ptr++;
        definicion++;
      }
      *ptr = 0;


      fseek(fileDicc, -81, SEEK_CUR);
      fwrite(correct, 1, strlen(correct), fileDicc);
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
    if (fseek(fileDicc, numLinea * 81, SEEK_SET) != 0){
      fprintf(stderr, "No se puede mover a la posición numLinea");
      exit(3);
    }
    // No se puede leer la línea
    if (fread(linea, 1, 81, fileDicc) != 81){
      fprintf(stderr, "No se puede leer la linea");
      exit(4);
    }
    // Si la llave ya existe
    if (strncmp(linea, llave, tamLlave) == 0){
      fprintf(stderr, "La llave ya existe");
      exit(5);
    }

    // Si la línea está vacía
    if (linea[0] == ' '){
      char correct[81];
      char *ptr = correct;

      // Copiar llave y definición a correct
      while(*llave != 0){
        *ptr = *llave;
        ptr++;
        llave++;
      }
      *ptr = ':';
      ptr++;
      while(*definicion != 0){
        *ptr = *definicion;
        ptr++;
        definicion++;
      }
      *ptr = 0;

      fseek(fileDicc, -81, SEEK_CUR);
      fwrite(correct, 1, strlen(correct), fileDicc);
      fclose(fileDicc);
      return 0;

    }

    // Si la línea está ocupada
    numLinea++;
  }
  fprintf(stderr, "%s: el diccionario esta lleno\n",nomArch);
  exit(6);
}
