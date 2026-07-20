#include "worker.hpp"

Worker::Worker(int id) : id(id){}

bool Worker::isAvailable(){
    return this->available;
}

void Worker::doTask(std::function<void()> &&task){
    //Sleep until notified.
    std::function<void()> toDo = std::move(task);
    this->available = false;

    try{
        std::cout << "Attempting task from Worker " << this->id << std::endl;
        std::jthread thread(toDo); //Run thread task
        std::cout << "Task Ran!";
    } catch(std::string err) {
        std::cout << "Error doing task from Worker " << this->id << "Error: " << err << std::endl;
        this->available = true;
        
        return;
    }
}
Worker::~Worker(){}