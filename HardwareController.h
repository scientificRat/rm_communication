//
// Created by 黄正跃 on 2017/10/25.
//

#ifndef RM_COMMUNICATION_HARDWARECONNECTOR_H
#define RM_COMMUNICATION_HARDWARECONNECTOR_H

#include "Serial.h"

class HardwareController {

private:
    // constants
    static const uint8_t START_UPPER_MONITOR_CTR = 0x00;
    static const uint8_t GIMBAL_MOVETO = 0x01;
    static const uint8_t GIMBAL_MOVEBY = 0x02;
    static const uint8_t GIMBAL_STOP = 0x03;
    static const uint8_t START_FRICTION = 0x04;
    static const uint8_t STOP_FRICTION = 0x05;
    static const uint8_t START_SHOOTING = 0x06;
    static const uint8_t STOP_SHOOTING = 0x07;
    static const uint8_t REQUEST_CURR_STATE = 0x08;
    Serial* serial;


public:

    explicit HardwareController(Serial* s) : serial(s) {}

    HardwareController() = delete;

    void startControlMode();

    void moveGimbalTo(int16_t yaw, int16_t pitch);

    void moveGimbalBy(int16_t d_yaw, int16_t d_pitch);

    void stopGimble();

    void startFrictionWheel();

    void stopFrictionWheel();

    void startShooting();

    void stopShooting();

    void requestCurrentState();

    void reset();

private:

    void sendBytes(const uint8_t *buffer, size_t size);

    void sendByte(uint8_t byte);

    void sendBlankFourBytes();

    void sendHead();

    void sendTail();
};


#endif //RM_COMMUNICATION_HARDWARECONNECTOR_H
