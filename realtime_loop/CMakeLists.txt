cmake_minimum_required(VERSION 3.27)
project(realtime_loop C)

set(CMAKE_C_STANDARD 17)

add_executable(realtime_loop main.c
        GasControlExecutive.c
        GasDisplayThread.c
        GasDisplayThread.h
        ShareData.c
        ShareData.h
        loop1.c
        loop2.c)
