cmake_minimum_required(VERSION 3.27)
project(realtime_staticPriority C)

set(CMAKE_C_STANDARD 17)

add_executable(realtime_staticPriority main.c
        MotorController.c
        MotorController.h
        MotorData.c
        MotorData.h
        MotorDisplay.c
        MotorDisplay.h
        MotorPositionSensor.c
        MotorPositionSensor.h)
