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

Tal como se ve en mi implementación, no existe tal TDA menú, ya que toda la información que necesitaba cada jugador fue guardada en el TDA TP, tal como se explicó en el párrafo anterior.

---

## Respuestas a las preguntas teóricas
### Estructura interna del TDA `TP`

```c
typedef struct pista_jugador {
    lista_t *pista;
    unsigned cant_obstaculos;
    unsigned largo_pista;
    unsigned max_obstaculos;
    int dificultad;
    double velocidad;
} pista_jugador_t;

typedef struct jugadores {
    struct pokemon_info *pokemon_seleccionado[2];
    pista_jugador_t *pista_jugador[2];
} jugadores_t;

struct tp {
    abb_t *pokemones;
    jugadores_t jugadores;
};
```

#### Explicación:

1. **`pista_jugador_t`**:
   - Esta estructura representa la información relacionada con la pista de juego para un jugador.
   - `pista`: Es un puntero a una lista (`lista_t`) que contiene los elementos de la pista (espacios vacíos y obstáculos).
   - `cant_obstaculos`: Número de obstáculos presentes actualmente en la pista.
   - `largo_pista`: Longitud total de la pista.
   - `max_obstaculos`: Máximo número de obstáculos permitidos en la pista.
   - `dificultad`: Nivel de dificultad de la pista.
   - `velocidad`: Velocidad del jugador o del avance en la pista.

2. **`jugadores_t`**:
   - Esta estructura contiene la información relacionada con los jugadores de la carrera de obstáculos. El Jugador 1 es el usuario, y el Jugador 2 es la computadora.
   - `pokemon_seleccionado`: Un array de tamaño 2 que almacena punteros a `pokemon_info`, que representan los pokemones seleccionados para cada jugador.
   - `pista_jugador`: Un array de tamaño 2 que contiene punteros a `pista_jugador_t`, que representan las pistas individuales de cada jugador.

3. **`struct tp`**:
   - Esta es la estructura principal que encapsula todo el TDA `TP`.
   - `pokemones`: Es un puntero a un árbol binario de búsqueda (`abb_t`) que almacena los pokemones disponibles en el juego.
   - `jugadores`: Es un campo que contiene la estructura `jugadores_t`, que a su vez almacena la información específica de los jugadores.

#### Razones por las cuales diseñé esta estructura:

- La estructura `tp` organiza y encapsula todos los datos relacionados con el juego. Agrupa los pokemones en un árbol binario de búsqueda (`pokemones`) para facilitar la búsqueda eficiente por nombre y manejar la colección de pokemon de manera ordenada y estructurada.

- La estructura `jugadores_t` separa la información de cada jugador (`pokemon_seleccionado` y `pista_jugador`) en una entidad específica, lo que facilita la gestión de cada jugador por separado y evita la complejidad de mezclar los datos de ambos jugadores en una sola estructura.

- Esta estructura permite fácilmente agregar nuevas funcionalidades o datos relacionados con el juego. Por ejemplo, podrías extender `pista_jugador_t` para incluir más detalles sobre la pista o mejorar `jugadores_t` para manejar más jugadores si el juego así lo requiriera en el futuro.

- Utilizar estructuras de datos tales como listas (`lista_t`) y árboles (`abb_t`) permite manejar eficientemente grandes cantidades de datos (por ejemplo, muchos pokemon o muchos obstáculos en una pista) con operaciones rápidas de búsqueda, inserción y eliminación.


### Complejidad de las operaciones implementadas
##### `tp_crear()`
- Complejidad: O(n) -> donde n es el tamaño del archivo, debido a la operación strrchr y strcmp. La función `leer_archivo` tiene su propia complejidad dependiente de la implementación.

##### `tp_cantidad_pokemon()`
- Complejidad: O(log n) -> que corresponde a la complejidad de la operación `abb_tamanio()`

##### `tp_buscar_pokemon()`
- Complejidad: O(log n) -> que corresponde a la complejidad de la operación `abb_buscar()`

##### `tp_nombres_disponibles()`
- Complejidad: O(n), donde n es el número de elementos en el abb de pokemones, debido a la función `abb_con_cada_elemento`.

##### `tp_seleccionar_pokemon()`
- Complejidad: O(log n), donde n es el número de elementos en el abb de pokemones, debido a la llamada a la función `tp_buscar_pokemon`.

##### `tp_pokemon_seleccionado()`
- Complejidad: O(log n), donde n es el número de elementos en el abb de pokemones, debido a la llamada a la función `tp_buscar_pokemon`.

##### `tp_agregar_obstaculo()`
- Complejidad: depende de las operaciones de lista utilizadas, como `lista_elemento_en_posicion`, `lista_quitar_de_posicion`, y `lista_insertar_en_posicion`.

##### `tp_quitar_obstaculo()`
- Complejidad: depende de las operaciones de lista utilizadas, como `lista_elemento_en_posicion` y `lista_quitar_de_posicion`.

##### `tp_obstaculos_pista()`
- Complejidad: O(n), debido a la operación de lista utilizada `lista_elemento_en_posicion`.

##### `tp_limpiar_pista()`
- Complejidad: O(n), donde n es el número de elementos en la lista de la pista del jugador, debido a la operación de lista utilizada `lista_quitar`.

##### `tp_calcular_tiempo_pista()`
- Complejidad: O(n), donde n es el número de elementos en la lista de la pista del jugador, debido a la operación de lista utilizada `lista_elemento_en_posicion`.

##### `tp_tiempo_por_obstaculo()`
- Complejidad: O(n), donde n es el número de elementos en la lista de la pista del jugador, debido a la operación de lista utilizada `lista_elemento_en_posicion`.

##### `tp_destruir()`
- Complejidad: O(n + m), donde n es el número de elementos en el árbol binario de búsqueda tp->pokemones y m es el número de elementos en las listas de tp->jugadores.
