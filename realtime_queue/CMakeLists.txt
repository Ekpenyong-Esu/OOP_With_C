cmake_minimum_required(VERSION 3.27)
project(realtime_queue C)

set(CMAKE_C_STANDARD 17)

add_executable(realtime_queue main.c
        GasContoller.c
        GasContoller.h
        GasData.c
        GasData.h
        GasDataQueue.c
        GasDataQueue.h
        GasDisplay.c
        GasDisplay.h
        HeSensor.c
        HeSensor.h
        N2Sensor.c
        N2Sensor.h
        O2Sensor.c
        O2Sensor.h
        QueuingExample.h
        SensorThread.c
        SensorThread.h)
