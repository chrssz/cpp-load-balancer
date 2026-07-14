#pragma once

#include <iostream>
#include <memory>
#include <thread>
#include <atomic>
#include <functional>

class Worker{
    private:
        std::atomic<bool> available = true;
        std::jthread thread;

    public:
        Worker();
        bool isAvailable();
        void doTask(std::function<void()> &&task);
        ~Worker();
};
    