cmake_minimum_required(VERSION 3.8)
project(rm_communication)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp TCPSerial.cpp TCPSerial.h)
add_executable(rm_communication ${SOURCE_FILES})