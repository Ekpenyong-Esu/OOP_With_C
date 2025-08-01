set(APP_SOURCES "main.c")

add_executable(${APP_NAME} ${APP_SOURCES})

target_include_directories(${APP_NAME} PUBLIC 
    "${CMAKE_BINARY_DIR}/configured_files/include"
    "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(${APP_NAME} PUBLIC 
    LibGasController
    LibGasData
    LibGasDataQueue
    LibGasDisplay
    LibGasSensorBase
    LibHeSensor
    LibN2Sensor
    LibO2Sensor
    LibSensorThread)

# Link with FreeRTOS if available
find_package(FreeRTOS)
if(FreeRTOS_FOUND)
    target_link_libraries(${APP_NAME} PUBLIC FreeRTOS)
endif()

if(${ENABLE_WARNINGS})
    target_set_warnings(TARGET ${APP_NAME} ENABLE ${ENABLE_WARNINGS} AS_ERRORS ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(TARGET ${APP_NAME} ENABLE ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target(${APP_NAME})
endif()
