#include "server.hpp"

Server::Server(int threadPoolSize) : threadpool(ThreadPool(threadPoolSize)){}

void Server::start(std::string PORT_NUMBER){

    initWinSock();
    ListeningSocket listen(PORT_NUMBER);
    
    if(listen.setup() == -1){
        std::cout << "Error starting server" << std::endl;
        WSACleanup();
        return;
    }   
    
    WSAPOLLFD poll_fd{};
    poll_fd.fd = listen.getSocket();
    poll_fd.events = POLLRDNORM;

    this->poll_fds.push_back(std::move(poll_fd));

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
                threadpool.enqueue(
                    [conn](){
                        //Conn task.
                        conn->receive();
                        conn->snd();
                    }
                );
            }
        }


    }
    WSACleanup();
}
Server::~Server(){}