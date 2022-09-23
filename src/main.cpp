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
    w8s::TCPServer svr{};
    svr.set_port("8080");
    svr.init();
    svr.set_receive_handler([&](w8s::ClientSocket client_socket, char* data, int len) {
        // std::cout << "Received incoming message:\n" << data << '\n';

        w8s::HTTPRequest req{};
        req.initialize_from_message(std::string{data});

        std::cout << "Request target: " << req.target << '\n';
        std::cout << "Request method: " << req.method << '\n';

        
        w8s::HTTPResponse res{};

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
    w8s::HTTPServer svr{};
    
    svr.set_port(8080);  // It is 8080 by default
    svr.init();

    std::string default_text { "Have a nice day!" };

    std::string about_text { "This is a toy http server." };

    svr.on_get("/", [&](auto req) {  // Set callback for "/" endpoint
        w8s::HTTPResponse res{};

        res.status = 200;
        res.status_message = "Success";
        res.headers.insert({"Content-Type", "text/plain"});
        res.headers.insert({"Content-Length", std::to_string(default_text.size())});
        res.body = default_text;

        std::cout << "Hit '/'\n";

        return res;
    });

    svr.on_get("/about/", [&](auto req) {  // Set callback for "/about" endpoint
        w8s::HTTPResponse res{};

        res.status = 200;
        res.status_message = "Success";
        res.headers.insert({"Content-Type", "text/plain"});
        res.headers.insert({"Content-Length", std::to_string(about_text.size())});

        res.body = about_text;

        std::cout << "Hit '/about'\n";

        return res;
    });

    svr.run();  // Start the server
}