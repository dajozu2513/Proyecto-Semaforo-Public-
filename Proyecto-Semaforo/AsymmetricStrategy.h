#pragma once
#include "Strategy.h"
#include "Logger.h"
#include "Metrics.h"
#include <thread>
#include <chrono>
#include <mutex>

class AsymmetricStrategy : public Strategy {
private:
    Logger& logger;
    Metrics& metrics;

public:
    AsymmetricStrategy(Logger& logger, Metrics& metrics)
        : logger(logger), metrics(metrics) {
    }

    void comer(int id, Fork& left, Fork& right) override {
        using namespace std::chrono_literals;

        if (id % 2 == 0) {
            std::unique_lock<std::mutex> rightLock(right.mtx);
            logger.log(id, "tomo el tenedor derecho");
            std::this_thread::sleep_for(100ms);

            std::unique_lock<std::mutex> leftLock(left.mtx);
            logger.log(id, "tomo el tenedor izquierdo");
        }
        else {
            std::unique_lock<std::mutex> leftLock(left.mtx);
            logger.log(id, "tomo el tenedor izquierdo");
            std::this_thread::sleep_for(100ms);

            std::unique_lock<std::mutex> rightLock(right.mtx);
            logger.log(id, "tomo el tenedor derecho");
        }

        logger.log(id, "comiendo");

        // Aquí terminó la espera HAMBRIENTO -> COMIENDO
        metrics.finalizarEspera(id);
        metrics.incrementarComida(id);

        std::this_thread::sleep_for(500ms);
    }
};
