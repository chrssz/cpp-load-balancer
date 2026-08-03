#pragma once
#include <string>
#include <unordered_map>
struct Response{
    std::string version = "HTTP/1.1";
    int statusCode = 200;
    std::string reasonPhrase = "OK";
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};

class HttpResponse{
    public:
        HttpResponse();
        //Builds a raw string from the response object
        std::string build(Response& res);
        Response ok(std::string body, std::string contentType);
        Response badRequest(std::string message);
        Response notFound();
        Response internalError();
        Response serviceUnavailable();
        ~HttpResponse();
};