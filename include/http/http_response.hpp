#pragma once

#include <string>
#include <map>

namespace w8s {

struct HTTPResponse {
    std::string version{"1.1"};
    unsigned int status{200};
    std::string status_message{""};
    std::string body{""};
    std::map<std::string, std::string> headers{};

    std::string build_message();
};

}