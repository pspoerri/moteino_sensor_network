# This configuration file outlines some of the ways Arduino CMake
# can be used. For a detailed explenation of all the options please
# reade README.rst.

set(CMAKE_TOOLCHAIN_FILE ../CMakeModules/ArduinoToolchain.cmake) # Arduino Toolchain

cmake_minimum_required(VERSION 2.8)

project(MoteinoSensorNetwork_Server C CXX)

#print_board_list()
#print_programmer_list()

set(ARDUINO_DEFAULT_BOARD uno)
set(ARDUINO_DEFAULT_PORT /dev/ttyUSB0)

set(LIBRARY_SRCS
    ../libraries/DHT22/DHT22.cpp
    ../libraries/RFM69/RFM69.cpp
    ../libraries/SPIFlash/SPIFlash.cpp
)
set(LIBRARY_HDRS
)
include_directories(../libraries/DHT22/ ../libraries/RFM69/ ../libraries/SPIFlash ../communication/)

set(CODE_SRCS
    src/main.cpp
    ${LIBRARY_SRCS}
)

generate_arduino_firmware(MoteinoSensorNetwork
      SRCS  ${CODE_SRCS}
      HDRS  ${LIBRARY_HDRS}
      )

