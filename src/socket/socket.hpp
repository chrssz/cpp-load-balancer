#pragma once

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <cstddef>
#include <string>
void initWinSock();



class SocketWrapper {
    protected:
        SOCKET createSocket();
        SOCKET s;

    public:
        SocketWrapper();
        SocketWrapper(SOCKET created);
        SOCKET getSocket();
        virtual ~SocketWrapper();
};

class ListeningSocket : public SocketWrapper {
    private:
        std::string PORT;
    
    protected:
        void bindSocket();
        int setListen();

    public:
        ListeningSocket(std::string PORT_NUMBER);
        ~ListeningSocket();

        int setup();
};


class ConnectedSocket : public SocketWrapper {
    public:
        ConnectedSocket();
        ConnectedSocket(SOCKET created);
        int snd();
        int receive();
        
        ~ConnectedSocket();
};