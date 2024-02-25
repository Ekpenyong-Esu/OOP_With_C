cmake_minimum_required(VERSION 3.27)
project(Adapter2 C)

set(CMAKE_C_STANDARD 17)

add_executable(Adapter2 main.c
        display_client.c
        display_client.h
        gas_data.h
        gas_mixer_client.c
        gas_mixer_client.h
        gas_sensor.c
        gas_sensor.h)
