#pragma once

#include <string>
#include <map>

namespace http_server {

struct URLTarget {
    std::string route{""};
    std::map<std::string, std::string> query_params{};

    bool is_valid{false};
};

}