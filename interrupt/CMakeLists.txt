cmake_minimum_required(VERSION 3.27)
project(untitled1 C)

set(CMAKE_C_STANDARD 17)

add_executable(untitled1 main.c
        ButtonHandler.c
        ButtonHandler.h
        Led.c
        Led.h
        RobotInterruptVectorTable.h
        MicrowaveEmitter.h
        Timer.h
        button.c
        ButtonDriver.c
        Timer.c
        MicrowaveEmitter.c)
