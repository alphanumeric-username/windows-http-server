cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(HttpWritter)

include_directories(include)

add_library(http 
    src/http_request.cpp 
    src/http_response.cpp)
add_library(tcp_server src/tcp_server.cpp)

add_executable(w8svr src/main.cpp)

target_link_libraries(w8svr tcp_server http)
target_link_libraries(tcp_server wsock32 ws2_32)