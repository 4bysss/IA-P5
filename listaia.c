/*******************************************/
/*             LISTAIA .C                  */
/*                                         */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#include "listaia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int esVacia(LISTA c) { return (c == VACIA); } // esVacia

void InsertarPrimero(LISTA *c, void *n, int size) {
  LISTA p = (LISTA)malloc(sizeof(LISTA) + size);
  memcpy((void *)p->nodo, (void *)n, size);
  p->next = (*c);
  *c = p;
} // InsertarPrimero

void ExtraerPrimero(LISTA c, void *n, int size) {
  memcpy((void *)n, (void *)c->nodo, size);
}; // Extraer primer elemento

void EliminarPrimero(LISTA *c) {
  LISTA p;
  p = *c;
  *c = p->next;
  free(p);
} // Eliminar primer elemento de la lista

void InsertarUltimo(LISTA *c, void *n, int size) {
 // printf("Malloc en proceso\nEspacio usado: %ld\n",size+sizeof(LISTA));
  LISTA p = malloc(sizeof(LISTA) + size);
  LISTA aux = VACIA;
  // creando el nodo
  memcpy((void *)(p->nodo), (void *)n, size);
  p->next = NULL;
  if (esVacia(*c)) {
    *c = p;
  } else {
    aux = *c;
    while (aux->next != NULL) {
      aux = aux->next;
    }
    aux->next = p;
  }
} // InsertarUltimo

LISTA Concatenar(LISTA c, LISTA p) {
  LISTA aux;
  if (esVacia(c))
    c = p;
  else {
    aux = c;
    while (aux->next != NULL) {
      aux = aux->next;
    }
    aux->next = p;
  }
  return c;
} // Concatenar

int EstaEn(LISTA c, tNodo *buscado) {
  LISTA aux;
  aux = c;
  tNodo *n = (tNodo *)calloc(1, sizeof(tNodo));;
  
  if (!esVacia(aux)) {
    while (!esVacia(aux)){
      ExtraerPrimero(aux,n,sizeof(tNodo));
      if(iguales(n->estado,buscado->estado)){
       // printf("\n\nEncontrado!\n\n");
        return 1;
      }
      aux=aux->next;
    }
  }
  return 0;
}
