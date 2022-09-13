#include "http/http_server.hpp"

namespace http_server {

URL HTTPServer::parse_url(std::string url_str) {
    URL url{};

    auto scheme_end_idx {url_str.find_first_of("://", 0)};
    if(scheme_end_idx == std::string::npos) {
        return url; 
    }

    url.scheme = url_str.substr(0, scheme_end_idx);
    url_str = url_str.substr(scheme_end_idx + 3);

    auto authority_end_idx {url_str.find_first_of('/')};

    url.authority = url_str.substr(0, authority_end_idx);
    url_str = url_str.substr(authority_end_idx);

    auto route_end_idx {url_str.find_first_of('?')};
    if(route_end_idx != std::string::npos) {
        // TODO: Parse params
    }

    url.is_valid = true;

    return url;
}

}