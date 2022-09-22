#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>

#include <functional>
#include <string>

namespace http_server {

struct ClientSocket {
    SOCKET sock{ INVALID_SOCKET };
    void send_data(char* data, int len);
    void send_data(const char* data, int len);
    void close();
};

typedef std::function<void(ClientSocket, char*, int)> TCPReceiveHandler;

class TCPServer {
private:
    std::string port_{"8080"};
    SOCKET listen_socket_{INVALID_SOCKET};
    struct addrinfo* ai_result{ NULL };
    bool is_running_{ false };

    TCPReceiveHandler on_receive_{};
public:
    void set_port(std::string port);
    void set_receive_handler(TCPReceiveHandler on_receive);

    void init();
    void run();
    void stop();
};

}