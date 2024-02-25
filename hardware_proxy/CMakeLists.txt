cmake_minimum_required(VERSION 3.27)
project(hardware_proxy C)

set(CMAKE_C_STANDARD 17)

add_executable(hardware_proxy main.c
        HWProxyExample.h
        MotorData.h
        MotorProxy.h
        MotorProxy.c)
