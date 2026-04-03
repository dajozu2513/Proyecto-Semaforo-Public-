#pragma once
#include <mutex>
#include <iostream>
#include <string>
#include <chrono>

class Logger {
private:
    std::mutex mtx;
    std::chrono::steady_clock::time_point startTime;

public:
    Logger();
    void log(int id, const std::string& action);
};
