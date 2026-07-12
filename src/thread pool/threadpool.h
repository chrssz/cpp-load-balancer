#pragma once

#include<iostream>
#include<memory>
#include<thread>
#include<vector>
#include<queue>
#include<functional>


class ThreadPool{
    private:
        std::queue<std::function<void()>> tasks;
    public:
        ThreadPool(){}
        ~ThreadPool(){}
        
};