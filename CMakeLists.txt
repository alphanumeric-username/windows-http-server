cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(HttpWritter)

include_directories(include)

file(GLOB http_SRC src/http/*.cpp)
add_library(http ${http_SRC})
add_library(tcp_server src/tcp_server.cpp)
add_library(str_tools src/str_tools.cpp)

add_executable(w8svr src/main.cpp)

target_link_libraries(tcp_server wsock32 ws2_32)
target_link_libraries(http tcp_server str_tools)

target_link_libraries(w8svr tcp_server http)