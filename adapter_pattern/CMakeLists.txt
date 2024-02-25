cmake_minimum_required(VERSION 3.27)
project(adapter_pattern C)

set(CMAKE_C_STANDARD 17)

add_executable(adapter_pattern main.c
        Acme02Adater.h
        Acme02SensorProxy.h
        i02Sensor.h
        Ultmate02SensorProxy.h
        Ultimate02Adapter.h
        GasMixer.h
        GasDisplay.h
        Acme02Adapter.c
        AcmeO2SensorProxy.c
        GasDisplay.c
        GasMixer.c
        UltimateO2Adapter.c
        UltimateO2SensorProxy.c)
