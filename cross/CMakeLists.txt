cmake_minimum_required (VERSION 2.6)


SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)


SET(CMAKE_C_COMPILER   /usr/bin/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabihf-g++)
SET(CMAKE_FIND_ROOT_PATH /usr/arm-linux-gnueabihf)

PROJECT(demo-led-status-indication)

add_executable(demo-led-status-indication-arm ../src/main.cc ../src/led.cc )

