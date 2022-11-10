/*******************************************/
/* 		    BUSQUEDA.C                     */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "OrdenarLista.h"
#include "busqueda.h"
#include "listaia.h"
 #include "puzle.h"


void solucionFin(int res) {
  printf("\nFin de la busqueda\n");
  if (res)
    printf("Se ha llegado al objetivo\n");
  else
    printf("No se ha llegado al objetivo\n");
}
void dispNodo(tNodo *nodo) {
  dispEstado(nodo->estado);
  printf("\n");
}
void dispCamino(tNodo *nodo) {
  if (nodo->padre == NULL) {
    printf("\n Desde el inicio\n");
    dispEstado(nodo->estado);
  } else {
    dispCamino(nodo->padre);
    dispOperador(nodo->operador);
    dispEstado(nodo->estado);
  }
}

void dispSolucion(tNodo *nodo) {
  printf("Profundidad=%d\n", nodo->profundidad);
  printf("Coste=%d\n", nodo->costeCamino);
  printf("ValHeuristico=%d\n",nodo->valHeuristica);
  dispCamino(nodo);
}

/* Crea el nodo ra�z. */
tNodo *nodoInicial() {
  tNodo *inicial = (tNodo *)malloc(sizeof(tNodo));
  inicial->estado = estadoInicial();
  dispEstado(inicial->estado);
  inicial->padre = NULL;
  inicial->costeCamino = 0;
  inicial->profundidad = 0;
  return inicial;
}

LISTA expandir(tNodo *nodo) {
  unsigned op;
  LISTA sucesores = VACIA;
  tNodo *nuevo = calloc(1, sizeof(tNodo));
  tEstado *s;
  for (op = 1; op <= NUM_OPERADORES; op++) {
    if (esValido(op, nodo->estado)) {
      // s=(tEstado *)calloc(1,sizeof(tEstado));
      s = aplicaOperador(op, nodo->estado);
      nuevo->estado = s;
      nuevo->padre = nodo;
      nuevo->operador = op;
      nuevo->costeCamino = nodo->costeCamino + coste(op, nodo->estado);
      nuevo->valHeuristica = 0;
      for(int i=0;i<N;i++){
        for (int j = 0; j < N; j++)
        {
          if(s->celdas[i][j]!=puzle_final[i][j]&&s->celdas[i][j]!=0){nuevo->valHeuristica++;}
        }
        
      }
      nuevo->profundidad = nodo->profundidad + 1;
      //dispOperador(op);
      InsertarUltimo(&sucesores, (tNodo *)nuevo, (sizeof(tNodo)));
    }
  }
  return sucesores;
}

int busqueda() {
  //printf("Print busqueda\n");
  int objetivo = 0, visitados = 0;
  tNodo *Actual = (tNodo *)calloc(1, sizeof(tNodo));
  tNodo *Inicial = nodoInicial();

  LISTA Abiertos = VACIA;
  LISTA Sucesores = VACIA;
  LISTA Cerrados = VACIA;
  InsertarPrimero(&Abiertos, (tNodo *)Inicial, sizeof(tNodo));
  while (!esVacia(Abiertos) && !objetivo) {
    Actual = (tNodo *)calloc(1, sizeof(tNodo));
    ExtraerPrimero(Abiertos, Actual, sizeof(tNodo));
    EliminarPrimero(&Abiertos);
    if (!EstaEn(Cerrados, Actual)) {
      objetivo = testObjetivo(Actual->estado);
      if (!objetivo) {
        Sucesores = expandir(Actual);
        Abiertos = ordenarLista(Abiertos, Sucesores,0);
      }
      //printf("Inserta en cerrados\n");
      InsertarUltimo(&Cerrados, (tNodo *)Actual, sizeof(tNodo));
      //printf("Insertado en cerrados\n");
    }
    visitados++;

  } // while

  printf("\nVisitados= %d\n", visitados);
  if (objetivo)
    dispSolucion(Actual);
  free(Sucesores);
  free(Cerrados);
  free(Inicial);
  free(Actual);
  return objetivo;
}
