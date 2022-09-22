#pragma once

#include "tcp_server.hpp"
#include "http/url.hpp"
#include "http/http_response.hpp"
#include "http/http_request.hpp"

#include <string>
#include <map>
#include <functional>
#include <tuple>

namespace http_server {

typedef std::function<HTTPResponse(HTTPRequest)> HTTPReceiveHandler;

class HTTPServer {
private:
    TCPServer server_{};
    std::map<std::tuple<std::string, std::string>, HTTPReceiveHandler> callbacks_{};
public:
    void set_port(int port);

    void init();
    void run();
    void stop();

    URLTarget parse_target(std::string route_str);
    void set_callback(std::string method, std::string route, HTTPReceiveHandler callback);
    void on_get(std::string route, HTTPReceiveHandler callback);
    void on_post(std::string route, HTTPReceiveHandler callback);
    void on_put(std::string route, HTTPReceiveHandler callback);
    void on_delete(std::string route, HTTPReceiveHandler callback);
};

}