cmake_minimum_required(VERSION 3.27)
project(SmartData C)

set(CMAKE_C_STANDARD 17)

add_executable(SmartData main.c
        SmartColor.h
        Smartint.h
        SmartDataExample.h
        PatientDataClass.c
        SmartColor.c)
