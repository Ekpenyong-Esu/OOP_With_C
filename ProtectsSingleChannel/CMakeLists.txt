cmake_minimum_required(VERSION 3.27)
project(ProtectsSingleChannel C)

set(CMAKE_C_STANDARD 17)

add_executable(ProtectsSingleChannel main.c
        CheckTemperature.h
        FurnaceController.h
        Thermometer.h
        Thermostat.h
        Thermometer.c
        Thermostat.c
        CheckTemperature.c)
