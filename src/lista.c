#include "lista.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *nodo_inicio;
	nodo_t *nodo_final;
	size_t espacios;
};

struct lista_iterador {
	nodo_t *actual;
	lista_t *lista;
	nodo_t *anterior;
	int sarasa;
};

lista_t *lista_crear()
{
	lista_t *lista = malloc(sizeof(lista_t));
	if (lista == NULL) {
		return NULL;
	}
	lista->nodo_inicio = NULL;
	lista->nodo_final = NULL;
	lista->espacios = 0;

	return lista;
}

nodo_t *nuevo_nodo(void *elemento)
{
	nodo_t *nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL)
		return NULL;

	nodo->elemento = elemento;
	nodo->siguiente = NULL;

	return nodo;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (lista == NULL)
		return NULL;
	nodo_t *nodo = nuevo_nodo(elemento);

	if (nodo == NULL)
		return NULL;

	if (lista->espacios == 0) {
		lista->nodo_inicio = nodo;
		lista->nodo_final = nodo;
		lista->espacios = 1;
		return lista;
	}

	lista->nodo_final->siguiente = nodo;
	lista->nodo_final = nodo;
	(lista->espacios) += 1;

	return lista;
}

nodo_t *lista_nodo_en_posicion(lista_t *lista, size_t posicion)
{
	if (lista == NULL)
		return NULL;

	nodo_t *nodo = lista->nodo_inicio;
	if (nodo == NULL)
		return NULL;

	size_t i = 0;

	if (posicion >= lista->espacios) {
		nodo = lista->nodo_final;
	}

	while (i < posicion) {
		nodo = nodo->siguiente;
		i++;
	}

	return nodo;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (lista == NULL)
		return NULL;

	if (lista->espacios == 0 || posicion >= lista->espacios) {
		return lista_insertar(lista, elemento);
	}

	nodo_t *nodo = nuevo_nodo(elemento);

	if (nodo == NULL)
		return NULL;

	if (posicion == 0) {
		nodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo;
	} else {
		nodo_t *nodo_anterior =
			lista_nodo_en_posicion(lista, posicion - 1);
		if (nodo_anterior == NULL) {
			free(nodo);
			return NULL;
		}
		nodo->siguiente = nodo_anterior->siguiente;
		nodo_anterior->siguiente = nodo;
	}

	(lista->espacios)++;

	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if (lista == NULL || lista->espacios == 0)
		return NULL;

	nodo_t *nodo_a_quitar = lista->nodo_final;
	if (nodo_a_quitar == NULL)
		return NULL;

	size_t i = lista->espacios;
	if (lista->espacios == 1)
		i = 2;

	lista->nodo_final = lista_nodo_en_posicion(lista, i - 2);
	if (lista->nodo_final != NULL)
		lista->nodo_final->siguiente = NULL;

	void *elemento = nodo_a_quitar->elemento;
	free(nodo_a_quitar);
	(lista->espacios)--;

	if (lista->espacios == 0) {
		lista->nodo_inicio = NULL;
		lista->nodo_final = NULL;
	}

	return elemento;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (lista == NULL || lista->espacios == 0)
		return NULL;

	nodo_t *nodo_a_eliminar = NULL;

	if (posicion >= lista->espacios) {
		return lista_quitar(lista);
	}

	if (posicion == 0) {
		nodo_a_eliminar = lista->nodo_inicio;
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
	} else {
		nodo_t *predecesor =
			lista_nodo_en_posicion(lista, posicion - 1);
		if (predecesor == NULL || predecesor->siguiente == NULL)
			return NULL;

		nodo_a_eliminar = predecesor->siguiente;
		predecesor->siguiente = nodo_a_eliminar->siguiente;
	}
	void *elemento = nodo_a_eliminar->elemento;
	free(nodo_a_eliminar);
	(lista->espacios)--;

	if (lista->espacios == 0) {
		lista->nodo_inicio = NULL;
		lista->nodo_final = NULL;
	}

	return elemento;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (lista == NULL || posicion >= lista->espacios)
		return NULL;

	nodo_t *nodo = lista_nodo_en_posicion(lista, posicion);

	if (nodo == NULL)
		return NULL;

	return nodo->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if (lista == NULL || comparador == NULL)
		return NULL;

	nodo_t *nodo = lista->nodo_inicio;

	while (nodo != NULL) {
		if (comparador(nodo->elemento, contexto) == 0)
			return nodo->elemento;
		nodo = nodo->siguiente;
	}

	return NULL;
}

void *lista_primero(lista_t *lista)
{
	if (lista == NULL || lista->espacios == 0)
		return NULL;

	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if (lista == NULL || lista->espacios == 0)
		return NULL;

	return lista->nodo_final->elemento;
}

bool lista_vacia(lista_t *lista)
{
	return lista == false || lista->espacios == 0 ||
	       lista->nodo_inicio == NULL || lista->nodo_final == NULL;
}

size_t lista_tamanio(lista_t *lista)
{
	if (lista == NULL || lista->espacios == 0)
		return 0;

	return lista->espacios;
}

void lista_destruir(lista_t *lista)
{
	if (lista == NULL)
		return;

	nodo_t *nodo = lista->nodo_inicio;

	while (nodo != NULL) {
		nodo_t *nodo_siguiente = nodo->siguiente;
		free(nodo);
		nodo = nodo_siguiente;
	}
	free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if (lista == NULL)
		return;

	nodo_t *nodo = lista->nodo_inicio;

	while (nodo != NULL) {
		nodo_t *nodo_siguiente = nodo->siguiente;
		if (funcion != NULL) {
			funcion(nodo->elemento);
		}
		free(nodo);
		nodo = nodo_siguiente;
	}
	free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (lista == NULL)
		return 0;

	lista_iterador_t *lista_iterador = malloc(sizeof(lista_iterador_t));

	if (lista_iterador == NULL)
		return NULL;

	lista_iterador->lista = lista;
	lista_iterador->actual = lista->nodo_inicio;

	return lista_iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	return (iterador != NULL && iterador->actual != NULL);
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (!lista_iterador_tiene_siguiente(iterador) || iterador == NULL) {
		return false;
	}
	if ((iterador->actual = iterador->actual->siguiente))
		return true;
	return false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if (iterador == NULL)
		return NULL;
	if (lista_iterador_tiene_siguiente(iterador))
		return iterador->actual->elemento;

	return NULL;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	if (iterador != NULL)
		free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (lista == NULL || lista->espacios == 0 || funcion == NULL)
		return 0;

	nodo_t *nodo = lista->nodo_inicio;
	size_t cant_elementos_iterados = 0;
	bool continuo_iterando = true;

	while (nodo != NULL && cant_elementos_iterados < lista->espacios &&
	       continuo_iterando) {
		continuo_iterando = funcion(nodo->elemento, contexto);

		nodo = nodo->siguiente;
		cant_elementos_iterados++;
	}

	return cant_elementos_iterados;
}