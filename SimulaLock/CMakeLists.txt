cmake_minimum_required(VERSION 3.27)
project(SimulaLock C)

set(CMAKE_C_STANDARD 17)

add_executable(SimulaLock main.c
        DopplerSpeedSensor.c
        DopplerSpeedSensor.h
        GPSPositionSensor.c
        GPSPositionSensor.h
        OpticalSpeedSensor.c
        OpticalSpeedSensor.h
        SensorMaster.c
        SensorMaster.h)
