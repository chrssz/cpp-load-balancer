#include <memory>
#include "../socket/socket.hpp"
#include "../httpparse/parse.hpp"
#include "../httpparse/response.hpp"

class ConnectionHandler{
    public:
        ConnectionHandler();
        virtual void handle(std::shared_ptr<ConnectedSocket> conn) = 0;
        virtual Response handleRequest(const Request& req) = 0;
        ~ConnectionHandler();
};

class HttpServerHandler : public ConnectionHandler{
    public:
        HttpServerHandler();
        void handle(std::shared_ptr<ConnectedSocket> conn) override;
        Response handleRequest(const Request& req) override;
        ~HttpServerHandler();
};

class LoadBalanceHandler : public ConnectionHandler{
    public:
        LoadBalanceHandler();
        void handle(std::shared_ptr<ConnectedSocket> conn) override;
        ~LoadBalanceHandler();
};