cmake_minimum_required(VERSION 3.27)
project(poll C)

set(CMAKE_C_STANDARD 17)

add_executable(poll main.c
        BCPeriodicPoller.c
        BCPeriodicPoller.h
        BCTimer.c
        BCTimer.h
        BreathingCircuitSensor.c
        BreathingCircuitSensor.h
        MedicalDisplay.c
        MedicalDisplay.h)
