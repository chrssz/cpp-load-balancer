#include <memory>
#include "../socket/socket.hpp"
#include "../httpparse/parse.hpp"
#include "../httpparse/response.hpp"

class ConnectionHandler{
    public:
        ConnectionHandler();
        virtual void handle(std::shared_ptr<ConnectedSocket> conn) = 0;
        //Handles a request, and creates a response.
        Response handleRequest(const Request& req);
        ~ConnectionHandler();
};

class HttpServerHandler : public ConnectionHandler{
    public:
        HttpServerHandler();
        void handle(std::shared_ptr<ConnectedSocket> conn) override;
        ~HttpServerHandler();
};

class LoadBalanceHandler : public ConnectionHandler{
    public:
        LoadBalanceHandler();
        void handle(std::shared_ptr<ConnectedSocket> conn) override;
        ~LoadBalanceHandler();
};