
#pragma once

#include <iostream>
#include <memory>
#include "../socket/socket.hpp"
#include "../threadpool/threadpool.hpp"

class Server {
    private:
        std::vector<std::shared_ptr<SocketWrapper>> socks; //Manages all connected sockets.
        std::vector<WSAPOLLFD> poll_fds; //Required for WSAPolling.
        ThreadPool threads; 
    public:
        Server();
        void start();
        ~Server();
};