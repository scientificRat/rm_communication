//
// Created by 黄正跃 on 2017/10/24.
//


#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <exception>
#include <arpa/inet.h>
#include <thread>
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


TCPSerial::~TCPSerial() {
    close(socket_fd);
}

void TCPSerial::startControlMode() {
    sendHead();
    sendByte(START_UPPER_MONITOR_CTR);
    sendBlankEightBytes();
    sendTail();
}


void TCPSerial::moveGimbalTo(int yaw, int pitch) {
    sendHead();
    sendByte(MOVETO);
    sendBytes((uint8_t *) &yaw, 4);
    sendBytes((uint8_t *) &pitch, 4);
    sendTail();
}

void TCPSerial::moveGimbalBy(int d_yaw, int d_pitch) {
    sendHead();
    sendByte(MOVEBY);
    sendBytes((uint8_t *) &d_yaw, 4);
    sendBytes((uint8_t *) &d_pitch, 4);
    sendTail();
}

void TCPSerial::startFrictionWheel() {
    sendHead();
    sendByte(START_FRICTION);
    sendBlankEightBytes();
    sendTail();
}

void TCPSerial::stopFrictionWheel() {
    sendHead();
    sendByte(STOP_FRICTION);
    sendBlankEightBytes();
    sendTail();
}

void TCPSerial::startShooting() {
    sendHead();
    sendByte(START_SHOOTING);
    sendBlankEightBytes();
    sendTail();
}

void TCPSerial::stopShooting() {
    sendHead();
    sendByte(STOP_SHOOTING);
    sendBlankEightBytes();
    sendTail();
}

void TCPSerial::reset() {
    stopShooting();
    stopFrictionWheel();
    moveGimbalTo(0, 0);
}

inline void TCPSerial::sendBytes(const uint8_t *buffer, size_t size) {
    if (send(socket_fd, buffer, size, 0) < 0) {
        throw std::runtime_error(std::string("send error") + strerror(errno));
    }
}

inline void TCPSerial::sendByte(uint8_t byte) {
    if (send(socket_fd, &byte, 1, 0) < 0) {
        throw std::runtime_error(std::string("send error") + strerror(errno));
    }
}

void TCPSerial::sendBlankEightBytes() {
    static uint8_t bytes[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    sendBytes(bytes, 8);
}

void TCPSerial::sendHead() {
    static uint8_t head[2] = {0x0a, 0x0d};
    sendBytes(head, 2);
}

void TCPSerial::sendTail() {
    static uint8_t tail[2] = {0x0d, 0x0a};
    sendBytes(tail, 2);
}
