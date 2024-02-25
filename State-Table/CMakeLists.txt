cmake_minimum_required(VERSION 3.27)
project(State_Table C)

set(CMAKE_C_STANDARD 17)

add_executable(State_Table main.c
        TokenizerStateTable.c
        TokenizerStateTable.h
        StateTablePattern.h)
