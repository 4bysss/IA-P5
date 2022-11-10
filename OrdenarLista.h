#include "busqueda.h"
#include "listaia.h"
#ifndef _busqueda
#define _busqueda_
int comparaV (tNodo *e, tNodo *nuevo);
int comparaA (tNodo *e, tNodo *nuevo);
LISTA insertarOrdenado(LISTA c, tNodo *n, int tipo);
LISTA ordenarLista(LISTA Ab, LISTA q, int tipo);
#endif