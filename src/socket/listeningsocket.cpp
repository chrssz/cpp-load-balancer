#include "socket.h"


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
    
    getaddrinfo(nullptr, "80", &hints, &result);
    
    if(result != 0) {
        std::cout << "Failed to bind to Listening Socket " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        WSACleanup();
    }
    
    bind(this->s, result->ai_addr, result->ai_addrlen);
    freeaddrinfo(result);
}


int ListeningSocket::setListen() {
    return listen(s, MAX_CON);
}


int ListeningSocket::acceptConnect() {

    SOCKET clientSocket = accept(s, nullptr, nullptr);
    

    if (clientSocket == INVALID_SOCKET)
    {
        return -1;
    }

    ConnectedSocket new_socket(clientSocket);
    //Add this connected socket to a socket manager.
    //TBD...
    return 0;
}


void ListeningSocket::start() {
    bindSocket();

    if(setListen() == -1){
        return;
    }

    while (true){
        acceptConnect();
    }
    
}