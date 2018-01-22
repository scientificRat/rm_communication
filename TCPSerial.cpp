//
// Created by 黄正跃 on 2017/10/24.
//

#include <exception>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "TCPSerial.h"

TCPSerial::TCPSerial(std::string ip, short port, bool printFeedback = false) {

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        throw std::runtime_error("create socket error");
    }
    sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    // IPv4
    server_addr.sin_family = AF_INET;
    // port to connect
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) < 0) {
        throw std::runtime_error("ip format invalid");
    }

    printf("[INFO] start connecting to '%s' at port %d ....\n", ip.c_str(), port);


    if (connect(socket_fd, (sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        throw std::runtime_error(std::string("connect error: ") + strerror(errno));
    }

    printf("[INFO] connected\n\n");

    // 打印回显
    if (printFeedback) {
        new std::thread([&]() {
            ssize_t n = -1;
            uint8_t buffer[1024];
            while ((n = recv(socket_fd, buffer, 1024, 0)) >= 0) {
                buffer[n] = '\0';
                fprintf(stderr, "%s", buffer);
            }
            throw std::runtime_error(std::string("recv error") + strerror(errno));
        });
    }

}

inline void TCPSerial::sendBytes(const uint8_t *buffer, size_t size) {
    if (send(socket_fd, buffer, size, 0) < 0) {
        throw std::runtime_error(std::string("send error") + strerror(errno));
    }
}


TCPSerial::~TCPSerial() {
    close(socket_fd);
}


