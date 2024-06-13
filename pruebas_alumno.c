#include "pa2m.h"
#include "src/tp.h"
#include "src/tp_estructura_privada.h"

void creo_tp_con_archivo_ejemplo()
{
	TP *tp = tp_crear("ejemplo/pokemones.txt");
	pa2m_afirmar(tp != NULL, "Crea el TP abriendo el archivo pokemones.txt.");
	pa2m_afirmar(tp_cantidad_pokemon(tp) != 0, "Cantidad pokemones es distinto de 0.");
	pa2m_afirmar(tp_cantidad_pokemon(tp) == 25, "Cantidad pokemones es igual a 25.");

	tp_destruir(tp);
}

void busco_nombres_de_pokemones(){
	TP *tp = tp_crear("ejemplo/pokemones.txt");	
	
	pa2m_afirmar(tp_cantidad_pokemon(tp) == 25, "Hay 25 pokemones disponibles.");

	char* string = tp_nombres_disponibles(tp); 
	printf("%s", string);
	free(string);

	tp_destruir(tp);
}

void pruebas_tp_seleccionar_pokemon(){
	TP *tp = tp_crear("ejemplo/pokemones.txt");
	const char* nombre = "Pikachu";

	const struct pokemon_info *poke = tp_buscar_pokemon(tp, nombre);
	pa2m_afirmar(strcmp(nombre, poke->nombre) == 0, "Pikachu existe en el archivo");

	bool seleccionado = tp_seleccionar_pokemon(tp, JUGADOR_1, "Pikachu");
	pa2m_afirmar(seleccionado == true, "Selecciono a Pikachu como pokemon del Jugador 1.");

	seleccionado = tp_seleccionar_pokemon(tp, JUGADOR_2, "Pikachu");
	pa2m_afirmar(seleccionado == false, "El Jugador 2 no puede elegir a Pikachu como su pokemon, porque ese pokemon le pertenece al Jugador 1.");

	seleccionado = tp_seleccionar_pokemon(tp, JUGADOR_2, "Bulbasaur");
	pa2m_afirmar(seleccionado == true, "Selecciono a Bulbasaur como pokemon del Jugador 2.");

	seleccionado = tp_seleccionar_pokemon(tp, JUGADOR_1, "Bulbasaur");
	pa2m_afirmar(seleccionado == false, "El Jugador 1 no puede elegir a Bulbasaur como su pokemon, porque ese pokemon le pertenece al Jugador 2.");
	

	tp_destruir(tp);
}

void pruebas_tp_pokemon_seleccionado() {
	TP *tp = tp_crear("ejemplo/pokemones.txt");
	const struct pokemon_info *pokemon_info = tp_pokemon_seleccionado(tp, JUGADOR_1);
	pa2m_afirmar(pokemon_info == NULL, "No hay pokemon seleccionado para el Jugador 1.");

	tp_seleccionar_pokemon(tp, JUGADOR_1, "Pikachu");
	pokemon_info = tp_pokemon_seleccionado(tp, JUGADOR_1);
	pa2m_afirmar(pokemon_info != NULL, "Hay pokemon seleccionado para el Jugador 1.");
	pa2m_afirmar(strcmp(pokemon_info->nombre, "Pikachu") == 0, "El pokemon seleccionado por el Jugador 1 es Pikachu.");

	pokemon_info = tp_pokemon_seleccionado(tp, JUGADOR_2);
	pa2m_afirmar(pokemon_info == NULL, "No hay pokemon seleccionado para el Jugador 2.");

	tp_destruir(tp);
}

void pruebas_imprimir_pistas_vacias(){
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	imprimir_pista(tp);

	tp_destruir(tp);
}

void pruebas_imprimir_pistas_con_obstaculos(){
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	enum TP_OBSTACULO obstaculo1 = OBSTACULO_FUERZA;
	unsigned posicion1 = aleatoria(MAX_LARGO_PISTA, 0);

	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo1, posicion1) == 1, "Hay 1 obstáculo en la pista del Jugador 1.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo1, posicion1) == 1, "Hay 1 obstáculo en la pista del Jugador 2.");

	enum TP_OBSTACULO obstaculo2 = OBSTACULO_DESTREZA;
	unsigned posicion2 = aleatoria(MAX_LARGO_PISTA, 0);

	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo2, posicion2) == 2, "Hay 2 obstáculos en la pista del Jugador 1.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo2, posicion2) == 2, "Hay 2 obstáculos en la pista del Jugador 2.");

	enum TP_OBSTACULO obstaculo3 = OBSTACULO_INTELIGENCIA;
	unsigned posicion3 = aleatoria(MAX_LARGO_PISTA, 0);

	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo3, posicion3) == 3, "Hay 3 obstáculos en la pista del Jugador 1.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo3, posicion3) == 3, "Hay 3 obstáculos en la pista del Jugador 2.");

	imprimir_pista(tp);

	tp_destruir(tp);
}

void pruebas_limpiar_pista_con_obstaculos(){
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	enum TP_OBSTACULO obstaculo1 = OBSTACULO_FUERZA;
	unsigned posicion1 = aleatoria(MAX_LARGO_PISTA, 0);

	tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo1, posicion1);
	tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo1, posicion1);

	enum TP_OBSTACULO obstaculo2 = OBSTACULO_DESTREZA;
	unsigned posicion2 = aleatoria(MAX_LARGO_PISTA, 0);

	tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo2, posicion2);
	tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo2, posicion2);

	enum TP_OBSTACULO obstaculo3 = OBSTACULO_INTELIGENCIA;
	unsigned posicion3 = aleatoria(MAX_LARGO_PISTA, 0);

	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo3, posicion3) == 3, "Hay 3 obstáculos en la pista del Jugador 1.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo3, posicion3) == 3, "Hay 3 obstáculos en la pista del Jugador 2.");

	imprimir_pista(tp);

	printf("\nLimpiando pista de Jugador 1...");

	tp_limpiar_pista(tp, JUGADOR_1);

	pa2m_afirmar(cant_obstaculos_actual_jugador(tp, JUGADOR_1) == 0, "No hay obstáculos en la pista del Jugador 1.");

	imprimir_pista(tp);

	printf("\nLimpiando pista de Jugador 2...");

	tp_limpiar_pista(tp, JUGADOR_2);

	pa2m_afirmar(cant_obstaculos_actual_jugador(tp, JUGADOR_2) == 0, "No hay obstáculos en la pista del Jugador 2.");

	imprimir_pista(tp);

	tp_destruir(tp);
}

void pruebas_quitar_obstaculo_de_pista(){
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	enum TP_OBSTACULO obstaculo1 = OBSTACULO_FUERZA;
	unsigned posicion1 = aleatoria(MAX_LARGO_PISTA, 0);

	tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo1, posicion1);
	tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo1, posicion1);

	enum TP_OBSTACULO obstaculo2 = OBSTACULO_DESTREZA;
	unsigned posicion2 = aleatoria(MAX_LARGO_PISTA, 0);
	
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo2, posicion2) == 2, "Hay 2 obstáculos en la pista del Jugador 1.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo2, posicion2) == 2, "Hay 2 obstáculos en la pista del Jugador 2.");

	imprimir_pista(tp);

	pa2m_afirmar(tp_quitar_obstaculo(tp, JUGADOR_1, posicion1) == 1, "Quitar deja 1 obstáculo en la pista del Jugador 1.");

	imprimir_pista(tp);

	pa2m_afirmar(tp_quitar_obstaculo(tp, JUGADOR_2, posicion2) == 1, "Quitar deja 1 obstáculo en la pista del Jugador 2.");

	imprimir_pista(tp);

	tp_destruir(tp);
}

void pruebas_string_con_obstaculos_de_cada_pista(){
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	enum TP_OBSTACULO obstaculo1 = OBSTACULO_FUERZA;
	unsigned posicion1 = aleatoria(MAX_LARGO_PISTA, 0);

	tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo1, posicion1);
	tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo1, posicion1);

	enum TP_OBSTACULO obstaculo2 = OBSTACULO_DESTREZA;
	unsigned posicion2 = aleatoria(MAX_LARGO_PISTA, 0);

	tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo2, posicion2);

	enum TP_OBSTACULO obstaculo3 = OBSTACULO_INTELIGENCIA;
	unsigned posicion3 = aleatoria(MAX_LARGO_PISTA, 0);
	
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo2, posicion2) == 2, "Hay 2 obstáculos en la pista del Jugador 1.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo3, posicion3) == 3, "Hay 3 obstáculos en la pista del Jugador 2.");

	imprimir_pista(tp);

	char *obstaculos = tp_obstaculos_pista(tp, JUGADOR_1);

	printf("\nObstáculos en la pista del Jugador 1: %s\n", obstaculos);

	free(obstaculos);

	char *obstaculos2 = tp_obstaculos_pista(tp, JUGADOR_2);

	printf("\nObstáculos en la pista del Jugador 2: %s\n", obstaculos2);

	free(obstaculos2);

	tp_destruir(tp);
}

void pruebas_calcular_tiempo_pista(){
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	const char* nombre1 = "Pikachu";
	const struct pokemon_info *poke1 = tp_buscar_pokemon(tp, nombre1);
	tp_seleccionar_pokemon(tp, JUGADOR_1, "Pikachu");
	pa2m_afirmar(strcmp(poke1->nombre, "Pikachu") == 0, "El pokemon seleccionado por el Jugador 1 es Pikachu.");

	const char* nombre2 = "Bulbasaur";
	const struct pokemon_info *poke2 = tp_buscar_pokemon(tp, nombre2);
	tp_seleccionar_pokemon(tp, JUGADOR_2, "Bulbasaur");
	pa2m_afirmar(strcmp(poke2->nombre, "Bulbasaur") == 0, "El pokemon seleccionado por el Jugador 2 es Bulbasaur.");

	enum TP_OBSTACULO obstaculo1 = OBSTACULO_FUERZA;
	unsigned posicion1 = aleatoria(MAX_LARGO_PISTA, 0);
	tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo1, posicion1);
	tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo1, posicion1);

	enum TP_OBSTACULO obstaculo2 = OBSTACULO_DESTREZA;
	unsigned posicion2 = aleatoria(MAX_LARGO_PISTA, 0);
	tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo2, posicion2);
	tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo2, posicion2);

	enum TP_OBSTACULO obstaculo3 = OBSTACULO_INTELIGENCIA;
	unsigned posicion3 = aleatoria(MAX_LARGO_PISTA, 0);

	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo3, posicion3) == 3, "Hay 3 obstáculos en la pista del Jugador 1.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo3, posicion3) == 3, "Hay 3 obstáculos en la pista del Jugador 2.");

	imprimir_pista(tp);

	printf("\nTiempo pista Jugador 1: %d", tp_calcular_tiempo_pista(tp, JUGADOR_1));
	printf("\nTiempo pista Jugador 2: %d", tp_calcular_tiempo_pista(tp, JUGADOR_2));

	tp_destruir(tp);
}

void pruebas_csv_tiempo_pista(){
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	const char* nombre1 = "Pikachu";
	const struct pokemon_info *poke1 = tp_buscar_pokemon(tp, nombre1);
	tp_seleccionar_pokemon(tp, JUGADOR_1, "Pikachu");
	pa2m_afirmar(strcmp(poke1->nombre, "Pikachu") == 0, "El pokemon seleccionado por el Jugador 1 es Pikachu.");

	const char* nombre2 = "Bulbasaur";
	const struct pokemon_info *poke2 = tp_buscar_pokemon(tp, nombre2);
	tp_seleccionar_pokemon(tp, JUGADOR_2, "Bulbasaur");
	pa2m_afirmar(strcmp(poke2->nombre, "Bulbasaur") == 0, "El pokemon seleccionado por el Jugador 2 es Bulbasaur.");


	enum TP_OBSTACULO obstaculo1 = OBSTACULO_FUERZA;
	unsigned posicion1 = aleatoria(MAX_LARGO_PISTA, 0);

	tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo1, posicion1);
	tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo1, posicion1);

	enum TP_OBSTACULO obstaculo2 = OBSTACULO_DESTREZA;
	unsigned posicion2 = aleatoria(MAX_LARGO_PISTA, 0);

	tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo2, posicion2);

	enum TP_OBSTACULO obstaculo3 = OBSTACULO_INTELIGENCIA;
	unsigned posicion3 = aleatoria(MAX_LARGO_PISTA, 0);
	
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo2, posicion2) == 2, "Hay 2 obstáculos en la pista del Jugador 1.");
	pa2m_afirmar(tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo3, posicion3) == 3, "Hay 3 obstáculos en la pista del Jugador 2.");

	imprimir_pista(tp);

	char *obstaculos = tp_tiempo_por_obstaculo(tp, JUGADOR_1);

	printf("\nTiempo por obstáculo en la pista del Jugador 1: %s\n", obstaculos);

	free(obstaculos);

	char *obstaculos2 = tp_tiempo_por_obstaculo(tp, JUGADOR_2);

	printf("\nTiempo por obstáculo en la pista del Jugador 2: %s\n", obstaculos2);

	free(obstaculos2);

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

	return pa2m_mostrar_reporte();
}