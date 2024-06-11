#ifndef __TP_ESTRUCTURA_PRIVADA_H__
#define __TP_ESTRUCTURA_PRIVADA_H__

#include "tp.h"
#include "abb.h"
#include "abb_estructura_privada.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <time.h>

#define _POSIX_C_SOURCE 200809L

#define DIFICULTAD_FACIL 1
#define DIFICULTAD_NORMAL 2
#define DIFICULTAD_DIFICIL 3
#define DIFICULATD_IMPOSIBLE 4

#define MAX_LARGO_PISTA 50
#define PISTA_VACIA "_"
#define PISTA_FUERZA "F"
#define PISTA_DESTREZA "D"
#define PISTA_INTELIGENCIA "I"

typedef struct jugadores jugadores_t;
typedef struct pista_jugador pista_jugador_t;


// ------------- FUNCIONES AUXILIARES TP.C -------------

void leer_archivo(TP *tp, const char *nombre_archivo);
bool guardar_nombres_como_string(void *dato, void *aux);
void creacion_pista(pista_jugador_t *pista_jugador);
unsigned aleatoria (int maximo, int minimo);
void imprimir_pista(TP *tp);

unsigned cant_obstaculos_actual_jugador(TP *tp, enum TP_JUGADOR jugador);

#endif // __TP_ESTRUCTURA_PRIVADA_H__