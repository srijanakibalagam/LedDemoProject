PROJECT(demo-led-status-indication)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
cmake_minimum_required(VERSION 2.8)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin)

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

add_executable(${BINARY_NAME} main.cc led.cc run_led.cc)
TARGET_LINK_LIBRARIES(${BINARY_NAME} ${CONAN_LIBS})


# Create the gcov target. Run coverage tests with 'make gcov'
add_custom_target(gcov
    COMMAND mkdir -p coverage
    COMMAND ${CMAKE_CURRENT_BINARY_DIR} main
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )

add_custom_command(TARGET gcov
    COMMAND echo "=================== GCOV ===================="
    COMMAND gcov -b ${CMAKE_CURRENT_BINARY_DIR}/*.cpp -o ${OBJECT_DIR}
    | grep -A 5 "main.cpp" > CoverageSummary.tmp
    COMMAND cat CoverageSummary.tmp
    COMMAND echo "-- Coverage files have been output to ${CMAKE_CURRENT_BINARY_DIR}/coverage"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/coverage
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
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

# Testing
enable_testing()

add_test(output_test ${CMAKE_CURRENT_BINARY_DIR}/${BINARY_NAME})
set_tests_properties(output_test PROPERTIES PASS_REGULAR_EXPRESSION "0;5;10")
