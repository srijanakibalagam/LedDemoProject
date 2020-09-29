CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

PROJECT(swf-raspi-tutorial)

INCLUDE(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
CONAN_BASIC_SETUP()

SET(BINARY_NAME "${CMAKE_PROJECT_NAME}.${CONAN_SETTINGS_OS}.${CONAN_SETTINGS_ARCH}")

ADD_EXECUTABLE(${BINARY_NAME}-test test_runner.cc source_test.cc ../src/run_led.cc)

TARGET_LINK_LIBRARIES(${BINARY_NAME}-test ${CONAN_LIBS} pthread)

# Create the gcov target. Run coverage tests with 'make gcov'
add_custom_target(gcov
    COMMAND mkdir -p coverage
    COMMAND ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )