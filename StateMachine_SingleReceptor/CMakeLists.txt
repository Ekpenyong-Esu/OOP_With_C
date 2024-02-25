cmake_minimum_required(VERSION 3.27)
project(StateMachine_SingleReceptor_ C)

set(CMAKE_C_STANDARD 17)

add_executable(StateMachine_SingleReceptor_ main.c
        TSREventQueue.c
        TSREventQueue.h
        TSRSyncSingleReceptor.c
        TSRSyncSingleReceptor.h
        TokenizeAsyncSinglepkg.h)
