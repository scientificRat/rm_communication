cmake_minimum_required(VERSION 3.8)
project(rm_communication)
find_package( OpenCV REQUIRED )

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp TCPSerial.cpp TCPSerial.h HardwareController.cpp HardwareController.h Serial.h USBSerial.cpp USBSerial.h)
add_executable(rm_communication ${SOURCE_FILES})
target_link_libraries(rm_communication ${OpenCV_LIBS} )