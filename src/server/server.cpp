#include "server.hpp"

Server::Server(){}
void Server::start(std::string PORT_NUMBER){
    this->port_number = PORT_NUMBER;
}
int Server::getConnCount(){
    return this->poll_fds.size();
}
std::string Server::getPort(){
    if(this->port_number.empty()){
        return "ERROR";
    }
    return this->port_number;
}
Server::~Server(){}