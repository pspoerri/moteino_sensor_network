# This configuration file outlines some of the ways Arduino CMake
# can be used. For a detailed explenation of all the options please
# reade README.rst.

set(CMAKE_TOOLCHAIN_FILE ../CMakeModules/ArduinoToolchain.cmake) # Arduino Toolchain

cmake_minimum_required(VERSION 2.8)

project(MoteinoSensorNetwork_Client C CXX)

print_board_list()
print_programmer_list()

set(NODEID "0x63" CACHE STRING "Moteino Network Node ID")
add_definitions(-DRFM_NODEID=${NODEID})


##
set(ARDUINO_DEFAULT_BOARD uno) 
set(ARDUINO_DEFAULT_PORT /dev/ttyUSB0)
##

set(LIBRARY_SRCS
    ../libraries/DHT22/DHT22.cpp
    ../libraries/RFM69/RFM69.cpp
    ../libraries/SPIFlash/SPIFlash.cpp
    ../libraries/Low-Power/LowPower.cpp
)
set(LIBRARY_HDRS
)
include_directories(
    ../libraries/DHT22/
    ../libraries/RFM69/
    ../libraries/SPIFlash/
    ../libraries/Low-Power/
    ../communication/)

set(CODE_SRCS
    src/main.cpp
    src/temperaturesensor.cpp
    ${LIBRARY_SRCS}
)

generate_arduino_firmware(MoteinoSensorNetwork
      SRCS  ${CODE_SRCS}
      HDRS  ${LIBRARY_HDRS}
      )
##
