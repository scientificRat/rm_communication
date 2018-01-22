//
// Created by scientificrat on 18-1-20.
//

#ifndef RM_COMMUNICATION_USBSERIAL_H
#define RM_COMMUNICATION_USBSERIAL_H


#include "Serial.h"
#include <iostream>

class USBSerial: public Serial {
private:
    int fd; // file description for the serial port
public:
    explicit USBSerial(std::string dev_name);

    void sendBytes(const uint8_t *buffer, size_t size) override;



};


#endif //RM_COMMUNICATION_USBSERIAL_H
