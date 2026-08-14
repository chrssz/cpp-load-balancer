#include "server/httpserver.hpp"
#include "server/loadbalserver.hpp"
int main(){
    
    int const THREAD_POOL_SIZE = 3;
    initWinSock();
    
    LoadBalServer lb(50);

    //Adds http backend servers that the loadbalacner will choose from.
    lb.addServer(std::make_unique<HttpServer>(1, 2));
    lb.addServer(std::make_unique<HttpServer>(2, 2));
    lb.addServer(std::make_unique<HttpServer>(3, 2));
    
    std::vector<std::unique_ptr<Server>>& server_list = lb.getServerList();

    std::vector<std::string> ports = {"81", "82", "83"};
    //Http servers need to be start before lb
    std::vector<std::jthread> threads;
    //Note: On Server_list start, thread gets busy setting up the listening loop for each server. Need to spawn a thread
    for(int i = 0; i < ports.size(); ++i){
        
        auto l = [serv = &*server_list[i], port = ports[i]]{
            serv->start(port);
        };
        std::jthread thread(l);
        threads.push_back(std::move(thread));
    }
    
    lb.start("80");

    WSACleanup();

}