#include "parse.hpp"
std::ostream& operator<<(std::ostream& stream, const Request& r) {
   stream << "Method: " << r.method << "\n"
          << "Path: " << r.path << "\n"
          << "Version: " << r.version << "\n"
          << "Valid: " << (r.valid ? "true" : "false") << "\n"
          << "Headers:\n";
   
   for (const auto& [key, value] : r.headers) {
       stream << "  " << key << ": " << value << "\n";
   }
   
   stream << "Body:\n" << r.body;
   
   return stream;
}

HttpParse::HttpParse(){}
Request HttpParse::parse(std::string& buffer){
   //TODO: Results from testing with curl, Fix below.
   /*
      Test case: curl -v -X POST http://localhost:80/ 
      \  -H "Content-Type: application/json" \  -H "User-Agent: CppLoadBalancerTest" \  -d '{"test": "hello world"}'
      --------------------------------------------------------------------------------------------
      Path: Expected = localhost, Output = Host:localhost
      Version: Expected = 1.1, Output = Accept: /
      Body: Expected = {test: Hello World}, Output = {test:

   */
   //This is mandatory.
   /*
         Request Line: METHOD 
         Host Path: //example.com
         Version: 
         Headers: e.g Content-Length
         Body: data payload.
   */
   Request r{};
   const std::size_t END_LINE_OFFSET = 2;
   std::size_t i = 0;
   std::size_t endLine;
   std::size_t colonPos;

   //Request, method line
   endLine = buffer.find("\r\n", i);

   if(endLine == std::string::npos){
      return r;
   }

   r.method = slice_str(buffer, i, endLine);

   //Host Path
   i = endLine + END_LINE_OFFSET;
   endLine = buffer.find("\r\n", i);

   if(endLine == std::string::npos){
      return r;
   }

   r.path = slice_str(buffer, i, endLine);

   //Version
   i = endLine + END_LINE_OFFSET;
   endLine = buffer.find("\r\n", i);

   if(endLine == std::string::npos){
      return r;
   }

   r.version = slice_str(buffer, i, endLine);

   //Move to first header
   i = endLine + END_LINE_OFFSET;

   //Headers
   while(i < buffer.length()){
      endLine = buffer.find("\r\n", i);

      //No complete header line yet
      if(endLine == std::string::npos){
         return r;
      }

      //Empty line means we reached the end of the headers
      if(endLine == i){
         i = endLine + END_LINE_OFFSET;
         break;
      }

      //Find the colon separating the header key and value
      colonPos = buffer.find(":", i);

      //Invalid header
      if(colonPos == std::string::npos || colonPos > endLine){
         return r;
      }

      std::string header_key = slice_str(buffer, i, colonPos);
      std::string header_val = slice_str(buffer, colonPos + 1, endLine);

      //Remove leading whitespace from header
      if(!header_val.empty() && header_val[0] == ' '){
         header_val.erase(0, 1);
      }
      
      r.headers[header_key] = header_val;

      //Move to next header
      i = endLine + END_LINE_OFFSET;
   }

   //Anything after the blank line is body data
   r.body = slice_str(buffer, i, buffer.length());

   //Successfully parsed request
   r.valid = true;
   std::cout << r << std::endl;
   return r;
}

std::string HttpParse::slice_str(std::string& s, int start, int endPos){
   if (start >= endPos){
      return "";
   }

   std::string output;
   for(int i = start; i < endPos; ++i){
      output.push_back(s[i]);
   }
   
   return output;
}



HttpParse::~HttpParse(){}