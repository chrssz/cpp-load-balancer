#pragma once

#include <iostream>
#include <memory>
#include<vector>
#include "../socket/socket.hpp"

class Server {
    protected:
        std::string port_number;
    public:
        Server();
        virtual void start(std::string PORT_NUMBER);
        std::string getPort();
        ~Server();
};
