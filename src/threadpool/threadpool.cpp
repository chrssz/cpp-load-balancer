#include "threadpool.hpp"

ThreadPool::ThreadPool(int workerSize){
    for(int i = 0; i < workerSize; ++i){
        std::unique_ptr<Worker> worker = std::make_unique<Worker>(i);
        
        worker->doTask([this]{
            return getTask();
        });
        //Vector workers needs to be changed to take in unique_ptrs of workers. FIX
        this->workers.push_back(std::move(worker));
    }
}

/*
    IMPORTANT GET CMAKE GOING PROJECT IS GETTING LARGE: DO ON MY NEXT CODING SESSION

    Task Thread Pool Assignmet.
        .Notify an available worker to pick up the task using Worker.doTask(std::move(this->getTask()))
    
*/
std::function<void()> ThreadPool::getTask(){
    if(this->tasks.size() == 0){
        return {};
    }
    std::function<void()> func = std::move(this->tasks.front());
    this->tasks.pop();
    return func;
}
void ThreadPool::enqueue(std::function<void()> task){
    this->tasks.push(std::move(task));
}

ThreadPool::~ThreadPool(){}