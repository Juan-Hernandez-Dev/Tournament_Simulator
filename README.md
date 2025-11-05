# Mini Simulador de Torneo

## Descripción
Sistema de simulación de torneos con eliminación simple usando estructuras de datos propias (cola circular y árbol binario).

## Autor
- Juan Hernández (ID: 552652)
- Fecha: 2025-11-04

## Compilación
Es necesario tener instalado g++ y cmake para compilar el proyecto.
```bash
./compile_run.bat
```

## Ejecución
Al descargar el proyecto, existe un ejecutable previo en build, puede ejecutarse directamente.
En caso de no existir, run.bat llama a compile_run.bat, sin embargo, compile_run.bat requiere que estén instalados g++ y cmake.
```bash
./run.bat
```

## Ejecución manual (requiere ejecutable previo)
```bash
cd build
./TournamentSim.exe
```

## Requisitos
- Archivo `jugadores.txt` en el mismo directorio
- Un nombre de jugador por línea
- Mínimo recomendado: 8 jugadores

## Estructura del Proyecto

```
Tournament_Simulator/
│   CMakeLists.txt       # CMake configuration file
│   compile_run.bat      # Batch file to compile and run the program
│   jugadores.txt        # File with player names
│   README.md            # This file
│   run.bat              # Batch file to run the program
│
├───.vscode
│       settings.json    # Disable module call warnings, not required for compilation
│
├───include
│       bracket.h        # Bracket definition to build tournament tree
│       player.h         # Player definition
│       player_queue.h   # Circular queue of players
│
├───src
│       bracket.cpp      # Bracket implementation
│       main.cpp         # Main function
│       player_queue.cpp # Circular queue of players implementation
│       text_utils.cpp   # Utility functions implementation
│
└───utils
│       text_utils.h     # Utility functions declaration
```

## Decisiones de Diseño

### Cola Circular
- Implementación propia sin STL
- Arreglo dinámico con punteros front/rear
- Capacidad máxima de 64 jugadores

### Árbol Binario Completo
- Cada hoja representa un jugador
- Nodos internos representan enfrentamientos
- Construcción bottom-up desde las hojas

### Simulación
- Ganadores aleatorios (50/50) con `rand()`
- Semilla basada en tiempo: `srand(time(0))`
- Los jugadores BYE avanzan automáticamente
- Procesamiento por rondas desde hojas hacia raíz

## Ejemplo de Salida

```
REGISTRO (COLA)
[front ->] Ana, Luis, Marta, Pepe, Carlos, Sofia, Miguel, Elena

RONDA 1
(Ana vs Luis) -> Gana: Ana
(Marta vs Pepe) -> Gana: Pepe
(Carlos vs Sofia) -> Gana: Carlos
(Miguel vs Elena) -> Gana: Elena

RONDA 2
(Ana vs Pepe) -> Gana: Pepe
(Carlos vs Elena) -> Gana: Carlos

RONDA 3
(Pepe vs Carlos) -> Gana: Pepe

CAMPEÓN
Pepe
```

## Completado con BYE
Si el número de jugadores no es potencia de 2, se agregan automáticamente participantes "BYE" para completar el bracket.

## Validaciones
- Nombres vacíos son ignorados
- Jugadores duplicados son aceptados (con advertencia en consola)
- Manejo de errores básico en lectura de archivo