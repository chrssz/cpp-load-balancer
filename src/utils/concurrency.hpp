#pragma once

#include <queue>

/*A collection of utils for Concurrency Programming*/

namespace utils::concurrency{

    template<class T>
    class ThreadSafeQueue{
        private:
            std::queue<T> queue;
        public:
            ThreadSafeQueue();
            ~ThreadSafeQueue();  
    };


};

#include "concurrency.tpp"