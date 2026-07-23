#include <string>
struct Request{
    std::string method; //Http

};
class HttpParse{
    private:

    public:
        HttpParse();
        std::string parse(std::byte buffer);

        ~HttpParse();

};