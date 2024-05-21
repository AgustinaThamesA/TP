#include "tp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct tp {
	int cantidad_pokemon;
	struct pokemon_info* pokemon;
	struct pokemon_info* pokemon_seleccionado[2];
	unsigned* obstaculos_pista[2];
	int longitud_pista[2];
};

TP *tp_crear(const char *nombre_archivo)
{
	FILE* archivo = fopen(nombre_archivo, "r");
	if (archivo == NULL)
		return NULL;

	TP* tp = malloc(sizeof(TP));
	if (tp == NULL){
		fclose(archivo);
		return NULL;
	}

	fscanf(archivo, "%d\n", &(tp->cantidad_pokemon));
	tp->pokemon = malloc(tp->cantidad_pokemon * sizeof(struct pokemon_info));

	if (tp->pokemon == NULL){
		fclose(archivo);
		free(tp);
		return NULL;
	}

	for (int i = 0; i < tp->cantidad_pokemon; i++){
		char nombre[50];
		int fuerza, destreza, inteligencia;
		fscanf(archivo, "%s,%d,%d,%d\n", nombre, &fuerza, &destreza, &inteligencia);
		tp->pokemon[i].nombre = malloc(strlen(nombre) + 1);
		strcpy(tp->pokemon[i].nombre, nombre);
		tp->pokemon[i].fuerza = fuerza;
		tp->pokemon[i].destreza = destreza;
        	tp->pokemon[i].inteligencia = inteligencia;
	}

	fclose(archivo);
	return tp;
}

int tp_cantidad_pokemon(TP *tp)
{
	if (tp == NULL)
		return 0;
	return tp->cantidad_pokemon;
}

const struct pokemon_info *tp_buscar_pokemon(TP *tp, const char *nombre)
{
	if (tp == NULL || nombre == NULL)
		return NULL;
	
	for (int i = 0; i < tp->cantidad_pokemon; i++){
		if (strcmp(tp->pokemon[i].nombre, nombre) == 0)
			return &tp->pokemon[i];
	}

	return NULL;
}

char *tp_nombres_disponibles(TP *tp)
{
	return NULL;
}

bool tp_seleccionar_pokemon(TP *tp, enum TP_JUGADOR jugador, const char *nombre)
{
	return false;
}

const struct pokemon_info *tp_pokemon_seleccionado(TP *tp,
						   enum TP_JUGADOR jugador)
{
	if (tp == NULL)
		return NULL;
	return tp->pokemon_seleccionado[jugador];
}

unsigned tp_agregar_obstaculo(TP *tp, enum TP_JUGADOR jugador,
			      enum TP_OBSTACULO obstaculo, unsigned posicion)
{
	return 0;
}

unsigned tp_quitar_obstaculo(TP *tp, enum TP_JUGADOR jugador, unsigned posicion)
{
	return 0;
}

char *tp_obstaculos_pista(TP *tp, enum TP_JUGADOR jugador)
{
	return NULL;
}

void tp_limpiar_pista(TP *tp, enum TP_JUGADOR jugador)
{
	if (tp == NULL || tp->obstaculos_pista[jugador] == NULL)
		return;
	
	free(tp->obstaculos_pista[jugador]);
	tp->longitud_pista[jugador] = 0;
	return;
}

unsigned tp_calcular_tiempo_pista(TP *tp, enum TP_JUGADOR jugador)
{
	return 0;
}

char *tp_tiempo_por_obstaculo(TP *tp, enum TP_JUGADOR jugador)
{
	return NULL;
}

void tp_destruir(TP *tp)
{
	if (tp == NULL)
		return;
	for (int i = 0; i < tp->cantidad_pokemon; i++) {
        	free(tp->pokemon[i].nombre);
	}
	free(tp->pokemon);

	for (int i = 0; i < 2; i++) {
		if (tp->pokemon_seleccionado[i]) {
			free(tp->pokemon_seleccionado[i]->nombre);
			free(tp->pokemon_seleccionado[i]);
			}
	}

	for (int i = 0; i < 2; i++) {
		free(tp->obstaculos_pista[i]);
	}

	free(tp);
}
