Proyecto: Filósofos Comelones Concurrentes

Curso: Sistemas Operativos  
Autores: David Joel Soto Zuñiga y Jeimy Espinoza Barquero
Lenguaje: C++17  
Entorno: Visual Studio 2022  
Fecha: 14/11/2025

---

Cómo compilar y ejecutar

1. Abre el proyecto en Visual Studio 2022.  
2. Compila con `Ctrl + Shift + B`.  
3. Ejecuta con `Ctrl + F5`.  
4. En consola, selecciona una estrategia:

Sin interbloqueo (std::lock)

Estrategia Asimétrica

Estrategia del Mesero (Waiter)

5. Los resultados en consola incluyen colores por estado y las métricas se guardan automáticamente en el archivo 'resultados.cvs'.

---

Arquitectura del sistema

| Componente | Descripción |
|-------------|-------------|
| Philosopher | Ejecuta cada hilo concurrente; controla el ciclo de vida de cada filósofo. |
| Fork | Recurso compartido protegido con `std::mutex`. |
| Logger | Registro sincronizado de estados con colores en consola. |
| Strategy | Interfaz base para las estrategias anti-deadlock. |
| AsymmetricStrategy | Evita el interbloqueo alternando el orden de toma de tenedores (pares e impares). |
| Waiter | Controlador central que gestiona permisos para comer. |
| WaiterStrategy | Implementa la estrategia del mesero utilizando un semáforo interno. |
| NoDeadlockStrategy | Usa `std::lock` para tomar ambos tenedores a la vez sin riesgo de interbloqueo. |
| Metrics | Registra tiempos y frecuencias de cada estado en CSV. |

---

Ciclo de vida de un filósofo

Los filósofos alternan entre los siguientes estados:

pensando → programando → hambriento → comiendo → pensando

Tabla de transiciones (estado extra: *programando*)

| Estado anterior | Transición | Estado siguiente | Descripción |
|------------------|-------------|------------------|-------------|
| pensando | → | programando | El filósofo pasa de reflexión a acción. |
| programando | → | hambriento | Termina su tarea y busca recursos. |
| hambriento | → | comiendo | Obtiene ambos tenedores. |
| comiendo | → | pensando | Libera recursos y reflexiona nuevamente. |

---

Estrategias anti-deadlock implementadas

1. Sin interbloqueo (std::lock)
Usa `std::lock` para bloquear ambos tenedores de forma atómica.  
Evita el ciclo de espera mutua al adquirir ambos recursos al mismo tiempo.

2. Estrategia Asimétrica
Cada filósofo toma los tenedores en distinto orden:
- Filósofos pares: primero el derecho, luego el izquierdo.  
- Filósofos impares: primero el izquierdo, luego el derecho.

Esto rompe el ciclo circular de dependencia entre procesos, eliminando el riesgo de interbloqueo.

Estrategia del Mesero (Waiter)
Introduce un controlador centralizado que solo permite comer a un máximo de N−1 filósofos al mismo tiempo.  
El mesero gestiona los permisos mediante un semáforo (`std::condition_variable`).

Ventajas:
- Evita interbloqueo.
- Garantiza justicia (ningún filósofo pasa hambre).
- Control central fácil de extender.

---

Colores en consola

| Estado | Color | Significado |
|---------|--------|-------------|
| pensando | Fucsia | Estado reflexivo / creativo |
| programando | Azul | Acción lógica / productiva |
| hambriento | Rojo | Espera activa / necesidad de recursos |
| comiendo | Verde | Ejecución exitosa / satisfacción |

---

Métricas y logs

Cada ejecución genera un archivo CSV denominado 'resultados.cvs'.

Formato del CSV:

| id | estado | timestamp | duracion_ms |
|----|---------|------------|--------------|
| 0 | programando | 13:22:05 | 310 |
| 0 | hambriento | 13:22:06 | 120 |
| 0 | comiendo | 13:22:06 | 500 |

Los datos se usaron para calcular el tiempo promedio en cada estado, la frecuencia de comidas y la concurrencia efectiva por estrategia.

---

Conclusiones

- Todas las estrategias implementadas previenen el interbloqueo, cumpliendo los objetivos del proyecto.  
- La estrategia del mesero garantiza justicia absoluta, pero añade sobrecarga de sincronización.  
- La asimétrica es ligera y eficiente, con un patrón de ejecución natural y libre de espera circular.  
- El uso del estado extra (*programando*) aporta una visión más realista del ciclo de ejecución.  
- El patrón Strategy permitió alternar comportamientos sin modificar la estructura base del sistema.  
- El proyecto demuestra dominio de hilos, mutex, sincronización, y diseño modular en C++ moderno.

---

Ejemplo de ejecución

Proyecto Semaforo Operativos
Seleccione la estrategia:

Sin interbloqueo (std::lock)

Estrategia Asimetrica

Estrategia del Mesero (Waiter)
Opcion: 3

Usando Estrategia del Mesero
Filosofo 0 está pensando
Filosofo 1 está programando
Filosofo 2 está hambriento
Filosofo 2 recibió permiso del mesero
Filosofo 2 está comiendo
...

---

Estructura del repositorio

Proyecto-Semaforo/
│
├── Archivos de encabezado/
│ ├── AsymmetricStrategy.h
│ ├── Fork.h
│ ├── Logger.h
│ ├── Metrics.h
│ ├── NoDeadlockStrategy.h
│ ├── Philosopher.h
│ ├── Strategy.h
│ ├── Waiter.h
│ └── WaiterStrategy.h
│
├── Archivos de origen/
│ ├── Fork.cpp
│ ├── Logger.cpp
│ ├── Metrics.cpp
│ ├── Philosopher.cpp
│ └── Proyecto-Semaforo.cpp
│
├── metrics/
│ ├── resultados.cvs
│
└── README.md

---

Créditos

Proyecto desarrollado por David Joel Soto Zuñiga y Jeimy Espinoza Barquero
para el curso de Sistemas Operativos.  
Universidad Nacional de Costa Rica — 2025.