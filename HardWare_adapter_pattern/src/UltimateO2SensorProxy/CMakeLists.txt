set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Ultimate02SensorProxy.c")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Ultimate02SensorProxy.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("LibUltimateO2SensorProxy" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("LibUltimateO2SensorProxy" PUBLIC ${LIBRARY_INCLUDES})

# Link the LibECGPkg library to the LibArrhythmiaDetector library
# target_link_libraries("LibUltimateO2SensorProxy" PUBLIC e)


if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "LibUltimateO2SensorProxy"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "LibUltimateO2SensorProxy"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("LibUltimateO2SensorProxy")
endif()
