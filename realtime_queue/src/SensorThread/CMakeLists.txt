set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/SensorThread.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/SensorThread.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibSensorThread" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibSensorThread" PUBLIC ${LIBRARY_INCLUDES})

# Link required libraries
target_link_libraries("LibSensorThread" PUBLIC 
    LibGasSensorBase 
    LibO2Sensor 
    LibN2Sensor 
    LibHeSensor 
    LibGasDataQueue
    LibGasData)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibSensorThread"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibSensorThread"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibSensorThread")
endif()
