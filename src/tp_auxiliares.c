#include "tp_auxiliares.h"

int calculo_puntaje(TP *tp){
	if (tp == NULL) {
		return 0;
	}
	int puntaje = 0;

	int tiempo_jugador1 = (int)tp_calcular_tiempo_pista(tp, JUGADOR_1);
	int tiempo_jugador2 = (int)tp_calcular_tiempo_pista(tp, JUGADOR_2);
	
	puntaje = 100 - (100 * (abs(tiempo_jugador1-tiempo_jugador2)/(tiempo_jugador1-tiempo_jugador2)));

	return puntaje;
}

void establecer_dificultad(TP *tp, int dificultad){
	if (tp == NULL) return;

	pista_jugador_t *pista_jugador_1 = tp->jugadores.pista_jugador[JUGADOR_1];
	pista_jugador_t *pista_jugador_2 = tp->jugadores.pista_jugador[JUGADOR_2];

	if (pista_jugador_1 != NULL) {
		pista_jugador_1->dificultad = dificultad;
	}

	if (pista_jugador_2 != NULL) {
		pista_jugador_2->dificultad = dificultad;
		pista_jugador_2->max_obstaculos = (unsigned int)dificultad;
		pista_jugador_2->largo_pista = 5 * (unsigned int)dificultad;
	}

    tp->jugadores.pista_jugador[JUGADOR_1] = pista_jugador_1;
    tp->jugadores.pista_jugador[JUGADOR_2] = pista_jugador_2;
    
    pista_vacia(tp, JUGADOR_2);

    printf("\nLargo pista de su oponente: %d\n", tp->jugadores.pista_jugador[JUGADOR_2]->largo_pista);
	printf("La cantidad de obstáculos a la cual se enfrentará su oponente es: %d\n", tp->jugadores.pista_jugador[JUGADOR_2]->max_obstaculos);
    printf("La dificultad seleccionada es: %d\n", tp->jugadores.pista_jugador[JUGADOR_1]->dificultad);
}

void seleccionar_dificultad(TP *tp) {
	int dificultad;
	printf("Seleccione la dificultad:\n");
	printf("	1. Fácil\n");
	printf("	2. Normal\n");
	printf("	3. Difícil\n");
	printf("	4. Imposible\n");
	printf("Ingrese la dificultad: ");

	if (scanf("%d", &dificultad) != 1 && scanf("%d", &dificultad) != 2 && scanf("%d", &dificultad) != 3 && scanf("%d", &dificultad) != 4) {
		printf("Esa no es una de las opciones disponibles para la dificultad, pruebe otra vez...\n");
	}

	establecer_dificultad(tp, dificultad);
}

void mostrar_pokemones_disponibles(TP *tp) {
	printf("\nA continuación, se listarán los nombres de los pokemones dispuestos a ganar la gran carrera de obstáculos...\n");
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

    struct pokemon_info *pokemon = (struct pokemon_info *)array[index];
    return pokemon->nombre;
}

void seleccionar_pokemon(TP *tp) {
	char nombre[256];
	printf("Ingrese el nombre del pokemon que desea seleccionar: ");
	if (scanf("%255s", nombre) != 1) {
		fprintf(stderr, "Error al leer la opción\n");
	} else if (tp_buscar_pokemon(tp, nombre) == NULL){
                seleccionar_pokemon(tp);
                return;
        }
	tp_seleccionar_pokemon(tp, JUGADOR_1, nombre);

	unsigned int poke_compu;
	do {
		poke_compu = aleatoria(tp_cantidad_pokemon(tp), 0);
	} while (strcmp(tp_obtener_nombre_pokemon(tp, poke_compu), nombre) == 0);

	tp_seleccionar_pokemon(tp, JUGADOR_2, tp_obtener_nombre_pokemon(tp, poke_compu));
        const struct pokemon_info *poke_usuario = tp_pokemon_seleccionado(tp, JUGADOR_1);
        const struct pokemon_info *poke_computadora = tp_pokemon_seleccionado(tp, JUGADOR_2);
        printf("Usted estará compitiendo por el pokemon %s\n", poke_usuario->nombre);
        printf("El pokemon al cual te estarás enfrentando será... %s\n", poke_computadora->nombre);
}

void mostrar_menu_principal(int *opcion) {
    printf("Menú principal:\n");
    printf("	1. Ver pokemones disponibles\n");
    printf("	2. Correr carrera\n");
    printf("	3. Salir\n");
    printf("Ingrese una opción: ");
    
    if (scanf("%d", opcion) != 1 && scanf("%d", opcion) != 2 && scanf("%d", opcion) != 3) {
        fprintf(stderr, "Error al leer la opción\n");
    }
}

void agregar_obstaculos_a_pista_compu(TP *tp){
	for (int i = 0; i < tp->jugadores.pista_jugador[JUGADOR_2]->max_obstaculos; i++){
		unsigned obstaculo = aleatoria(3,0);
		
		enum TP_OBSTACULO obstaculo_aleatorio = 0;
		switch (obstaculo){
			case 0:
				obstaculo_aleatorio = OBSTACULO_FUERZA;
				break;
			case 1:
				obstaculo_aleatorio = OBSTACULO_DESTREZA;
				break;
			case 2:
				obstaculo_aleatorio = OBSTACULO_INTELIGENCIA;
				break;
			default:
				obstaculo_aleatorio = OBSTACULO_FUERZA;
		}
		unsigned obstaculo_posicion = aleatoria((int)tp->jugadores.pista_jugador[JUGADOR_2]->largo_pista, 0);
		tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo_aleatorio, obstaculo_posicion);
	}
}

void usuario_elije_pista(TP *tp){
	printf("Elija la longitud de su pista: ");
	int largo_pista_jugador = 0;
	while (scanf("%d", &largo_pista_jugador) != 1 || largo_pista_jugador < 5){
		printf("\n");
		printf("Elija un valor mayor o igual a 5.\n");
	}

	tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista = (unsigned)largo_pista_jugador;
	printf("\nLargo de su pista: %d\n", tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista);
	
	tp->jugadores.pista_jugador[JUGADOR_1]->max_obstaculos = tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista % 5 + 1;
	printf("\nCantidad de obstáculos: %d\n", tp->jugadores.pista_jugador[JUGADOR_1]->max_obstaculos);
        pista_vacia(tp, JUGADOR_1);

	for (int i = 0; i < tp->jugadores.pista_jugador[JUGADOR_1]->max_obstaculos; i++){
		printf("Elija la posición de uno de sus obstáculos: ");
		int posicion = 0;
		while (scanf("%d", &posicion) != 1 || posicion < 0 || posicion >= tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista){
			printf("Elija un valor entre 0 y %d.\n", tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista-1);
		}
		unsigned obstaculo = aleatoria(3,0);
		enum TP_OBSTACULO obstaculo_aleatorio = 0;
		switch (obstaculo){
			case 0:
				obstaculo_aleatorio = OBSTACULO_FUERZA;
				break;
			case 1:
				obstaculo_aleatorio = OBSTACULO_DESTREZA;
				break;
			case 2:
				obstaculo_aleatorio = OBSTACULO_INTELIGENCIA;
				break;
			default:
				obstaculo_aleatorio = OBSTACULO_FUERZA;
		}
		tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo_aleatorio, (unsigned)posicion);
                printf("Posición obstáculo: %d\n", posicion);
	}
	
}

void preparar_carrera(TP *tp) {
	printf("\n");
	usuario_elije_pista(tp);
	agregar_obstaculos_a_pista_compu(tp);
	printf("\n");
}

double calcular_velocidad(TP *tp, enum TP_JUGADOR jugador, size_t posicion) {
	const struct pokemon_info *pokemon_jugador = tp_pokemon_seleccionado(tp, jugador);
	pista_jugador_t *pista_jugador = tp->jugadores.pista_jugador[jugador];
	double velocidad = pista_jugador->velocidad;
	
	if (strcmp(lista_elemento_en_posicion(pista_jugador->pista, posicion), PISTA_VACIA) == 0){
		return velocidad;
	} else if (strcmp(lista_elemento_en_posicion(pista_jugador->pista, posicion), PISTA_FUERZA) == 0){
		velocidad -= (pokemon_jugador->fuerza / 10);
	} else if (strcmp(lista_elemento_en_posicion(pista_jugador->pista, posicion), PISTA_DESTREZA) == 0){
		velocidad -= (pokemon_jugador->destreza / 10);
	} else if (strcmp(lista_elemento_en_posicion(pista_jugador->pista, posicion), PISTA_INTELIGENCIA) == 0){
		velocidad -= (pokemon_jugador->inteligencia / 10);
	}

	switch (pista_jugador->dificultad) {
		case 1:
			velocidad += 1.1;
			break;
		case 2:
			velocidad += 0.9;
			break;
		case 3:
			velocidad += 0.7;
			break;
		case 4:
			velocidad += 0.5;
			break;
	}

	return velocidad;

}

void avanzar_pokemon(TP *tp, enum TP_JUGADOR jugador, double distancia) {
    if (tp == NULL || (jugador != JUGADOR_1 && jugador != JUGADOR_2)) {
        return;
    }

    pista_jugador_t *pista_jugador = tp->jugadores.pista_jugador[jugador];
    double velocidad_actual = calcular_velocidad(tp, jugador, (size_t)distancia);
    distancia += velocidad_actual;
    
    if (distancia < pista_jugador->largo_pista) {
        
	lista_quitar_de_posicion(pista_jugador->pista, (size_t)distancia);
        lista_insertar_en_posicion(pista_jugador->pista, "P", (size_t)distancia);
        
    }
    imprimir_pista(tp);
}

void correr_carrera(TP *tp) {
    double distancia_recorrida_jugador1 = 0;
    double distancia_recorrida_jugador2 = 0;
    double tiempo_transcurrido = 0;
    int turno = 0;

    pista_jugador_t *pista_jugador_1 = tp->jugadores.pista_jugador[JUGADOR_1];
    pista_jugador_t *pista_jugador_2 = tp->jugadores.pista_jugador[JUGADOR_2];

    double velocidad_jugador1 = (pista_jugador_1->largo_pista)/tp_calcular_tiempo_pista(tp, JUGADOR_1);
    double velocidad_jugador2 = (pista_jugador_2->largo_pista)/tp_calcular_tiempo_pista(tp, JUGADOR_2);
    pista_jugador_1->velocidad = velocidad_jugador1;
    pista_jugador_2->velocidad = velocidad_jugador2;

    while (distancia_recorrida_jugador1 <= pista_jugador_1->largo_pista ||
           distancia_recorrida_jugador2 <= pista_jugador_2->largo_pista) {
        // Update velocities only when necessary
        if (turno % 2 == 0) {
            velocidad_jugador1 = calcular_velocidad(tp, JUGADOR_1, (size_t)distancia_recorrida_jugador1);
        } else {
            velocidad_jugador2 = calcular_velocidad(tp, JUGADOR_2, (size_t)distancia_recorrida_jugador2);
        }

	pista_jugador_1->velocidad = velocidad_jugador1;
    	pista_jugador_2->velocidad = velocidad_jugador2;

        // Increment time and distances
        tiempo_transcurrido++;
        distancia_recorrida_jugador1 += velocidad_jugador1 * tiempo_transcurrido;
        distancia_recorrida_jugador2 += velocidad_jugador2 * tiempo_transcurrido;

        // Print progress (consider using a buffer or separate thread for this)
        printf("Tiempo transcurrido: %f segundos\n", tiempo_transcurrido);
        printf("Distancia recorrida por el jugador 1: %f metros\n", distancia_recorrida_jugador1);
        printf("Distancia recorrida por el jugador 2: %f metros\n", distancia_recorrida_jugador2);
        printf("Velocidad actual del jugador 1: %f km/h\n", velocidad_jugador1);
        printf("Velocidad actual del jugador 2: %f km/h\n", velocidad_jugador2);
        printf("\n");

        // Avanzar pokemones
        if (turno % 2 == 0) {
            avanzar_pokemon(tp, JUGADOR_1, distancia_recorrida_jugador1);
        } else {
            avanzar_pokemon(tp, JUGADOR_2, distancia_recorrida_jugador2);
        }
        turno++;

        sleep(1); // pausa de 1 segundo para ver el progreso
    }

    // Mostrar el resultado de la carrera
    printf("¡La carrera ha terminado!\n");
    if (distancia_recorrida_jugador1 >= pista_jugador_1->largo_pista) {
        printf("El jugador 1 ha ganado la carrera!\n");
    } else if (distancia_recorrida_jugador2 >= pista_jugador_2->largo_pista) {
        printf("El jugador 2 ha ganado la carrera!\n");
    }
}