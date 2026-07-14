#include "threadpool.h"

ThreadPool::ThreadPool(int workerSize){
    for(int i = 0; i < workerSize; ++i){
        Worker worker;
        this->workers.push_back(std::move(worker));
    }
}

/*
    For Start:
        Goal: Assign available workers to tasks
            #Method 1 is to check if queue has any tasks, if so 
                #iterate through workers to find available worker.
                    #What if none are available.. we continue loop. This can be Costly
        #*Waiting for ongoing tasks can be costly. This is true for all listeners

    #TODO: Address the cpu cost for all listeners, (in main, here in start, and connectedSockets)
           Investiagate a startegy to avoid a O(T_SIZE * N_WORKERS) time complexity check.
           Handle worker.h try-except. Approach it with a RAII design to keep code clean.
*/
void ThreadPool::start(){
    while(true){
        if(this->tasks.size() > 0){
            //Run this task
            
        }
    }
}
void ThreadPool::enqueue(std::function<void()> task){
    this->tasks.push(std::move(task));
}

ThreadPool::~ThreadPool(){
    //Clear Queue.

}