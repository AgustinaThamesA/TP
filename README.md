# TP: Carrera de obstáculos

## Repositorio de (Nombre Apellido) - (Padrón) - (Mail)

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

Cuando se ejecuta juego.c, y el usuario tiene que interactuar a tarvés de la consola, se le va informando las cosas necesarias, y le va pidiendo que cargue valores según lo que corresponda.

---

Explicación de cómo funcionan las estructuras desarrolladas en el TP y el funcionamiento general del mismo.

Aclarar en esta parte todas las decisiones que se tomaron al realizar el TP, cosas que no se aclaren en el enunciado, fragmentos de código que necesiten explicación extra, etc.

Incluír **EN TODOS LOS TPS** los diagramas relevantes al problema (mayormente diagramas de memoria para explicar las estructuras, pero se pueden utilizar otros diagramas si es necesario).

### Por ejemplo:

El programa funciona abriendo el archivo pasado como parámetro y leyendolo línea por línea. Por cada línea crea un registro e intenta agregarlo al vector. La función de lectura intenta leer todo el archivo o hasta encontrar el primer error. Devuelve un vector con todos los registros creados.

<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>

En el archivo `sarasa.c` la función `funcion1` utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` lo guardo en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```


<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>

---

## Respuestas a las preguntas teóricas
-   Explique la estructura interna del tda **TP**. Explique por qué utilizó esa estructura.
-   Justifique la complejidad de las operaciones implementadas.
