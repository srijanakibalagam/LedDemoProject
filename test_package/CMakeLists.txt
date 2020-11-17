CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

PROJECT(swf-raspi-tutorial)

INCLUDE(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
CONAN_BASIC_SETUP()
# Appending the CXX_Flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fprofile-arcs -ftest-coverage -fpermissive")
SET(BINARY_NAME "${CMAKE_PROJECT_NAME}.${CONAN_SETTINGS_OS}.${CONAN_SETTINGS_ARCH}")

ADD_EXECUTABLE(${BINARY_NAME}-test test_runner.cc source_test.cc ../src/run_led.cc)

TARGET_LINK_LIBRARIES(${BINARY_NAME}-test ${CONAN_LIBS} pthread)
