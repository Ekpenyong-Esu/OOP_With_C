cmake_minimum_required(VERSION 3.27)
project(Observer_pattern C)

set(CMAKE_C_STANDARD 17)

add_executable(Observer_pattern main.c
        ECGPkg.h
        ECG_Module.h
        HistogramDisplay.h
        NotificationHandle.h
        TMDQueue.h
        TimeMarkedData.h
        ECG_Module.c
        HistogramDisplay.c
        NotificationHandle.c
        TMDQueue.c
        TestBuilder.h
        TestBuilder.c
        TimeMarkedData.c)
