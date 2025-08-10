cmake_minimum_required(VERSION 3.10)
project(DSA C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Option to enable coverage
option(ENABLE_COVERAGE "Enable coverage reporting" ON)

if(ENABLE_COVERAGE AND CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "Building with code coverage flags")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

# Include folder contain file .h
include_directories(include)

# Adll lib from src
file(GLOB_RECURSE SOURCES src/*.c)
add_library(dsa_lib ${SOURCES})

# Test turn on
enable_testing()
add_subdirectory(tests)

# Coverage target
if(ENABLE_COVERAGE)
    find_program(LCOV_PATH lcov)
    find_program(GENHTML_PATH genhtml)

    if(LCOV_PATH AND GENHTML_PATH)
        add_custom_target(coverage
            COMMAND ${LCOV_PATH} --directory . --capture --output-file coverage.info
            COMMAND ${LCOV_PATH} --remove coverage.info '/usr/*' '*/tests/*' --ignore-errors unused --output-file coverage.info
            COMMAND ${GENHTML_PATH} coverage.info --output-directory coverage_report
            COMMENT "Generating coverage report in coverage_report/index.html"
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    endif()
endif()

