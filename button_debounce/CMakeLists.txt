cmake_minimum_required(VERSION 3.27)
project(button_debounce C)

set(CMAKE_C_STANDARD 17)

add_executable(button_debounce main.c
        button.c
        button.h
        ButtonDriver.c
        ButtonDriver.h
        MicrowaveEmitter.c
        MicrowaveEmitter.h
        Timer.c
        Timer.h)
