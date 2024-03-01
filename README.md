# Programación III: Proyecto Final

## Integrantes
* *Gino Jesus Daza Yalta*

## Generador y Visualizador de Laberintos

Este programa ofrece una experiencia interactiva para explorar y comparar los algoritmos de búsqueda en un laberinto. Su funcionalidad principal se centra en la generación de laberintos de un solo camino o con múltiples caminos, y la visualización de cómo los algoritmos de búsqueda, como Dijkstra, BFS (Breadth-First Search) y DFS (Depth-First Search), encuentran la salida.

## Características Principales

1. **Generación de Laberintos:**
   - Crea laberintos con un solo camino o con diferentes caminos para proporcionar diversas configuraciones de prueba.
   - Configuración interactiva para elegir el tipo de laberinto y sus dimensiones.

2. **Visualización de Algoritmos de Búsqueda:**
   - Implementación de los algoritmos Dijkstra, BFS y DFS para encontrar la salida del laberinto.
   - Animaciones visuales que muestran cómo los algoritmos exploran el espacio de búsqueda.

3. **Comparación de Tiempos:**
   - Muestra el tiempo que cada algoritmo tarda en encontrar la salida en diferentes configuraciones de laberintos.
   - Facilita la comparación de rendimiento entre los algoritmos en casos específicos.

4. **Interfaz Gráfica Atractiva:**
   - Utiliza SFML para crear una interfaz gráfica intuitiva y atractiva.
   - Permite interactuar con la aplicación mientras observas el progreso de los algoritmos.

## Uso

- Tamaño: Para cambiar el tamaño se pulsan los botones "--" "-" "+" "++", para aumentar o disminuir las filas o columnas.
- Laberinto: Para crear el laberinto se debe seleccionar el tipo de laberinto y luego pulsar la tecla "Enter".
- Entrada: Hacer clic izquierdo sobre un cuadro en el laberinto.
- Salida: Hacer clic derecho sobre un cuadro en el laberinto.
- Algoritmo y tiempo: Para correr un algoritmo se debe hacer clic sobre el nombre del algoritmo, esto mostrara la ruta seguida por el algoritmo y el tiempo en el que termino.
- Velocidad: Permite cambiar entre velocidades de visualizacion del algoritmo.
- Extra: El boton "prev" es para volver en matrices anteriores o deshacer el algoritmo ejecutado.

## Teclas especiales
- Para crear el laberinto se debe pulsar la tecla "Enter".
- Se puede aumentar el alto de la ventana con la flecha abajo.
- Con la tecla "c" se regresa al tamaño original.
- Con la tecla "d" se remueven todos los obstaculos del laberinto.
- Con el clic izquierdo en el laberinto se selecciona la entrada.
- Con el clic derecho en el laberinto se selecciona la salida.
- Con el clic de la rueda de raton se puede poner un obstaculo.

## Requisitos:
* Se necesita la libreria SFML 2.5.0
* El programa necesita como minimo dos hilos en el procesador, uno para dibujar la interfaz y otro para correr cada algoritmo

## Proyecto programación III
### Objetivos a cumplir
* El programa debe de generar un mapa con obstáculos, en donde pueden existir varios caminos para llegar de un lugar a otro. :white_check_mark:
* El programa debe de generar un mapa con un laberinto, en donde solo existe un camino para llegar de un punto a otro. :white_check_mark:
* El programa debe tener la opción de seleccionar el punto de partida, el destino, y el tamanó del mapa. :white_check_mark:
* Implementar los algoritmos Dijkstra, BFS y DFS y comparar sus tiempos de ejecución. :white_check_mark:
* (+) Crear un DEMO para a su programa. :white_check_mark:
### Rubrica:
* Se utilizo el patron de diseño Memento(boton prev) y Singleton(crear un solo menu).
* Se utilizo concurrencia, un hilo dibuja la interfaz y el otro modifica el laberinto.
* Programacion generica solo fue usado en la consola mientras se construian los algoritmos en un metodo llamado "print_matrix" y tenia necesidad de ver las distintas matrices(bool, int, float).
