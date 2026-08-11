#pragma once
#include "server.hpp"
#include "../connectionhandler/httphandler.hpp"
#include "../threadpool/threadpool.hpp"
class HttpServer : public Server {
    private:
        ThreadPool threadpool; 
    public:
        HttpServer(int theadPoolSize);
        void start(std::string PORT_NUMBER) override;
        ~HttpServer();    
};
