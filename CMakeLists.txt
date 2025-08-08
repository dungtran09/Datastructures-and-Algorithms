cmake_minimum_required(VERSION 3.10)
project(DSA C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Include folder contain file .h
include_directories(include)

# Adll lib from src
file(GLOB_RECURSE SOURCES src/*.c)
add_library(dsa_lib ${SOURCES})

# Test turn on
enable_testing()
add_subdirectory(tests)
