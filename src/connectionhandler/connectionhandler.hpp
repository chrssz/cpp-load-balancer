#include <memory>
#include "../socket/socket.hpp"
#include "../httpparse/parse.hpp"
#include "../httpparse/response.hpp"

class HttpServer; //Forward Declaration, so we can take in the server list as parameters.

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
    private:
        //Temporary for now
        int roundRobinPtr = 0;
        //Algorithms for choosing a server
        HttpServer& roundRobin(std::vector<HttpServer>& servers);
    public:
        LoadBalanceHandler();
        SOCKET getOutBoundConnection(std::string port_number);
        void handle(std::shared_ptr<ConnectedSocket> conn) override;
        void handle(std::shared_ptr<ConnectedSocket> conn,std::vector<HttpServer>& servers);
        ~LoadBalanceHandler();
};