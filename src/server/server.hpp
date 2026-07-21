
#pragma once

#include <iostream>
#include <memory>
#include "../socket/socket.hpp"
#include "../threadpool/threadpool.hpp"

class Server {
    private:
        std::vector<WSAPOLLFD> poll_fds; //Required for WSAPolling.
        ThreadPool threadpool; 
        
    public:
        Server(int theadPoolSize);
        void start(std::string PORT_NUMBER);
        ~Server();
};