#pragma once
#include <string>
#include <unordered_map>
struct Request{
    std::string method;      
    std::string path;       
    std::string version;     
    std::unordered_map<std::string, std::string> headers;
    std::string body;
    bool valid = false;
};

class HttpParse{
    private:

    public:
        HttpParse();
        Request parse(std::string& buffer);
        ~HttpParse();

};