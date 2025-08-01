set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/N2Sensor.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/N2Sensor.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibN2Sensor" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibN2Sensor" PUBLIC ${LIBRARY_INCLUDES})

# Link with LibGasSensorBase
target_link_libraries("LibN2Sensor" PUBLIC LibGasSensorBase)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibN2Sensor"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibN2Sensor"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibN2Sensor")
endif()
