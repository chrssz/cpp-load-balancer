#pragma once

#include<iostream>
#include<memory>
#include<thread>
#include<vector>
#include<queue>
#include<functional>

#include "worker.hpp"

class ThreadPool{
    private:
        std::queue<std::function<void()>> tasks;
        std::vector<Worker> workers;
        
    public:
        ThreadPool(int workerSize);
        std::function<void()> getTask();
        void enqueue(std::function<void()> task);
        ~ThreadPool();
        
};