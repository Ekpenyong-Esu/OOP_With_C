set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/O2Sensor.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/O2Sensor.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibO2Sensor" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibO2Sensor" PUBLIC ${LIBRARY_INCLUDES})

# Link the LibGasSensorBase library
target_link_libraries("LibO2Sensor" PUBLIC LibGasSensorBase)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibO2Sensor"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibO2Sensor"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibO2Sensor")
endif()
