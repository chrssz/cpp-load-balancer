#include "parse.hpp"

HttpParse::HttpParse(){}
Request HttpParse::parse(std::string& buffer){

    //Notes for algorithm.
    //Let \r\n ; denote the end of the request attributes.
    //Winsock requires a strict text based format.
    //This is mandatory.
    /*
            Request Line: METHOD / path.
            Host Header: //example.com
            Version: version of http.
            Extra Header: Content-Length
            Body: data payload.
    */
   Request r{};
   //Parse every line
   int i = 0; 
   //TODO: Think of a clean way to write this loop to populate the request, so far only ideas in mind are
      //If statements, case switch designs.
}
HttpParse::~HttpParse(){}