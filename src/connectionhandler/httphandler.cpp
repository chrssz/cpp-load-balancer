#include "httphandler.hpp"

HttpServerHandler::HttpServerHandler(){}

Response HttpServerHandler::handleRequest(const Request& req){
    HttpResponse responseObj;
    if(req.method == ""){
        return responseObj.badRequest("Invalid Request");
    }

    std::string valid_methods[5] = {"GET", "POST", "PUT", "DELETE", "PATCH"};

    for(int i = 0; i < sizeof(valid_methods); ++i){
        if (valid_methods[i] == req.method){
            return responseObj.ok("Valid Method Provided!", "text/plain");
        }
    }

    return responseObj.notFound();
}

void HttpServerHandler::handle(std::shared_ptr<ConnectedSocket> conn){
    std::string recieved = conn->receive();
    
    //Parse data
    HttpParse p;
    Request req = p.parse(recieved);
    
    //Response
    HttpResponse responseObj; //Needed for building raw string
    Response response = handleRequest(req);
    std::string responseString = responseObj.build(response);

    conn->snd(responseString);
    
}

HttpServerHandler::~HttpServerHandler(){}