#include "http/url.hpp"

#include "str_tools.hpp"

namespace w8s {

std::string normalize_route(std::string route) {
    
    route = str_tools::trim(route);
    route = str_tools::lowercase(route);

    auto idx { route.find_last_of('/') };
    if(idx == route.size() - 1) {
        route = route.substr(0, idx);
    }

    return route;
}

}
