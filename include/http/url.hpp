#pragma once

#include <string>
#include <map>

namespace w8s {

struct URLTarget {
    std::string route{""};
    std::map<std::string, std::string> query_params{};

    bool is_valid{false};
};


/**
 * @brief Normalizes a route
 * 
 * The route is normalized as follows:
 * 
 * ```
 * "/NamE/Of/THE/rouTE/  " -> "/name/of/the/route"
 * 
 * "/" -> ""
 * ```
 * 
 * @param route The route to be normalized.
 * @return std::string The normalized route.
 */
std::string normalize_route(std::string route);

}