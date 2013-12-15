# This configuration file outlines some of the ways Arduino CMake
# can be used. For a detailed explenation of all the options please
# reade README.rst.

set(CMAKE_TOOLCHAIN_FILE ../CMakeModules/ArduinoToolchain.cmake) # Arduino Toolchain

cmake_minimum_required(VERSION 2.8)

project(MoteinoSensorNetwork C CXX)

print_board_list()
print_programmer_list()


##
set(ARDUINO_DEFAULT_BOARD uno) 
set(ARDUINO_DEFAULT_PORT /dev/tty.usbserial-AM01QG4M)
##
generate_arduino_firmware(MoteinoSensorNetwork
      SRCS  src/main.c
#      HDRS  src/test.h
      BOARD uno)
##
