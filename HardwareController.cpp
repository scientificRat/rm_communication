//
// Created by 黄正跃 on 2017/10/25.
//

#include "HardwareController.h"


void HardwareController::startControlMode() {
    sendHead();
    sendByte(START_UPPER_MONITOR_CTR);
    sendBlankFourBytes();
    sendTail();
}


void HardwareController::moveGimbalTo(int16_t yaw, int16_t pitch) {
    sendHead();
    sendByte(GIMBAL_MOVETO);
    sendBytes((uint8_t *) &yaw, 2);
    sendBytes((uint8_t *) &pitch, 2);
    sendTail();
}

void HardwareController::moveGimbalBy(int16_t d_yaw, int16_t d_pitch) {
    sendHead();
    sendByte(GIMBAL_MOVEBY);
    sendBytes((uint8_t *) &d_yaw, 2);
    sendBytes((uint8_t *) &d_pitch, 2);
    sendTail();
}

void HardwareController::stopGimble() {
    sendHead();
    sendByte(GIMBAL_STOP);
    sendBlankFourBytes();
    sendTail();
}


void HardwareController::startFrictionWheel() {
    sendHead();
    sendByte(START_FRICTION);
    sendBlankFourBytes();
    sendTail();
}

void HardwareController::stopFrictionWheel() {
    sendHead();
    sendByte(STOP_FRICTION);
    sendBlankFourBytes();
    sendTail();
}

void HardwareController::startShooting() {
    sendHead();
    sendByte(START_SHOOTING);
    sendBlankFourBytes();
    sendTail();
}

void HardwareController::stopShooting() {
    sendHead();
    sendByte(STOP_SHOOTING);
    sendBlankFourBytes();
    sendTail();
}

/**
 * [仅限调试使用,需要设置printFeedback]
 * 本函数无返回值，单片机接收到请求命令后会尽快打印
 */
void HardwareController::requestCurrentState() {
    sendHead();
    sendByte(REQUEST_CURR_STATE);
    sendBlankFourBytes();
    sendTail();
}

void HardwareController::reset() {
    stopShooting();
    stopFrictionWheel();
    moveGimbalTo(0, 0);
}

inline void HardwareController::sendBytes(const uint8_t *buffer, size_t size) {
    this->serial->sendBytes(buffer, size);
}

inline void HardwareController::sendByte(uint8_t byte) {
    this->serial->sendBytes(&byte,1);
}

void HardwareController::sendBlankFourBytes() {
    static uint8_t bytes[4] = {0x00, 0x00, 0x00, 0x00};
    sendBytes(bytes, 4);
}

void HardwareController::sendHead() {
    static uint8_t head[2] = {0x0a, 0x0d};
    sendBytes(head, 2);
}

void HardwareController::sendTail() {
    static uint8_t tail[2] = {0x0d, 0x0a};
    sendBytes(tail, 2);
}


