#include "server.h"

Server::Server(): threads(ThreadPool(10)){}
void Server::start(){
    ListeningSocket listen;
    
    initWinSock();

    if(listen.setup() == -1){
        std::cout << "Error starting server" << std::endl;
        return;
    }

    WSAPOLLFD poll_fd{};
    poll_fd.fd = listen.getSocket();
    poll_fd.events = POLLRDNORM;
    
    this->poll_fds.push_back(poll_fd);

    while(true){
        //Thread waits here for connection
        int event = WSAPoll(this->poll_fds.data(), this->poll_fds.size(), -1);
        
        //Thread recieves connection.
        //Todo: Push new_conn along with its fd to vectors.
        SOCKET new_conn = accept(listen.getSocket(), nullptr, nullptr);
        if (new_conn != SOCKET_ERROR){
            std::shared_ptr<ConnectedSocket> conn = std::make_shared<ConnectedSocket>(new_conn);
            threads.enqueue(
                [conn](){
                    //Conn task.
                    conn->receive();
                }
            );
        }


    }
    WSACleanup();
}
Server::~Server(){}