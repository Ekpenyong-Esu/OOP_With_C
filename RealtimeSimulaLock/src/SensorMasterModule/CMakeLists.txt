set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/SensorMaster.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/SensorMaster.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibSensorMaster" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibSensorMaster" PUBLIC ${LIBRARY_INCLUDES})

# Link dependencies
target_link_libraries("LibSensorMaster" PUBLIC LibOpticalSpeedSensor)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibSensorMaster"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibSensorMaster"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibSensorMaster")
endif()e files
add_library(SensorMaster
    SensorMaster.c
)

# Add header files
target_include_directories(SensorMaster PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link dependencies
target_link_libraries(SensorMaster PUBLIC
    OpticalSpeedSensor
)
