#include "connectionhandler.hpp"

ConnectionHandler::ConnectionHandler(){}

Response ConnectionHandler::handleRequest(const Request& req){
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
ConnectionHandler::~ConnectionHandler(){}