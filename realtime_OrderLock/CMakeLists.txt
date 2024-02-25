cmake_minimum_required(VERSION 3.27)
project(realtime_OrderLock C)

set(CMAKE_C_STANDARD 17)

add_executable(realtime_OrderLock main.c
        ResourceList.c
        ResourceList.h
        Velocity.c
        Velocity.h
        VelocitySensor.c
        VelocitySensor.h)
