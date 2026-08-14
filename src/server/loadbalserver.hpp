#pragma once
#include "server.hpp"
#include "../connectionhandler/loadbhandler.hpp"
class LoadBalServer : public Server{
    private:
        std::vector<std::unique_ptr<Server>> servers = {};
    public:
        LoadBalServer(int id);
        std::vector<std::unique_ptr<Server>>& getServerList();
        void addServer(std::unique_ptr<Server> server);
        void start(std::string PORT_NUMBER) override;
        ~LoadBalServer();
};