#include "socket.h"


ConnectedSocket::ConnectedSocket(){
}
ConnectedSocket::ConnectedSocket(SOCKET created) : SocketWrapper(created) {
}

ConnectedSocket::~ConnectedSocket(){
}