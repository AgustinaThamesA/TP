#include "pa2m.h"
#include "src/tp.h"
#include "src/tp_estructura_privada.h"

void creo_tp_con_archivo_ejemplo()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");
	pa2m_afirmar(tp != NULL,
		     "Crea el TP abriendo el archivo pokemones.txt.");
	pa2m_afirmar(tp_cantidad_pokemon(tp) != 0,
		     "Cantidad pokemones es distinto de 0.");
	pa2m_afirmar(tp_cantidad_pokemon(tp) == 25,
		     "Cantidad pokemones es igual a 25.");

	tp_destruir(tp);
}

void busco_nombres_de_pokemones()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	pa2m_afirmar(tp_cantidad_pokemon(tp) == 25,
		     "Hay 25 pokemones disponibles.");

	char *string = tp_nombres_disponibles(tp);
	printf("%s", string);
	free(string);

	tp_destruir(tp);
}

void pruebas_tp_seleccionar_pokemon()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");
	const char *nombre = "Pikachu";

	const struct pokemon_info *poke = tp_buscar_pokemon(tp, nombre);
	pa2m_afirmar(strcmp(nombre, poke->nombre) == 0,
		     "Pikachu existe en el archivo");

	bool seleccionado = tp_seleccionar_pokemon(tp, JUGADOR_1, "Pikachu");
	pa2m_afirmar(seleccionado == true,
		     "Selecciono a Pikachu como pokemon del Jugador 1.");

	seleccionado = tp_seleccionar_pokemon(tp, JUGADOR_2, "Pikachu");
	pa2m_afirmar(
		seleccionado == false,
		"El Jugador 2 no puede elegir a Pikachu como su pokemon, porque ese pokemon le pertenece al Jugador 1.");

	seleccionado = tp_seleccionar_pokemon(tp, JUGADOR_2, "Bulbasaur");
	pa2m_afirmar(seleccionado == true,
		     "Selecciono a Bulbasaur como pokemon del Jugador 2.");

	seleccionado = tp_seleccionar_pokemon(tp, JUGADOR_1, "Bulbasaur");
	pa2m_afirmar(
		seleccionado == false,
		"El Jugador 1 no puede elegir a Bulbasaur como su pokemon, porque ese pokemon le pertenece al Jugador 2.");

	tp_destruir(tp);
}

void pruebas_tp_pokemon_seleccionado()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");
	const struct pokemon_info *pokemon_info =
		tp_pokemon_seleccionado(tp, JUGADOR_1);
	pa2m_afirmar(pokemon_info == NULL,
		     "No hay pokemon seleccionado para el Jugador 1.");

	tp_seleccionar_pokemon(tp, JUGADOR_1, "Pikachu");
	pokemon_info = tp_pokemon_seleccionado(tp, JUGADOR_1);
	pa2m_afirmar(pokemon_info != NULL,
		     "Hay pokemon seleccionado para el Jugador 1.");
	pa2m_afirmar(strcmp(pokemon_info->nombre, "Pikachu") == 0,
		     "El pokemon seleccionado por el Jugador 1 es Pikachu.");

	pokemon_info = tp_pokemon_seleccionado(tp, JUGADOR_2);
	pa2m_afirmar(pokemon_info == NULL,
		     "No hay pokemon seleccionado para el Jugador 2.");

	tp_destruir(tp);
}

void pruebas_imprimir_pistas_vacias()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");
	establecer_dificultad(tp, 4);
	tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista = 20;
	tp->jugadores.pista_jugador[JUGADOR_1]->max_obstaculos = 4;
	pista_vacia(tp, JUGADOR_1);
	tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista = 20;
	tp->jugadores.pista_jugador[JUGADOR_1]->max_obstaculos = 4;

	pa2m_afirmar(
		lista_vacia(tp->jugadores.pista_jugador[JUGADOR_1]->pista) ==
			false,
		"lista_t pista1 NO VACÍA.");
	pa2m_afirmar(
		lista_vacia(tp->jugadores.pista_jugador[JUGADOR_2]->pista) ==
			false,
		"lista_t pista2 NO VACÍA.");

	imprimir_pista(tp);

	tp_destruir(tp);
}

void pruebas_imprimir_pistas_con_obstaculos()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");
	establecer_dificultad(tp, 4);
	tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista = 20;
	tp->jugadores.pista_jugador[JUGADOR_1]->max_obstaculos = 4;
	pista_vacia(tp, JUGADOR_1);

	enum TP_OBSTACULO obstaculo1 = OBSTACULO_FUERZA;
	unsigned posicion1 = aleatoria(
		(int)tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista - 1,
		0);

	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo1,
					  posicion1) == 1,
		     "Hay 1 obstáculo en la pista del Jugador 1.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo1,
					  posicion1) == 1,
		     "Hay 1 obstáculo en la pista del Jugador 2.");

	enum TP_OBSTACULO obstaculo2 = OBSTACULO_DESTREZA;
	unsigned posicion2 = aleatoria(
		(int)tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista - 1,
		0);

	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo2,
					  posicion2) == 2,
		     "Hay 2 obstáculos en la pista del Jugador 1.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo2,
					  posicion2) == 2,
		     "Hay 2 obstáculos en la pista del Jugador 2.");

	enum TP_OBSTACULO obstaculo3 = OBSTACULO_INTELIGENCIA;
	unsigned posicion3 = aleatoria(
		(int)tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista - 1,
		0);

	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo3,
					  posicion3) == 3,
		     "Hay 3 obstáculos en la pista del Jugador 1.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo3,
					  posicion3) == 3,
		     "Hay 3 obstáculos en la pista del Jugador 2.");

	imprimir_pista(tp);

	tp_destruir(tp);
}

void pruebas_limpiar_pista_con_obstaculos()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	establecer_dificultad(tp, 4);
	tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista = 20;
	tp->jugadores.pista_jugador[JUGADOR_1]->max_obstaculos = 4;
	pista_vacia(tp, JUGADOR_1);

	enum TP_OBSTACULO obstaculo1 = OBSTACULO_FUERZA;
	unsigned posicion1 = aleatoria(
		(int)tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista - 1,
		0);

	tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo1, posicion1);
	tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo1, posicion1);

	enum TP_OBSTACULO obstaculo2 = OBSTACULO_DESTREZA;
	unsigned posicion2 = aleatoria(
		(int)tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista - 1,
		0);

	tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo2, posicion2);
	tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo2, posicion2);

	enum TP_OBSTACULO obstaculo3 = OBSTACULO_INTELIGENCIA;
	unsigned posicion3 = aleatoria(
		(int)tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista - 1,
		0);

	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo3,
					  posicion3) == 3,
		     "Hay 3 obstáculos en la pista del Jugador 1.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo3,
					  posicion3) == 3,
		     "Hay 3 obstáculos en la pista del Jugador 2.");

	imprimir_pista(tp);

	printf("\nLimpiando pista de Jugador 1...");

	tp_limpiar_pista(tp, JUGADOR_1);

	pa2m_afirmar(cant_obstaculos_actual_jugador(tp, JUGADOR_1) == 0,
		     "No hay obstáculos en la pista del Jugador 1.");

	imprimir_pista(tp);

	printf("\nLimpiando pista de Jugador 2...");

	tp_limpiar_pista(tp, JUGADOR_2);

	pa2m_afirmar(cant_obstaculos_actual_jugador(tp, JUGADOR_2) == 0,
		     "No hay obstáculos en la pista del Jugador 2.");

	imprimir_pista(tp);

	tp_destruir(tp);
}

void pruebas_quitar_obstaculo_de_pista()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	establecer_dificultad(tp, 4);
	tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista = 20;
	tp->jugadores.pista_jugador[JUGADOR_1]->max_obstaculos = 4;
	pista_vacia(tp, JUGADOR_1);

	enum TP_OBSTACULO obstaculo1 = OBSTACULO_FUERZA;
	unsigned posicion1 = aleatoria(
		(int)tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista - 1,
		0);

	printf("Posición 1: %u\n", posicion1);

	tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo1, posicion1);
	tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo1, posicion1);

	enum TP_OBSTACULO obstaculo2 = OBSTACULO_DESTREZA;
	unsigned posicion2 = aleatoria(
		(int)tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista - 1,
		0);

	printf("Posición 2: %u\n", posicion2);

	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo2,
					  posicion2) == 2,
		     "Hay 2 obstáculos en la pista del Jugador 1.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo2,
					  posicion2) == 2,
		     "Hay 2 obstáculos en la pista del Jugador 2.");

	imprimir_pista(tp);

	pa2m_afirmar(tp_quitar_obstaculo(tp, JUGADOR_1, posicion1) == 1,
		     "Quitar deja 1 obstáculo en la pista del Jugador 1.");

	imprimir_pista(tp);

	pa2m_afirmar(tp_quitar_obstaculo(tp, JUGADOR_2, posicion2) == 1,
		     "Quitar deja 1 obstáculo en la pista del Jugador 2.");

	imprimir_pista(tp);

	tp_destruir(tp);
}

void pruebas_string_con_obstaculos_de_cada_pista()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	establecer_dificultad(tp, 4);
	tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista = 20;
	tp->jugadores.pista_jugador[JUGADOR_1]->max_obstaculos = 4;
	pista_vacia(tp, JUGADOR_1);

	enum TP_OBSTACULO obstaculo1 = OBSTACULO_FUERZA;
	unsigned posicion1 = aleatoria(
		(int)tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista - 1,
		0);

	tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo1, posicion1);
	tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo1, posicion1);

	enum TP_OBSTACULO obstaculo2 = OBSTACULO_DESTREZA;
	unsigned posicion2 = aleatoria(
		(int)tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista - 1,
		0);

	tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo2, posicion2);

	enum TP_OBSTACULO obstaculo3 = OBSTACULO_INTELIGENCIA;
	unsigned posicion3 = aleatoria(
		(int)tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista - 1,
		0);

	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo2,
					  posicion2) == 2,
		     "Hay 2 obstáculos en la pista del Jugador 1.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo3,
					  posicion3) == 3,
		     "Hay 3 obstáculos en la pista del Jugador 2.");

	imprimir_pista(tp);

	char *obstaculos = tp_obstaculos_pista(tp, JUGADOR_1);

	printf("\nObstáculos en la pista del Jugador 1: %s\n", obstaculos);

	free(obstaculos);

	char *obstaculos2 = tp_obstaculos_pista(tp, JUGADOR_2);

	printf("\nObstáculos en la pista del Jugador 2: %s\n", obstaculos2);

	free(obstaculos2);

	tp_destruir(tp);
}

void pruebas_calcular_tiempo_pista()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	establecer_dificultad(tp, 4);
	tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista = 20;
	tp->jugadores.pista_jugador[JUGADOR_1]->max_obstaculos = 4;
	pista_vacia(tp, JUGADOR_1);

	const char *nombre1 = "Pikachu";
	const struct pokemon_info *poke1 = tp_buscar_pokemon(tp, nombre1);
	tp_seleccionar_pokemon(tp, JUGADOR_1, "Pikachu");
	pa2m_afirmar(strcmp(poke1->nombre, "Pikachu") == 0,
		     "El pokemon seleccionado por el Jugador 1 es Pikachu.");

	const char *nombre2 = "Bulbasaur";
	const struct pokemon_info *poke2 = tp_buscar_pokemon(tp, nombre2);
	tp_seleccionar_pokemon(tp, JUGADOR_2, "Bulbasaur");
	pa2m_afirmar(strcmp(poke2->nombre, "Bulbasaur") == 0,
		     "El pokemon seleccionado por el Jugador 2 es Bulbasaur.");

	enum TP_OBSTACULO obstaculo1 = OBSTACULO_FUERZA;
	unsigned posicion1 = aleatoria(
		(int)tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista - 1,
		0);
	tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo1, posicion1);
	tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo1, posicion1);

	enum TP_OBSTACULO obstaculo2 = OBSTACULO_DESTREZA;
	unsigned posicion2 = aleatoria(
		(int)tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista - 1,
		0);
	tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo2, posicion2);
	tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo2, posicion2);

	enum TP_OBSTACULO obstaculo3 = OBSTACULO_INTELIGENCIA;
	unsigned posicion3 = aleatoria(
		(int)tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista - 1,
		0);

	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo3,
					  posicion3) == 3,
		     "Hay 3 obstáculos en la pista del Jugador 1.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo3,
					  posicion3) == 3,
		     "Hay 3 obstáculos en la pista del Jugador 2.");

	imprimir_pista(tp);

	printf("\nTiempo pista Jugador 1: %d",
	       tp_calcular_tiempo_pista(tp, JUGADOR_1));
	printf("\nTiempo pista Jugador 2: %d",
	       tp_calcular_tiempo_pista(tp, JUGADOR_2));

	tp_destruir(tp);
}

void pruebas_csv_tiempo_pista()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	establecer_dificultad(tp, 4);
	tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista = 20;
	tp->jugadores.pista_jugador[JUGADOR_1]->max_obstaculos = 4;
	pista_vacia(tp, JUGADOR_1);

	const char *nombre1 = "Pikachu";
	const struct pokemon_info *poke1 = tp_buscar_pokemon(tp, nombre1);
	tp_seleccionar_pokemon(tp, JUGADOR_1, "Pikachu");
	pa2m_afirmar(strcmp(poke1->nombre, "Pikachu") == 0,
		     "El pokemon seleccionado por el Jugador 1 es Pikachu.");

	const char *nombre2 = "Bulbasaur";
	const struct pokemon_info *poke2 = tp_buscar_pokemon(tp, nombre2);
	tp_seleccionar_pokemon(tp, JUGADOR_2, "Bulbasaur");
	pa2m_afirmar(strcmp(poke2->nombre, "Bulbasaur") == 0,
		     "El pokemon seleccionado por el Jugador 2 es Bulbasaur.");

	enum TP_OBSTACULO obstaculo1 = OBSTACULO_FUERZA;
	unsigned posicion1 = aleatoria(
		(int)tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista - 1,
		0);

	tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo1, posicion1);
	tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo1, posicion1);

	enum TP_OBSTACULO obstaculo2 = OBSTACULO_DESTREZA;
	unsigned posicion2 = aleatoria(
		(int)tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista - 1,
		0);

	tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo2, posicion2);

	enum TP_OBSTACULO obstaculo3 = OBSTACULO_INTELIGENCIA;
	unsigned posicion3 = aleatoria(
		(int)tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista - 1,
		0);

	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo2,
					  posicion2) == 2,
		     "Hay 2 obstáculos en la pista del Jugador 1.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo3,
					  posicion3) == 3,
		     "Hay 3 obstáculos en la pista del Jugador 2.");

	imprimir_pista(tp);

	char *obstaculos = tp_tiempo_por_obstaculo(tp, JUGADOR_1);

	printf("\nTiempo por obstáculo en la pista del Jugador 1: %s\n",
	       obstaculos);

	free(obstaculos);

	char *obstaculos2 = tp_tiempo_por_obstaculo(tp, JUGADOR_2);

	printf("\nTiempo por obstáculo en la pista del Jugador 2: %s\n",
	       obstaculos2);

	free(obstaculos2);

	tp_destruir(tp);
}

void pruebas_control_chanu()
{
	TP *tp1 = tp_crear("ejemplo.txt");

	pa2m_afirmar(tp1 == NULL,
		     "No puedo crear un TP con un archivo inexistente.");

	TP *tp2 = tp_crear("ejemplo/pruebas.txt");

	pa2m_afirmar(tp2 == NULL,
		     "No puedo crear un TP con un archivo incorrecto.");

	TP *tp = tp_crear("ejemplo/pokemones.txt");

	pa2m_afirmar(
		cant_obstaculos_actual_jugador(tp, JUGADOR_1) == 0,
		"No hay obstáculos inicialmente en la pista del Jugador 1.");
	pa2m_afirmar(
		cant_obstaculos_actual_jugador(tp, JUGADOR_2) == 0,
		"No hay obstáculos inicialmente en la pista del Jugador 2.");

	pa2m_afirmar(tp_obstaculos_pista(tp, JUGADOR_1) == NULL,
		     "Obstáculos de J1 en 0.");
	pa2m_afirmar(tp_obstaculos_pista(tp, JUGADOR_2) == NULL,
		     "Obstáculos de J2 en 0.");

	pa2m_afirmar(
		tp_tiempo_por_obstaculo(tp, JUGADOR_1) == NULL,
		"No se puede calcular el tiempo por obstáculo si no hay pista disponible.");

	pa2m_afirmar(
		tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_FUERZA, 0) == 1,
		"Puedo agregar un obstaculo de fuerza al jugador 1 en la posicion 0 (F).");
	pa2m_afirmar(
		tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA, 0) == 2,
		"Puedo agregar un obstaculo de destreza al jugador 1 en la posicion 0 (DF).");
	pa2m_afirmar(
		tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA,
				     1) == 3,
		"Puedo agregar un obstaculo de inteligencia al jugador 1 en la posicion 1 (DIF).");
	pa2m_afirmar(
		tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA,
				     3) == 4,
		"Puedo agregar un obstaculo de inteligencia al jugador 1 en la posicion 3 (DIFI).");

	char *obstaculos = tp_obstaculos_pista(tp, JUGADOR_1);
	pa2m_afirmar(
		strcmp(obstaculos, "DIFI") == 0,
		"Los obstaculos en la pista del jugador 1 son los correctos (DIFI).");
	pa2m_afirmar(
		tp_quitar_obstaculo(tp, JUGADOR_1, 0) == 3,
		"Puedo quitar un obstaculo de la pista del jugador 1 en la posicion 0 (IFI).");

	pa2m_afirmar(
		tp_quitar_obstaculo(tp, JUGADOR_1, 1) == 2,
		"Puedo quitar un obstaculo de la pista del jugador 1 en la posicion 1 (II).");

	char *obstaculos2 = tp_obstaculos_pista(tp, JUGADOR_1);
	printf("\nObstáculos en la pista del Jugador 2: %s\n", obstaculos2);
	pa2m_afirmar(
		strcmp(obstaculos2, "II") == 0,
		"Los obstaculos en la pista del jugador 1 son los correctos (II).");

	free(obstaculos);
	free(obstaculos2);

	tp_destruir(tp);
}

void pruebas_tiempo_chanu()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	printf("Otra pista\n\n");

	tp->jugadores.pista_jugador[JUGADOR_1]->largo_pista = 8;
	tp->jugadores.pista_jugador[JUGADOR_2]->largo_pista = 8;
	tp->jugadores.pista_jugador[JUGADOR_1]->max_obstaculos = 8;

	const char *nombre1 = "Caterpie";
	const struct pokemon_info *poke1 = tp_buscar_pokemon(tp, nombre1);
	tp_seleccionar_pokemon(tp, JUGADOR_1, "Caterpie");
	pa2m_afirmar(strcmp(poke1->nombre, "Caterpie") == 0,
		     "El pokemon seleccionado por el Jugador 1 es Caterpie.");

	const char *nombre2 = "Dragonite";
	const struct pokemon_info *poke2 = tp_buscar_pokemon(tp, nombre2);
	tp_seleccionar_pokemon(tp, JUGADOR_2, "Dragonite");
	pa2m_afirmar(strcmp(poke2->nombre, "Dragonite") == 0,
		     "El pokemon seleccionado por el Jugador 2 es Dragonite.");

	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA, 0);
	tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_INTELIGENCIA, 0);

	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_FUERZA, 1);
	tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_FUERZA, 1);

	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA, 2);
	tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_DESTREZA, 2);

	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA, 3);
	tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_DESTREZA, 3);

	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA, 4);
	tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_DESTREZA, 4);

	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA, 5);
	tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_DESTREZA, 5);

	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA, 6);
	tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_INTELIGENCIA, 6);

	tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA, 7);
	tp_agregar_obstaculo(tp, JUGADOR_2, OBSTACULO_INTELIGENCIA, 7);

	char *obstaculos1 = tp_obstaculos_pista(tp, JUGADOR_1);
	printf("\nObstáculos en la pista del Jugador 1: %s\n", obstaculos1);
	pa2m_afirmar(
		strcmp(obstaculos1, "IFDDDDII") == 0,
		"Los obstaculos en la pista del jugador 1 son los correctos (IFDDDDII).");
	free(obstaculos1);

	char *obstaculos2 = tp_obstaculos_pista(tp, JUGADOR_2);
	printf("\nObstáculos en la pista del Jugador 2: %s\n", obstaculos2);
	pa2m_afirmar(
		strcmp(obstaculos2, "IFDDDDII") == 0,
		"Los obstaculos en la pista del jugador 2 son los correctos (IFDDDDII).");
	free(obstaculos2);

	char *tiempo_1 = tp_tiempo_por_obstaculo(tp, JUGADOR_1);
	printf("\nTiempo de la pista del Jugador 1: %s\n", tiempo_1);
	pa2m_afirmar(
		strcmp(tiempo_1, "9,7,2,1,0,0,9,8") == 0,
		"Los tiempos de obstaculos para caterpie son los correctos (9,7,2,1,0,0,9,8).");
	free(tiempo_1);
	unsigned tiempo_pista_1 = tp_calcular_tiempo_pista(tp, JUGADOR_1);
	printf("Tiempo pista 1: %d\n", tiempo_pista_1);
	pa2m_afirmar(tiempo_pista_1 == 36,
		     "El tiempo de caterpie es el correcto (36).");

	char *tiempo_2 = tp_tiempo_por_obstaculo(tp, JUGADOR_2);
	printf("\nTiempo de la pista del Jugador 2: %s\n", tiempo_2);
	pa2m_afirmar(
		strcmp(tiempo_2, "2,1,0,0,0,0,2,1") == 0,
		"Los tiempos de obstaculos para dragonite son los correctos (2,1,0,0,0,0,2,1).");
	free(tiempo_2);
	unsigned tiempo_pista_2 = tp_calcular_tiempo_pista(tp, JUGADOR_2);
	printf("Tiempo pista 2: %d\n", tiempo_pista_2);
	pa2m_afirmar(tiempo_pista_2 == 6,
		     "El tiempo de dragonite es el correcto (6).");

	tp_destruir(tp);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== Pruebas de creación ========================");
	creo_tp_con_archivo_ejemplo();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de búsqueda ========================");
	busco_nombres_de_pokemones();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de selección ========================");
	pruebas_tp_seleccionar_pokemon();
	printf("\n");
	pruebas_tp_pokemon_seleccionado();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de pista vacía ========================");
	pruebas_imprimir_pistas_vacias();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de pista con obstáculos ========================");
	pruebas_imprimir_pistas_con_obstaculos();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de quitar obstáculos ========================");
	pruebas_quitar_obstaculo_de_pista();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de limpieza de pista ========================");
	pruebas_limpiar_pista_con_obstaculos();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de string de obstáculos ========================");
	pruebas_string_con_obstaculos_de_cada_pista();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de cálculo de tiempo ========================");
	pruebas_calcular_tiempo_pista();
	printf("\n");
	pruebas_csv_tiempo_pista();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de chanu ========================");
	pruebas_control_chanu();
	printf("\n");
	pruebas_tiempo_chanu();

	return pa2m_mostrar_reporte();
}