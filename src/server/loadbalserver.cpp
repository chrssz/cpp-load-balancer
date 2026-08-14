#include "loadbalserver.hpp"

LoadBalServer::LoadBalServer(int id) : Server(id){}

void LoadBalServer::addServer(std::unique_ptr<Server> server){
    this->servers.push_back(std::move(server));
}
std::vector<std::unique_ptr<Server>>& LoadBalServer::getServerList(){
    return this->servers;
}
void LoadBalServer::start(std::string PORT_NUMBER){
    this->port_number = PORT_NUMBER;
    ListeningSocket listen(PORT_NUMBER);
    
    if(listen.setup() == -1){
        std::cout << "Error starting server" << std::endl;
        return;
    }   
    
    WSAPOLLFD poll_fd{};
    poll_fd.fd = listen.getSocket();
    poll_fd.events = POLLRDNORM;
    
    LoadBalanceHandler connHandle;
    
    while(true){
        //Thread waits here for connection
        int event = WSAPoll(&poll_fd, 1, -1);
        if(event == SOCKET_ERROR){
            std::cout << "WSAPOll failed with error: " << WSAGetLastError() << std::endl;
            break;
        }
        
        if(poll_fd.revents & POLLRDNORM){
            SOCKET new_conn = accept(listen.getSocket(), nullptr, nullptr);
            
            if (new_conn != SOCKET_ERROR){

                std::shared_ptr<ConnectedSocket> conn = std::make_shared<ConnectedSocket>(new_conn);
                //Load balancer will be singal threaded for now.
                connHandle.handle(std::move(conn), this->servers);
            }
            
        }
    }
}
LoadBalServer::~LoadBalServer(){}