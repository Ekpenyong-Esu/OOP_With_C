cmake_minimum_required(VERSION 3.27)
project(StatePattern C)

set(CMAKE_C_STANDARD 17)

add_executable(StatePattern main.c
        Context.c
        Context.h
        GN_ProcessingFractionState.c
        GN_ProcessingFractionState.h
        GN_ProcessingWholeState.c
        GN_ProcessingWholeState.h
        NoNumberState.c
        NoNumberState.h
        StateActionSet.c
        StateActionSet.h
        SPClient.h
        StatePattern.h
        StatePatternBuilder.h)
