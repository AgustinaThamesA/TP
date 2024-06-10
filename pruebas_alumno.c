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

    
	for (int j = 0; j < 3; j++) {
		enum TP_OBSTACULO obstaculo;
		switch (j) {
		case 0:
			obstaculo = OBSTACULO_FUERZA;
			break;
		case 1:
			obstaculo = OBSTACULO_DESTREZA;
			break;
		case 2:
			obstaculo = OBSTACULO_INTELIGENCIA;
			break;
		}
		unsigned posicion = aleatoria(MAX_LARGO_PISTA, 0);
		tp_agregar_obstaculo(tp, JUGADOR_1, obstaculo, posicion);
		tp_agregar_obstaculo(tp, JUGADOR_2, obstaculo, posicion);
	}


	imprimir_pista(tp);

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

	return pa2m_mostrar_reporte();
}