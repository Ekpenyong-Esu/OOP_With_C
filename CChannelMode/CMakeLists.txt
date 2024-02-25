cmake_minimum_required(VERSION 3.27)
project(CChannelMode C)

set(CMAKE_C_STANDARD 17)

add_executable(CChannelMode main.c
        CalculateColor.h
        EMGChannel.h
        EMGSensorDeviceDriver.h
        MovingAverageFilter.h
        ConvertToFrequency.h
        EMGChannel.c)
