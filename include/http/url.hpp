#pragma once

#include <string>
#include <map>

namespace http_server {

struct URL {
    std::string scheme{""};
    std::string authority{""};
    std::string route{""};
    std::map<std::string, std::string> query_params{};

    bool is_valid{false};
};

}