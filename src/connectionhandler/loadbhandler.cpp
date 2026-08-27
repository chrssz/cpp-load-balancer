#include "loadbhandler.hpp"

LoadBalanceHandler::LoadBalanceHandler(){}
std::unique_ptr<ConnectedSocket> LoadBalanceHandler::getOutBoundConnection(std::string port_number){
    //TODO;
    addrinfo hints{};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    addrinfo* result = nullptr;
    int ret = getaddrinfo(nullptr, port_number.c_str(), &hints, &result);
        
    if(ret != 0){
        std::cout << "Failed to create out bound connection" << std::endl;
        return std::make_unique<ConnectedSocket>(INVALID_SOCKET);
    }

    SOCKET new_conn = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    
    if(new_conn == INVALID_SOCKET){
        freeaddrinfo(result);
        return std::make_unique<ConnectedSocket>(INVALID_SOCKET);
    }

    if(connect(new_conn, result->ai_addr, result->ai_addrlen) == SOCKET_ERROR){
        closesocket(new_conn);
        freeaddrinfo(result);
        return std::make_unique<ConnectedSocket>(INVALID_SOCKET);
    }

    freeaddrinfo(result);
    
    return std::make_unique<ConnectedSocket>(new_conn);
}
Server& LoadBalanceHandler::roundRobin(std::vector<std::unique_ptr<Server>>& servers){
    //Simple algorithm; will move algorithms to their own class
    Server& toReturn = *servers[this->roundRobinPtr];
    
    this->roundRobinPtr = (this->roundRobinPtr + 1) % servers.size();
    
    return toReturn;
}
void LoadBalanceHandler::handle(std::shared_ptr<ConnectedSocket> conn){
    std::cout << "Error handling connection, handle requires (conn, serverVector)" << std::endl;
}
void LoadBalanceHandler::handle(std::shared_ptr<ConnectedSocket> conn, std::vector<std::unique_ptr<Server>>& servers){
    std::cout << "Load balancer handling new connection!" << std::endl;
    
    Server& server = roundRobin(servers); //Server assignment algorithm
    std::string portNum = server.getPort();
  

    std::unique_ptr<ConnectedSocket> outBoundConn = std::move(getOutBoundConnection(portNum));

    if(outBoundConn->getSocket() == INVALID_SOCKET){
        //Send back an error to client
        HttpResponse r;
        Response resObj = r.badRequest("Error connecting to reverse proxy");
        std::string resString = r.build(resObj);
        
        conn->snd(resString);
        return;
    }

    std::string dataFromClient = conn->receive();

    outBoundConn->snd(dataFromClient);

    std::string dataFromServer = outBoundConn->receive();

    conn->snd(dataFromServer);
    
    std::cout << "Load balancer sending data back to client Size: " << dataFromServer.size() << std::endl;
}

LoadBalanceHandler::~LoadBalanceHandler(){}
