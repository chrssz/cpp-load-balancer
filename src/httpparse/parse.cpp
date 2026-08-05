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
   Request r{};
   const std::size_t END_LINE_OFFSET = 2;
   std::size_t i = 0;
   std::size_t endLine;
   std::size_t colonPos;

   //Request Line
   endLine = buffer.find("\r\n", i);

   if(endLine == std::string::npos){
      return r;
   }

   std::string requestLine = slice_str(buffer, i, endLine);

   //Split request line by spaces into method, path, version
   std::size_t firstSpace = requestLine.find(' ');
   if(firstSpace == std::string::npos){
      return r;
   }

   std::size_t secondSpace = requestLine.find(' ', firstSpace + 1);
   if(secondSpace == std::string::npos){
      return r;
   }

   r.method  = slice_str(requestLine, 0, firstSpace);
   r.path    = slice_str(requestLine, firstSpace + 1, secondSpace);
   r.version = slice_str(requestLine, secondSpace + 1, requestLine.length());

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

      colonPos = buffer.find(":", i);

      //Invalid header
      if(colonPos == std::string::npos || colonPos > endLine){
         return r;
      }

      std::string header_key = slice_str(buffer, i, colonPos);
      std::string header_val = slice_str(buffer, colonPos + 1, endLine);
      //Remove leading whitespace from header value
      if(!header_val.empty() && header_val[0] == ' '){
         header_val.erase(0, 1);
      }

      r.headers[header_key] = header_val;
      i = endLine + END_LINE_OFFSET;
   }
   //Anything after the blank line is body data
   r.body = slice_str(buffer, i, buffer.length());

   r.valid = true;
   
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