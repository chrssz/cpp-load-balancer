#include "threadpool.hpp"

ThreadPool::ThreadPool(int workerSize){
    for(int i = 0; i < workerSize; ++i){
        Worker worker(i);
        this->workers.push_back(std::move(worker));
    }
}

/*
    IMPORTANT GET CMAKE GOING PROJECT IS GETTING LARGE: DO ON MY NEXT CODING SESSION

    Task Thread Pool Assignmet.
        1. Server.cpp, listening socket will be in charge of only establishing connected sockets.
        2. When a socket establishes, its enqueued to thread pool.
            .Notify an available worker to pick up the task using Worker.doTask(std::move(this->getTask()))
        
        #Notes: Our queue, is not thread safe. Server.cpp modifies, and workers getTask modify it. 
                Potential Solutions: Make a custom safe queue which utilizes mutexes.(More core, More files, Clean and modular threadpool doesnt controll mutexes)
                Add In mutexes into thread pool (less Code, makes code complex, doesn't make a queue safe.)
*/
std::function<void()> ThreadPool::getTask(){
    if(this->tasks.size() == 0){
        return nullptr;
    }
    std::function<void()> func = std::move(this->tasks.front());

    return func;
}
void ThreadPool::enqueue(std::function<void()> task){
    this->tasks.push(std::move(task));
}

ThreadPool::~ThreadPool(){
    
}