#include "threadpool.hpp"

ThreadPool::ThreadPool(int workerSize){
    for(int i = 0; i < workerSize; ++i){
    
        std::jthread thread([this](std::stop_token stoken)
            {
                while(true){
                    if(stoken.stop_requested()){
                        return;
                    }
                    this->getTask(stoken)();
                }
            }
        );
        
        this->workers.push_back(std::move(thread));
    }
}

std::function<void()> ThreadPool::getTask(std::stop_token stoken){
    auto task = this->tasks.pop(stoken);

    if(!task.has_value()){return []{};}
    
    return task.value();
}
void ThreadPool::enqueue(std::function<void()> task){
    this->tasks.push(std::move(task));
}

ThreadPool::~ThreadPool(){
    for(auto &worker: this->workers){
        worker.request_stop();
    }
}