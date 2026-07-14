#include "socket.h"


ConnectedSocket::ConnectedSocket(){

}
ConnectedSocket::ConnectedSocket(SOCKET created) : SocketWrapper(created) {
}
int ConnectedSocket::send(){

}

void ConnectedSocket::start(){
    std::byte buffer[1024]; 

    while(true){
        int received = recv(this->s, (char*)&buffer, sizeof(buffer), 0);

        if(received == 0){
            std::cout << "Received data " << std::endl;
        }
    }
}
ConnectedSocket::~ConnectedSocket(){
}