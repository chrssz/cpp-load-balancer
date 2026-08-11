#pragma once
#include "server.hpp"
#include "../connectionhandler/loadbhandler.hpp"
class LoadBalServer : public Server{
    public:
        LoadBalServer();
        void start(std::string PORT_NUMBER) override;
        ~LoadBalServer();
};