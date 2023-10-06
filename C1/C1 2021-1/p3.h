typedef struct nodo {
  int x;
  struct nodo *izq, *der;
} Nodo;
int elimUnicos(Nodo **pa);
