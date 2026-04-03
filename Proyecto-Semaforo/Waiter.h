#pragma once
#include <mutex>
#include <condition_variable>

class Waiter {
private:
    int maxAllowed;
    int currentEating;
    std::mutex mtx;
    std::condition_variable cv;

public:
    Waiter(int maxAllowed) : maxAllowed(maxAllowed), currentEating(0) {}

    void solicitarPermiso() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return currentEating < maxAllowed; });
        currentEating++;
    }

    void liberarPermiso() {
        std::lock_guard<std::mutex> lock(mtx);
        currentEating--;
        cv.notify_all();
    }
};
