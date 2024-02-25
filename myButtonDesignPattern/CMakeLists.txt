cmake_minimum_required(VERSION 3.27)
project(myButtonDesignPattern C)

set(CMAKE_C_STANDARD 17)

add_executable(myButtonDesignPattern main.c
        Button.c
        Button.h)
