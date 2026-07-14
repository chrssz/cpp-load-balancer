#include "socket.h"
#include "threadpool.h"

int main(){
    ListeningSocket listen;

    initWinSock();

    if(listen.setup() == -1){
        return -1;
    }

    while(true){
        SOCKET clientSocket = accept(listen.getSocket(), nullptr, nullptr);
        

        if (clientSocket != INVALID_SOCKET) {
            ConnectedSocket new_socket(clientSocket);
            //Add this to threadpool.
            //TBD...
            return -1;
        }


        return 1;
    }
    WSACleanup();
}