#pragma once

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

void initWinSock();


class SocketWrapper {
    protected:
        SOCKET createSocket();
        SOCKET s;

    public:
        SocketWrapper();
        SocketWrapper(SOCKET created);
        virtual ~SocketWrapper();
};


class ListeningSocket : public SocketWrapper {
    private:
        const int MAX_CON = 5;

    protected:
        void bindSocket();
        int setListen();
        int acceptConnect();

    public:
        ListeningSocket();
        ~ListeningSocket();

        void start();
};


class ConnectedSocket : public SocketWrapper {
    public:
        ConnectedSocket();
        ConnectedSocket(SOCKET created);
        ~ConnectedSocket();
};