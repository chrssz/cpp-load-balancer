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
        int id;
    public:
        Worker(int id);
        bool isAvailable();
        void doTask(std::function<void()> &&task);
        ~Worker();
};
    