#pragma once

#include <iostream>
#include <memory>
#include<vector>
#include "../socket/socket.hpp"

class Server {
    protected:
        int id;
        int total_connections = 0;
        int current_connections = 0;
        std::string port_number;
        
    public:
        Server(int id);
        virtual void start(std::string PORT_NUMBER);
        int getId();
        int getTotalConns();
        std::string getPort();
        virtual ~Server();
};
