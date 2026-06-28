# Proyecto Semáforo — Filósofos Comelones Concurrentes

Simulación concurrente del problema clásico de los Filósofos Comelones en C++17, con tres estrategias anti-deadlock implementadas mediante el patrón Strategy. Desarrollado para el curso de Sistemas Operativos.

---

## Tecnologías

- **C++17**
- **std::thread**, **std::mutex**, **std::condition_variable**
- **Visual Studio 2022**

## Compilar y ejecutar

1. Abrir `Proyecto-Semaforo.sln` en Visual Studio 2022
2. Compilar: `Ctrl + Shift + B`
3. Ejecutar: `Ctrl + F5`
4. Seleccionar estrategia en consola (1, 2 o 3)

## Estrategias disponibles

| Opción | Estrategia | Mecanismo |
|---|---|---|
| 1 | Sin interbloqueo | `std::lock` — adquiere ambos tenedores atómicamente |
| 2 | Asimétrica | Filósofos pares: derecho→izquierdo; impares: izquierdo→derecho |
| 3 | Mesero (Waiter) | Semáforo central limita a N−1 filósofos comiendo simultáneamente |

## Ciclo de vida de un filósofo

```
pensando → programando → hambriento → comiendo → pensando
```

## Arquitectura

| Componente | Rol |
|---|---|
| `Philosopher` | Hilo concurrente; ciclo de vida completo |
| `Fork` | Recurso compartido protegido con `std::mutex` |
| `Strategy` | Interfaz base (patrón Strategy) |
| `NoDeadlockStrategy` | Implementa `std::lock` |
| `AsymmetricStrategy` | Orden asimétrico de adquisición |
| `Waiter` / `WaiterStrategy` | Control centralizado con `condition_variable` |
| `Logger` | Registro sincronizado con colores ANSI por estado |
| `Metrics` | Registra tiempos y frecuencias; exporta CSV |

## Salida en consola (colores por estado)

| Estado | Color |
|---|---|
| pensando | Fucsia |
| programando | Azul |
| hambriento | Rojo |
| comiendo | Verde |

## Métricas

Cada ejecución genera `resultados.csv` con columnas:

```
id | estado | timestamp | duracion_ms
```

Los datos permiten comparar tiempo promedio por estado, frecuencia de comidas y concurrencia efectiva entre estrategias.

---

Desarrollado por **David Joel Soto Zuñiga** y **Jeimy Espinoza Barquero**
Curso: Sistemas Operativos — Universidad Nacional de Costa Rica, 2025
