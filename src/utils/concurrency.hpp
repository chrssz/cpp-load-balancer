#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
/*A collection of utils for Concurrency Programming*/

namespace utils::concurrency{

    template<class T>
    class ThreadSafeQueue{
        private:
            std::queue<T> queue;
            std::mutex mtx;
            
            std::condition_variable_any cv;
        public:
            ThreadSafeQueue();
            bool empty();
            int size();
            void push(T data);
            T pop(std::stop_token stoken);
            ~ThreadSafeQueue();  
    };


};

#include "concurrency.tpp"