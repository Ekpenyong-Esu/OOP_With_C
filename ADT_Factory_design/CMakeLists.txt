cmake_minimum_required(VERSION 3.27)
project(ADT_Factory_design C)

set(CMAKE_C_STANDARD 17)

add_executable(ADT_Factory_ design src/main.c
        src/factoryImplementation.c
        test/test_code.cpp
)
