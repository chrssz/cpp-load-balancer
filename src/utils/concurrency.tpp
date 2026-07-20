#pragma once

namespace utils::concurrency{
    /* Thread Safe Queue */
    template<class T>
    ThreadSafeQueue<T>::ThreadSafeQueue(){};

    template<class T>
    ThreadSafeQueue<T>::~ThreadSafeQueue(){};
    
    template<class T>
    int ThreadSafeQueue<T>::size(){
        {
            std::lock_guard<std::mutex> lock(this->mtx);
            int size = this->queue.size();
        }
    
        return size;
    }

    template<class T>
    void ThreadSafeQueue<T>::push(T data){
        {
            std::lock_guard lock(this->mtx);
            this->queue.push(data);
        }
        this->cv.notify_one();
    }

    template<class T>
    T ThreadSafeQueue<T>::pop(std::stop_token stoken){
        T output;
        {
            std::unique_lock<std::mutex> lock(this->mtx);
    

            this->cv.wait(lock, stoken, [this]{
                return this->queue.empty() == false;
            });

            if(this->queue.empty()){return nullptr;}
            
            output = std::move(this->queue.front());
            this->queue.pop();
        }

        return output;
    }
}