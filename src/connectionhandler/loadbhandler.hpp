#pragma once
#include "connectionhandler.hpp"
#include "../server/httpserver.hpp"
#include "../httpparse/response.hpp"

class LoadBalanceHandler : public ConnectionHandler{
    private:
        std::mutex mtx;
        //Temporary for now
        int roundRobinPtr = 0;
        //Algorithms for choosing a server
        Server& roundRobin(std::vector<std::unique_ptr<Server>>& servers);
    public:
        LoadBalanceHandler();
        std::unique_ptr<ConnectedSocket> getOutBoundConnection(std::string port_number);
        void handle(std::shared_ptr<ConnectedSocket> conn) override;
        void handle(std::shared_ptr<ConnectedSocket> conn,std::vector<std::unique_ptr<Server>>& servers);
        ~LoadBalanceHandler();
};