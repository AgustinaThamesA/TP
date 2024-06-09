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
	printf("%p", (void*)poke);
/*
	bool seleccionado = tp_seleccionar_pokemon(tp, JUGADOR_1, "Pikachu");
	pa2m_afirmar(seleccionado == true, "Selecciono a Pikachu como pokemon del Jugador 1.");

	seleccionado = tp_seleccionar_pokemon(tp, JUGADOR_2, "Pikachu");
	pa2m_afirmar(seleccionado == false, "El Jugador 2 no puede elegir a Pikachu como su pokemon, porque ese pokemon le pertenece al Jugador 1.");

	seleccionado = tp_seleccionar_pokemon(tp, JUGADOR_2, "Charmander");
	pa2m_afirmar(seleccionado == true, "Selecciono a Charmander como pokemon del Jugador 2.");

	seleccionado = tp_seleccionar_pokemon(tp, JUGADOR_1, "Charmander");
	pa2m_afirmar(seleccionado == false, "El Jugador 1 no puede elegir a Charmander como su pokemon, porque ese pokemon le pertenece al Jugador 2.");

*/

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
/*
void pruebas_imprimir_pista_vacia(){
	TP *tp = tp_crear("ejemplo/pokemones.txt");

	unsigned total_obstaculos = tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_FUERZA, 0);
	pa2m_afirmar(total_obstaculos == 1, "Se agregó correctamente un obstáculo de fuerza a la pista del Jugador 1.");
	//imprimir_pista(tp, JUGADOR_1);

	total_obstaculos = tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_DESTREZA, 1);
	pa2m_afirmar(total_obstaculos == 2, "Se agregó correctamente un obstáculo de destreza a la pista del Jugador 1.");
	//imprimir_pista(tp, JUGADOR_1);

	total_obstaculos = tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_INTELIGENCIA, 2);
	pa2m_afirmar(total_obstaculos == 3, "Se agregó correctamente un obstáculo de fuerza a la pista del Jugador 1.");
	//imprimir_pista(tp, JUGADOR_1);

	total_obstaculos = tp_agregar_obstaculo(tp, JUGADOR_1, OBSTACULO_FUERZA, 30);
	pa2m_afirmar(total_obstaculos == 0, "No se puede agregar un obstáculo fuera de los límites de la pista.");
	//imprimir_pista(tp, JUGADOR_1);

	total_obstaculos = tp_agregar_obstaculo(tp, -1, OBSTACULO_DESTREZA, 4);
	pa2m_afirmar(total_obstaculos == 0, "No se puede agregar un obstáculo a la pista de un jugador inválido.");
	//imprimir_pista(tp, JUGADOR_1);
	
	tp_destruir(tp);
}

*/

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
	//pruebas_tp_pokemon_seleccionado();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de pista ========================");
	//pruebas_imprimir_pista_vacia();

	return pa2m_mostrar_reporte();
}
