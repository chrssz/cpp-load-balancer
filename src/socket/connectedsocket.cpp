#include "socket.hpp"


ConnectedSocket::ConnectedSocket(){

}
ConnectedSocket::ConnectedSocket(SOCKET created) : SocketWrapper(created) {
}
int ConnectedSocket::snd(){
    std::string body = "Hello World";
    std::string res = "HTTP/1.1 200 OK\r\n"
                      "Content-Type: text/plain; charset=utf-8\r\n"
                      "Content-Length: " + std::to_string(body.size()) + "\r\n"
                      "Connection: close\r\n\r\n" 
                      + body;
            
    send(this->s, res.c_str(), res.size(), 0);
    return 1;
}

int ConnectedSocket::receive(){
    
    std::byte buffer[1024]; 

    
    int received = recv(this->s, (char*)&buffer, sizeof(buffer), 0);

    if(received == 0 || received == SOCKET_ERROR){
        std::cout << "Problem receiving data " << WSAGetLastError() << std::endl;
        return -1;
    }
    std::cout << "Received data " << std::endl;

    return 1;
}
ConnectedSocket::~ConnectedSocket(){
}