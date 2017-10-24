#include <iostream>
#include "TCPSerial.h"

int main() {
    std::cout << "Communication test" << std::endl;
    TCPSerial tcpSerial("192.168.4.1", 9000, true);
    tcpSerial.startControlMode();
    while (true) {

    }
    return 0;
}