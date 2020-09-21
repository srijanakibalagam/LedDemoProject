CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
PROJECT(swf-raspi-tutorial)

INCLUDE(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

# Set the compiler options
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

CONAN_BASIC_SETUP()

# Create OBJECT_DIR variable
set(OBJECT_DIR ${CMAKE_BINARY_DIR})
message("-- Object files will be output to: ${OBJECT_DIR}")

file(GLOB SRCS *.cpp)

SET(BINARY_NAME "${CMAKE_PROJECT_NAME}.${CONAN_SETTINGS_OS}.${CONAN_SETTINGS_ARCH}")

ADD_EXECUTABLE(${BINARY_NAME}-test test_runner.cc source_test.cc ../src/run_led.cc)

TARGET_LINK_LIBRARIES(${BINARY_NAME}-test ${CONAN_LIBS} pthread)

# Create the gcov target. Run coverage tests with 'make gcov'
add_custom_target(gcov
    COMMAND mkdir -p coverage
    COMMAND ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

add_custom_command(TARGET gcov
    COMMAND echo "=================== GCOV ===================="
    COMMAND gcov -b ${CMAKE_SOURCE_DIR}/*.cpp -o ${OBJECT_DIR}
    | grep -A 5 "main.cpp" > CoverageSummary.tmp
    COMMAND cat CoverageSummary.tmp
    COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/coverage"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
    )


add_dependencies(gcov gtestbin)
# Make sure to clean up the coverage folder
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES coverage)

# Create the gcov-clean target. This cleans the build as well as generated 
# .gcda and .gcno files.
add_custom_target(scrub
COMMAND ${CMAKE_MAKE_PROGRAM} clean
COMMAND rm -f ${OBJECT_DIR}/*.gcno
COMMAND rm -f ${OBJECT_DIR}/*.gcda
WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Testing
enable_testing()

add_test(output_test ${CMAKE_CURRENT_BINARY_DIR}/gtestbin)
set_tests_properties(output_test PROPERTIES PASS_REGULAR_EXPRESSION "0;5;10")
