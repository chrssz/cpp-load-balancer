#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
struct Request{
    std::string method;      
    std::string path;       
    std::string version;     
    std::unordered_map<std::string, std::string> headers;
    std::string body;
    bool valid = false;
};

std::ostream& operator<<(std::ostream& stream, const Request& r);

class HttpParse{
    private:
        std::string slice_str(std::string& s, int start, int endPos); //EndPos is non inclusive. [start, end)
       
    public:
        HttpParse();
        Request parse(std::string& buffer);
        ~HttpParse();
};