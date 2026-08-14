#include "server.hpp"

Server::Server(int id) : id(id){}
void Server::start(std::string PORT_NUMBER){
    this->port_number = PORT_NUMBER;
}
int Server::getId(){
    return this->id;
}
int Server::getTotalConns(){
    return this->total_connections;
}
std::string Server::getPort(){
    if(this->port_number.empty()){
        return "ERROR";
    }
    return this->port_number;
}
Server::~Server(){}