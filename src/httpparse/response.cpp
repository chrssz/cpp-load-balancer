#include "response.hpp"

std::ostream& operator<<(std::ostream& stream, const Response& r) {
   stream << "Version: " << r.version << "\n"
          << "Status Code: " << r.statusCode << "\n"
          << "Reason Phrase: " << r.reasonPhrase << "\n"
          << "Headers:\n";
   
   for (const auto& [key, value] : r.headers) {
       stream << "  " << key << ": " << value << "\n";
   }
   
   stream << "Body:\n" << r.body;
   
   return stream;
}

HttpResponse::HttpResponse(){}
std::string HttpResponse::build(Response& res){
    //Set the content length
    res.headers["Content-Length"] = std::to_string(res.body.size());
    res.headers["Connection"] = "close";
    //Below builds example: HTTP/1.1 STATUS REASONPHRASE
    std::string output = res.version + " " + std::to_string(res.statusCode) +
                        " " + res.reasonPhrase + "\r\n";

    //get headers; values are already strings
    for(const auto& [key, val] : res.headers){
        output += key + ": " + val + "\r\n";
    }
    
    output += "\r\n"; //Need to end the headers with a extra \r\n. \r\n\r\n

    output += res.body;

    return output;

}

Response HttpResponse::ok(std::string body, std::string contentType){
    Response r;
    r.statusCode = 200;
    r.reasonPhrase = "OK";
    r.headers["Content-Type"] = contentType;
    r.body = body;

    return r;
}
Response HttpResponse::badRequest(std::string message){
    Response r;
    r.statusCode = 400;
    r.reasonPhrase = "Bad Request";
    r.headers["Content-Type"] = "text/plain";
    r.body = message;

    return r;
}
Response HttpResponse::notFound(){
    Response r;
    r.statusCode = 404;
    r.reasonPhrase = "Not Found";
    r.headers["Content-Type"] = "text/plain";
    r.body = "404 Not Found";

    return r;
}
Response HttpResponse::internalError(){
    Response r;
    r.statusCode = 500;
    r.reasonPhrase = "Internal Server Error";
    r.headers["Content-Type"] = "text/plain";
    r.body = "500 Internal Server Error";

    return r;
}
Response HttpResponse::serviceUnavailable(){
    Response r;
    r.statusCode = 503;
    r.reasonPhrase = "Service Unavailable";
    r.headers["Content-Type"] = "text/plain";
    r.body = "503 No backends available";

    return r;
}
HttpResponse::~HttpResponse(){}