#pragma once

#include<iostream>
#include<memory>
#include<thread>
#include<vector>
#include<queue>
#include<functional>

#include "../utils/concurrency.hpp"

class ThreadPool{
    private:
        std::vector<std::jthread> workers;
        utils::concurrency::ThreadSafeQueue<std::function<void()>> tasks;

    public:
        ThreadPool(int workerSize);
        
        std::function<void()> getTask(std::stop_token stoken);
        void enqueue(std::function<void()> task);
        ~ThreadPool();
        
};