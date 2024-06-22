# TP: Carrera de obstáculos

## Repositorio de Agustina Thames Alderete - 111287 - athames@fi.uba.ar

- Para ejecutar con valgrind usando mis pruebas:

```bash
make valgrind-alumno
```

- Para ejecutar con valgrind usando el archivo juego.c, el cual ejecuta la carrera de obstáculos:
```bash
make 
```
---
##  Funcionamiento

En este TP integrador, se implementa una carrera de obstáculos de pokemones, en la cual el usuario interactúa mediante ciertos comandos por terminal, respondiendo con lo que se le pide para crear su propia pista, etc.

Si bien en el enunciado del TP se recomienda implementar un TDA menú, en mi TP no lo hice, ya que manejo todo lo que necesito desde el struct TP. 

A tener en cuenta:

- El archivo juego.c únicamente contiene el main que se ejecuta al correr el juego utilizando 'make'. 
- El archivo tp_auxiliares.c contiene todas las funciones (y sus auxiliares) que se utilicen en la ejecución del juego.

Lo que plantea mi juego es que el usuario pueda elegir su pokemón, que seleccione la dificultad a la que se enfrentarán ambos pokemones (del jugador y de la computadora), y que cree su pista a su gusto. Cuando se está creando la pista, se le pide al jugador que elija el largo de la pista y las posiciones de los obstáculos. Sin embargo, no será informado sobre el tipo de cada obstáculo, eso se hace aleatorio tras bambalinas. 

Luego, se muestran ambas pistas y comienza la carrera. Si bien los movimientos de los pokemones en las pistas no se muestran, se va mostrando la velocidad, el tiempo transcurrido y la distancia recorrida de cada pokemon. 

Cuando se ejecuta juego.c, y el usuario tiene que interactuar a través de la consola, se le va informando las cosas necesarias, y le va pidiendo que cargue valores según lo que corresponda. El comportamiento del usuario debe seguir el siguiente diagrama:

<div align="center">
<img width="70%" src="img/diagrama_juego_tp_final.drawio.svg">
</div>

---

### Funcionamiento general de funciones de tp.c
#### `tp_crear(const char *nombre_archivo)`

Esta función intenta crear una estructura `TP` (la estructura principal para el juego) a partir de un archivo cuyo nombre se pasa como parámetro.

- Verifica que `nombre_archivo` no sea NULL.
- Luego verifica que el archivo tenga la extensión ".txt".
- Crea un objeto `TP` y lo inicializa.
- Abre el archivo para lectura y llama a `leer_archivo` para procesar su contenido.
- Para cada jugador (2 jugadores en total), inicializa una estructura `pista_jugador_t` y una lista de obstáculos (`pista`) utilizando las funciones ya implementadas del TDA Lista.
- Inicializa algunos campos de la estructura `pista_jugador_t` y llama a `pista_vacia`.
- Finalmente, devuelve el objeto `TP` creado.

#### `tp_cantidad_pokemon(TP *tp)`
Retorna la cantidad de pokemon almacenados en una estructura `TP`.

#### `tp_buscar_pokemon(TP *tp, const char *nombre)`
Busca un pokemon por nombre dentro de la estructura `TP`.

#### `tp_nombres_disponibles(TP *tp)`
Retorna una cadena con los nombres de todos los pokemon disponibles.

#### `tp_seleccionar_pokemon(TP *tp, enum TP_JUGADOR jugador, const char *nombre)`
Permite a un jugador seleccionar un pokemon.

#### `tp_pokemon_seleccionado(TP *tp, enum TP_JUGADOR jugador)`
Retorna el Pokemon seleccionado por un jugador.

#### `tp_agregar_obstaculo(TP *tp, enum TP_JUGADOR jugador, enum TP_OBSTACULO obstaculo, unsigned posicion)`
Agrega un obstáculo a la pista de un jugador.

#### `tp_quitar_obstaculo(TP *tp, enum TP_JUGADOR jugador, unsigned posicion)`
Quita un obstáculo de la pista de un jugador.

#### `tp_obstaculos_pista(TP *tp, enum TP_JUGADOR jugador)`
Retorna los obstáculos presentes en la pista de un jugador.

#### `tp_limpiar_pista(TP *tp, enum TP_JUGADOR jugador)`
Limpia la pista de un jugador.

#### `tp_calcular_tiempo_pista(TP *tp, enum TP_JUGADOR jugador)`
Calcula el tiempo total que tardará un jugador en completar la pista.

#### `tp_tiempo_por_obstaculo(TP *tp, enum TP_JUGADOR jugador)`
Retorna el tiempo que tomará superar cada obstáculo en la pista de un jugador.

#### `tp_destruir(TP *tp)`
Libera toda la memoria asignada para la estructura `TP` y sus elementos.

--- 

A continuación, se muestra un diagrama que grafica el uso de memoria en mi implementación:

<div align="center">
<img width="70%" src="img/stack_heap_tp_final.drawio.svg">
</div>

---

### Decisiones tomadas en el desarrollo del TP integrador

- Se asume que existen definiciones para estructuras como `TP`, `pista_jugador_t`, así como funciones auxiliares como `leer_archivo`, `lista_crear`, `pista_vacia`, entre otras (como `abb_tamanio`, `abb_buscar`, etc.).
- Cada función está diseñada para trabajar con la estructura `TP` y sus componentes (`jugadores`, `pokemones`, etc.) de manera coherente y segura, manejando adecuadamente los casos de error y liberando memoria cuando sea necesario.
- Se utilizan TDAs implementados a los largo de la cursada, ya que las estructuras necesitaban de ciertos tipos de datos que favorecen la implementación según el manejo en las operaciones de cada TDA.

---

### Explicación extra del juego implementado

Si bien no se muestra el progeso de los pokemones en sus respectivas pistas, se muestra información que le permite al usuario imaginarse el progreso de cada uno en el transcurso de la carrera.

Se tomó la decisión de hacer estructuras dentro del TDA TP, ya que la mayoría de los campos se relacionan con otros. Se tuvo en cuenta el orden de utilización de la información guardada en cada estructura. 

Tal como se ve en mi implementación, no existe tal TDA menú, ya que toda la información que necesitaba cada jugador fue guardada en el TDA Tp, tal como se explicó en el párrafo anterior.

---

## Respuestas a las preguntas teóricas
-   Explique la estructura interna del tda **TP**. Explique por qué utilizó esa estructura.
-   Justifique la complejidad de las operaciones implementadas.
