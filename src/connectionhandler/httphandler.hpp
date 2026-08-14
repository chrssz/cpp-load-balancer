#pragma once
#include "connectionhandler.hpp"

#include "../server/httpserver.hpp"
#include "../httpparse/parse.hpp"
#include "../httpparse/response.hpp"

class HttpServerHandler : public ConnectionHandler{
    public:
        HttpServerHandler();
        Response handleRequest(const Request& req);
        void handle(std::shared_ptr<ConnectedSocket> conn) override;
        ~HttpServerHandler();
};