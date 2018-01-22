//
// Created by 黄正跃 on 2017/10/24.
//

#ifndef RM_COMMUNICATION_TCPSERIAL_H
#define RM_COMMUNICATION_TCPSERIAL_H


#include "Serial.h"


class TCPSerial : public Serial {

private:
    // socket file descriptor
    int socket_fd;

public:

    TCPSerial() = delete;

    TCPSerial(std::string ip, short port, bool printFeedback);

    void sendBytes(const uint8_t *buffer, size_t size) override;

    ~TCPSerial() override;

};

#endif //RM_COMMUNICATION_TCPSERIAL_H
