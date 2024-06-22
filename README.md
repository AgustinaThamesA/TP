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





A continuación, se muestra un diagrama que grafica el uso de memoria en mi implementación:

<div align="center">
<img width="70%" src="img/stack_heap_tp_final.drawio.svg">
</div>



---

## Respuestas a las preguntas teóricas
-   Explique la estructura interna del tda **TP**. Explique por qué utilizó esa estructura.
-   Justifique la complejidad de las operaciones implementadas.
