#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <memory>
#include <limits>
#include <cstdlib>

#include "Philosopher.h"
#include "Fork.h"
#include "Logger.h"
#include "AsymmetricStrategy.h"
#include "Waiter.h"
#include "WaiterStrategy.h"
#include "NoDeadlockStrategy.h"
#include "Metrics.h"

int main() {
    const int N = 5;
    const int DURACION_SEG = 10;

    while (true) {
        system("cls");

        Logger logger;
        std::vector<Fork> forks(N);
        Waiter waiter(N - 1); // máximo N-1 filósofos intentando comer

        Metrics metrics(N);

        int opcion = -1;

        // === menú ===
        std::cout << "Proyecto Sistemas Operativos\n";
        std::cout << "Seleccione la estrategia:\n";
        std::cout << "1. Sin interbloqueo (std::lock en ambos tenedores)\n";
        std::cout << "2. Estrategia Asimetrica (pares der->izq / impares izq->der)\n";
        std::cout << "3. Estrategia del Mesero (Waiter)\n";
        std::cout << "0. Salir\n";
        std::cout << "Opcion: ";

        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "\nEntrada invalida. Presione ENTER para continuar...";
            std::cin.get();
            std::cin.get();
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (opcion == 0) {
            system("cls");
            std::cout << "Saliendo del simulador.\n";
            std::cout << "Gracias :)\n";
            break;
        }

        if (opcion < 1 || opcion > 3) {
            std::cout << "\nOpcion no valida. Presione ENTER para continuar...";
            std::cin.get();
            continue;
        }
        // === configurar estrategia según opcion ===
        std::unique_ptr<Strategy> strategy;

        switch (opcion) {
        case 1:
            std::cout << "\n> Usando Estrategia SIN INTERBLOQUEO (std::lock)\n";
            strategy = std::make_unique<NoDeadlockStrategy>(logger, metrics);
            break;
        case 2:
            std::cout << "\n> Usando Estrategia ASIMETRICA (pares der->izq / impares izq->der)\n";
            strategy = std::make_unique<AsymmetricStrategy>(logger, metrics);
            break;
        case 3:
            std::cout << "\n> Usando Estrategia del MESERO (Waiter)\n";
            strategy = std::make_unique<WaiterStrategy>(logger, waiter, metrics);
            break;
        }

        if (!strategy) {
            std::cerr << "\nError interno: no se pudo inicializar la estrategia.\n";
            std::cout << "Presione ENTER para volver al menu...";
            std::cin.get();
            continue;
        }

        // === crear filosofos ===
        std::vector<std::unique_ptr<Philosopher>> philosophers;
        philosophers.reserve(N);

        for (int i = 0; i < N; ++i) {
            philosophers.emplace_back(
                new Philosopher(
                    i,
                    forks[i],
                    forks[(i + 1) % N],
                    logger,
                    *strategy,
                    metrics
                )
            );
        }

        // === iniciar simulacion ===
        std::cout << "\nIniciando simulacion con " << N
            << " filosofos durante " << DURACION_SEG
            << " segundos...\n\n";

        for (auto& p : philosophers) {
            p->start();
        }

        std::this_thread::sleep_for(std::chrono::seconds(DURACION_SEG));

        // === detener simulacion ===
        for (auto& p : philosophers) {
            p->stop();
        }

        // ===guardar metricas de esta simulacion ===
        metrics.guardarCSV("resultados.csv");

        // === resumen final ===
        std::cout << "\n---------------------------------\n";
        std::cout << "Simulacion terminada correctamente.\n";
        std::cout << "Resumen:\n";
        std::cout << " - Estrategia usada: "
            << (opcion == 1 ? "Sin interbloqueo (std::lock)"
                : opcion == 2 ? "Asimetrica (par/impar)"
                : "Mesero (Waiter)")
            << "\n";
        std::cout << " - Filosofos: " << N << "\n";
        std::cout << " - Duracion: " << DURACION_SEG << " segundos\n";
        std::cout << " - Estados observables: pensando, programando, hambriento, comiendo\n";
        std::cout << "---------------------------------\n";

        // === pausa antes de volver al menu ===
        std::cout << "\nPresione ENTER para volver al menu...";
        std::cin.get();
    }

    return 0;
}
