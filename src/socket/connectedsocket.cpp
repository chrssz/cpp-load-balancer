#include "socket.hpp"


ConnectedSocket::ConnectedSocket(){

}
ConnectedSocket::ConnectedSocket(SOCKET created) : SocketWrapper(created) {
}
int ConnectedSocket::snd(std::string& data){
    send(this->s, data.c_str(), data.size(), 0);
    return 1;
}
//Recieve will read and parse data line by line.
std::string ConnectedSocket::receive(){
    char buffer[4096] = {};
    int received = 0;
    std::string output;

    while(true){
        int received = recv(this->s, buffer, sizeof(buffer), 0);

        if(received == 0 || received == SOCKET_ERROR){
            std::cout << "Problem receiving data " << WSAGetLastError() << std::endl;
            return "";
        }

        output.append(buffer, received);
        
        if(output.find("\r\n\r\n") != std::string::npos) {
            //Recieved data up to headers. Body not included.
            break;
        }

    }
    int headerEnd = output.find("\r\n\r\n");
    if(headerEnd == std::string::npos){
        return output;
    }

    //Extract body if exists
    std::string headerSection = output.substr(0, headerEnd);
    int contentLengthPos = headerSection.find("Content-Length: ");
    if(contentLengthPos != std::string::npos){
        int contentStart = contentLengthPos + 16;
        int contentEnd = headerSection.find("\r\n", contentStart);
        
        int contentLength = std::stoi(headerSection.substr(contentStart, contentEnd - contentStart));

        int currentBody = output.size() - (headerEnd + 4);

        while(currentBody < contentLength){
            int received = recv(this->s, buffer, sizeof(buffer), 0);
            if(received <= 0){
                break;
            }
                
            output.append(buffer, received);
            currentBody += received;
        }
    }
    std::cout << "Received data complete. " << std::endl;

    return output;
}

ConnectedSocket::~ConnectedSocket(){
}