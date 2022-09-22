#pragma once

#include <string>
#include <vector>

namespace str_tools {

bool is_whitespace(char c);

std::string ltrim(std::string raw);
std::string rtrim(std::string raw);
std::string trim(std::string raw);

std::vector<std::string> split(std::string input, std::string separator);
std::vector<std::string> split_remove_empty(std::string input, std::string separator);

}