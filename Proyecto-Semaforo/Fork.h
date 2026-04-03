#pragma once
#include <mutex>

class Fork {
public:
    std::mutex mtx;
};
