#include "str_tools.hpp"

namespace str_tools {

bool is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

std::string ltrim(std::string raw) {
    int i;
    for(i = 0; i < raw.length() && is_whitespace(raw.at(i)); i++);

    return std::string{ raw.substr(i) };
}

std::string rtrim(std::string raw) {
    int i;
    for(i = raw.length() - 1; i > -1 && is_whitespace(raw.at(i)); i--);

    return std::string{ raw.substr(0, i+1) };
}

std::string trim(std::string raw) {
    return ltrim(rtrim(raw));
}

std::vector<std::string> split(std::string input, std::string separator) {
    std::vector<std::string> output{};

    for(auto i = input.find(separator); i != std::string::npos; i = input.find(separator)) {
        auto substr = input.substr(0, i);
        output.emplace_back(substr);

        input = input.substr(i + separator.size());
    }

    output.emplace_back(input);

    return output;
}

std::vector<std::string> split_remove_empty(std::string input, std::string separator) {
    auto split_input {split(input, separator)};

    std::vector<std::string> output {};

    for(auto s : split_input) {
        if(s.size() > 0) {
            output.emplace_back(s);
        }
    }

    return output;
}

}
