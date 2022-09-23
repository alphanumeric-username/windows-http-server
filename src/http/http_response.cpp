#include "http/http_response.hpp"

#include <sstream>

namespace w8s {

std::string HTTPResponse::build_message() {
    std::stringstream ss{};

    ss << "HTTP/" << version << ' ' << status << ' ' << status_message << '\n';

    for(auto& header : headers) {
        ss << header.first << ": " << header.second << '\n';
    }

    ss << '\n' << body;

    return ss.str();
}

}