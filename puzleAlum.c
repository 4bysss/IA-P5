/*******************************************/
/* 		      PUZLE.C                      */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "OrdenarLista.c"
#include "puzle.h"

tEstado *crearEstado(int puzle[N][N]) {
  tEstado *estado = (tEstado *)malloc(sizeof(tEstado));
  int i, j, ficha;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++) {
      ficha = puzle[i][j];
      estado->celdas[i][j] = ficha;
      if (ficha == 0) {
        estado->fila = i;
        estado->col = j;
      }
    }
  return estado;
}

tEstado *estadoInicial() { return crearEstado(puzle_inicial); }

tEstado *estadoObjetivo() { return crearEstado(puzle_final); }

int coste(unsigned op, tEstado *estado) { return 1; }

void dispEstado(tEstado *estado) {
  int i, j;

  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++)
      printf("%d", estado->celdas[i][j]);
    printf("\n");
  }
  printf("\n");
}

void dispOperador(unsigned op) {
  switch (op) {
  case ARRIBA:
    printf("Movimiento ARRIBA:\n");
    break;
  case ABAJO:
    printf("Movimiento ABAJO:\n");
    break;
  case IZQUIERDA:
    printf("Movimiento IZQUIERDA:\n");
    break;
  case DERECHA:
    printf("Movimiento DERECHA:\n");
    break;
  }
}

int iguales(tEstado *s, tEstado *t) {
  int val = 1;
  for (int i = 0; i < N && val; i++) {
    for (int j = 0; j < N && val; j++) {
      val = (s->celdas[i][j] == t->celdas[i][j]);
    }
  }
  return val;
}

int testObjetivo(tEstado *estado) {
  int val = 1;
  for (int i = 0; i < N && val; i++) {
    for (int j = 0; j < N && val; j++) {
      val = (estado->celdas[i][j] == puzle_final[i][j]);
    }
  }
  return val;
}

int esValido(unsigned op, tEstado *estado) {
  int valido = 1;
  switch (op) {
  case ARRIBA:
    if (estado->fila == 0) {
      valido = 0;
    }
    break;

  case ABAJO:
    if (estado->fila == N - 1) {
      valido = 0;
    }
    break;

  case IZQUIERDA:
    if (estado->col == 0) {
      valido = 0;
    }
    break;

  case DERECHA:
    if (estado->col == N - 1) {
      valido = 0;
    }
    break;
  }
  return valido;
}

tEstado *aplicaOperador(unsigned op, tEstado *estado) {
  tEstado *nuevo = (tEstado *)malloc(sizeof(tEstado));
  memcpy(nuevo, estado, sizeof(tEstado));
  if (esValido(op, nuevo)) {
    switch (op) {
    case ABAJO:
      nuevo->celdas[nuevo->fila][nuevo->col] =
          nuevo->celdas[nuevo->fila + 1][nuevo->col];
      ++nuevo->fila;
      nuevo->celdas[nuevo->fila][nuevo->col] = 0;
      break;
    case ARRIBA:
      nuevo->celdas[nuevo->fila][nuevo->col] =
          nuevo->celdas[nuevo->fila - 1][nuevo->col];
      --nuevo->fila;
      nuevo->celdas[nuevo->fila][nuevo->col] = 0;
      break;
    case IZQUIERDA:
      nuevo->celdas[nuevo->fila][nuevo->col] =
          nuevo->celdas[nuevo->fila][nuevo->col - 1];
      --nuevo->col;
      nuevo->celdas[nuevo->fila][nuevo->col] = 0;
      break;
    case DERECHA:
      nuevo->celdas[nuevo->fila][nuevo->col] =
          nuevo->celdas[nuevo->fila][nuevo->col + 1];
      ++nuevo->col;
      nuevo->celdas[nuevo->fila][nuevo->col] = 0;
      break;
    }
  }
  return nuevo;
}
