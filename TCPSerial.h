//
// Created by 黄正跃 on 2017/10/24.
//

#ifndef RM_COMMUNICATION_TCPSERIAL_H
#define RM_COMMUNICATION_TCPSERIAL_H


#include <cstdint>
#include <cstddef>
#include <string>


class TCPSerial {

private:

    static const uint8_t START_UPPER_MONITOR_CTR = 0x00;
    static const uint8_t MOVETO = 0x01;
    static const uint8_t MOVEBY = 0x02;
    static const uint8_t START_FRICTION = 0x03;
    static const uint8_t STOP_FRICTION = 0x04;
    static const uint8_t START_SHOOTING = 0x05;
    static const uint8_t STOP_SHOOTING = 0x06;

    std::string ip;
    short port;
    int socket_fd;

public:

    TCPSerial() = delete;

    TCPSerial(std::string ip, short port, bool printFeedback);

    void startControlMode();

    void moveGimbalTo(int yaw, int pitch);

    void moveGimbalBy(int d_yaw, int d_pitch);

    void startFrictionWheel();

    void stopFrictionWheel();

    void startShooting();

    void stopShooting();

    void reset();

    ~TCPSerial();

private:

    void sendBytes(const uint8_t *buffer, size_t size);

    void sendByte(uint8_t byte);

    void sendBlankEightBytes();

    void sendHead();

    void sendTail();

};


#endif //RM_COMMUNICATION_TCPSERIAL_H
