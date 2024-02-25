cmake_minimum_required(VERSION 3.27)
project(untitled C)

set(CMAKE_C_STANDARD 17)

add_executable(untitled main.c
        DisplayClient.c
        DisplayClient.h
        GasData.c
        GasData.h
        GasNotificationHandle.c
        GasNotificationHandle.h
        GasSensor.c
        GasSensor.h
        SafetyMonitorClient.c)
