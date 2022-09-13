#include "http/http_request.hpp"

#include <sstream>

namespace http_server {

std::string HTTPRequest::build_message() {
    std::stringstream ss{};

    ss << method << " " << target << " HTTP/" << version << '\n';

    for(auto& header : headers) {
        ss << header.first << ": " << header.second << '\n';
    }

    ss << '\n' << body;

    return ss.str();
}

}