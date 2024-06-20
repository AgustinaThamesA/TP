#include "src/tp_auxiliares.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	int opcion = 0;
	do {
		mostrar_menu_principal(&opcion);

		switch (opcion) {
		case 1:
			seleccionar_dificultad(tp);
			mostrar_pokemones_disponibles(tp);
			seleccionar_pokemon(tp);
			break;
		case 2:
			printf("¡Vamos a correr la carrera!...\n");
			preparar_carrera(tp);

			printf("\n\nLas pistas ya están listas, échales un vistazo..\n\n");
			imprimir_pista(tp);
			correr_carrera(tp);
			break;
		case 3:
			printf("Saliendo del juego..\n");
			break;
		default:
			printf("Revisa que la opción ingresada debe ser una de las opciones especificadas al principio!\n");
		}
	} while (opcion < 3);

	tp_destruir(tp);

	return 0;
}