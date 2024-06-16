#include "src/tp.h"
#include "src/tp_estructura_privada.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void seleccionar_dificultad(TP *tp) {
	int dificultad;
	printf("Seleccione la dificultad:\n");
	printf("1. Fácil\n");
	printf("2. Normal\n");
	printf("3. Difícil\n");
	printf("4. Imposible\n");
	printf("Ingrese la dificultad: ");

	if (scanf("%d\n", &dificultad) < 1 || scanf("%d", &dificultad) > 4) {
		printf("Esa no es una de las opciones disponibles para la dificultad, pruebe otra vez...\n");
		seleccionar_dificultad(tp);
	}

	establecer_dificultad(tp, dificultad);
}

void mostrar_pokemones_disponibles(TP *tp) {
	printf("A continuación, se listarán los nombres de los pokemones dispuestos a ganar la gran carrera de obstáculos...\n");
	char *nombres = tp_nombres_disponibles(tp);
	printf("%s\n", nombres);
	free(nombres);
}

char *tp_obtener_nombre_pokemon(TP *tp, unsigned int index) {
	if (tp == NULL || index >= tp_cantidad_pokemon(tp)) {
		return NULL;
	}

	void *array[tp_cantidad_pokemon(tp)];
	size_t elementos_recorridos = abb_recorrer(tp->pokemones, INORDEN, array, (size_t)tp_cantidad_pokemon(tp));

	if (elementos_recorridos <= index) {
		return NULL;
	}

	return (char *)array[index];
}

void seleccionar_pokemon(TP *tp) {
	char nombre[256];
	printf("Ingrese el nombre del pokemon que desea seleccionar: ");
	if (scanf("%255s", nombre) != 1) {
		fprintf(stderr, "Error al leer la opción\n");
	}
	tp_seleccionar_pokemon(tp, JUGADOR_1, nombre);

	unsigned int poke_compu;
	do {
		poke_compu = aleatoria(tp_cantidad_pokemon(tp), 0);
	} while (strcmp(tp_obtener_nombre_pokemon(tp, poke_compu), nombre) == 0);

	tp_seleccionar_pokemon(tp, JUGADOR_2, tp_obtener_nombre_pokemon(tp, poke_compu));
}


void mostrar_menu_principal(int *opcion) {
    printf("Menú principal:\n");
    printf("1. Ver pokemones disponibles\n");
    printf("2. Correr carrera\n");
    printf("3. Salir\n");
    printf("Ingrese una opción: ");
    
    if (scanf("%d", opcion) != 1) {
        fprintf(stderr, "Error al leer la opción\n");
    }
}

void correr_carrera() {
	printf("Carrera en curso...\n");
	// Simulación de la carrera
	for (int i = 0; i < 10; i++) {
		printf(" avanza \n");
	}
	printf("Carrera finalizada!\n");
}



int main(int argc, char const *argv[])
{
	//Se recomienda pasar el archivo de texto con los pokemon como argumento al ejecutar el programa

	//crear el juego
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	int opcion = 0;
	do {
		mostrar_menu_principal(&opcion);

		switch (opcion){
			case 1:
				mostrar_pokemones_disponibles(tp);
				seleccionar_dificultad(tp);
				break;
			case 2:
				printf("¡Vamos a correr la carrera!...\n");
				correr_carrera();
                		break;
			case 3:
				printf("Saliendo del juego..\n");
				printf("El puntaje final es: %d\n", calculo_puntaje(tp));
				break;
			default:
				printf("Revisa que la opción ingresada debe ser una de las opciones especificadas al principio!\n");
		}
	} while (opcion < 3);

	tp_destruir(tp);

	return 0;
}