cmake_minimum_required(VERSION 3.13)  # CMake version check
project(getinstance)                  # Create project "simple_example"
#set(CMAKE_C_STANDARD 11)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES
        src/getinstance.c
        src/getinstance.h
        src/main.c)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(getinstance ${SOURCE_FILES})
