cmake_minimum_required(VERSION 3.27)
project(Led_design_pattern C)

set(CMAKE_C_STANDARD 17)

add_executable(Led_design_pattern main.c
        led_stm.c)
