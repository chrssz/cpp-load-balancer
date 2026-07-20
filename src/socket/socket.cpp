#include "socket.hpp"

void initWinSock(){
    //NOTE: Function caller must call WSACleanup
    WSADATA wsaData;

    int result;

    result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if(result != 0) {
        std::cout << "WSAStartup failed " << result << std::endl;
        WSACleanup();
        return;
    }

}
SOCKET SocketWrapper::createSocket() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

SOCKET SocketWrapper::getSocket(){
    return this->s;
}
SocketWrapper::SocketWrapper(): s(createSocket()) {}

SocketWrapper::SocketWrapper(SOCKET created): s(created) {}

SocketWrapper::~SocketWrapper() {
    closesocket(s);
}