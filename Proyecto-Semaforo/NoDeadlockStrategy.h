#pragma once
#include "Strategy.h"
#include "Logger.h"
#include "Metrics.h"
#include <thread>
#include <chrono>
#include <mutex>

class NoDeadlockStrategy : public Strategy {
private:
    Logger& logger;
    Metrics& metrics;

public:
    NoDeadlockStrategy(Logger& logger, Metrics& metrics)
        : logger(logger), metrics(metrics) {
    }

    void comer(int id, Fork& left, Fork& right) override {
        using namespace std::chrono_literals;

        std::unique_lock<std::mutex> leftLock(left.mtx, std::defer_lock);
        std::unique_lock<std::mutex> rightLock(right.mtx, std::defer_lock);

        std::lock(leftLock, rightLock);

        logger.log(id, "tomo ambos tenedores");
        logger.log(id, "comiendo");

        metrics.finalizarEspera(id);
        metrics.incrementarComida(id);

        std::this_thread::sleep_for(500ms);
    }
};
