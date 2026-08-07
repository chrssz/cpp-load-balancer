#pragma once

#include <iostream>
#include <memory>
#include "../socket/socket.hpp"
#include "../threadpool/threadpool.hpp"
#include "../connectionhandler/connectionhandler.hpp"

class Server {
    public:
        Server();
        virtual void start(std::string PORT_NUMBER);
        ~Server();
};

class HttpServer : public Server {
    private:
        private:
        std::vector<WSAPOLLFD> poll_fds; //Required for WSAPolling.
        ThreadPool threadpool; 
    
    public:
        HttpServer(int theadPoolSize);
        void start(std::string PORT_NUMBER) override;
        ~HttpServer();    
};

class LoadBalServer : public Server{
    private:
        std::vector<WSAPOLLFD> poll_fds;
    public:
        LoadBalServer();
        void start(std::string PORT_NUMBER) override;
        ~LoadBalServer();
};