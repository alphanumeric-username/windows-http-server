#include "http/http_server.hpp"

#include "str_tools.hpp"

#include <iostream>

namespace w8s {

void HTTPServer::set_port(int port) {
    server_.set_port(std::to_string(port));
}

void HTTPServer::init() {
    auto& callbacks = callbacks_;

    server_.set_receive_handler([&](ClientSocket client_socket, char* data, int len) {
        HTTPRequest req {};
        req.initialize_from_message(std::string{data});

        HTTPResponse res{};

        auto url_target { parse_target(req.target) };

        if(callbacks.count({req.method, url_target.route}) > 0) {
            res = callbacks.at({req.method, url_target.route})(req);
        } else {
            res.status = 404;
            res.status_message = "Not found";
            res.headers.insert({"Content-Length", std::to_string(0)});
            std::cout << "Not found\n";
        }

        auto res_message{res.build_message()};
        client_socket.send_data(res_message.data(), res_message.size());
    });

    set_port(8080);

    server_.init(); 
}
void HTTPServer::run() { server_.run(); }
void HTTPServer::stop() { server_.stop(); }

URLTarget HTTPServer::parse_target(std::string target_str) {
    URLTarget url_target{};

    auto params_start_idx {target_str.find_first_of('?')};
    
    url_target.route = normalize_route(target_str.substr(0, params_start_idx));
    
    if(params_start_idx != std::string::npos && target_str.substr(params_start_idx).size() > 1) {
        target_str = target_str.substr(params_start_idx + 1);
        auto assignments {str_tools::split(target_str, "&")};

        for(auto a : assignments) {
            auto parsed_assignment {str_tools::split(a, "=")};
            url_target.query_params.insert_or_assign(parsed_assignment[0], parsed_assignment[1]);
        }
    }

    url_target.is_valid = true;

    return url_target;
}

void HTTPServer::set_callback(std::string method, std::string route, HTTPReceiveHandler callback) {
    method = str_tools::uppercase(str_tools::trim(method));
    route = normalize_route(route);

    callbacks_.insert_or_assign({ method, route}, callback);
}

void HTTPServer::on_get(std::string route, HTTPReceiveHandler callback) { set_callback("GET", route, callback); }
void HTTPServer::on_post(std::string route, HTTPReceiveHandler callback) { set_callback("POST", route, callback); }
void HTTPServer::on_put(std::string route, HTTPReceiveHandler callback) { set_callback("PUT", route, callback); }
void HTTPServer::on_delete(std::string route, HTTPReceiveHandler callback) { set_callback("DELETE", route, callback); }


}