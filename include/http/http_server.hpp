#pragma once

#include "tcp_server.hpp"
#include "http/url.hpp"

#include <string>

namespace http_server {

class HTTPServer {
public:
    URL parse_url(std::string url_str);
};

}