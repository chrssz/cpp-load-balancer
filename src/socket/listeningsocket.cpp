#include "socket.hpp"


ListeningSocket::ListeningSocket() {
}


ListeningSocket::~ListeningSocket() {

}


void ListeningSocket::bindSocket() {
    addrinfo hints{};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    addrinfo* result = nullptr;
    
    int ret = getaddrinfo(nullptr, "80", &hints, &result);
    
    if(ret != 0) {
        std::cout << "Failed to bind to Listening Socket " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        return;
    }
    
    if(bind(this->s, result->ai_addr, result->ai_addrlen) == SOCKET_ERROR){
        std::cout << "Bind failed! " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        return;
    }

    freeaddrinfo(result);
    std::cout << "Successfull bind to Listening Socket" << std::endl;
}


int ListeningSocket::setListen() {
    return listen(s, 0);
}


int ListeningSocket::setup() {
    this->bindSocket();

    if(this->setListen() == -1){
        return -1;
    }

    return 1;
    
}
