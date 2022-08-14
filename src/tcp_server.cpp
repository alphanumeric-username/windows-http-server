#include "tcp_server.hpp"

#include <iostream>

namespace http_server {

bool winsock_was_initialized { false };

void TCPServer::set_port(std::string port) {
    port_ = port;
}

void TCPServer::set_receive_handler(std::function<void(ClientSocket, char*, int)> on_receive) {
    on_receive_ = on_receive;
}

void TCPServer::init() {
    int iResult;

    if(!winsock_was_initialized) {
        WSADATA wsaData;

        iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
        if(iResult != 0) {
            std::cerr << "[TCP Server]: WSAStartup failed: " << iResult;
            return;
        }

        winsock_was_initialized = true;
    }

    struct addrinfo* result { NULL };
    struct addrinfo* ptr { NULL };
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, port_.c_str(), &hints, &result);
    if(iResult != 0) {
        std::cerr << "[TCP Server]: getaddrinfo failed: " << iResult;
        WSACleanup();
        return;
    }

    listen_socket_ = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if(listen_socket_ == INVALID_SOCKET) {
        std::cerr << "[TCP Server]: Error at socket(): " << WSAGetLastError() << '\n';
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    iResult = bind(listen_socket_, result->ai_addr, (int) result->ai_addrlen);
    if(iResult == SOCKET_ERROR) {
        std::cerr << "[TCP Server]: Error at bind: " << WSAGetLastError() << '\n';
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    std::cout << "[TCP Server]: Bound to ???" /*<< result->ai_addr*/ << ':' << port_ << "'\n";
    freeaddrinfo(result);
}

void TCPServer::run() {
    int iResult;

    iResult = listen(listen_socket_, SOMAXCONN);
    if(iResult == SOCKET_ERROR) {
        std::cerr << "[TCP Server]: Error at listen: " << WSAGetLastError() << '\n';
        return;
    }

    is_running_ = true;

    while(is_running_) {
        SOCKET client_socket = INVALID_SOCKET;
        sockaddr client_addr;
        int client_addr_size{sizeof(client_addr)};
        char buffer[1024];
        int buff_len = 1024;

        client_socket = accept(listen_socket_, &client_addr, &client_addr_size);
        if(client_socket == INVALID_SOCKET) {
            std::cerr << "[TCP Server]: accept failed: " << WSAGetLastError() << '\n';
            continue;
        }

        do {
            iResult = recv(client_socket, buffer, buff_len, 0);
            if(iResult > 0) {
                ClientSocket cs;
                cs.sock = client_socket;
                on_receive_(cs, buffer, buff_len);
            }
        } while(iResult > 0);

        closesocket(client_socket);
    }
}

void ClientSocket::send_data(char* data, int len) {
    send(sock, data, len, 0);
}

void ClientSocket::send_data(const char* data, int len) {
    send(sock, data, len, 0);
}

void ClientSocket::close() {
    closesocket(sock);
}


}