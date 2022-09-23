#include "http/http_request.hpp"

#include "str_tools.hpp"

#include <sstream>
#include <iostream>


namespace w8s {

void HTTPRequest::initialize_from_message(std::string message) {
    auto lines {str_tools::split(message, "\n")};
    
    // Get data from the first line
    auto line1 {lines[0]};
    auto line1_tokens {str_tools::split_remove_empty(line1, " ")};

    method = line1_tokens[0];
    target = line1_tokens[1];
    version = line1_tokens[2];

    // Get data from headers
    // std::cout << "Getting headers\n";
    int i;
    for(i = 1; lines[i].size() > 1; i++) {
        // std::cout << lines[i].size() << " " << lines[i] << '\n';
        auto header_tokens = str_tools::split(lines[i], ":");
        headers.insert_or_assign(header_tokens[0], str_tools::trim(header_tokens[1]));
    }

    // Get data body data
    // std::cout << "Getting body\n";
    for(i++; i < lines.size(); body.append(lines[i]).append("\n"), i++);

    // std::cout << "End\n";
}

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