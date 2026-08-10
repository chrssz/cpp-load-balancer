#include "server.hpp"

LoadBalServer::LoadBalServer(){}
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
    
    this->poll_fds.push_back(std::move(poll_fd));
    LoadBalanceHandler connHandle;
    
    while(true){
        //Thread waits here for connection
        int event = WSAPoll(this->poll_fds.data(), this->poll_fds.size(), -1);
        if(event == SOCKET_ERROR){
            std::cout << "WSAPOll failed with error: " << WSAGetLastError() << std::endl;
            break;
        }
        
        if(this->poll_fds[0].revents & POLLRDNORM){
            SOCKET new_conn = accept(listen.getSocket(), nullptr, nullptr);
            
            if (new_conn != SOCKET_ERROR){

                std::shared_ptr<ConnectedSocket> conn = std::make_shared<ConnectedSocket>(new_conn);
                //Load balancer will be singal threaded for now.
                connHandle.handle(std::move(conn));
            }
        }
    }
}
LoadBalServer::~LoadBalServer(){}