cmake_minimum_required(VERSION 3.27)
project(client_server_pattern C)

set(CMAKE_C_STANDARD 17)

add_executable(client_server_pattern main.c
        ECGPkg.h
        ECG_Module.h
        ECG_Module.c
        TimeMarkedData.h
        TMDQueue.h
        TMDQueue.c
        TimeMarkedData.c
        HistogramDisplay.h
        HistogramDisplay.c
        TestBuilder.h
        TestBuilder.c
        QRSDetector.h
        QRSDetector.c
        WaveformDisplay.h
        WaveformDisplay.c)
