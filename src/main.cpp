#include "server/server.hpp"
int main(){
    
    int const THREAD_POOL_SIZE = 4;
    initWinSock();
    
    HttpServer serv(THREAD_POOL_SIZE);
    serv.start("80");
    
    WSACleanup();

}