#pragma once

#include<iostream>
#include<memory>
#include<thread>
#include<vector>
#include<queue>
#include<functional>

#include "worker.h"

class ThreadPool{
    private:
        std::queue<std::function<void()>> tasks;
        std::vector<Worker> workers;
        
    public:
        ThreadPool(int workerSize);
        void start();
        void enqueue(std::function<void()> task);
        
        ~ThreadPool(){}
        
};