#pragma once
#include "connectionhandler.hpp"
#include "../server/httpserver.hpp"

class LoadBalanceHandler : public ConnectionHandler{
    private:
        //Temporary for now
        int roundRobinPtr = 0;
        //Algorithms for choosing a server
        HttpServer& roundRobin(std::vector<HttpServer>& servers);
    public:
        LoadBalanceHandler();
        std::unique_ptr<ConnectedSocket> getOutBoundConnection(std::string port_number);
        void handle(std::shared_ptr<ConnectedSocket> conn) override;
        void handle(std::shared_ptr<ConnectedSocket> conn,std::vector<HttpServer>& servers);
        ~LoadBalanceHandler();
};