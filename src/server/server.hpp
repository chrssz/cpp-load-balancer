#pragma once

#include <iostream>
#include <memory>
#include "../socket/socket.hpp"
#include "../threadpool/threadpool.hpp"
#include "../connectionhandler/connectionhandler.hpp"

class Server {
    protected:
        std::string port_number;
        std::vector<WSAPOLLFD> poll_fds; //Required for WSAPolling.
    public:
        Server();
        virtual void start(std::string PORT_NUMBER);
        int getConnCount();
        std::string getPort();
        ~Server();
};

class HttpServer : public Server {
    private:
        ThreadPool threadpool; 
    public:
        HttpServer(int theadPoolSize);
        void start(std::string PORT_NUMBER) override;
        ~HttpServer();    
};

class LoadBalServer : public Server{
    public:
        LoadBalServer();
        void start(std::string PORT_NUMBER) override;
        ~LoadBalServer();
};