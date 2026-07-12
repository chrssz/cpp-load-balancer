#include "socket.h"


SOCKET SocketWrapper::createSocket() {
    return socket(AF_INET, SOCK_STREAM, 0);
}


SocketWrapper::SocketWrapper(): s(createSocket()) {

}

SocketWrapper::SocketWrapper(SOCKET created): s(created) {
    
}
SocketWrapper::~SocketWrapper() {
    closesocket(s);
}