cmake_minimum_required(VERSION 3.27)
project(mediatorC__)

set(CMAKE_CXX_STANDARD 17)

add_executable(mediatorC__ main.cpp
        motor.cpp
        motor.h
        robot_action.cpp
        robot_action.h
        robot_arm_manager.cpp
        robot_arm_manager.h
        rotating_motor.h
        sliding_motor.h)
