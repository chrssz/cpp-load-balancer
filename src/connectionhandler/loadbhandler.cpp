#include "connectionhandler.hpp"

LoadBalanceHandler::LoadBalanceHandler(){}
SOCKET LoadBalanceHandler::getOutBoundConnection(std::string port_number){
    //TODO;
}
HttpServer& LoadBalanceHandler::roundRobin(std::vector<HttpServer>& servers){
    //Simple algorithm; will move algorithms to their own class
    HttpServer& toReturn = servers[this->roundRobinPtr];
    
    this->roundRobinPtr = (this->roundRobinPtr + 1) % servers.size();
    return toReturn;
}
void LoadBalanceHandler::handle(std::shared_ptr<ConnectedSocket> conn){
    std::cout << "Error handling connection, handle requires (conn, serverVector)" << std::endl;
}
void LoadBalanceHandler::handle(std::shared_ptr<ConnectedSocket> conn, std::vector<HttpServer>& servers){
    std::cout << "Load balancer handling new connection!";
    //We need to assign this connection to a server using a algorithm.
    HttpServer& s = roundRobin(servers);
    
}

LoadBalanceHandler::~LoadBalanceHandler(){}
