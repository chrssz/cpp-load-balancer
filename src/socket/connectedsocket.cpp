#include "socket.h"


ConnectedSocket::ConnectedSocket(){

}
ConnectedSocket::ConnectedSocket(SOCKET created) : SocketWrapper(created) {
}
int ConnectedSocket::send(){

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