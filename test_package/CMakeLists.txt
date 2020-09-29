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
    COMMAND ${CMAKE_BINARY_DIR} main
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

add_custom_command(TARGET gcov
    COMMAND echo "=================== GCOV ===================="
    COMMAND gcov -b ${CMAKE_BINARY_DIR}/*.cpp -o ${OBJECT_DIR}
    | grep -A 5 "main.cpp" > CoverageSummary.tmp
    COMMAND cat CoverageSummary.tmp
    COMMAND echo "-- Coverage files have been output to ${CMAKE_CURRENT_BINARY_DIR}/coverage"
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

add_test(output_test ${CMAKE_BINARY_DIR}/${BINARY_NAME})
set_tests_properties(output_test PROPERTIES PASS_REGULAR_EXPRESSION "0;5;10")