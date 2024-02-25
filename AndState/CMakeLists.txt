cmake_minimum_required(VERSION 3.27)
project(AndState C)

set(CMAKE_C_STANDARD 17)

add_executable(AndState main.c
        AndStateList.c
        AndStateList.h
        DecompBuilder.h
        DecompClient.h
        ErrorState.c
        ErrorStateClass.h
        Klaxon.h
        Light.h
        LightController.c
        LightController.h
        LightPkg.h
        ModeStateClass.c
        ModeStateClass.h
        StateActionSet.c
        StateActionSet.h)
