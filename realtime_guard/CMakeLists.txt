cmake_minimum_required(VERSION 3.27)
project(realtime_guard C)

set(CMAKE_C_STANDARD 17)

add_executable(realtime_guard main.c
        Attitude.c
        Attitude.h
        AtttudeController.c
        AtttudeController.h
        FlightDataDisplay.c
        FlightDataDisplay.h
        KinematicData.c
        KinematicData.h
        Navigator.c
        Navigator.h
        Position.c
        Position.h
        GuardedCallExample.h)
