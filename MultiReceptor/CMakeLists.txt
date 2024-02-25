cmake_minimum_required(VERSION 3.27)
project(MultiReceptor C)

set(CMAKE_C_STANDARD 17)

add_executable(MultiReceptor main.c
        MultiReceptor.c
        MultiReceptor.h)
