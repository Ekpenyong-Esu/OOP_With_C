cmake_minimum_required(VERSION 3.27)
project(Sensor C)

set(CMAKE_C_STANDARD 17)

add_executable(main main.c Sensor.c Sensor.h)

