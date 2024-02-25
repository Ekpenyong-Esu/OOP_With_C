cmake_minimum_required(VERSION 3.27)
project(OwnShipAttitude C)

set(CMAKE_C_STANDARD 17)

add_executable(OwnShipAttitude main.c
        AttitudeDataType.h
        AlarmManager.h
        OwnShipAttitude.h
        OwnShipAttitude.c)
