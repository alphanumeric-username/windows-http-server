#include "tcp_server.hpp"
#include "http/http_server.hpp"
#include "http/http_response.hpp"
#include "http/http_request.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

#include <iostream>
#include <cstring>

const std::string RETURN_MESSAGE { "Have a nice day!" };

void test_server_1();
void test_server_2();

int main(int argc, char* argv[]) {
    test_server_2();
}

void test_server_1() {
    http_server::TCPServer svr{};
    svr.set_port("8080");
    svr.init();
    svr.set_receive_handler([&](http_server::ClientSocket client_socket, char* data, int len) {
        // std::cout << "Received incoming message:\n" << data << '\n';

        http_server::HTTPRequest req{};
        req.initialize_from_message(std::string{data});

        std::cout << "Request target: " << req.target << '\n';
        std::cout << "Request method: " << req.method << '\n';

        
        http_server::HTTPResponse res{};

        res.status = 200;
        res.status_message = "Success";
        res.headers.insert({"Content-Type", "text/plain"});
        res.headers.insert({"Content-Length", std::to_string(RETURN_MESSAGE.size())});
        res.body = RETURN_MESSAGE;
        
        auto msg { res.build_message() };

        std::cout << "Sending outgoing message:\n" << msg << '\n';

        client_socket.send_data(msg.c_str(), msg.length());
        client_socket.close();
    });
    svr.run();
}

void test_server_2() {
    http_server::HTTPServer svr{};
    
    svr.init();

    svr.on_get("/", [&](http_server::HTTPRequest req) {
        http_server::HTTPResponse res{};

        res.status = 200;
        res.status_message = "Success";
        res.headers.insert({"Content-Type", "text/plain"});
        res.headers.insert({"Content-Length", std::to_string(RETURN_MESSAGE.size())});
        res.body = RETURN_MESSAGE;

        std::cout << "Request fullfilled\n";

        return res;
    });

    svr.run();
}