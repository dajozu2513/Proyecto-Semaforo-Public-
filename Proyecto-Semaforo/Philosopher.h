#pragma once
#include <thread>
#include <atomic>
#include <chrono>
#include <string>
#include "Fork.h"
#include "Logger.h"
#include "Strategy.h"
#include "Metrics.h"

class Philosopher {
private:
    int id;
    Fork& leftFork;
    Fork& rightFork;
    Logger& logger;
    Strategy& strategy;
    Metrics& metrics;
    std::atomic<bool> running;
    std::thread t;

public:
    Philosopher(int id, Fork& left, Fork& right, Logger& logger, Strategy& strategy, Metrics& metrics);
    void start();
    void stop();
    void run();
};
