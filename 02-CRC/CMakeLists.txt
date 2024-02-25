cmake_minimum_required(VERSION 3.27)
project(02_CRC C)

set(CMAKE_C_STANDARD 17)

add_executable(02_CRC main.c
        AlarmManager.h
        CRCExample.h
        PatientData.h
        CRCCalculator.c
        PatientData.c)
