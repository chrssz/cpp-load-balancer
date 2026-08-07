#include "connectionhandler.hpp"

HttpServerHandler::HttpServerHandler(){}

void HttpServerHandler::handle(std::shared_ptr<ConnectedSocket> conn){
    std::string recieved = conn->receive();
    
    //Parse data
    HttpParse p;
    Request req = p.parse(recieved);
    std::cout << "Data Recieved" << std::endl;

    std::cout << req << std::endl;

    std::cout << "----------------------------------------------" << std::endl;
    //Response
    HttpResponse responseObj; //Needed for building raw string
    Response response = handleRequest(req);
    std::string responseString = responseObj.build(response);

    conn->snd(responseString);
    
    std::cout << "Data sending back" << std::endl;
    std::cout << response << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
}

HttpServerHandler::~HttpServerHandler(){}