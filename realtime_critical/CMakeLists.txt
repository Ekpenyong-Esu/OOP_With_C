cmake_minimum_required(VERSION 3.27)
project(realtime_critical C)

set(CMAKE_C_STANDARD 17)

add_executable(realtime_critical main.c
        CRDisplay.c
        CRRobotArmManager.c
        CRRobotArmManager.h
        RobotArm.h
        UserIput.h)
