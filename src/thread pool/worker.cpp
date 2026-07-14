#include "worker.h"

Worker::Worker(){}

bool Worker::isAvailable(){
    return this->available;
}

void Worker::doTask(std::function<void()> &&task){
    std::function<void()> toDo = std::move(task);
    this->available = false;
    //Clean this up with RAII In the future...
    try{
        toDo();
    } catch(std::string err) {
        std::cout << "Error doing task " << err << std::endl;
        this->available = true;
        
        return;
    }
}
Worker::~Worker(){}