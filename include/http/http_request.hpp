#pragma once

#include <string>
#include <map>

namespace http_server {

struct HTTPRequest {
    std::string method{"GET"};
    std::string target{"/"};
    std::string version{"1.1"};
    std::string body{""};
    std::map<std::string, std::string> headers{};

    HTTPRequest();
    HTTPRequest(std::string message);
    
    std::string build_message();
};

}