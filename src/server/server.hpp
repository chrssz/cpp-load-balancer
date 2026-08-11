#pragma once

#include <iostream>
#include <memory>
#include<vector>
#include "../socket/socket.hpp"

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
