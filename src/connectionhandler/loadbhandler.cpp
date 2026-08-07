#include "connectionhandler.hpp"

LoadBalanceHandler::LoadBalanceHandler(){}

void LoadBalanceHandler::handle(std::shared_ptr<ConnectedSocket> conn){
    std::cout << "Load balancer handling new connection!";
}
LoadBalanceHandler::~LoadBalanceHandler(){}
