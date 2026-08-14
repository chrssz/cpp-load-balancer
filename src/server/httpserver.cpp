#include "httpserver.hpp"

HttpServer::HttpServer(int threadPoolSize) : threadpool(ThreadPool(threadPoolSize)){}

void HttpServer::start(std::string PORT_NUMBER){
    this->port_number = PORT_NUMBER;
    ListeningSocket listen(PORT_NUMBER);
    
    if(listen.setup() == -1){
        std::cout << "Error starting server" << std::endl;
        return;
    }   
    
    WSAPOLLFD poll_fd{};
    poll_fd.fd = listen.getSocket();
    poll_fd.events = POLLRDNORM;


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
                threadpool.enqueue(
                    [conn](){
                        //Conn task.
                        HttpServerHandler connHandle;
                        connHandle.handle(std::move(conn));
                    }
                );
            }
        }
    }
}
HttpServer::~HttpServer(){}