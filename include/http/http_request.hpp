#pragma once

#include <string>
#include <map>

namespace w8s {

struct HTTPRequest {
    std::string method{"GET"};
    std::string target{"/"};
    std::string version{"1.1"};
    std::string body{""};
    std::map<std::string, std::string> headers{};

    std::string build_message();
    void initialize_from_message(std::string message);
};

}