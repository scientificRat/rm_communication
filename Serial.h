//
// Created by 黄正跃 on 2017/10/25.
//

#ifndef RM_COMMUNICATION_SERIAL_H
#define RM_COMMUNICATION_SERIAL_H


#include <cstdint>
#include <cstddef>

// abstract class
class Serial {

public:

    virtual void sendBytes(const uint8_t *buffer, size_t size) = 0;

    virtual ~Serial() = default;

};


#endif //RM_COMMUNICATION_SERIAL_H
