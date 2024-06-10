#include "tp.h"
#include "tp_estructura_privada.h"

struct pista_jugador{
    char* pista[MAX_LARGO_PISTA];
    unsigned largo_actual;
};

struct jugadores {
    struct pokemon_info *pokemon_seleccionado[2];
    pista_jugador_t* pista_jugador[2];
};

struct tp {
    abb_t* pokemones;
    jugadores_t jugadores;
}; 

int comparar_pokemon(void *poke1, void *poke2) {
    struct pokemon_info *pokemon1 = (struct pokemon_info *)poke1;
    struct pokemon_info *pokemon2 = (struct pokemon_info *)poke2;
    return strcasecmp(pokemon1->nombre, pokemon2->nombre);
}

char *strdup2(const char *s)
{
	char *s2 = malloc(strlen(s) + 1);
    if (s2 == NULL) return NULL;
	strcpy(s2, s);
	return s2;
}

void leer_archivo(TP *tp, const char *nombre_archivo){
    if (tp == NULL) return;
	FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        free(tp);
        return;
    }

    tp->pokemones = abb_crear(comparar_pokemon);
    if (tp->pokemones == NULL) {
        fclose(archivo);
        free(tp);
        return;
    }

    char poke[256];
	while (fgets(poke, sizeof(poke), archivo)) {
	    struct pokemon_info *pokemon = calloc(1, sizeof(struct pokemon_info));
	    if (pokemon == NULL) {
            abb_destruir(tp->pokemones);
            fclose(archivo);
            free(tp);
            return;
        }

	    char *nombre = strtok(poke, ",");
        char *fuerza = strtok(NULL, ",");
        char *destreza = strtok(NULL, ",");
        char *inteligencia = strtok(NULL, ",");

        if (nombre != NULL && fuerza != NULL && destreza != NULL && inteligencia != NULL) {
            pokemon->nombre = strdup2(nombre);
            pokemon->fuerza = atoi(fuerza);
            pokemon->destreza = atoi(destreza);
            pokemon->inteligencia = atoi(inteligencia);

            abb_insertar(tp->pokemones, pokemon);
        } else {
            fprintf(stderr, "Error: Formato de línea incorrecto\n");
            free(pokemon);
        }
	}

	fclose(archivo);
}

TP *tp_crear(const char *nombre_archivo)
{
    TP *tp = calloc(1,sizeof(TP));
    if (!tp) return NULL;

    for (int i = 0; i < 2; i++) {
        tp->jugadores.pista_jugador[i] = malloc(sizeof(pista_jugador_t));
        if (!tp->jugadores.pista_jugador[i]) {
            free(tp);
            return NULL;
        }
        tp->jugadores.pista_jugador[i]->largo_actual = 0; // Initialize largo_actual to 0
        creacion_pista(tp->jugadores.pista_jugador[i]);
    }

    leer_archivo(tp, nombre_archivo);
    
    return tp;
}

int tp_cantidad_pokemon(TP *tp){
    if (tp == NULL) return 0;
    return (int)abb_tamanio(tp->pokemones); 
}

const struct pokemon_info *tp_buscar_pokemon(TP *tp, const char *nombre) {
    if (tp == NULL) return NULL;

    struct pokemon_info buscar;
    buscar.nombre = strdup2(nombre);

    struct pokemon_info *poke_buscado = abb_buscar(tp->pokemones, &buscar);
    free(buscar.nombre);

    return poke_buscado;
}

bool concatenar_nombres(void *elemento, void *aux) {
    struct pokemon_info *pokemon = (struct pokemon_info *)elemento;
    char **nombres = (char **)aux;

    if (*nombres == NULL) {
        *nombres = malloc(strlen(pokemon->nombre) + 1);
        if (*nombres == NULL) return false;
        strcpy(*nombres, pokemon->nombre);
    } else {
        size_t len_actual = strlen(*nombres);
        size_t len_nuevo = len_actual + strlen(pokemon->nombre) + 3;
        char *temp = realloc(*nombres, len_nuevo);
        if (temp == NULL) {
            free(*nombres);
            return false;
        }

        *nombres = temp;

        strcat(*nombres, pokemon->nombre);
        strcat(*nombres, ",");
        strcat(*nombres, " ");
    }

    return true;
}

char *tp_nombres_disponibles(TP *tp) {
    if (tp == NULL) return NULL;
    
    char *string = NULL;

    if (!abb_con_cada_elemento(tp->pokemones, INORDEN, concatenar_nombres, &string)) {
        free(string);
        return NULL;
    }

    return string;
} 

bool tp_seleccionar_pokemon(TP *tp, enum TP_JUGADOR jugador, const char *nombre) {
    if (tp == NULL || nombre == NULL) {
        return false;
    }

    const struct pokemon_info *poke = tp_buscar_pokemon(tp, nombre);
    if (poke == NULL) {
        return false;
    }

    if (jugador == JUGADOR_1 && tp->jugadores.pokemon_seleccionado[JUGADOR_2] != NULL && strcmp(tp->jugadores.pokemon_seleccionado[JUGADOR_2]->nombre, poke->nombre) == 0) {
        return false;
    }

    if (jugador == JUGADOR_2 && tp->jugadores.pokemon_seleccionado[JUGADOR_1] != NULL && strcmp(tp->jugadores.pokemon_seleccionado[JUGADOR_1]->nombre, poke->nombre) == 0) {
        return false;
    }

    if (tp->jugadores.pokemon_seleccionado[jugador] != NULL) {
        free(tp->jugadores.pokemon_seleccionado[jugador]->nombre);
        free(tp->jugadores.pokemon_seleccionado[jugador]);
    }

    tp->jugadores.pokemon_seleccionado[jugador] = malloc(sizeof(struct pokemon_info));
    if (tp->jugadores.pokemon_seleccionado[jugador] == NULL) {
        return false;
    }

    tp->jugadores.pokemon_seleccionado[jugador]->nombre = strdup2(poke->nombre);
    if (tp->jugadores.pokemon_seleccionado[jugador]->nombre == NULL) {
        free(tp->jugadores.pokemon_seleccionado[jugador]);
        tp->jugadores.pokemon_seleccionado[jugador] = NULL; // Asegurarse de asignar NULL
        return false;
    }

    tp->jugadores.pokemon_seleccionado[jugador]->fuerza = poke->fuerza;
    tp->jugadores.pokemon_seleccionado[jugador]->destreza = poke->destreza;
    tp->jugadores.pokemon_seleccionado[jugador]->inteligencia = poke->inteligencia;

    return true;
}

const struct pokemon_info *tp_pokemon_seleccionado(TP *tp, enum TP_JUGADOR jugador) {
    if (tp->jugadores.pokemon_seleccionado[jugador] == NULL)  return NULL;
    
    const struct pokemon_info *poke = tp_buscar_pokemon(tp, tp->jugadores.pokemon_seleccionado[jugador]->nombre);
    if (poke == NULL) {
        return NULL;
    }
    
    return poke;
}

void creacion_pista(pista_jugador_t *pista_jugador){
    for (int i = 0; i < MAX_LARGO_PISTA; i++){
        pista_jugador->pista[i] = PISTA_VACIA;
	}
    pista_jugador->largo_actual = 0;
}

unsigned aleatoria (int maximo, int minimo) {
	srand (( unsigned)time(NULL));

	int numero = rand () % maximo + minimo;

	return (unsigned)numero;
}

unsigned tp_agregar_obstaculo(TP *tp, enum TP_JUGADOR jugador, enum TP_OBSTACULO obstaculo, unsigned posicion) {
    if (tp == NULL || jugador != JUGADOR_1 || jugador != JUGADOR_2 || obstaculo != OBSTACULO_DESTREZA || obstaculo != OBSTACULO_FUERZA || obstaculo != OBSTACULO_INTELIGENCIA) {
        return 0;
    }

    pista_jugador_t *pista_jugador = tp->jugadores.pista_jugador[jugador];

    if (posicion >= MAX_LARGO_PISTA) {
        posicion = MAX_LARGO_PISTA - 1;
    }

    for (unsigned i = pista_jugador->largo_actual; i > posicion; i--) {
        pista_jugador->pista[i] = pista_jugador->pista[i - 1];
    }

    char *obstaculo_str = NULL;
    switch (obstaculo) {
        case OBSTACULO_FUERZA:
            obstaculo_str = strdup2(PISTA_FUERZA);
            break;
        case OBSTACULO_DESTREZA:
            obstaculo_str = strdup2(PISTA_DESTREZA);
            break;
        case OBSTACULO_INTELIGENCIA:
            obstaculo_str = strdup2(PISTA_INTELIGENCIA);
            break;
        default:
            return 0; 
    }

    if (obstaculo_str == NULL) {
        return 0;
    }

    pista_jugador->pista[posicion] = obstaculo_str;
    pista_jugador->largo_actual++;

    return pista_jugador->largo_actual;
}

void imprimir_pista(TP *tp){
    if (tp == NULL) return;

    printf("\nPista Jugador 1:\n");
    if (tp->jugadores.pista_jugador[JUGADOR_1]) {
        for (int i = 0; i < MAX_LARGO_PISTA; i++){
            printf("%s", tp->jugadores.pista_jugador[JUGADOR_1]->pista[i]);
        }
    }
    printf("\nPista Jugador 2:\n");
    if (tp->jugadores.pista_jugador[JUGADOR_2]) {
        for (int i = 0; i < MAX_LARGO_PISTA; i++){
            printf("%s", tp->jugadores.pista_jugador[JUGADOR_2]->pista[i]);
        }
    }
    printf("\n");
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
	if (tp == NULL || jugador != JUGADOR_1 || jugador != JUGADOR_2) return;

	for (int i = 0; i < MAX_LARGO_PISTA; i++){
		tp->jugadores.pista_jugador[jugador]->pista[i] = PISTA_VACIA;
	}
    printf("Pista en preparación para la siguiente carrera..");
}

unsigned tp_calcular_tiempo_pista(TP *tp, enum TP_JUGADOR jugador)
{
	return 0;
}

char *tp_tiempo_por_obstaculo(TP *tp, enum TP_JUGADOR jugador)
{
	return NULL;
}

bool destruir_strdup2(void *elemento, void *aux) {
    struct pokemon_info *pokemon = (struct pokemon_info *)elemento;
    free(pokemon->nombre);
    free(pokemon);
    return true;
}

void tp_destruir(TP *tp) {
    if (tp == NULL) return;
    abb_con_cada_elemento(tp->pokemones, INORDEN, destruir_strdup2, NULL);
    abb_destruir(tp->pokemones);

    for (int i = 0; i < 2; i++) {
        if (tp->jugadores.pokemon_seleccionado[i] != NULL) {
            free(tp->jugadores.pokemon_seleccionado[i]->nombre);
            free(tp->jugadores.pokemon_seleccionado[i]);
        }
        if (tp->jugadores.pista_jugador[i] != NULL) {
            for (unsigned j = 0; j < tp->jugadores.pista_jugador[i]->largo_actual; j++) {
                free(tp->jugadores.pista_jugador[i]->pista[j]);
            }
            free(tp->jugadores.pista_jugador[i]);
        }
    }

    free(tp);
}
