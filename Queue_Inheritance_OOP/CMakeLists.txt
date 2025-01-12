cmake_minimum_required(VERSION 3.27)
project(Queue C)

set(CMAKE_C_STANDARD 17)

add_executable(Queue
        Queue.h
        Queue.c
        QueueTest.c
        CachedQueue.c
        CachedQueue.h
        main.c
)
