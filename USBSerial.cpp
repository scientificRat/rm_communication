//
// Created by scientificrat on 18-1-20.
//

#include "USBSerial.h"
#include <fcntl.h>      // File control definitions
#include <unistd.h>
#include <termios.h>    // POSIX terminal control definitionss

USBSerial::USBSerial(std::string dev_name) {
    this->fd = open(dev_name.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if(this->fd == -1){
        fprintf(stderr,"open_port: Unable to open %s. \n",dev_name.c_str());
        exit(0);
    }
    fcntl(this->fd, F_SETFL, 0);
    termios port_settings{0};                   // structure to store the port settings in
    cfsetispeed(&port_settings, B115200);       // set baud rates
    cfsetospeed(&port_settings, B115200);
    port_settings.c_cflag &= ~PARENB;           // set no parity, stop bits, data bits
    port_settings.c_cflag &= ~CSTOPB;
    port_settings.c_cflag &= ~CSIZE;
    port_settings.c_cflag |= CS8;
    // apply the settings to the port
    tcsetattr(this->fd, TCSANOW, &port_settings);
}

void USBSerial::sendBytes(const uint8_t *buffer, size_t size) {
    if(write(fd, buffer, size)!=size){
        fprintf(stderr,"serial send failed!");
    }
}

