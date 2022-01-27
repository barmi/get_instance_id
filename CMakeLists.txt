cmake_minimum_required(VERSION 3.11)
project(getinstance C)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_C_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_C_FLAGS_RELEASE_INIT "-Wall")

include_directories(src)

add_executable(getinstance
        src/main.c
        src/xcloudutil.c
        src/xcloudutil.h
        )

