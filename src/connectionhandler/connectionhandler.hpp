#pragma once

#include <memory>
#include "../socket/socket.hpp"

class ConnectionHandler{
    public:
        ConnectionHandler();
        virtual void handle(std::shared_ptr<ConnectedSocket> conn) = 0;
        ~ConnectionHandler();
};

