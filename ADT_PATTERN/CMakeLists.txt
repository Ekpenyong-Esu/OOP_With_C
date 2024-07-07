cmake_minimum_required(VERSION 3.26)

project(ADT_PATTERN)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Include directories
include_directories(include)

# Add main application executable
add_executable(main src/main.c src/factoryImplementation.c)

# Add test executable
add_executable(test_task test/test_code.cpp)

target_link_libraries(
        test_task
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_task)
