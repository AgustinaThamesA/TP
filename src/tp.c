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

/* MIO QUE NO FUNCA
struct tp {
    abb_t* pokemones;
    int cantidad_pokemones;
    int dificultad;
    abb_t *puntajes;
    int cantidad_intentos;
    jugadores_t jugadores[2]; 
};
*/

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

    leer_archivo(tp, nombre_archivo);
    
    return tp;
}

int tp_cantidad_pokemon(TP *tp){
    if (tp == NULL) return 0;
    return (int)abb_tamanio(tp->pokemones); 
}

const struct pokemon_info *tp_buscar_pokemon(TP *tp, const char *nombre)
{
	if (tp == NULL) return NULL;
    return abb_buscar(tp->pokemones, (char*)nombre);
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
    if (tp->jugadores.pokemon_seleccionado[jugador] != NULL) {
        free(tp->jugadores.pokemon_seleccionado[jugador]);
    }
/*
    if (jugador == JUGADOR_1 && strcmp(tp->jugadores.pokemon_seleccionado[JUGADOR_2]->nombre, nombre) == 0) {
        return false;
    } else if (jugador == JUGADOR_2 && strcmp(tp->jugadores.pokemon_seleccionado[JUGADOR_1]->nombre, nombre) == 0) {
        return false;
    }

*/

    printf("%s\n", nombre);
    tp->jugadores.pokemon_seleccionado[jugador]->nombre = (char*)nombre;

    return true;
}

const struct pokemon_info *tp_pokemon_seleccionado(TP *tp, enum TP_JUGADOR jugador) {
    if (tp->jugadores.pokemon_seleccionado[jugador] == NULL)  return NULL;
    
    struct pokemon_info *pokemon_info = abb_buscar(tp->pokemones, tp->jugadores.pokemon_seleccionado[jugador]->nombre);
    if (pokemon_info == NULL) return NULL; 
    
    return pokemon_info;
}

void creacion_pista(char* pista_jugador[MAX_LARGO_PISTA]){
    for (int i = 0; i < MAX_LARGO_PISTA; i++){
        pista_jugador[i] = PISTA_VACIA;
	}
}

int aleatoria (int maximo, int minimo){
	srand (( unsigned)time(NULL));

	int numero = rand () % maximo + minimo;

	return numero;
}

unsigned tp_agregar_obstaculo(TP *tp, enum TP_JUGADOR jugador, enum TP_OBSTACULO obstaculo, unsigned posicion) {
    return 0;
}

void imprimir_pista(TP *tp, enum TP_JUGADOR jugador){
    if (tp == NULL || jugador != JUGADOR_1 || jugador != JUGADOR_2) return;
    printf("\n");
	for (int i = 0; i < MAX_LARGO_PISTA; i++){
		printf("%s", tp->jugadores.pista_jugador[jugador]->pista[i]);
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
        free(tp->jugadores.pokemon_seleccionado[i]);
        free(tp->jugadores.pista_jugador[i]);
    }

    free(tp);
}
