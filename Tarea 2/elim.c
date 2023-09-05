#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elim.h"

void eliminar(char *str, char *pat);
char *eliminados(char *str, char *pat);

// Elimina todas las ocurrencias de pat en str
void eliminar(char *str, char *pat) {
    int len = strlen(pat); // Guardamos el largo de pat
    char *p1 = str;
    char *p2 = p1;
    char *puntero_pat = pat;

    while (*p1) {
        p2 = p1;
        puntero_pat = pat;

        int match = 1;

        for (int i = 0; i < len; i++) { // Recorremos el pat (puntero_pat) y vemos si hay match
            if (*p2 != *puntero_pat || *p2 == '\0') {
                match = 0;
                break;
            }
            p2++;
            puntero_pat++;
        }

        // Si hay match vamos a saltarnos todo el pat
        if (match) {
            p1 += len;
        }
        // Si no hay match vamos a avanzar el puntero y reiniciar los punteros
        else {
            *str = *p1;
            p1++;
            str++;
        }
    }
    *str = 0;
}

char *eliminados(char *str, char *pat) {
    int len = strlen(pat); // Guardamos el largo de pat
    char *p1 = str;
    char *p2 = p1;
    char *puntero_pat = pat;
    int count = 0;

    while (*p1) {
        p2 = p1;
        puntero_pat = pat;
        int match = 1; // bool si hay match o no

        for (int i = 0; i < len; i++) { // Recorremos el pat (puntero_pat) y vemos si hay match
            if (*p2 != *puntero_pat || *p2 == '\0') {
                match = 0;
                break;
            }
            p2++;
            puntero_pat++;
        }

        // Si hay match vamos a saltarnos todo el pat
        if (match) {
            p1 += len;
        } 
        else {
            count++;
            p1++;
        }
    }

    char *str2 = malloc(count + 1); // Asigna memoria para la nueva cadena
    char *p3 = str2; // Puntero para la nueva cadena
    p1 = str;
    p2 = str;
    puntero_pat = pat;

    while (*p1) {
        p2 = p1;
        puntero_pat = pat;
        int match = 1;

        for (int i = 0; i < len; i++) {
            if (*p2 != *puntero_pat || *p2 == '\0') {
                match = 0;
                break;
            }
            p2++;
            puntero_pat++;
        }

        if (match) {
            p1 += len;
        } 
        else {
            *p3 = *p1;
            p1++;
            p3++;
        }
    }
    *p3 = 0;
    return str2;
}
