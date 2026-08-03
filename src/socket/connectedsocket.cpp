#include "socket.hpp"


ConnectedSocket::ConnectedSocket(){

}
ConnectedSocket::ConnectedSocket(SOCKET created) : SocketWrapper(created) {
}
int ConnectedSocket::snd(){
    HttpResponse http_response;
    Response res = http_response.ok("Hello World!", "Greetings");

    std::string res_str = http_response.build(res);

    send(this->s, res_str.c_str(), res_str.size(), 0);
    return 1;
}
//Recieve will read and parse data line by line.
int ConnectedSocket::receive(){
    char buffer[4096] = {};
    int received = 0;
    std::string s;
    

    while(true){
        int received = recv(this->s, buffer, sizeof(buffer), 0);

        if(received == 0 || received == SOCKET_ERROR){
            std::cout << "Problem receiving data " << WSAGetLastError() << std::endl;
            return -1;
        }

        s.append(buffer, received);
        std::cout << "Received a stream of data!. " << std::endl;

        if(s.find("\r\n\r\n") != std::string::npos) {
            //Recieved data up to headers. Body not included.
            break;
        }

    }
    

    HttpParse parse;
    std::string str(buffer);
    Request parsed = parse.parse(str);
    
    std::cout << "Received data complete. " << std::endl;

    return 1;
}
ConnectedSocket::~ConnectedSocket(){
}