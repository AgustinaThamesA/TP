#ifndef __TP_ESTRUCTURA_PRIVADA_H__
#define __TP_ESTRUCTURA_PRIVADA_H__

#include "tp.h"
#include "tp_auxiliares.h"
#include "abb.h"
#include "abb_estructura_privada.h"
#include "lista.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

#define _POSIX_C_SOURCE 200809L

#define MAX_LARGO_PISTA 50
#define PISTA_VACIA "_"
#define PISTA_FUERZA "F"
#define PISTA_DESTREZA "D"
#define PISTA_INTELIGENCIA "I"

// ------------- STRUCTS -------------

typedef struct pista_jugador {
	lista_t *pista;
	unsigned cant_obstaculos;
	unsigned largo_pista;
	unsigned max_obstaculos;
	int dificultad;
	double velocidad;
} pista_jugador_t;

typedef struct jugadores {
	struct pokemon_info *pokemon_seleccionado[2];
	pista_jugador_t *pista_jugador[2];
} jugadores_t;

struct tp {
	abb_t *pokemones;
	jugadores_t jugadores;
};

// ------------- FUNCIONES AUXILIARES TP.C -------------

// Comparador que se utiliza para crear el abb que contiene a los
// pokemones
int comparar_pokemon(void *poke1, void *poke2);

// Función con implementación similar a strdup()
char *strdup2(const char *s);

// Guarda los pokemones ordenados alfabéticamente en un ABB auxiliar
bool guardar_alfabeticamente(void *elemento, void *aux);

// Función que lee un archivo con extensión .txt
// e inserta la información obtenida en tp->pokemones
bool leer_archivo(TP *tp, FILE *archivo);

// Concatena los nombres de los pokemones en un string separado
// por comas, para mostrar los nombres disponibles
bool concatenar_nombres(void *elemento, void *aux);

// Función que inicializa la pista de un jugador con espacios vacíos
void pista_vacia(TP *tp, enum TP_JUGADOR jugador);

// Función que devuelve un número aleatorio entre mínimo y máximo
unsigned aleatoria(int maximo, int minimo);

// Función que devuelve la cantidad de obstáculos del jugador
unsigned cant_obstaculos_actual_jugador(TP *tp, enum TP_JUGADOR jugador);

// Función que imprime por consola las pistas
void imprimir_pista(TP *tp);

// Función que concatena los obstáculos en un string
bool concatenar_obstaculos(void *elemento, void *aux);

// Función que libera la memoria de un struct pokemon_info y
// el campo que corresponde al nombre del pokemon
bool destruir_strdup2(void *elemento, void *aux);

#endif // __TP_ESTRUCTURA_PRIVADA_H__
