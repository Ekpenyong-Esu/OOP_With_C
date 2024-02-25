cmake_minimum_required(VERSION 3.27)
project(mediator C)

set(CMAKE_C_STANDARD 17)

add_executable(mediator main.c
        robot_action.h
        robot_arm_manager.h
        rotating_joint.h
        sliding_joint.c
        sliding_joint.h
        rotating_joint.c
        robot_arm_manager.c)
