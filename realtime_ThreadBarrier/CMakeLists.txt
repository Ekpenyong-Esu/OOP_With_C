cmake_minimum_required(VERSION 3.27)
project(realtime_ThreadBarrier C)

set(CMAKE_C_STANDARD 17)

add_executable(realtime_ThreadBarrier main.c
        ThreadBarrier.c
        ThreadBarrier.h)
