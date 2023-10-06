typedef struct nodo {
  int x;
  struct nodo *izq, *der;
} Nodo;

int buscarPar(Nodo *a, int z, int p);
int buscar(Nodo *a, int z);
