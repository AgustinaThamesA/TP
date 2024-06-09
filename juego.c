#include "src/tp.h"
#include "src/tp_estructura_privada.h"

void mostrar_menu_principal() {
    printf("Menú principal:\n");
    printf("1. Ver pokemones disponibles\n");
    printf("2. Correr carrera\n");
    printf("3. Salir\n");
    printf("Ingrese una opción: ");
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
	TP *tp = tp_crear(argv[1]);

	int opcion = 1;
	do {
		mostrar_menu_principal();
		//scanf("%d", &opcion);

		switch (opcion){
			case 1:
				printf("A continuación, se listarán los nombres de los pokemones dispuestos a ganar la gran carrera de obstáculos...");
				tp_nombres_disponibles(tp);
				break;
			case 2:
				printf("¡Vamos a correr la carrera!...");
				correr_carrera();
                		break;
			case 3:
				printf("Saliendo del juego..");
				tp_destruir(tp);
				break;
			default:
				printf("Revisa que la opción ingresada debe ser una de las opciones especificadas al principio!");
		}
	} while (opcion > 3);

	return 0;
}