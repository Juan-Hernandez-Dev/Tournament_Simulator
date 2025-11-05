# Mini Simulador de Torneo

## Descripción
Sistema de simulación de torneos con eliminación simple usando estructuras de datos propias (cola circular y árbol binario).

## Autor
- Juan Hernández (ID: 552652)
- Fecha: 2025-11-04

## Compilación

```bash
g++ -std=c++11 main.cpp player_queue.cpp bracket.cpp -o tournament
```

## Ejecución

```bash
./tournament
```

## Requisitos
- Archivo `jugadores.txt` en el mismo directorio
- Un nombre de jugador por línea
- Mínimo recomendado: 8 jugadores

## Estructura del Proyecto

```
├── main.cpp           # Programa principal
├── player.h           # Definición de jugador
├── player_queue.h     # Interfaz de cola
├── player_queue.cpp   # Implementación de cola circular
├── bracket.h          # Interfaz de árbol de torneo
├── bracket.cpp        # Implementación del bracket
├── jugadores.txt      # Archivo de jugadores
└── README.md          # Este archivo
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