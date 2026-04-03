#pragma once
#include "Strategy.h"
#include "Waiter.h"
#include "Logger.h"
#include "Metrics.h"
#include <thread>
#include <chrono>
#include <mutex>

class WaiterStrategy : public Strategy {
private:
    Logger& logger;
    Waiter& waiter;
    Metrics& metrics;

public:
    WaiterStrategy(Logger& logger, Waiter& waiter, Metrics& metrics)
        : logger(logger), waiter(waiter), metrics(metrics) {
    }

    void comer(int id, Fork& left, Fork& right) override {
        using namespace std::chrono_literals;

        waiter.solicitarPermiso();

        logger.log(id, "recibio permiso del mesero");
        std::unique_lock<std::mutex> leftLock(left.mtx);
        logger.log(id, "tomo el tenedor izquierdo");
        std::this_thread::sleep_for(100ms);

        std::unique_lock<std::mutex> rightLock(right.mtx);
        logger.log(id, "tomo el tenedor derecho");

        logger.log(id, "comiendo");
        metrics.finalizarEspera(id);
        metrics.incrementarComida(id);

        std::this_thread::sleep_for(500ms);

        waiter.liberarPermiso();
    }
};
