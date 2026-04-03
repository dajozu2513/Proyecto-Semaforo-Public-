#include "Philosopher.h"
#include <iostream>

Philosopher::Philosopher(int id, Fork& left, Fork& right, Logger& logger, Strategy& strategy, Metrics& metrics)
    : id(id),
    leftFork(left),
    rightFork(right),
    logger(logger),
    strategy(strategy),
    metrics(metrics),
    running(false)
{
}

void Philosopher::start() {
    running = true;
    t = std::thread(&Philosopher::run, this);
}

void Philosopher::stop() {
    running = false;
    if (t.joinable()) t.join();
}

void Philosopher::run() {
    using namespace std::chrono_literals;

    while (running) {
        logger.log(id, "pensando");
        std::this_thread::sleep_for(400ms);

        logger.log(id, "programando");
        std::this_thread::sleep_for(300ms);

        metrics.iniciarEspera(id);
        logger.log(id, "hambriento");

        strategy.comer(id, leftFork, rightFork);
    }
}
