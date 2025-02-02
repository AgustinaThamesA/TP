#include "tp.h"
#include "tp_estructura_privada.h"

// ------------- FUNCIONES AUXILIARES -------------

int comparar_pokemon(void *poke1, void *poke2)
{
	struct pokemon_info *pokemon1 = (struct pokemon_info *)poke1;
	struct pokemon_info *pokemon2 = (struct pokemon_info *)poke2;
	return strcasecmp(pokemon1->nombre, pokemon2->nombre);
}

char *strdup2(const char *s)
{
	char *s2 = malloc(strlen(s) + 1);
	if (s2 == NULL)
		return NULL;
	strcpy(s2, s);
	return s2;
}

bool guardar_alfabeticamente(void *elemento, void *aux)
{
	if (elemento == NULL)
		return false;
	struct pokemon_info *pokemon = (struct pokemon_info *)elemento;
	abb_t *auxiliar = aux;
	abb_insertar(auxiliar, pokemon);
	return true;
}

bool leer_archivo(TP *tp, FILE *archivo)
{
	if (tp == NULL || archivo == NULL)
		return false;

	tp->pokemones = abb_crear(comparar_pokemon);
	if (tp->pokemones == NULL) {
		fclose(archivo);
		free(tp);
		return false;
	}

	char poke[256];
	while (fgets(poke, sizeof(poke), archivo)) {
		struct pokemon_info *pokemon =
			calloc(1, sizeof(struct pokemon_info));
		if (pokemon == NULL) {
			abb_destruir(tp->pokemones);
			fclose(archivo);
			free(tp);
			return false;
		}

		char *nombre = strtok(poke, ",");
		char *fuerza = strtok(NULL, ",");
		char *destreza = strtok(NULL, ",");
		char *inteligencia = strtok(NULL, ",");

		if (nombre != NULL && fuerza != NULL && destreza != NULL &&
		    inteligencia != NULL) {
			pokemon->nombre = strdup2(nombre);
			pokemon->fuerza = atoi(fuerza);
			pokemon->destreza = atoi(destreza);
			pokemon->inteligencia = atoi(inteligencia);

			abb_insertar(tp->pokemones, pokemon);
		} else {
			free(pokemon);
			fclose(archivo);
			abb_destruir(tp->pokemones);
			free(tp);
			return false;
		}
		if (feof(archivo)) {
			break;
		}
		if (ferror(archivo)) {
			free(pokemon);
			abb_destruir(tp->pokemones);
			fclose(archivo);
			free(tp);
			return false;
		}
	}

	abb_t *temporal = abb_crear(comparar_pokemon);
	if (temporal == NULL) {
		abb_destruir(tp->pokemones);
		fclose(archivo);
		free(tp);
		return false;
	}

	abb_con_cada_elemento(tp->pokemones, INORDEN, guardar_alfabeticamente,
			      temporal);

	abb_destruir(tp->pokemones);
	tp->pokemones = temporal;

	fclose(archivo);
	return true;
}

bool concatenar_nombres(void *elemento, void *aux)
{
	struct pokemon_info *pokemon = (struct pokemon_info *)elemento;
	char **nombres = (char **)aux;

	if (*nombres == NULL) {
		*nombres = malloc(strlen(pokemon->nombre) + 1);
		if (*nombres == NULL)
			return false;
		strcpy(*nombres, pokemon->nombre);

	} else {
		size_t len_actual = strlen(*nombres);
		len_actual = strlen(*nombres);
		size_t len_nuevo = len_actual + strlen(pokemon->nombre) + 3;
		char *temp = realloc(*nombres, len_nuevo);
		if (temp == NULL) {
			free(*nombres);
			return false;
		}

		*nombres = temp;
		strcat(*nombres, ",");
		strcat(*nombres, pokemon->nombre);
	}

	return true;
}

void pista_vacia(TP *tp, enum TP_JUGADOR jugador)
{
	pista_jugador_t *pista_jugador = tp->jugadores.pista_jugador[jugador];
	for (size_t i = 0; i < pista_jugador->largo_pista; i++) {
		lista_insertar_en_posicion(pista_jugador->pista, PISTA_VACIA,
					   i);
	}

	tp->jugadores.pista_jugador[jugador] = pista_jugador;
	if (lista_vacia(tp->jugadores.pista_jugador[jugador]->pista) == true)
		printf("Pista vacía no inicializada correctamente.\n");
	tp->jugadores.pista_jugador[jugador]->cant_obstaculos = 0;
}

unsigned aleatoria(int maximo, int minimo)
{
	static bool inicializado = false;
	if (!inicializado) {
		srand((unsigned)time(NULL));
		inicializado = true;
	}

	int numero = rand() % maximo + minimo;

	return (unsigned)numero;
}

unsigned cant_obstaculos_actual_jugador(TP *tp, enum TP_JUGADOR jugador)
{
	if (tp == NULL || (jugador != JUGADOR_1 && jugador != JUGADOR_2)) {
		return 0;
	}
	return tp->jugadores.pista_jugador[jugador]->cant_obstaculos;
}

void imprimir_pista(TP *tp)
{
	if (tp == NULL)
		return;

	printf("\nPista Jugador 1:\n");
	if (tp->jugadores.pista_jugador[JUGADOR_1] &&
	    tp->jugadores.pista_jugador[JUGADOR_1]->pista) {
		for (size_t i = 0;
		     i < tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista;
		     i++) {
			char *elemento = lista_elemento_en_posicion(
				tp->jugadores.pista_jugador[JUGADOR_1]->pista,
				i);
			printf("%c", *elemento);
		}
	}
	printf("\n");

	printf("Pista Jugador 2:\n");
	if (tp->jugadores.pista_jugador[JUGADOR_2] &&
	    tp->jugadores.pista_jugador[JUGADOR_2]->pista) {
		for (size_t i = 0;
		     i < tp->jugadores.pista_jugador[JUGADOR_2]->largo_pista;
		     i++) {
			char *elemento = lista_elemento_en_posicion(
				tp->jugadores.pista_jugador[JUGADOR_2]->pista,
				i);
			printf("%c", *elemento);
		}
	}
	printf("\n");
}

bool concatenar_obstaculos(void *elemento, void *aux)
{
	if (elemento == NULL || aux == NULL)
		return false;
	char **str_obstaculos = (char **)aux;
	char *obstaculo = (char *)elemento;
	if (strcmp(obstaculo, PISTA_FUERZA) == 0 ||
	    strcmp(obstaculo, PISTA_DESTREZA) == 0 ||
	    strcmp(obstaculo, PISTA_INTELIGENCIA) == 0) {
		if (*str_obstaculos == NULL) {
			*str_obstaculos = malloc(strlen(obstaculo) + 1);
			strcpy(*str_obstaculos, obstaculo);
		} else {
			char *temp = malloc(strlen(*str_obstaculos) +
					    strlen(obstaculo) + 1);
			strcpy(temp, *str_obstaculos);
			strcat(temp, obstaculo);
			free(*str_obstaculos);
			*str_obstaculos = temp;
		}
	}
	return true;
}

bool destruir_strdup2(void *elemento, void *aux)
{
	struct pokemon_info *pokemon = (struct pokemon_info *)elemento;
	free(pokemon->nombre);
	free(pokemon);
	return true;
}

// ------------- FUNCIONES ORIGINALES -------------

TP *tp_crear(const char *nombre_archivo)
{
	if (nombre_archivo == NULL)
		return NULL;

	const char *extension = strrchr(nombre_archivo, '.');
	if (extension == NULL || strcmp(extension, ".txt") != 0) {
		return NULL;
	}

	TP *tp = calloc(1, sizeof(TP));
	if (!tp)
		return NULL;

	FILE *archivo = fopen(nombre_archivo, "r");
	if (archivo == NULL) {
		free(tp);
		return NULL;
	}

	if (!leer_archivo(tp, archivo)) {
		return NULL;
	}

	for (int i = 0; i < 2; i++) {
		tp->jugadores.pista_jugador[i] =
			malloc(sizeof(pista_jugador_t));
		if (!tp->jugadores.pista_jugador[i]) {
			free(tp);
			return NULL;
		}
		tp->jugadores.pista_jugador[i]->pista = lista_crear();
		if (!tp->jugadores.pista_jugador[i]->pista) {
			free(tp->jugadores.pista_jugador[i]);
			free(tp);
			return NULL;
		}

		tp->jugadores.pista_jugador[i]->cant_obstaculos = 0;
		tp->jugadores.pista_jugador[i]->largo_pista = 20;
		tp->jugadores.pista_jugador[i]->max_obstaculos = 0;
		tp->jugadores.pista_jugador[i]->dificultad = 0;
		tp->jugadores.pista_jugador[i]->velocidad = 0;

		pista_vacia(tp, i);
	}

	return tp;
}

int tp_cantidad_pokemon(TP *tp)
{
	if (tp == NULL)
		return 0;
	return (int)abb_tamanio(tp->pokemones);
}

const struct pokemon_info *tp_buscar_pokemon(TP *tp, const char *nombre)
{
	if (tp == NULL)
		return NULL;

	struct pokemon_info buscar;
	buscar.nombre = strdup2(nombre);

	struct pokemon_info *poke_buscado = abb_buscar(tp->pokemones, &buscar);
	free(buscar.nombre);

	return poke_buscado;
}

char *tp_nombres_disponibles(TP *tp)
{
	if (tp == NULL)
		return NULL;

	char *string = NULL;

	if (!abb_con_cada_elemento(tp->pokemones, PREORDEN, concatenar_nombres,
				   &string)) {
		free(string);
		return NULL;
	}

	return string;
}

bool tp_seleccionar_pokemon(TP *tp, enum TP_JUGADOR jugador, const char *nombre)
{
	if (tp == NULL || nombre == NULL) {
		return false;
	}

	const struct pokemon_info *poke = tp_buscar_pokemon(tp, nombre);
	if (poke == NULL) {
		return false;
	}

	if (jugador == JUGADOR_1 &&
	    tp->jugadores.pokemon_seleccionado[JUGADOR_2] != NULL &&
	    strcmp(tp->jugadores.pokemon_seleccionado[JUGADOR_2]->nombre,
		   poke->nombre) == 0) {
		return false;
	}

	if (jugador == JUGADOR_2 &&
	    tp->jugadores.pokemon_seleccionado[JUGADOR_1] != NULL &&
	    strcmp(tp->jugadores.pokemon_seleccionado[JUGADOR_1]->nombre,
		   poke->nombre) == 0) {
		return false;
	}

	if (tp->jugadores.pokemon_seleccionado[jugador] != NULL) {
		free(tp->jugadores.pokemon_seleccionado[jugador]->nombre);
		free(tp->jugadores.pokemon_seleccionado[jugador]);
	}

	tp->jugadores.pokemon_seleccionado[jugador] =
		malloc(sizeof(struct pokemon_info));
	if (tp->jugadores.pokemon_seleccionado[jugador] == NULL) {
		return false;
	}

	tp->jugadores.pokemon_seleccionado[jugador]->nombre =
		strdup2(poke->nombre);
	if (tp->jugadores.pokemon_seleccionado[jugador]->nombre == NULL) {
		free(tp->jugadores.pokemon_seleccionado[jugador]);
		tp->jugadores.pokemon_seleccionado[jugador] = NULL;
		return false;
	}

	tp->jugadores.pokemon_seleccionado[jugador]->fuerza = poke->fuerza;
	tp->jugadores.pokemon_seleccionado[jugador]->destreza = poke->destreza;
	tp->jugadores.pokemon_seleccionado[jugador]->inteligencia =
		poke->inteligencia;

	return true;
}

const struct pokemon_info *tp_pokemon_seleccionado(TP *tp,
						   enum TP_JUGADOR jugador)
{
	if (tp->jugadores.pokemon_seleccionado[jugador] == NULL)
		return NULL;

	const struct pokemon_info *poke = tp_buscar_pokemon(
		tp, tp->jugadores.pokemon_seleccionado[jugador]->nombre);
	if (poke == NULL) {
		return NULL;
	}

	return poke;
}

unsigned tp_agregar_obstaculo(TP *tp, enum TP_JUGADOR jugador,
			      enum TP_OBSTACULO obstaculo, unsigned posicion)
{
	if (tp == NULL || (jugador != JUGADOR_1 && jugador != JUGADOR_2)) {
		return 0;
	}

	pista_jugador_t *pista_jugador = tp->jugadores.pista_jugador[jugador];

	if (posicion >= pista_jugador->largo_pista) {
		posicion = pista_jugador->largo_pista - 2;
	}

	if (strcmp(lista_elemento_en_posicion(pista_jugador->pista, posicion),
		   PISTA_VACIA) == 0)
		lista_quitar_de_posicion(pista_jugador->pista, posicion);

	switch (obstaculo) {
	case OBSTACULO_FUERZA:
		lista_insertar_en_posicion(pista_jugador->pista, PISTA_FUERZA,
					   posicion);

		break;
	case OBSTACULO_DESTREZA:
		lista_insertar_en_posicion(pista_jugador->pista, PISTA_DESTREZA,
					   posicion);

		break;
	case OBSTACULO_INTELIGENCIA:
		lista_insertar_en_posicion(pista_jugador->pista,
					   PISTA_INTELIGENCIA, posicion);

		break;
	default:
		return 0;
	}

	pista_jugador->cant_obstaculos++;
	tp->jugadores.pista_jugador[jugador] = pista_jugador;

	return pista_jugador->cant_obstaculos;
}

unsigned tp_quitar_obstaculo(TP *tp, enum TP_JUGADOR jugador, unsigned posicion)
{
	if (tp == NULL || (jugador != JUGADOR_1 && jugador != JUGADOR_2)) {
		return 0;
	}

	pista_jugador_t *pista_jugador = tp->jugadores.pista_jugador[jugador];

	if (posicion >= pista_jugador->largo_pista) {
		posicion = pista_jugador->largo_pista - 1;
	}

	char *obstaculo =
		lista_elemento_en_posicion(pista_jugador->pista, posicion);

	if (obstaculo != NULL && (strcmp(obstaculo, PISTA_FUERZA) == 0 ||
				  strcmp(obstaculo, PISTA_DESTREZA) == 0 ||
				  strcmp(obstaculo, PISTA_INTELIGENCIA) == 0)) {
		lista_quitar_de_posicion(pista_jugador->pista, posicion);

		pista_jugador->cant_obstaculos--;
	}

	tp->jugadores.pista_jugador[jugador] = pista_jugador;

	return tp->jugadores.pista_jugador[jugador]->cant_obstaculos;
}

char *tp_obstaculos_pista(TP *tp, enum TP_JUGADOR jugador)
{
	if (tp == NULL || (jugador != JUGADOR_1 && jugador != JUGADOR_2) ||
	    cant_obstaculos_actual_jugador(tp, jugador) == 0) {
		return NULL;
	}

	pista_jugador_t *pista_jugador = tp->jugadores.pista_jugador[jugador];
	char *obstaculos =
		calloc(1, (pista_jugador->cant_obstaculos + 1) * sizeof(char));
	if (obstaculos == NULL)
		return NULL;

	lista_con_cada_elemento(pista_jugador->pista, concatenar_obstaculos,
				&obstaculos);

	return obstaculos;
}

void tp_limpiar_pista(TP *tp, enum TP_JUGADOR jugador)
{
	if (tp == NULL || (jugador != JUGADOR_1 && jugador != JUGADOR_2))
		return;

	lista_t *pista = tp->jugadores.pista_jugador[jugador]->pista;

	while (!lista_vacia(pista)) {
		lista_quitar(pista);
	}

	tp->jugadores.pista_jugador[jugador]->pista = pista;

	pista_vacia(tp, jugador);

	printf("\nPista en preparación para la siguiente carrera...\n");
}

unsigned tp_calcular_tiempo_pista(TP *tp, enum TP_JUGADOR jugador)
{
	if (tp == NULL || tp->jugadores.pokemon_seleccionado[jugador] == NULL ||
	    lista_vacia(tp->jugadores.pista_jugador[jugador]->pista) ||
	    tp->jugadores.pista_jugador[jugador]->cant_obstaculos == 0) {
		return 0;
	}

	unsigned tiempo_total = 0;
	pista_jugador_t *pista_jugador = tp->jugadores.pista_jugador[jugador];
	struct pokemon_info *pokemon =
		tp->jugadores.pokemon_seleccionado[jugador];

	int obstaculos_seguidos[3] = { 0, 0,
				       0 }; // fuerza, destreza, inteligencia
	for (size_t i = 0; i < pista_jugador->largo_pista; i++) {
		char *obstaculo =
			lista_elemento_en_posicion(pista_jugador->pista, i);
		if (strcmp(obstaculo, PISTA_VACIA) != 0) {
			int tiempo_obstaculo = 0;
			if (strcmp(obstaculo, PISTA_FUERZA) == 0) {
				if (10 - pokemon->fuerza -
					    (obstaculos_seguidos[0]) <
				    0) {
					tiempo_obstaculo = 0;
				} else {
					tiempo_obstaculo =
						abs(10 - pokemon->fuerza -
						    (obstaculos_seguidos[0]));
				}
				obstaculos_seguidos[0]++;
				obstaculos_seguidos[1] =
					obstaculos_seguidos[2] = 0;
			} else if (strcmp(obstaculo, PISTA_DESTREZA) == 0) {
				if (10 - pokemon->destreza -
					    (obstaculos_seguidos[1]) <
				    0) {
					tiempo_obstaculo = 0;
				} else {
					tiempo_obstaculo =
						abs(10 - pokemon->destreza -
						    (obstaculos_seguidos[1]));
				}
				obstaculos_seguidos[1]++;
				obstaculos_seguidos[0] =
					obstaculos_seguidos[2] = 0;
			} else if (strcmp(obstaculo, PISTA_INTELIGENCIA) == 0) {
				if (10 - pokemon->inteligencia -
					    (obstaculos_seguidos[2]) <
				    0) {
					tiempo_obstaculo = 0;
				} else {
					tiempo_obstaculo =
						abs(10 - pokemon->inteligencia -
						    (obstaculos_seguidos[2]));
				}
				obstaculos_seguidos[2]++;
				obstaculos_seguidos[1] =
					obstaculos_seguidos[0] = 0;
			}
			tiempo_total += (unsigned)tiempo_obstaculo;
		}
	}
	return tiempo_total;
}

char *tp_tiempo_por_obstaculo(TP *tp, enum TP_JUGADOR jugador)
{
	if (tp == NULL || (jugador != JUGADOR_1 && jugador != JUGADOR_2) ||
	    lista_vacia(tp->jugadores.pista_jugador[jugador]->pista) ||
	    tp->jugadores.pista_jugador[jugador]->cant_obstaculos == 0) {
		return NULL;
	}

	pista_jugador_t *pista_jugador = tp->jugadores.pista_jugador[jugador];
	char *csv = malloc((pista_jugador->largo_pista * 4) * sizeof(char));
	if (!csv) {
		return NULL;
	}
	csv[0] = '\0';

	struct pokemon_info *pokemon =
		tp->jugadores.pokemon_seleccionado[jugador];

	if (pokemon == NULL) {
		free(csv);
		return NULL;
	}

	int obstaculos_seguidos[3] = { 0, 0,
				       0 }; // fuerza, destreza, inteligencia
	for (size_t i = 0; i < pista_jugador->largo_pista; i++) {
		char *obstaculo =
			lista_elemento_en_posicion(pista_jugador->pista, i);
		if (strcmp(obstaculo, PISTA_VACIA) != 0) {
			int tiempo_obstaculo = 0;
			if (strcmp(obstaculo, PISTA_FUERZA) == 0) {
				if (10 - pokemon->fuerza -
					    (obstaculos_seguidos[0]) <
				    0) {
					tiempo_obstaculo = 0;
				} else {
					tiempo_obstaculo =
						abs(10 - pokemon->fuerza -
						    (obstaculos_seguidos[0]));
				}
				obstaculos_seguidos[0]++;
				obstaculos_seguidos[1] =
					obstaculos_seguidos[2] = 0;
			} else if (strcmp(obstaculo, PISTA_DESTREZA) == 0) {
				if (10 - pokemon->destreza -
					    (obstaculos_seguidos[1]) <
				    0) {
					tiempo_obstaculo = 0;
				} else {
					tiempo_obstaculo =
						abs(10 - pokemon->destreza -
						    (obstaculos_seguidos[1]));
				}
				obstaculos_seguidos[1]++;
				obstaculos_seguidos[0] =
					obstaculos_seguidos[2] = 0;
			} else if (strcmp(obstaculo, PISTA_INTELIGENCIA) == 0) {
				if (10 - pokemon->inteligencia -
					    (obstaculos_seguidos[2]) <
				    0) {
					tiempo_obstaculo = 0;
				} else {
					tiempo_obstaculo =
						abs(10 - pokemon->inteligencia -
						    (obstaculos_seguidos[2]));
				}
				obstaculos_seguidos[2]++;
				obstaculos_seguidos[1] =
					obstaculos_seguidos[0] = 0;
			}
			char tiempo_str[12];
			sprintf(tiempo_str, "%d", tiempo_obstaculo);
			if (strlen(csv) > 0) {
				strcat(csv, ",");
			}
			strcat(csv, tiempo_str);
		}
	}
	return csv;
}

void tp_destruir(TP *tp)
{
	if (tp == NULL)
		return;

	if (abb_vacio(tp->pokemones) == false) {
		abb_con_cada_elemento(tp->pokemones, INORDEN, destruir_strdup2,
				      NULL);
		abb_destruir(tp->pokemones);
	}

	for (int i = 0; i < 2; i++) {
		if (tp->jugadores.pista_jugador[i] != NULL) {
			if (tp->jugadores.pokemon_seleccionado[i] != NULL) {
				free(tp->jugadores.pokemon_seleccionado[i]
					     ->nombre);
				free(tp->jugadores.pokemon_seleccionado[i]);
			}
			if (tp->jugadores.pista_jugador[i]->pista != NULL)
				lista_destruir(
					tp->jugadores.pista_jugador[i]->pista);
			free(tp->jugadores.pista_jugador[i]);
		}
	}

	free(tp);
}