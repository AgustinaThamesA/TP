#ifndef __TP_ESTRUCTURA_PRIVADA_H__
#define __TP_ESTRUCTURA_PRIVADA_H__

#include "tp.h"
#include "abb.h"
#include "abb_estructura_privada.h"
#include "lista.h"

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

// ------------- STRUCTS -------------

typedef struct pista_jugador{
    lista_t *pista;
    unsigned cant_obstaculos;
    unsigned largo_pista; // REVISAR
    unsigned max_obstaculos; // REVISAR
    lista_t *puntajes; // REVISAR
    int dificultad; // REVISAR
}pista_jugador_t;

typedef struct jugadores { // CAMBIAR A TDA MENU ???
    struct pokemon_info *pokemon_seleccionado[2];
    pista_jugador_t* pista_jugador[2];
}jugadores_t;

struct tp {
    abb_t* pokemones;
    jugadores_t jugadores;
}; 

// ------------- FUNCIONES AUXILIARES TP.C -------------

int comparar_pokemon(void *poke1, void *poke2);

char *strdup2(const char *s);

void leer_archivo(TP *tp, const char *nombre_archivo);

bool concatenar_nombres(void *elemento, void *aux);

void pista_vacia(TP *tp, enum TP_JUGADOR jugador);

unsigned aleatoria (int maximo, int minimo);

unsigned cant_obstaculos_actual_jugador(TP *tp, enum TP_JUGADOR jugador);

void imprimir_pista(TP *tp);

bool concatenar_obstaculos(void *elemento, void *aux);

bool destruir_strdup2(void *elemento, void *aux);

// ------------- FUNCIONES AUXILIARES JUEGO.C -------------
// DEBERÍA HACER UN JUEGO.H PARA PONER LAS FIRMAS DE LAS FUNCIONES 
// AUXILIARES AHÍ

int calculo_puntaje(TP *tp);

void establecer_dificultad(TP *tp, int dificultad);





#endif // __TP_ESTRUCTURA_PRIVADA_H__