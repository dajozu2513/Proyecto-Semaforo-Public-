# Traffic Light Project — Concurrent Dining Philosophers

Concurrent simulation of the classic Dining Philosophers problem in C++17, featuring three anti-deadlock strategies implemented using the Strategy pattern. Developed for the Operating Systems course.

---

## Technologies

- **C++17**
- **std::thread**, **std::mutex**, **std::condition_variable**
- **Visual Studio 2022**

## Build and Run

1. Open `Proyecto-Semaforo.sln` in Visual Studio 2022
2. Build: `Ctrl + Shift + B`
3. Run: `Ctrl + F5`
4. Select a strategy from the console (1, 2, or 3)

## Available Strategies

| Option | Strategy | Mechanism |
|---|---|---|
| 1 | Deadlock-free | `std::lock` — acquires both forks atomically |
| 2 | Asymmetric | Even philosophers: right→left; odd philosophers: left→right |
| 3 | Waiter | Central semaphore limits to N−1 philosophers eating simultaneously |

## Philosopher Lifecycle

```
thinking → scheduling → hungry → eating → thinking
```

## Architecture

| Component | Role |
|---|---|
| `Philosopher` | Concurrent thread; full lifecycle |
| `Fork` | Shared resource protected with `std::mutex` |
| `Strategy` | Base interface (Strategy pattern) |
| `NoDeadlockStrategy` | Implements `std::lock` |
| `AsymmetricStrategy` | Asymmetric acquisition order |
| `Waiter` / `WaiterStrategy` | Centralized control with `condition_variable` |
| `Logger` | Synchronized logging with ANSI colors per state |
| `Metrics` | Records timings and frequencies; exports CSV |

## Console Output (colors by state)

| State | Color |
|---|---|
| thinking | Magenta |
| scheduling | Blue |
| hungry | Red |
| eating | Green |

## Metrics

Each run generates `resultados.csv` with columns:

```
id | state | timestamp | duration_ms
```

The data allows comparing average time per state, eating frequency, and effective concurrency across strategies.

---

Developed by **David Joel Soto Zuñiga** and **Jeimy Espinoza Barquero**
Course: Operating Systems — Universidad Nacional de Costa Rica, 2025
