#ifndef __TP_AUXILIARES_H__
#define __TP_AUXILIARES_H__

#include "tp_estructura_privada.h"


int calculo_puntaje(TP *tp);

void establecer_dificultad(TP *tp, int dificultad);

void seleccionar_dificultad(TP *tp);

void mostrar_pokemones_disponibles(TP *tp);

char *tp_obtener_nombre_pokemon(TP *tp, unsigned int index);

void seleccionar_pokemon(TP *tp);

void mostrar_menu_principal(int *opcion);

void agregar_obstaculos_a_pista_compu(TP *tp);

void usuario_elije_pista(TP *tp);

void preparar_carrera(TP *tp);

void correr_carrera(TP *tp);

#endif // __TP_AUXILIARES_H__