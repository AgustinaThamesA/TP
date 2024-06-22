#ifndef __TP_AUXILIARES_H__
#define __TP_AUXILIARES_H__

#include "tp_estructura_privada.h"
#include <stddef.h>

// Calcula el puntaje final aplicando la fórmula indicada en el
// enunciado
int calculo_puntaje(TP *tp);

// Establece la dificulad del juego de ambos jugadores, y completa
// los campos correspondientes para cada jugador
void establecer_dificultad(TP *tp, int dificultad);

// Le pide al usuario que seleccione la dificultad del juego
void seleccionar_dificultad(TP *tp);

// Función que le muestra al usuario los nombres de los
// pokemones disponibles
void mostrar_pokemones_disponibles(TP *tp);

// Devuelve el nombre del pokemon en la posición aleatoria para
// el pokemon de la computadora (Jugador 2)
char *tp_obtener_nombre_pokemon(TP *tp, unsigned int index);

// Función que le permite al usuario seleccionar un pokemon
// para la carrera
void seleccionar_pokemon(TP *tp);

// Imprime por pantalla el menú principal y le pide al usuario
// que seleccione una opción según corresponda
void mostrar_menu_principal(int *opcion);

// Función que le agrega obstáculos aleatorios a la pista
// del Jugador 2 (computadora)
void agregar_obstaculos_a_pista_compu(TP *tp);

// Se le pide al usuario que diseñe su propia pista (largo y
// posición de obstáculos
void usuario_elije_pista(TP *tp);

// Función que llama a las dos funciones anteriores para
// preparar las pistas para la carrera
void preparar_carrera(TP *tp);

// Función que calcula la velocidad de un jugador en la
// posición que se encuentre en ese momento
double calcular_velocidad(TP *tp, enum TP_JUGADOR jugador, size_t posicion);

// Función que simula el avance en la pista del jugador
void avanzar_pokemon(TP *tp, enum TP_JUGADOR jugador, double distancia);

// Función que llama a todas las funciones necesarias para
// que ambos jugadores corran la carrera de obstáculos
void correr_carrera(TP *tp);

#endif // __TP_AUXILIARES_H__
