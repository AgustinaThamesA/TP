#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

nodo_abb_t *nodo_crear(void *elemento)
{
	nodo_abb_t *nodo = calloc(1,sizeof(nodo_abb_t));
	if (nodo == NULL) {
		return NULL;
	}
	nodo->elemento = elemento;
	nodo->izquierda = NULL;
	nodo->derecha = NULL;
	return nodo;
}

abb_t *abb_crear(abb_comparador comparador)
{
	abb_t *abb = calloc(1,sizeof(abb_t));
	if (abb == NULL || comparador == NULL) {
		free(abb);
		return NULL;
	}
	abb->comparador = comparador;
	abb->tamanio = 0;
	abb->nodo_raiz = NULL;
	return abb;
}

nodo_abb_t *abb_insertar_recursivo(abb_t *arbol, nodo_abb_t *nodo_actual,
				   void *elemento)
{
	if (arbol == NULL || !(arbol->comparador))
		return NULL;

	if (nodo_actual == NULL) {
		nodo_abb_t *nodo_aux = nodo_crear(elemento);
		if (nodo_aux == NULL)
			return NULL;
		return nodo_aux;
	}

	if (arbol->comparador(elemento, nodo_actual->elemento) <= 0) {
		nodo_actual->izquierda = abb_insertar_recursivo(
			arbol, nodo_actual->izquierda, elemento);
	} else {
		nodo_actual->derecha = abb_insertar_recursivo(
			arbol, nodo_actual->derecha, elemento);
	}

	return nodo_actual;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL)
		return NULL;

	arbol->nodo_raiz =
		abb_insertar_recursivo(arbol, arbol->nodo_raiz, elemento);
	(arbol->tamanio)++;
	return arbol;
}

void borrar_hoja(nodo_abb_t **nodo)
{
	nodo_abb_t *aux = (*nodo);
	free(aux);
	(*nodo) = NULL;
	return;
}

void borrar_1_hijo(nodo_abb_t **nodo)
{
	nodo_abb_t *aux = (*nodo);
	if (!(*nodo)->izquierda) {
		(*nodo) = aux->derecha;
		free(aux);
		return;
	}
	if (!(*nodo)->derecha) {
		(*nodo) = aux->izquierda;
		free(aux);
		return;
	}
}

void borrar_2_hijos(nodo_abb_t **nodo)
{
	nodo_abb_t *aux = (*nodo);
	nodo_abb_t **sucesor = &(aux->izquierda);

	if (!(*sucesor)->derecha) {
		(*sucesor)->derecha = aux->derecha;
		(*nodo) = (*sucesor);
		free(aux);
		return;
	}
	while ((*sucesor)->derecha) {
		sucesor = &(*sucesor)->derecha;
	}
	(*nodo) = (*sucesor);
	(*sucesor) = (*sucesor)->izquierda;
	(*nodo)->izquierda = aux->izquierda;
	(*nodo)->derecha = aux->derecha;
	free(aux);
}

void borrar_nodo(nodo_abb_t **nodo)
{
	if (!(*nodo)->izquierda && !(*nodo)->derecha) {
		borrar_hoja(nodo);
		return;
	}

	if (!(*nodo)->izquierda || !(*nodo)->derecha) {
		borrar_1_hijo(nodo);
		return;
	}

	borrar_2_hijos(nodo);
}

void *arbol_borrar_recursivo(abb_t *arbol, void *elemento, nodo_abb_t **nodo)
{
	if (!arbol || !arbol->comparador)
		return NULL;
	if (!nodo || !*nodo)
		return NULL;

	if ((arbol->comparador)(elemento, (*nodo)->elemento) == 0) {
		void *aux = (*nodo)->elemento;
		borrar_nodo(nodo);
		return aux;
	}

	if ((arbol->comparador)(elemento, (*nodo)->elemento) >= 0)
		return arbol_borrar_recursivo(arbol, elemento,
					      &((*nodo)->derecha));

	return arbol_borrar_recursivo(arbol, elemento, &((*nodo)->izquierda));
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (abb_vacio(arbol))
		return NULL;
	if (abb_buscar(arbol, elemento) == NULL)
		(arbol->tamanio)++;

	(arbol->tamanio)--;
	return arbol_borrar_recursivo(arbol, elemento, &(arbol->nodo_raiz));
}

void *buscar_nodo_abb(nodo_abb_t *nodo, void *elemento,
		      abb_comparador comparador)
{
	if (nodo == NULL) {
		return NULL;
	}

	if (comparador(elemento, nodo->elemento) < 0) {
		return buscar_nodo_abb(nodo->izquierda, elemento, comparador);
	} else if (comparador(elemento, nodo->elemento) > 0) {
		return buscar_nodo_abb(nodo->derecha, elemento, comparador);
	} else if (comparador(elemento, nodo->elemento) == 0) {
		return nodo->elemento;
	} else {
		return NULL;
	}
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL || arbol->comparador == NULL || elemento == NULL)
		return NULL;
	return buscar_nodo_abb(arbol->nodo_raiz, elemento, arbol->comparador);
}

bool abb_vacio(abb_t *arbol)
{
	return (arbol == NULL || arbol->nodo_raiz == NULL ||
		abb_tamanio(arbol) == 0);
}

size_t abb_tamanio(abb_t *arbol)
{
	if (arbol == NULL)
		return 0;
	return arbol->tamanio;
}

void destruir_nodo_abb(abb_t *arbol, nodo_abb_t *nodo)
{
	if (nodo == NULL || arbol == NULL)
		return;

	if (nodo->izquierda != NULL)
		destruir_nodo_abb(arbol, nodo->izquierda);

	if (nodo->derecha != NULL)
		destruir_nodo_abb(arbol, nodo->derecha);

	free(nodo);
}

void abb_destruir(abb_t *arbol)
{
	if (arbol == NULL)
		return;
	if (arbol->nodo_raiz != NULL) {
		destruir_nodo_abb(arbol, arbol->nodo_raiz);
	}

	free(arbol);
	arbol = NULL;
}

void destruir_todo_nodo_abb(abb_t *arbol, nodo_abb_t *nodo,
			    void (*destructor)(void *))
{
	if (nodo == NULL || arbol == NULL)
		return;

	if (nodo->izquierda != NULL)
		destruir_todo_nodo_abb(arbol, nodo->izquierda, destructor);

	if (nodo->derecha != NULL)
		destruir_todo_nodo_abb(arbol, nodo->derecha, destructor);

	if (destructor != NULL && nodo->elemento != NULL)
		destructor(nodo->elemento);

	free(nodo);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (arbol == NULL)
		return;
	if (arbol->nodo_raiz)
		destruir_todo_nodo_abb(arbol, arbol->nodo_raiz, destructor);

	free(arbol);
	arbol = NULL;
}

bool inorden_con_cada_elemento(nodo_abb_t *nodo, size_t tamanio,
			       bool (*funcion)(void *, void *), void *aux,
			       size_t *iteraciones)
{
	if (nodo == NULL)
		return true;

	bool continua_iterando = inorden_con_cada_elemento(
		nodo->izquierda, tamanio, funcion, aux, iteraciones);

	if (!continua_iterando)
		return false;

	(*iteraciones)++;
	if (funcion(nodo->elemento, aux) == false)
		return false;

	return inorden_con_cada_elemento(nodo->derecha, tamanio, funcion, aux,
					 iteraciones);
}

bool preorden_con_cada_elemento(nodo_abb_t *nodo, size_t tamanio,
				bool (*funcion)(void *, void *), void *aux,
				size_t *iteraciones)
{
	if (nodo == NULL)
		return true;

	(*iteraciones)++;

	if (funcion(nodo->elemento, aux) == false)
		return false;

	bool continua_iterando = preorden_con_cada_elemento(
		nodo->izquierda, tamanio, funcion, aux, iteraciones);

	if (!continua_iterando)
		return false;

	return preorden_con_cada_elemento(nodo->derecha, tamanio, funcion, aux,
					  iteraciones);
}

bool postorden_con_cada_elemento(nodo_abb_t *nodo, size_t tamanio,
				 bool (*funcion)(void *, void *), void *aux,
				 size_t *iteraciones)
{
	if (nodo == NULL)
		return true;

	bool continua_iterando = postorden_con_cada_elemento(
		nodo->izquierda, tamanio, funcion, aux, iteraciones);

	if (!continua_iterando)
		return false;

	continua_iterando = postorden_con_cada_elemento(
		nodo->derecha, tamanio, funcion, aux, iteraciones);

	if (!continua_iterando)
		return false;

	(*iteraciones)++;

	if (funcion(nodo->elemento, aux) == false)
		return false;

	return continua_iterando;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (abb_vacio(arbol) || funcion == NULL)
		return 0;

	size_t iteraciones = 0;

	switch (recorrido) {
	case INORDEN:
		inorden_con_cada_elemento(arbol->nodo_raiz, arbol->tamanio,
					  funcion, aux, &iteraciones);
		break;
	case PREORDEN:
		preorden_con_cada_elemento(arbol->nodo_raiz, arbol->tamanio,
					   funcion, aux, &iteraciones);
		break;
	case POSTORDEN:
		postorden_con_cada_elemento(arbol->nodo_raiz, arbol->tamanio,
					    funcion, aux, &iteraciones);
		break;
	}

	return iteraciones;
}

void inorden_recorrer(nodo_abb_t *nodo_actual, void **array,
		      size_t tamanio_array, size_t *contador)
{
	if (!nodo_actual || *contador >= tamanio_array)
		return;

	inorden_recorrer(nodo_actual->izquierda, array, tamanio_array,
			 contador);

	if (*contador < tamanio_array) {
		array[*contador] = nodo_actual->elemento;
		*contador = *contador + 1;
	}

	inorden_recorrer(nodo_actual->derecha, array, tamanio_array, contador);
}

void preorden_recorrer(nodo_abb_t *nodo_actual, void **array,
		       size_t tamanio_array, size_t *contador)
{
	if (!nodo_actual || *contador >= tamanio_array)
		return;

	if (*contador < tamanio_array) {
		array[*contador] = nodo_actual->elemento;
		*contador = *contador + 1;
	}

	preorden_recorrer(nodo_actual->izquierda, array, tamanio_array,
			  contador);

	preorden_recorrer(nodo_actual->derecha, array, tamanio_array, contador);
}

void postorden_recorrer(nodo_abb_t *nodo_actual, void **array,
			size_t tamanio_array, size_t *contador)
{
	if (!nodo_actual || *contador >= tamanio_array)
		return;

	postorden_recorrer(nodo_actual->izquierda, array, tamanio_array,
			   contador);

	postorden_recorrer(nodo_actual->derecha, array, tamanio_array,
			   contador);

	if (*contador < tamanio_array) {
		array[*contador] = nodo_actual->elemento;
		*contador = *contador + 1;
	}
}

void abb_recorrer_rec(nodo_abb_t *nodo_actual, abb_recorrido recorrido,
		      void **array, size_t tamanio_array, size_t *contador)
{
	if (!nodo_actual || *contador >= tamanio_array)
		return;

	switch (recorrido) {
	case PREORDEN:
		preorden_recorrer(nodo_actual, array, tamanio_array, contador);
		break;

	case INORDEN:
		inorden_recorrer(nodo_actual, array, tamanio_array, contador);
		break;

	case POSTORDEN:
		postorden_recorrer(nodo_actual, array, tamanio_array, contador);
		break;

	default:
		break;
	}
	return;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	size_t contador = 0;
	if (arbol && array)
		abb_recorrer_rec(arbol->nodo_raiz, recorrido, array,
				 tamanio_array, &contador);
	return contador;
}